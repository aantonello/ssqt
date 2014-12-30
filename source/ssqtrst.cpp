/**
 * @file
 * Defines the SSRecordset class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 15, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqtshrd.hpp"
#include "ssqtfld.hpp"
#include "ssqtrec.hpp"
#include "ssqtrst.hpp"
#include "sql/dataset.hpp"

/* ===========================================================================
 * SSRecordset class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Constructors & Destructor
 * ------------------------------------------------------------------------ */

// SSRecordset::SSRecordset(const SSRecordset &rst);/*{{{*/
SSRecordset::SSRecordset(const SSRecordset &rst) : m_db(rst.m_db),
    m_prefix(rst.m_prefix), m_table(rst.m_table), m_data(NULL),
    m_current(rst.m_current), m_index(rst.m_index), m_style(rst.m_style)
{
    m_data = ((rst.m_data) ? rst.m_data->retain() : NULL);

    /* If the original recordset is in an add new state, don't copy its
     * current record. Instead position this recordset at the last record in
     * the dataset list.
     */
    if ((rst.m_index < 0) && (rst.m_current != NULL))
    {
        m_index = ((int)m_data->rowsCount() - 1);
        m_current = m_data->rowAt(m_index);
    }
    /* If the original recordset is in edit mode don't copy its current
     * record. Grab one from the dataset instead.
     */
    else if ((rst.m_current != NULL) && (rst.m_current->locked()))
        m_current = m_data->rowAt(m_index);
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Opening and Closing a Recordset
 * ------------------------------------------------------------------------ */

// error_t SSRecordset::open();/*{{{*/
error_t SSRecordset::open()
{
    if (!m_data) return SSE_INVAL;

    error_t result = m_data->exec();
    if (result != SSNO_ERROR)
        return result;

    moveNext();
    return SSNO_ERROR;
}
/*}}}*/
// error_t SSRecordset::open(const QString &query);/*{{{*/
error_t SSRecordset::open(const QString &query)
{
    if (query.isEmpty()) return SSE_INVAL;
    close();

    if (!query.startsWith("SELECT"))
    {
        m_table = query;
        query = QString("SELECT * FROM %1").arg(query);
    }

    m_data = new ss::dataset(database());
    if (!m_data) return SSE_NOMEM;

    error_t errNo;
    if ((errNo = m_data->exec(query)) != SSNO_ERROR)
    {
        close();
        return errNo;
    }
    moveNext();
    return SSNO_ERROR;
}
/*}}}*/
// error_t SSRecordset::open(const QString &table, const QString &fields = QString("*"), const QString &where = QString());/*{{{*/
error_t SSRecordset::open(const QString &table, const QString &fields, const QString &where)
{
    if (table.isEmpty()) return SSE_INVAL;

    QString stmt("SELECT");

    if (fields.isEmpty())
        stmt.append(" * ");
    else
        stmt.append(QString(" %1 ").arg(fields));

    stmt.append(QString("FROM %1").arg(table));

    if (!where.isEmpty())
        stmt.append(QString(" WHERE %1").arg(where));

    /* Holds the table information. */
    m_table = table;

    return open(stmt);
}
/*}}}*/
// bool SSRecordset::compile(const QString &query);/*{{{*/
bool SSRecordset::compile(const QString &query)
{
    if (query.isEmpty()) return false;
    close();

    m_data = new ss::dataset(database());
    if (!m_data) return SSE_NOMEM;

    if (m_data->compile(query) != SSNO_ERROR)
    {
        close();
    }
    return (m_data != NULL);
}
/*}}}*/
// SSRecordset& SSRecordset::bind(uint paramPos, const QVariant &paramVal);/*{{{*/
SSRecordset& SSRecordset::bind(uint paramPos, const QVariant &paramVal)
{
    if (m_data) m_data->bind(paramPos, paramVal);
    return *this;
}
/*}}}*/
// SSRecordset& SSRecordset::bind(const QString &paramName, const QVariant &paramVal);/*{{{*/
SSRecordset& SSRecordset::bind(const QString &paramName, const QVariant &paramVal)
{
    if (m_data) m_data->bind(paramName, paramVal);
    return *this;
}
/*}}}*/
// SSRecordset& SSRecordset::bind(const QVariant &paramVal);/*{{{*/
SSRecordset& SSRecordset::bind(const QVariant &paramVal)
{
    if (m_data) m_data->bind(paramVal);
    return *this;
}
/*}}}*/
// void SSRecordset::close();/*{{{*/
void SSRecordset::close()
{
    cancel();

    if (m_data) m_data->release();
    m_data = NULL;
    m_index  = -1;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Current Record Changing
 * ------------------------------------------------------------------------ */

// bool SSRecordset::moveFirst();/*{{{*/
bool SSRecordset::moveFirst()
{
    if ((m_style == SS_RECORDSET_FORWARDONLY) || (m_data == NULL) ||
        ((m_index < 0) && (m_current != NULL)) ||
        ((m_current != NULL) && m_current->locked()) ||
        (m_index == 0))
        return false;

    m_index = 0;
    m_current = m_data->rowAt(m_index);
    return (m_current != NULL);
}
/*}}}*/
// bool SSRecordset::movePrev();/*{{{*/
bool SSRecordset::movePrev()
{
    if ((m_style == SS_RECORDSET_FORWARDONLY) || (m_data == NULL) ||
        ((m_index < 0) && (m_current != NULL)) ||
        ((m_current != NULL) && m_current->locked()) ||
        (m_index == 0))
        return false;

    --m_index;
    m_current = m_data->rowAt(m_index);
    return (m_current != NULL);
}
/*}}}*/
// bool SSRecordset::moveNext();/*{{{*/
bool SSRecordset::moveNext()
{
    if ((m_data == NULL) ||
        ((m_index < 0) && (m_current != NULL)) ||
        ((m_current != NULL) && m_current->locked()))
        return false;

    if ((m_index + 1) >= (int)m_data->rowsCount())
    {
        QSqlRecord sqlRecord;
        if (!m_data->read(sqlRecord))
            return false;

        QSqlIndex sqlIndex;

        /* When we are a read only recordset there is no index information. */
        if (!readOnly())
        {
            QSqlDatabase db = database();
            sqlIndex = db.primaryIndex(sourceTable());
        }

        SSRecord *record = createRecord(sqlRecord, sqlIndex, m_prefix);
        m_data->appendRow(record);
    }

    ++m_index;
    m_current = m_data->rowAt(m_index);
    return (m_current != NULL);
}
/*}}}*/
// bool SSRecordset::moveLast();/*{{{*/
bool SSRecordset::moveLast()
{
    /* The first call is only to ensure that we are not in the last row
     * already.
     */
    if (!moveNext()) return false;

    /* Move to the next record until we reach the end of the results. */
    while (moveNext());

    m_index = ((int)m_data->rowsCount() - 1);
    m_current = m_data->rowAt(m_index);
    return (m_current != NULL);
}
/*}}}*/
// bool SSRecordset::seek(int offset, int origin = SS_SEEK_SET);/*{{{*/
bool SSRecordset::seek(int offset, int origin)
{
    if (m_data == NULL) return false;   /* Cannot move anywhere. */

    int startPoint = ((origin == SS_SEEK_SET) ? 0 :
                      (origin == SS_SEEK_CUR) ? m_index : -1);

    if (origin == SS_SEEK_END)
    {
        if (m_style == SS_RECORDSET_FORWARDONLY)
            return false;   /* Any move in this case is illegal. */

        moveLast();
        m_index = ((int)m_data->rowsCount() - 1) + offset;
        m_current = m_data->rowAt(m_index);
    }
    else
    {
        startPoint += offset;
        if ((startPoint < m_index) && (m_style == SS_RECORDSET_FORWARDONLY))
            return false;

        while ((m_index < startPoint) && moveNext());

        if (m_index < startPoint) return false;
    }
    return true;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Editing Records
 * ------------------------------------------------------------------------ */

// SSRecord* SSRecordset::addNew();/*{{{*/
SSRecord* SSRecordset::addNew()
{
    if (readOnly()) return NULL;
    if (!m_data) return NULL;

    /* Check if we have a new record waiting or a locked record. */
    if (((m_index < 0) && (m_current != NULL)) ||
        ((m_current != NULL) && (m_current->locked())))
        return NULL;

    QSqlDatabase db = database();
    QSqlRecord  rec = db.record( sourceTable() );
    QSqlIndex   idx = db.primaryIndex( sourceTable() );

    QStringList columns = m_data->columns();

    /* When we have a list of columns defined in the select statement we
     * should return the new record with the same list.
     * NOTE: When 'columns' is empty all columns was selected. Don't filter
     * them.
     */
    if (columns.empty())
    {
        size_t size = rec.count();
        for (size_t j = 0; j < size; ++j)
            rec.setValue(j, rec.field(j).defaultValue());
    }
    else
    {
        int limit = rec.count();
        for (int i = (limit - 1); i >= 0; --i)
        {
            if (!columns.contains(rec.fieldName(i)))
            {
                rec.remove(i);
                continue;
            }

            /* When a column is kept, we can provide its default value. */
            rec.setValue(i, rec.field(i).defaultValue());
        }
    }

    SSRecord *record = createRecord(rec, idx, m_prefix);
    if (!record) return NULL;

    m_index = -1;
    m_current = record;

    return record;
}
/*}}}*/
// SSRecord* SSRecordset::edit();/*{{{*/
SSRecord* SSRecordset::edit()
{
    if (readOnly() || !m_data || !m_current) return NULL;

    if ((m_index < 0) && (m_current != NULL))
        return NULL;    /* Record added but not cancelled or committed. */

    if ((m_current != NULL) && (m_current->locked()))
        return m_current;   /* Record already locked. */

    /* Check if the position is right. */
    if (m_current != m_data->rowAt(m_index))
        return NULL;

    if (!m_data->lockRow(m_index, this))
        return NULL;

    /* We will use a cloned copy of the original SSRecord object. This way we
     * can restore the original data when the user cancel an editing
     * operation.
     */
    SSRecord *record = createRecord( m_current->clone() );
    if (!record)
    {
        m_current->unlock(this);
        return NULL;
    }
    m_current = record;
    return m_current;
}
/*}}}*/
// void SSRecordset::cancel();/*{{{*/
void SSRecordset::cancel()
{
    if ((m_index < 0) && (m_current != NULL))
    {
        /* We are canceling an added record. */
        delete m_current;

        m_index = ((int)m_data->rowsCount() - 1);
        m_current = m_data->rowAt(m_index);
    }
    else if ((m_index >= 0) && (m_current != NULL) && (m_current->locked()))
    {
        /* We are canceling a record edition. */
        if (m_current->unlock(this))
        {
            /* The editing operation does not follow copies of a recordset
             * object. But, to be sure we don't mess up things, we check if
             * the record could be unlocked since it only allows the original
             * context to unlock it.
             */
            delete m_current;   /* The editing object is a clone of the original. */

            m_current = m_data->rowAt(m_index);
            m_current->unlock(this);    /* Unlock the original also. */
        }
    }
}
/*}}}*/
// error_t SSRecordset::commit(const QString &filter = QString());/*{{{*/
error_t SSRecordset::commit(const QString &filter)
{
    error_t result = SSNO_ERROR;

    if ((m_index < 0) && (m_current != NULL))
    {
        /* An adding operation is in course. */
        if ((result = m_current->onWrite()) != SSNO_ERROR)
            return result;

        result = m_data->insert(m_current, database(), sourceTable());
        if (result != SSNO_ERROR) return result;

        m_index = (int)m_data->appendRow(m_current);
        m_index--;      /* Correct the index of the added row. */
    }
    else if ((m_index >= 0) && (m_current != NULL) && m_current->locked())
    {
        /* And editing operation is in course. */
        if ((result = m_current->onWrite()) != SSNO_ERROR)
            return result;

        result = m_data->update(m_current, database(), sourceTable(), filter);
        if (result != SSNO_ERROR) return result;

        /* Now we get the original record from the dataset. Change all column
         * values and unlock it. The cloned object, used while the user was
         * editing the record, will be released.
         */
        SSRecord *record = m_data->rowAt(m_index);
        size_t    limit  = record->count();

        for (size_t i = 0; i < limit; ++i)
            record->field(i).set( m_current->field(i).value() );

        /* The local copy can be deleted. */
        delete m_current;

        /* Unlock the original record. */
        record->unlock(this);
        m_current = record;
    }
    return result;
}
/*}}}*/
// error_t SSRecordset::delete(const QString &filter = QString());/*{{{*/
error_t SSRecordset::delete(const QString &filter)
{
    if (readOnly() || (m_data == NULL) || (m_current == NULL) ||
        ((m_index < 0) && (m_current != NULL)) ||
        ((m_index >= 0) && (m_current != NULL) && m_current->locked()))
        return SSE_PERM;

    /* Verify where the position is right. */
    if (m_current != m_data->rowAt(m_index))
        return SSE_INVAL;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Recordset Attributes
 * ------------------------------------------------------------------------ */

// bool SSRecordset::empty() const;/*{{{*/
/**
 * Checks whether this recordset is empty.
 * @return \b true when this recordset has no rows yet. It also returns \b
 * true when the recordset was not opened. Otherwise \b false.
 * @since 1.2
 **/
bool SSRecordset::empty() const
{
    return ((m_data == NULL) || (m_data->rowsCount() == 0));
}
/*}}}*/
// bool SSRecordset::readOnly() const;/*{{{*/
bool SSRecordset::readOnly() const
{
    if (!m_data) return true;
    if (m_table.isEmpty() || m_table.contains(',')) return true;

    QString stmt(m_data->statement());

    return (stmt.isEmpty() || stmt.contains("join", Qt::CaseInsensitive) ||
            stmt.contains("union", Qt::CaseInsensitive));
}
/*}}}*/

