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
#ifndef __RST_T_HPP_DEFINED__
#define __RST_T_HPP_DEFINED__

namespace ss {

/**
 * Implements a shareable list of records.
 * As a shareable object the \c dataset is meant to be used as a heap
 * allocated pointer. When all references are released (see
 * SSSharedT::release()) the destructor is executed and the instance will be
 * freed from memory.
 *
 * The list of records is also a list of shared object pointers, allowing
 * clients to extend the \c SSRecord class to something more useful.
 *
 * Operations that change the database stored data are separated from
 * operations that change the list of records. The \c dataset object works in
 * cooperation with the \c SSRecordset object that does part of the work on
 * updating the list of records. A \c dataset object cannot build an instance
 * of a \c SSRecord class on its own because that class can be extended by
 * the client application. So this task is delegated to \c SSRecordset
 * objects.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class dataset : public SSSharedT<dataset>
{
public:
    // dataset();/*{{{*/
    /**
     * Default constructor.
     * @since 1.2
     **/
    dataset();
    /*}}}*/
    // dataset(uint style, const QSqlDatabase &db);/*{{{*/
    /**
     * Builds the object defining the source database and style.
     * @param style Style for this dataset. Can be:
     * - \c SS_RECORDSET_FORWARDONLY: Data will be not kept when rows are read
     *   from the database. They are discarded as soon as the next row is
     *   read.
     * - \c SS_RECORDSET_DYNAMIC: Rows are kept for future use. The list can
     *   be navigated forward or backward. This style uses much more memory.
     * .
     * @param db Database to be used in the queries.
     * @since 1.2
     **/
    dataset(uint style, const QSqlDatabase &db);
    /*}}}*/
    // ~dataset();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~dataset();
    /*}}}*/

public:
    // error_t exec();/*{{{*/
    /**
     * Executes a statement previously compiled in the internal query.
     * @return An error status. When a previously compiled statement is not
     * found the result is the error code \c SSE_INVAL. SQL driver errors also
     * can be returned. In this case mostly are greater than zero instead of
     * negative numbers.
     * @remarks The current list of rows, if any, will be released.
     * @since 1.2
     **/
    error_t exec();
    /*}}}*/
    // error_t exec(const QString &stmt);/*{{{*/
    /**
     * Executes a ready made statement.
     * @param stmt A \c QString object with the statement to be executed.
     * @return An error status. If the \a stmt string is empty the result is
     * the error code \c SSE_INVAL. SQL driver errors also can be returned. In
     * this case mostly are greater than zero instead of negative numbers.
     * @remarks The current list of rows, if any, will be released.
     * @since 1.2
     **/
    error_t exec(const QString &stmt);
    /*}}}*/
    // error_t compile(const QString &stmt);/*{{{*/
    /**
     * Prepares a statement to be executed.
     * @param stmt String with the statement to be compiled.
     * @returns \c SSNO_ERROR when the compilation is Ok. Some drivers delay
     * the compilation to be done when the statement is executed. An error
     * code is returned if the compilation fails. When the internal query
     * already has rows the operation fails with error \c SSE_PERM. If the
     * argument passed through \a stmt is an empty string, the result is the
     * error \c SSE_INVAL.
     * @since 1.2
     **/
    error_t compile(const QString &stmt);
    /*}}}*/
    // void bind(uint pos, const QVariant &val);/*{{{*/
    /**
     * Binds a value to a parameter in the specified position.
     * @param pos Zero based position of the parameter.
     * @param val Value to be bound to the parameter. To set a parameter with
     * \b NULL build a \c QVariant object using the underlining type (e.g.:
     * QVariant(QVariant::String)).
     * @since 1.2
     **/
    void bind(uint pos, const QVariant &val);
    /*}}}*/
    // void bind(const QString &arg, const QVariant &val);/*{{{*/
    /**
     * Binds a value to a parameter in the specified position.
     * @param arg Name of the parameter to be bound.
     * @param val Value to be bound to the parameter. To set a parameter with
     * \b NULL build a \c QVariant object using the underlining type (e.g.:
     * QVariant(QVariant::String)).
     * @since 1.2
     **/
    void bind(const QString &arg, const QVariant &val);
    /*}}}*/
    // void bind(const QVariant &val);/*{{{*/
    /**
     * Binds a value to a positional parameter.
     * @param val Value to be bound. On each call to this operation
     * the value is bound to the lower unbound parameter. To bound a parameter
     * with \b NULL build a \c QVariant with the underlining type (e.g.:
     * QVariant(QVariant::Int)).
     * @since 1.2
     **/
    void bind(const QVariant &val);
    /*}}}*/
    // bool read(QSqlRecord &rec) const;/*{{{*/
    /**
     * Reads the next record from the internal query object.
     * @param rec Reference to a \c QSqlRecord object. When the function
     * succeeds this object will return with the data read from the database.
     * @returns When succeeded the result will be \b true. Otherwise \b false.
     * @remarks This operation does not add data to the list of records.
     * @since 1.2
     **/
    bool read(QSqlRecord &rec) const;
    /*}}}*/
    // error_t insert(SSRecord *record, const QSqlDatabase &db, const QString &table);/*{{{*/
    /**
     * Builds and executes an <code>INSERT INTO</code> instruction.
     * @param record \c SSRecord pointer with the data to be added in the
     * database.
     * @param db The \c QSqlDatabase object where data will be added.
     * @param table The table name where the data will be added.
     * @return An error status. This can be an error code if one or more
     * parameters are invalid or an code from the database driver. If
     * everything goes well, the result will be \c SSNO_ERROR.
     * @since 1.2
     **/
    error_t insert(SSRecord *record, const QSqlDatabase &db, const QString &table);
    /*}}}*/
    // error_t update(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);/*{{{*/
    /**
     * Builds and executes an <code>UPDATE ... SET</code> statement.
     * @param record \c SSRecord pointer with the data to be changed in the
     * database.
     * @param db The \c QSqlDatabase object where data will be stored.
     * @param table The table name where the data will be stored.
     * @param filter A filter to be used in the \c WHERE clause to limit the
     * number of records updated. If empty the function will build its own.
     * @return An error status. This can be an error code if one or more
     * parameters are invalid or an code from the database driver. If
     * everything goes well, the result will be \c SSNO_ERROR.
     * @since 1.2
     **/
    error_t update(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);
    /*}}}*/
    // error_t delete(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);/*{{{*/
    /**
     * Builds and executes a \c DELETE statement.
     * @param record \c SSRecord pointer with the data to be deleted.
     * @param db The \c QSqlDatabase object where data will be deleted.
     * @param table The table name where the data will be deleted.
     * @param filter A filter to be used in the \c WHERE clause to limit the
     * number of records deleted. If empty the function will build its own.
     * @return An error status. This can be an error code if one or more
     * parameters are invalid or an code from the database driver. If
     * everything goes well, the result will be \c SSNO_ERROR.
     * @remarks The list of records isn't affected by this operation.
     * @since 1.2
     **/
    error_t delete(SSRecord *record, const QSqlDatabase &db, const QString &table, const QString &filter);
    /*}}}*/

public:
    // error_t errorCode() const;/*{{{*/
    /**
     * Returns the last error code resulted of an database operation.
     * @return A database error code casted to an \c error_t value. When no
     * error exists, zero is returned (\c SSNO_ERROR).
     * @since 1.2
     **/
    error_t errorCode() const;
    /*}}}*/
    // size_t rowsCount() const;/*{{{*/
    /**
     * Retrieves the number of rows in this result set.
     * @return A \b size_t value with the number of rows in the internal list.
     * @since 1.2
     **/
    size_t rowsCount() const;
    /*}}}*/
    // bool   empty() const;/*{{{*/
    /**
     * Checks whether the internal list is empty or not.
     * @return \b true when there is no \c SSRecord object in the list.
     * Otherwise \b false.
     * @since 1.2
     **/
    bool   empty() const;
    /*}}}*/
    // SSRecord* rowAt(uint position) const;/*{{{*/
    /**
     * Get a pointer to an object in the specified position.
     * @param position Zero based position of the required object.
     * @returns The object pointer. When the \a position is invalid, the
     * result will be \b NULL.
     * @since 1.2
     **/
    SSRecord* rowAt(uint position) const;
    /*}}}*/
    // QString statement() const;/*{{{*/
    /**
     * Retrieves the current statement used to open this object.
     * @return A \c QString object with the statement used in this object.
     * This is defined by one of `dataset::exec()` methods. When none of
     * those methods was executed yet, the return value is undefined.
     * @since 1.2
     **/
    QString statement() const;
    /*}}}*/
    // QStringList columns() const;/*{{{*/
    /**
     * Get the list of columns used to open this dataset.
     * @return A \c QStringList object with the list of columns names. If this
     * dataset was not opened with a \c SELECT statement the result is an
     * empty list. An empty list is also returned when the dataset was open
     * using all columns from the source table.
     * @since 1.2
     **/
    QStringList columns() const;
    /*}}}*/

public:
    // int    indexOf(SSRecord *record);/*{{{*/
    /**
     * Search for the index of an object in the list.
     * @param record The object pointer to search of. Must not be \b NULL.
     * When so, the result will be \b -1.
     * @returns The position of the object in the list if it was found.
     * Otherwise \b -1.
     * @since 1.2
     **/
    int    indexOf(SSRecord *record);
    /*}}}*/
    // size_t appendRow(SSRecord *record);/*{{{*/
    /**
     * Append an \c SSRecord object pointer to the end of the list.
     * @param record Pointer to be added. Must not be \b NULL. When so, the
     * result will be zero.
     * @return The number of elements in the list after the new record added.
     * If the operation fails. The result will be zero.
     * @since 1.2
     **/
    size_t appendRow(SSRecord *record);
    /*}}}*/
    // int    insertRow(uint index, SSRecord *record);/*{{{*/
    /**
     * Inserts a record into the specified position.
     * @param index Zero based position to insert the record into the list. If
     * this value is equal to or greater than the number of rows in the list,
     * the record will be appended to it.
     * @param record Pointer to the record object to be appended. If this
     * parameter is \b NULL, the function does nothing and returns \b -1.
     * @return The zero based index of the record in the list. When the
     * operation fails, the result will be \b -1.
     * @since 1.2
     **/
    int    insertRow(uint index, SSRecord *record);
    /*}}}*/
    // bool   removeRow(SSRecord *record);/*{{{*/
    /**
     * Removes a \c SSRecord object from the internal list.
     * @param record Pointer to the object. This must be the same pointer
     * stored in the list. If \b NULL the function does nothing.
     * @returns \b true when the pointer is found and removed from the list.
     * Otherwise \b false.
     * @remarks The \a record pointer is still valid when the function
     * returns. Is responsibility of the caller to free this pointer from the
     * memory.
     * @since 1.2
     **/
    bool   removeRow(SSRecord *record);
    /*}}}*/
    // bool   removeRow(uint position);/*{{{*/
    /**
     * Removes a \c SSRecord object in the specified position.
     * @param position Zero based position of the object to remove.
     * @returns \b true when the object is removed from the list. Otherwise \b
     * false. The operation will fail when \a position points to a place out
     * of the list bounds.
     * @remarks The object pointer is deleted in this operation. If you don't
     * want that use #removeRow(SSRecord*).
     * @since 1.2
     **/
    bool   removeRow(uint position);
    /*}}}*/
    // void   removeAll();/*{{{*/
    /**
     * Remove all rows in the list.
     * @remarks All objects \c SSRecord stored in the list will be deleted
     * also. Its memory will be freed.
     * @note When this object is shared all references will be affected by
     * this operation. That is, any change in the list will affect all
     * references of this result object.
     * @since 1.2
     **/
    void   removeAll();
    /*}}}*/
    // SSRecord* lockRow(uint index, void *context);/*{{{*/
    /**
     * Locks a record for changes.
     * @param index Zero based position of the record to lock.
     * @param context The context for locking the record.
     * @return On failure the result will be \b NULL. The function can fail
     * if the passed \a index is invalid or the requested record is already
     * locked in another context. On success the result is the \c SSRecord
     * object locked in the passed context. Changes and deletion will be not
     * allowed while this record is locked.
     * @remarks The returned pointer is not placed in the list.
     * @since 1.2
     **/
    SSRecord* lockRow(uint index, void *context);
    /*}}}*/

private:
    // QString recordFilter(SSRecord *record, const QSqlDatabase &db, const QString &table);/*{{{*/
    /**
     * Builds a filter to limit changes in the passed record.
     * @param record Pointer to the \c SSRecord object to build the filter.
     * Must not be \b NULL.
     * @param db The \c QSqlDatabase object. Must be a valid database.
     * @param table The source table name. Cannot be empty.
     * @return A \c QString object with the filter to be used in the \c WHERE
     * clause. This filter could be used in any \c UPDATE or \c DELETE
     * statement using the \c SSRecord passed at the first parameter.
     * @since 1.2
     **/
    QString recordFilter(SSRecord *record, const QSqlDatabase &db, const QString &table);
    /*}}}*/

protected:
    QSqlDatabase m_db;              /**< Source database object.        */
    QSqlQuery m_query;              /**< Query source of records.       */
    QList<column_t *> m_columns;    /**< List of columns definitions.   */
    QList<SSRecord *> m_rows;       /**< Records list.                  */
    uint m_style;                   /**< This dataset style.            */
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline dataset::dataset();/*{{{*/
inline dataset::dataset() : SSSharedT<dataset>(), m_db(), m_query(),
    m_columns(), m_rows(), m_style(SS_RECORDSET_FORWARDONLY) {
    m_query.setForwardOnly(true);
}
/*}}}*/
// inline dataset::dataset(uint style, const QSqlDatabase &db);/*{{{*/
inline dataset::dataset(uint style, const QSqlDatabase &db) : SSSharedT<dataset>(),
    m_db(db), m_query(db), m_columns(), m_rows(), m_style(style) {
    m_query.setForwardOnly(true);
}
/*}}}*/
// inline dataset::~dataset();/*{{{*/
inline dataset::~dataset() {
    removeAll();
    m_query.finish();
}
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Statement Operations {{{
 * ------------------------------------------------------------------------ */
// inline void dataset::bind(uint pos, const QVariant &val);/*{{{*/
inline void dataset::bind(uint pos, const QVariant &val) {
    m_query.bindValue((int)pos, val, QSql::In);
}
/*}}}*/
// inline void dataset::bind(const QString &arg, const QVariant &val);/*{{{*/
inline void dataset::bind(const QString &arg, const QVariant &val) {
    m_query.bindValue(arg, val, QSql::In);
}
/*}}}*/
// inline void dataset::bind(const QVariant &val);/*{{{*/
inline void dataset::bind(const QVariant &val) {
    m_query.addBindValue(val);
}
/*}}}*/
// inline bool read(QSqlRecord &rec) const;/*{{{*/
inline bool read(QSqlRecord &rec) const {
    if (!m_query.next()) return false;
    rec = m_query.record(); return true;
}
/*}}}*/
// Statement Operations }}}
/* ------------------------------------------------------------------------ */
 * Attributes {{{
 * ------------------------------------------------------------------------ */
// inline error_t dataset::errorCode() const;/*{{{*/
inline error_t dataset::errorCode() const {
    return m_query.lastError().nativeErrorCode().toInt();
}
/*}}}*/
// inline size_t dataset::rowsCount() const;/*{{{*/
inline size_t dataset::rowsCount() const {
    return m_rows.count();
}
/*}}}*/
// inline bool   dataset::empty() const;/*{{{*/
inline bool dataset::empty() const {
    return m_rows.empty();
}
/*}}}*/
// inline SSRecord* dataset::rowAt(uint position) const;/*{{{*/
inline SSRecord* dataset::rowAt(uint position) const {
    return ((position < rowsCount()) ? m_rows[position] : NULL);
}
/*}}}*/
// inline QString dataset::statement() const;/*{{{*/
inline QString dataset::statement() const {
    return m_query.executedQuery();
}
/*}}}*/
// Attributes }}}
/* ---------------------------------------------------------------------------
 * Operations {{{
 * ------------------------------------------------------------------------ */
// inline int    dataset::indexOf(SSRecord *record);/*{{{*/
inline int dataset::indexOf(SSRecord *record) {
    if (!record) return -1;
    return m_rows.indexOf(record);
}
/*}}}*/
// inline bool   dataset::removeRow(SSRecord *record);/*{{{*/
inline bool dataset::removeRow(SSRecord *record) {
    return m_rows.removeOne(record);
}
/*}}}*/
// Operations }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
};  /* namespace ss */
#endif /* __RST_T_HPP_DEFINED__ */
