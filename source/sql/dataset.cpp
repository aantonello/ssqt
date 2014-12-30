/**
 * @file
 * Declares the class dataset.
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
#include "../stdplx.hpp"
#include "../ssqtcmn.hpp"
#include "../ssqterr.hpp"
#include "../ssqtshrd.hpp"
#include "../ssqtfld.hpp"
#include "../ssqtrec.hpp"
#include "dataset.hpp"

namespace ss {

/* ===========================================================================
 * dataset class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Statement Operations
 * ------------------------------------------------------------------------ */

// error_t dataset::exec();/*{{{*/
error_t dataset::exec()
{
    if (m_query.isActive()) return SSE_INVAL;
    if (!m_query.exec()) return errorCode();
    return SSNO_ERROR;
}
/*}}}*/
// error_t dataset::exec(const QString &stmt);/*{{{*/
error_t dataset::exec(const QString &stmt)
{
    if (stmt.isEmpty()) return SSE_INVAL;
    if (m_query.isActive()) return SSE_INVAL;
    if (!m_query.exec(stmt)) return errorCode();
    return SSNO_ERROR;
}
/*}}}*/
// error_t dataset::compile(const QString &stmt);/*{{{*/
error_t dataset::compile(const QString &stmt)
{
    if (stmt.isEmpty()) return SSE_INVAL;
    if (m_query.isActive()) return SSE_PERM;

    return (m_query.prepare(stmt) ? SSNO_ERROR : errorCode());
}
/*}}}*/
// error_t dataset::insert(SSRecord *record, const QSqlDatabase &db, const QString &table);/*{{{*/
error_t dataset::insert(SSRecord *record, const QSqlDatabase &db, const QString &table)
{
    if ((record == NULL) || !db.isValid() || table.isEmpty())
        return SSE_INVAL;

    QStringList fieldList;
    QStringList valueList;
    size_t fieldCount = record->count();

    fieldList.reserve( fieldCount );
    valueList.reserve( fieldCount );

    for (size_t i = 0; i < fieldCount; ++i)
    {
        fieldList << record->field(i).name();
        valueList << "?";
    }

    QString stmt("INSERT INTO %1 (%2) VALUES (%3)");
    QSqlQuery query(db);

    query.prepare( stmt.arg(table).arg(fieldList.join(", ")).arg(valueList.join(", ")) );
    for (size_t x = 0; x < fieldCount; ++x)
    {
        if (record->field(x).autoValue())
            query.addBindValue( QVariant() );
        else
            query.addBindValue( record->field(x).value() );
    }

    error_t result = SSNO_ERROR;
    if (!query.exec())
        result = query.lastError().nativeErrorCode().toInt();

    return result;
}
/*}}}*/
// error_t dataset::update(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);/*{{{*/
error_t dataset::update(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter)
{
    if ((!record) || !db.isValid() || table.isEmpty())
        return SSE_INVAL;

    QString     stmt("%1 = ?");
    QStringList valueList;
    size_t      limit = record->count();

    /* We can build the 'set' list with all fields. Doesn't matter which one
     * is the primary key or not.
     */
    valueList.reserve( limit );
    for (size_t i = 0; i < limit; ++i)
        valueList << stmt.arg(record->field(i).name());

    /* When a filter is provided we will use it. Otherwise we need to build
     * one from the list of indexes in the database table.
     */
    QString where(filter);
    if (where.isEmpty())
        where = recordFilter(record, db, table);

    stmt = QString("UPDATE %1 SET %2 WHERE %3").arg(table, valueList.join(", "), where);
    QSqlQuery query(db);

    query.prepare( stmt );
    for (size_t x = 0; x < limit; ++x)
        query.addBindValue(record->field(x).value());

    error_t result = SSNO_ERROR;
    if (!query.exec())
        result = query.lastError().nativeErrorCode().toInt();

    return result;
}
/*}}}*/
// error_t dataset::delete(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);/*{{{*/
error_t dataset::delete(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter)
{
    if (!record || !db.isValid() || table.isEmpty())
        return SSE_INVAL;

    QString where(filter);
    if (where.isEmpty())
        where = recordFilter(record, db, table);

    QString stmt(QString("DELETE FROM %1 WHERE %2").arg(table, where));
    QSqlQuery query(db);

    error_t result = SSNO_ERROR;
    if (!query.exec(stmt))
        result = query.lastError().nativeErrorCode().toInt();

    return result;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Attributes
 * ------------------------------------------------------------------------ */

// QStringList dataset::columns() const;/*{{{*/
QStringList dataset::columns() const
{
    QString stmt( statement() );
    QString sel("SELECT");

    if (stmt.isEmpty() || !stmt.startsWith(sel, Qt::CaseInsensitive))
        return QStringList();

    int from = stmt.indexOf(" from", sel.length(), Qt::CaseInsensitive);
    if (from < sel.length())
        return QStringList();

    QString names = stmt.mid(sel.length() + 1, (from - sel.length()));
    QStringList list = names.split(',', QString::SkipEmptyParts, Qt::CaseSensitive);

    /* We should remove any space before and after each name. */
    /* We also should check for a '*' column name. */
    int limit = list.count();
    for (int i = (limit - 1); i >= 0; --i)
    {
        list[i] = list[i].trimmed();
        if (list[i].indexOf('*') >= 0)
            list.removeAt(i);
    }
    return list;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Operations
 * ------------------------------------------------------------------------ */

// size_t dataset::appendRow(SSRecord *record);/*{{{*/
size_t dataset::appendRow(SSRecord *record)
{
    if (!record) return 0;

    m_rows.append(record);
    return rowsCount();
}
/*}}}*/
// int    dataset::insertRow(uint index, SSRecord *record);/*{{{*/
int dataset::insertRow(uint index, SSRecord *record)
{
    if (!record) return -1;

    if (index >= rowsCount())
        return ((int)appendRow(record) - 1);

    m_rows.insert((int)index, record);
    return index;
}
/*}}}*/
// bool   dataset::removeRow(uint position);/*{{{*/
bool dataset::removeRow(uint position)
{
    if (position >= rowsCount())
        return false;

    SSRecord *record = m_rows.takeAt(position);
    delete record;

    return true;
}
/*}}}*/
// void   dataset::removeAll();/*{{{*/
void dataset::removeAll()
{
    qDeleteAll(m_rows);
    m_rows.clear();
}
/*}}}*/
// SSRecord* dataset::lockRow(uint index, void *context);/*{{{*/
SSRecord* dataset::lockRow(uint index, void *context)
{
    if ((index >= rowsCount()) || (context == NULL))
        return NULL;

    SSRecord *record = rowAt(index);
    if (!record->lock(context))
        return NULL;

    return record;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Private: Operations
 * ------------------------------------------------------------------------ */

// QString dataset::recordFilter(SSRecord *record, const QSqlDatabase &db, const QString &table);/*{{{*/
QString dataset::recordFilter(SSRecord *record, const QSqlDatabase &db, const QString &table)
{
    QSqlIndex indexes = db.primaryIndex(table);
    QSqlField field;
    QStringList whereList;
    int count = indexes.count();

    whereList.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        field = indexes.field(i);
        if (record->has(field(i).name()))
        {
            switch (field(i).type())
            {
            case QVariant::String:
            case QVariant::Date:
            case QVariant::Time:
            case QVariant::DateTime:
                whereList << QString("%1 = '%2'").arg(field(i).name(), record->field(i).asString());
                break;
            case QVariant::Double:
                whereList << QString("%1 = %2").arg(field(i).name()).arg(record->field(i).asFloat());
                break;
            case QVariant::LongLong:
            case QVariant::ULongLong:
                whereList << QString("%1 = %2").arg(field(i).name()).arg(record->field(i).asLong());
                break;
            default:        /* Other numeric values. */
                whereList << QString("%1 = %2").arg(field(i).name()).arg(record->field(i).asInt());
            }
        }
    }

    return whereList.join(" AND ");
}
/*}}}*/

}; /* namespace ss */
