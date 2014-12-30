/**
 * @file
 * Declares the SSRecordset class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 12, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTRST_HPP_DEFINED__
#define __SSQTRST_HPP_DEFINED__

namespace ss {
    class dataset;
};

/**
 * \ingroup ssqt_dao
 * Provides access to data in a database.
 * \c SSRecordset is a kind of class that enables the execution of SQL
 * statements of any kind, holding the resulting of the call in the same way
 * as others object libraries.
 *
 * There are two kinds of SSRecordset objects:
 * -# \c SS_RECORDSET_FORWARDONLY: This is the default. Builds a recordset
 *    object that can be moved ahead only. Data records are not cached, saving
 *    much memory.
 * -# \c SS_RECORDSET_DYNAMIC: Caches the read data, enabling you to move
 *    backwards in the list of retrieved records.
 * .
 * \par Default Prefix
 *
 * A SSRecordset object is aware of columns with default prefix. For example,
 * all columns of a "users" table can start with the "user_" prefix. Is easy
 * to work with default prefixes when using a recordset because it informs
 * every row, represented by the \c SSRecord class, of it.  When extracting
 * data from a SSRecord instance you could call a column named "user_name"
 * just with the string "name". See more about this in the SSRecord class
 * documentation.
 * \par Source Database
 *
 * When a database object is not defined in the constructor the SSRecordset
 * instance will try to retrieve the default one, by using the \c
 * QSqlDatabase::database() static member function without parameters. When
 * you need to define the database after the class instance is created you can
 * do so by using the member function
 * SSRecordset::database(const QSqlDatabase&).
 * \par Current Record
 *
 * An \c SSRecordset object works in the sense of a current record. When
 * a recordset is opened it tries to load the first record of the selected
 * set. When this fails the recordset is in an empty state
 * (SSRecordset::empty() returns \b true). The current record can be changed
 * by using one of the move functions (SSRecordset::moveFirst(),
 * SSRecordset::moveNext(), SSRecordset::movePrev(), SSRecordset::moveLast()),
 * or by using the SSRecordset::seek() operation. When the recordset has
 * a current record you can use the overloaded operator '->' to directly
 * access the member functions of the \c SSRecord object. Also, the
 * SSRecordset::field(uint) and SSRecordset::field(const QString&) member
 * functions provide directly access to fields in the current record, and
 * these operations can be abbreviated by using the overloaded operators '()'.
 * \par Adding or Editing Records
 *
 * The SSRecordset::addNew() member function also changes the current record.
 * But, this time, the current record is the newly added one. When \c addNew()
 * is used the current position, returned by the SSRecordset::position()
 * method, is invalid and will be \b -1. Moving to another record in this
 * state is not possible them. You will need to `SSRecordset::cancel()` or
 * `SSRecordset::commit()` the changes to be able to move to another record
 * again. You are not obligated to call SSRecordset::edit() to edit a record.
 * But, doing so, ensures that the editing record will not be deleted by copies
 * of the same recordset. When \c edit() is called, the record becomes
 * unavailable to other copies until \c cancel() or \c commit() are executed.
 *
 * \c addNew(), \c edit() and \c commit() can only be used on non read only
 * recordsets. A read only recordset is built when a \c SELECT statement with
 * more than one table is used to open it, or the \c SELECT statement has \c
 * JOIN or \c UNION instructions.
 *
 * Adding or editing a record in a recordset is a monolithic operation. That
 * is, only the original recordset can start and end the operations. If you
 * copy a recordset, by using its copy constructor or the assignment operator,
 * the editing (or added) record will not be transfered with the copy. The
 * operation must start and end in the same object.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class SSRecordset
{
public:
    /** @name Constructor & Destructor */ //@{
    // explicit SSRecordset(QSqlDatabase db = QSqlDatabase(), uint style = SS_RECORDSET_FORWARDONLY);/*{{{*/
    /**
     * Default, parametrized, constructor.
     * @param db Optional. The database to be used in this recordset.
     * @param style The recordset style. Can be \c SS_RECORDSET_DYNAMIC to
     * construct a dynamic recordset where you can navigate forward or
     * backwards in the list of records. Or it can be \c
     * SS_RECORDSET_FORWARDONLY, the default, where you can only navigate
     * forward. In this style much memory is saved and, in some drivers, the
     * performance is increased.
     * @since 1.2
     **/
    explicit SSRecordset(QSqlDatabase db = QSqlDatabase(), uint style = SS_RECORDSET_FORWARDONLY);
    /*}}}*/
    // SSRecordset(const SSRecordset &rst);/*{{{*/
    /**
     * Copy constructor.
     * @param rst The recordset instance to be copied.
     * @remarks Every aspects of the \a rst parameter will be copied.
     * Including the amount of rows retrieved and in cache, the current row
     * position and data. Changing data in rows will be reflected in all
     * copies. Copyng a recordset allows you to have all instances positioned
     * on different rows of the list, if the original object was created using
     * the \c SS_RECORDSET_DYNAMIC style. When \a rst is adding a new record
     * or editing one its current record is not copied. The current position
     * can become invalid them. You should not copy a recordset object in edit
     * mode.
     * @since 1.2
     **/
    SSRecordset(const SSRecordset &rst);
    /*}}}*/
    // ~SSRecordset();/*{{{*/
    /**
     * Destructor.
     * @since 1.2
     **/
    ~SSRecordset();
    /*}}}*/
    //@}
public:
    /** @name Opening and Closing a Recordset */ //@{
    // error_t open();/*{{{*/
    /**
     * Opens this recordset using a prepared \c SELECT statement.
     * @returns An error status. \b SSNO_ERROR when the execution was done
     * without errors.
     * @remarks To prepare a \c SELECT statement use the \c compile() set of
     * operations in conjuction with the \c bind() set of operations. When
     * there is no prepared statement to run, the function will return \c
     * SSE_INVAL.
     *
     * Open a recordset that is already opened will automatically close it.
     * This operation does not affect other copies, just the current one. This
     * means that is safe to close a recordset that was created by a copy of
     * another one. The original recordset object will be still valid.
     * @note Even when the execution of the statement succeeds doesn't mean
     * that there are records in this recordset. The query could return an
     * empty recordset. This operations will fetch the first row of data from
     * the database so, the SSRecordset::recordCount() member function will
     * return a valid value.
     * @since 1.2
     **/
    error_t open();
    /*}}}*/
    // error_t open(const QString &query);/*{{{*/
    /**
     * Opens this recordset with the specified \c SELECT statement.
     * @param query A \c QString object with a ready made \c SELECT statement.
     * Can also be just the name of a database table. In this case the value
     * will be used to set the SSRecordset::sourceTable() name and a \c SELECT
     * statement will be built to load all records of that table.
     * @returns An error status. \b SSNO_ERROR when the execution was done
     * without errors. If \a query is empty, the result will be \c SSE_INVAL
     * and the recordset will not be closed.
     * @remarks
     * Open a recordset that is already opened will automatically close it.
     * This operation does not affect other copies, just the current one. This
     * means that is safe to close a recordset that was created by a copy of
     * another one. The original recordset object will be still valid.
     * @note Even when the execution of the statement succeeds doesn't mean
     * that there are records in this recordset. The query could return an
     * empty recordset. This operations will fetch the first row of data from
     * the database so, the SSRecordset::recordCount() member function will
     * return a valid value.
     * @since 1.2
     **/
    error_t open(const QString &query);
    /*}}}*/
    // error_t open(const QString &table, const QString &fields = QString("*"), const QString &where = QString());/*{{{*/
    /**
     * Builds and execute a \c SELECT statement.
     * @param table The table name or names, separated with commas. The passed
     * value will be stored and available through the
     * SSRecordset::sourceTable() method.
     * @param fields Optional. List of fields to load. If not passed all
     * fields of the table, or tables, will be loaded. Field names must be
     * full names. That is, the SSRecordset::defaultPrefix() doesn't apply to
     * this list. Names must be separated with commas.
     * @param where Optional. The compare statement to be used in the \c WHERE
     * clause without the \c WHERE keyword.
     * @returns An error status. When the operation succeeds the result will
     * be \c SSNO_ERROR.
     * @remarks If this recordset is already opened it will be closed
     * automatically. If the statement succeeds the first record will be
     * loaded and ready to be used.
     * @since 1.2
     **/
    error_t open(const QString &table, const QString &fields = QString("*"), const QString &where = QString());
    /*}}}*/
    // bool compile(const QString &query);/*{{{*/
    /**
     * Compiles an SQL statement to be executed.
     * @param query A \c QString object with the statement to compile. The
     * statement can have parameters to be bound to values after compile.
     * Parameters can be used with the ORACLE notation (e.g.: ':name') or ODBC
     * notation (e.g.: '?'). Both styles cannot be mixed in the same
     * statement. When \a query is an empty string the result will be \b
     * false. The recordset will not be closed in this case.
     * @returns \b true if the statement was compiled successful. Otherwise \b
     * false. Notice that some drivers delay the compilation process to be
     * done only when the statement is executed. In this case this function
     * will returns \b true even when there are errors in the statement. The
     * errors will be discovered only when SSRecordset::open() function is
     * executed. An example of this behavior is the SQLite database driver.
     * @remarks If this recordset is already opened this operation will need
     * to close it. Closing a recordset does not affect its copies. They will
     * remain valid.
     *
     * When the statement has parameters to be bound use the set of operations
     * SSRecordset::bind() to do it. After bind all parameters, the statement
     * can be executed with SSRecordset::open() member function.
     * @since 1.2
     **/
    bool compile(const QString &query);
    /*}}}*/
    // SSRecordset& bind(uint paramPos, const QVariant &paramVal);/*{{{*/
    /**
     * Binds a compiled statement parameter with a value.
     * @param paramPos Position of the parameter in the compiled statement.
     * Position numbers starts at 0.
     * @param paramVal A \c QVariant object with the parameter value. When
     * a parameter needs to be set as \b NULL, build a \c QVariant object with
     * the underlining type (e.g.: QVariant(QVariant::String)).
     * @returns The operation returns a reference of \b this object allowing
     * chaining of this operation.
     * @remarks A statement must be prepared before using this method. See
     * SSRecordset::compile(const QString&).
     * @since 1.2
     **/
    SSRecordset& bind(uint paramPos, const QVariant &paramVal);
    /*}}}*/
    // SSRecordset& bind(const QString &paramName, const QVariant &paramVal);/*{{{*/
    /**
     * Binds a compiled statement parameter with a value.
     * @param paramName \c QString object with the placeholder name used in
     * the prepared statement. Placeholders are in the form ':name'.
     * @param paramVal A \c QVariant object with the parameter value. When
     * a parameter needs to be set as \b NULL, build a \c QVariant object with
     * the underlining type (e.g.: QVariant(QVariant::String)).
     * @returns The operation returns a reference of \b this object allowing
     * chaining of this operation.
     * @remarks A statement must be prepared before using this method. See
     * SSRecordset::compile(const QString&).
     * @since 1.2
     **/
    SSRecordset& bind(const QString &paramName, const QVariant &paramVal);
    /*}}}*/
    // SSRecordset& bind(const QVariant &paramVal);/*{{{*/
    /**
     * Binds a compiled statement parameter with a value.
     * @param paramVal A \c QVariant object with the parameter value. When
     * a parameter needs to be set as \b NULL, build a \c QVariant object with
     * the underlining type (e.g.: QVariant(QVariant::String)).
     * @returns The operation returns a reference of \b this object allowing
     * chaining of this operation.
     * @remarks A statement must be prepared before using this method. See
     * SSRecordset::compile(const QString&).
     * @note This operation can be used only in numerical placeholders, that
     * is, placeholders inserted in the statement using the style '?'. The
     * first call to \c bind() will set the value to the first placeholder.
     * The second call will set the value to the second placeholder and so
     * forth.
     * @since 1.2
     **/
    SSRecordset& bind(const QVariant &paramVal);
    /*}}}*/
    // void close();/*{{{*/
    /**
     * Closes this recordset object.
     * The operation will release the memory allocated and the list of
     * records. \c close() automatically calls SSRecordset::cancel() to cancel
     * any editing operation in course.
     * @note Closing a recordset object doesn't affect its copies. That is, if
     * you have multiple copies of a recordset object you will need to close
     * everyone to unload all data. Also, when a recordset object is out of
     * scope, its default destructor call \c close() automatically.
     * @since 1.2
     **/
    void close();
    /*}}}*/
    //@}
public:
    /** @name Current Record Changing */ //@{
    // bool moveFirst();/*{{{*/
    /**
     * Moves to the first record in the list, making it the current one.
     * @returns \b true when the operation succeeds. Otherwise \b false.
     * @remarks The operation will fail when the recordset was open with the
     * \c SS_RECORDSET_FORWARDONLY style. Even when the recordset was just
     * opened and it is positioned in the first row. Also, the operation will
     * fail if SSRecordset::addNew() or SSRecordset::edit() was called. You
     * need to SSRecordset::cancel() or SSRecordset::commit() to be enabled to
     * move the recordset position again. When this recordset style is \c
     * SS_RECORDSET_DYNAMIC and it is already positioned at the first record,
     * the result will be \b false.
     * @since 1.2
     **/
    bool moveFirst();
    /*}}}*/
    // bool movePrev();/*{{{*/
    /**
     * Moves this recordset to point to the record before the current one.
     * @returns \b true when the operation succeeds. Otherwise \b false.
     * @remarks The operation will fail when the recordset was open with the
     * \c SS_RECORDSET_FORWARDONLY style. Also, the operation will
     * fail if SSRecordset::addNew() or SSRecordset::edit() was called. You
     * need to SSRecordset::cancel() or SSRecordset::commit() to be enabled to
     * move the recordset position again. If this recordset style is \c
     * SS_RECORDSET_DYNAMIC and it is positioned at the first record, the
     * result will be \b false.
     * @since 1.2
     **/
    bool movePrev();
    /*}}}*/
    // bool moveNext();/*{{{*/
    /**
     * Moves this recordset to the record after the current one.
     * @returns \b true when the operation succeeds. Otherwise \b false.
     * @remarks The operation will fail if SSRecordset::addNew() or
     * SSRecordset::edit() was called. You need to SSRecordset::cancel() or
     * SSRecordset::commit() to be enabled to move the recordset position
     * again. The operation will also fails when the current record is already
     * the last one.
     * @note When new data is fetched from the database, the
     * SSRecordset::createRecord() virtual function will be called to create
     * the instance of the \c SSRecord class object. If you extended the \c
     * SSRecord class to create your own model you will need to override the
     * \c createRecord() member function to create your class object instance.
     * @since 1.2
     **/
    bool moveNext();
    /*}}}*/
    // bool moveLast();/*{{{*/
    /**
     * Moves this recordset to the last row in the loaded list.
     * @returns \b true when the operation succeeds. Otherwise \b false.
     * @remarks The operation will fail if SSRecordset::addNew() or
     * SSRecordset::edit() was called. You need to SSRecordset::cancel() or
     * SSRecordset::commit() to be enabled to move the recordset position
     * again. The operation will also fails when the current record is already
     * the last one.
     * @note To fetch new data from the database this operation will call
     * SSRecordset::moveNext().
     * @since 1.2
     **/
    bool moveLast();
    /*}}}*/
    // bool seek(int offset, int origin = SS_SEEK_SET);/*{{{*/
    /**
     * Move to the record offset starting from the position defined.
     * @param offset The offset rows to move. Positive values move forward in
     * the record list. Negative values move backward. If this recordset has
     * the \c SS_RECORDSET_FORWARDONLY style negative values are illegal and
     * the operation will fails.
     * @param origin The starting point to move the cursor of. The values
     * accepted in this parameter are:
     * - \b SS_SEEK_SET: Start in the first row. Notice that passing an \a
     *   offset that is less than the current position in a forward only
     *   recordset is illegal.
     * - \b SS_SEEK_CUR: Start from the current position. In forward only
     *   recordsets negative \a offset values are illegal.
     * - \b SS_SEEK_END: Start from the last record. When this origin is set
     *   only negative \a offset are valid. In forward only recordsets this
     *   operation is illegal.
     * .
     * @returns \b true when the operation succeeds. \b false otherwise.
     * @note To fetch new data from the database this operation will call
     * SSRecordset::moveNext().
     * @since 1.2
     **/
    bool seek(int offset, int origin = SS_SEEK_SET);
    /*}}}*/
    // virtual SSRecord* createRecord(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString());/*{{{*/
    /**
     * Called when new data is fetched from the database.
     * @param record Data retrieved from the database.
     * @param index Primary index of the database table, if any. If this
     * recordset is read only (see SSRecordset::readOnly()), this parameter
     * will be an empty \c QSqlIndex object.
     * @param prefix The default prefix (see SSRecordset::defaultPrefix()) of
     * columns names.
     * @return An heap allocated \c SSRecord object.
     * @remarks This operation is called when new data is fetched from the
     * database. Applications that extend the \c SSRecord class needs to
     * override this method to create its extended version. The default
     * implementation create a standard \c SSRecord object.
     * @note The ownership of the returned object is this recordset instance.
     * The result pointer will be freed when non longer needed.
     * @since 1.2
     **/
    virtual SSRecord* createRecord(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString());
    /*}}}*/
    // virtual SSRecord* createRecord(const SSRecord &record);/*{{{*/
    /**
     * Called when this recordset needs to create a copy of a record object.
     * @param record A constant reference to the original \c SSRecord object.
     * @return A new \c SSRecord instance copy of the original \a record.
     * @remarks This virtual member function is used when a new record object
     * needs to be created based on another record object. This allows
     * applications that extend the \c SSRecord class to build and use its own
     * object instance.
     * @note This recordset will owns this pointer and will delete it when it
     * is non longer needed. The default implementation simply calls the copy
     * constructor of a standard \c SSRecord object.
     * @since 1.2
     **/
    virtual SSRecord* createRecord(const SSRecord &record);
    /*}}}*/
    //@}
public:
    /** @name Editing Records */ //@{
    // SSRecord* addNew();/*{{{*/
    /**
     * Adds a new record to this recordset.
     * @returns On success an \c SSRecord class pointer. \b NULL on failure.
     * @remarks A recordset is only able to create a new record when it is not
     * read only (see SSRecordset::readOnly()). When this operation succeeds,
     * the current record is in an invalid state (SSRecordset::position()
     * returns \b -1) until you call SSRecordset::cancel() or
     * SSRecordset::commit(). The recordset is positioned in the new record
     * returned so any function in this class that operates in the current
     * record will operate in the added record returned. The SSRecordset
     * object is the owner of the SSRecord pointer returned. When \c cancel()
     * is called the pointer is released (deleted) from memory. When \c
     * commit() is called the new record data is stored in the database and
     * the pointer is added to the end of the list. If this recordset has the
     * \c SS_RECORDSET_FORWARDONLY style the new record will be the only one
     * available after \c commit(), unless there is more data to be fetched
     * from the database.
     * @note This operation will call SSRecordset::createRecord() to create
     * the \c SSRecord instance.
     * @since 1.2
     **/
    SSRecord* addNew();
    /*}}}*/
    // SSRecord* edit();/*{{{*/
    /**
     * Starts editing the current record.
     * @return The current record pointer. If there is no current record, the
     * function returns \b NULL.
     * @remarks You are not obligated to do so but is advised to call this
     * function before starting to change data in the current record. When
     * this function succeeds the current record is locked so others copies of
     * this recordset cannot change or delete it. This ensures that your copy
     * is the only one editing the record. If the record is already locked by
     * another copy, this method fails and the return value is \b NULL. While
     * the current record is locked you cannot move to another one. To release
     * the lock in the record call SSRecordset::cancel() or
     * SSRecordset::commit().
     * @note Calling \c edit() on a recordset that is already editing a record
     * does not have any side effect.
     * @since 1.2
     **/
    SSRecord* edit();
    /*}}}*/
    // void cancel();/*{{{*/
    /**
     * Cancels an editing operation or the addition of a new record.
     * When adding a new record (SSRecordset::addNew() was called) the
     * operation releases (delete) the object created. The recordset is moved
     * to the end of the list without fechting new records from the database.
     * When there is no records to move to, the current position remains
     * invalid. When an editing operation is in course this function unlocks
     * the record and restores the original data. All changes made are lost.
     * @note If there are no edit or adding operation in course, this function
     * does nothing.
     * @since 1.2
     **/
    void cancel();
    /*}}}*/
    // error_t commit(const QString &filter = QString());/*{{{*/
    /**
     * Commit the changes in the current record back to the database.
     * The exactly operation of this function depends on the type of the
     * editing record. If the record is a new added one this operation will
     * build an \c INSERT statement. If the record already exists and has been
     * edited the operation will build an \c UPDATE statement.
     * @param filter When the \c commit() operation needs to build an \c
     * UPDATE statement, it needs to create a \c WHERE clause to limit the
     * number of records changed. When you need more control about this clause
     * you can pass the filter in this parameter and it will be used in the \c
     * UPDATE statement. When using the indexes of the record is enough,
     * you don't need to build the filter. The \c SSRecordset object is smart
     * enough to build the filter on its own. In the \c INSERT statement this
     * parameter is not used and it is ignored.
     * @return When the operation succeeds the result is \c SSNO_ERROR. If the
     * operation fails an error code is returned. The error can be a standard
     * error code or a result status returned by the database driver.
     * @remarks This operation will call SSRecord::onWrite() enabling extended
     * classes to move that to the fields in that object. When \c onWrite()
     * fails the \c commit() operation is aborted.
     * @note If no edit or adding operation is in course, this function does
     * nothing.
     * @since 1.2
     **/
    error_t commit(const QString &filter = QString());
    /*}}}*/
    // error_t delete(const QString &filter = QString());/*{{{*/
    /**
     * Deletes the current record.
     * @param filter Filter to be used in the \c WHERE clause to select the
     * correct record to be deleted. When the indexes of the record are enough
     * to build this filter, the recordset object is smart enough to build the
     * \c WHERE clause on its own.
     * @return If the operation succeeds the operation returns \c SSNO_ERROR.
     * Otherwise an error code will be returned. Resulting errors can be
     * standard values or codes received from the database driver.
     * @since 1.2
     **/
    error_t delete(const QString &filter = QString());
    /*}}}*/
    //@}
public:
    /** @name Recordset Attributes */ //@{
    // bool empty() const;/*{{{*/
    /**
     * Checks whether this recordset is empty.
     * @return \b true when this recordset has no rows yet. It also returns \b
     * true when the recordset was not opened. Otherwise \b false.
     * @since 1.2
     **/
    bool empty() const;
    /*}}}*/
    // bool readOnly() const;/*{{{*/
    /**
     * Checks whether this recordset is read only or not.
     * @returns \b true when data in this recordset cannot be changed.
     * Otherwise \b false.
     * @remarks A read only recordset is built when the statement used to open
     * it has multiple tables, on or more \c JOIN instruction or one or more
     * \c UNION instruction.
     * @note Technically, data in a read only recordset can be changed, but it
     * will not be committed to the database.
     * @since 1.2
     **/
    bool readOnly() const;
    /*}}}*/
    // int recordCount() const;/*{{{*/
    /**
     * Retrieves the current number of records.
     * @return The current number of records in this recordset. Some drivers
     * does not support returning the number of rows found in a query. In this
     * case the result will be \b -1. Also, if the recordset is not open, the
     * result is \b -1. When the total number of records cannot be determined
     * and you have a \c SS_RECORDSET_DYNAMIC recordset style you can move to
     * the last row. Then the total number of rows will be available.
     * @since 1.2
     **/
    int recordCount() const;
    /*}}}*/
    // int columnCount() const;/*{{{*/
    /**
     * Gets the number of columns on each row of the recordset.
     * @returns A integer with the total number of columns.
     * @remarks This number is available only after the first row is fetched
     * from the database. Before that this operation always returns \b -1.
     * @since 1.2
     **/
    int columnCount() const {
        if (m_index < 0) return -1;
        return m_rows[m_index].count();
    }
    /*}}}*/
    // int position() const;/*{{{*/
    /**
     * Retrieves the current row position in the records list.
     * @returns An integer specifying the current row position. When no record
     * was fetched from the database yet the current row position is \b -1.
     * \b -1 is also returned after the recordset is closed. The first row
     * position is zero.
     * @since 1.2
     **/
    int position() const;
    /*}}}*/
    //@}
public:
    /** @name Recordset Properties */ //@{
    // QSqlDatabase database() const;/*{{{*/
    /**
     * Retrieves the database used by this recordset.
     * @return The previously defined database for the queries executed in
     * this recordset object. When no database was defined the default one
     * will be returned.
     * @remarks The resulting database still can be invalid so, it must be
     * checked first.
     * @since 1.2
     **/
    QSqlDatabase database() const;
    /*}}}*/
    // QString defaultPrefix() const;/*{{{*/
    /**
     * Retrieves the default column name prefix.
     * @return A \c QString object with the defined default prefix.
     * @remarks The user has to define this value before it can be used by
     * this recordset.
     * @since 1.2
     **/
    QString defaultPrefix() const;
    /*}}}*/
    // QString sourceTable() const;/*{{{*/
    /**
     * Retrieves the name of the table for the data.
     * @returns \c QString object with the table name.
     * @remarks This value must be set so it can be used by this object.
     * @since 1.2
     **/
    QString sourceTable() const;
    /*}}}*/
    // SSRecordset& database(QSqlDatabase db);/*{{{*/
    /**
     * Sets or changes the database to be used by this recordset.
     * @param db The database instance to be used on queries of this
     * recordset.
     * @return The operation returns a reference of \b this, allowing for
     * chaining calls in this recordset.
     * @since 1.2
     **/
    SSRecordset& database(QSqlDatabase db);
    /*}}}*/
    // SSRecordset& defaultPrefix(const QString &prefix);/*{{{*/
    /**
     * Sets or changes the default prefix for columns names.
     * @param prefix Default string prefix.
     * @return The operation returns a reference of \b this, allowing for
     * chaining calls in this recordset.
     * @since 1.2
     **/
    SSRecordset& defaultPrefix(const QString &prefix);
    /*}}}*/
    // SSRecordset& sourceTable(const QString &tableName);/*{{{*/
    /**
     * Sets or changes the name of the origin table.
     * @param tableName Name of the table in the database.
     * @return The operation returns a reference of \b this, allowing for
     * chaining calls in this recordset.
     * @since 1.2
     **/
    SSRecordset& sourceTable(const QString &tableName);
    /*}}}*/
    //@}
public:
    /** @name Current Row Operations */ //@{
    // SSRecord* record() const;/*{{{*/
    /**
     * Retrieves the current record object.
     * @return A pointer to the current record object. If the recordset is not
     * positioned on any record the result is \b NULL.
     * @since 1.2
     **/
    SSRecord* record() const {
        return ((m_index < 0) ? record_type() : m_rows[m_index]);
    }
    /*}}}*/
    // SSField&  field(uint index) const;/*{{{*/
    /**
     * Retrieves a field object in the current row.
     * @param index Zero based index of the required field.
     * @return The object representing the column at the specified index or
     * a default constructed object if the \a index value is invalid or there
     * is no current row.
     * @since 1.2
     **/
    SSField&    field(uint index) const {
        return record().field(index);
    }
    /*}}}*/
    // SSField&  field(const QString &fieldName) const;/*{{{*/
    /**
     * Retrieves a field object in the current row.
     * @param fieldName Name of the field to retrieve.
     * @return The object representing the column with the specified name or
     * a default constructed object if the \a fieldName value was not found or
     * there is no current row.
     * @since 1.2
     **/
    SSField&    field(const QString &fieldName) const {
        return record().field(fieldName);
    }
    /*}}}*/

    // SSField& operator ()(uint index) const;/*{{{*/
    /**
     * Retrieves a field object in the current row.
     * @param index Zero based index of the required field.
     * @return The object representing the column at the specified index or
     * a default constructed object if the \a index value is invalid or there
     * is no current row.
     * @since 1.2
     **/
    SSField& operator ()(uint index) const {
        return field(index);
    }
    /*}}}*/
    // SSField& operator ()(const QString &fieldName) const;/*{{{*/
    /**
     * Retrieves a field object in the current row.
     * @param fieldName Name of the field to retrieve.
     * @return The object representing the column with the specified name or
     * a default constructed object if the \a fieldName value was not found or
     * there is no current row.
     * @since 1.2
     **/
    SSField& operator ()(const QString &fieldName) const {
        return field(fieldName);
    }
    /*}}}*/
    //@}
protected:
    QSqlDatabase m_db;                  /**< Source of data.                */
    QString m_prefix;                   /**< Default columns name prefix.   */
    QString m_table;                    /**< Source table name.             */
    ss::dataset *m_data;                /**< Records list.                  */
    SSRecord    *m_current;             /**< Current record.                */
    int  m_index;                       /**< Current row in record list.    */
    uint m_style;                       /**< The recordset style.           */
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline SSRecordset::SSRecordset(QSqlDatabase db = QSqlDatabase(), uint style = SS_RECORDSET_FORWARDONLY);/*{{{*/
inline SSRecordset::SSRecordset(QSqlDatabase db, uint style) : m_db(db),
    m_data(NULL), m_current(NULL), m_index(-1), m_style(style) { }
/*}}}*/
// inline SSRecordset::~SSRecordset();/*{{{*/
inline SSRecordset::~SSRecordset() {
    close();
}
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Public: Current Record Changing {{{
 * ------------------------------------------------------------------------ */
// inline SSRecord* SSRecordset::createRecord(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString());/*{{{*/
inline SSRecord* SSRecordset::createRecord(const QSqlRecord &record,
                                           const QSqlIndex &index,
                                           const QString &prefix)
{
    return new SSRecord(record, index, prefix);
}
/*}}}*/
// inline SSRecord* SSRecordset::createRecord(const SSRecord &record);/*{{{*/
inline virtual SSRecord* SSRecordset::createRecord(const SSRecord &record) {
    return new SSRecord(record);
}
/*}}}*/
// Current Record Changing }}}
/* ---------------------------------------------------------------------------
 * Public: Recordset Attributes {{{
 * ------------------------------------------------------------------------ */
// inline int SSRecordset::recordCount() const;/*{{{*/
inline int SSRecordset::recordCount() const {
    return (m_data ? m_data->rowsCount() : -1);
}
/*}}}*/
// inline int SSRecordset::columnCount() const;/*{{{*/
inline int SSRecordset::columnCount() const {
    return ((m_index < 0) ? -1 : m_data->rowAt(m_index)->count());
}
/*}}}*/
// inline int SSRecordset::position() const;/*{{{*/
inline int SSRecordset::position() const {
    return m_index;
}
/*}}}*/
// Public: Recordset Attributes }}}
/* ---------------------------------------------------------------------------
 * Public: Recordset Properties {{{
 * ------------------------------------------------------------------------ */
// inline QSqlDatabase SSRecordset::database() const;/*{{{*/
inline QSqlDatabase SSRecordset::database() const {
    if (!m_db.isValid()) m_db = QSqlDatabase::database();
    return m_db;
}
/*}}}*/
// inline QString SSRecordset::defaultPrefix() const;/*{{{*/
inline QString SSRecordset::defaultPrefix() const {
    return m_prefix;
}
/*}}}*/
// inline QString SSRecordset::sourceTable() const;/*{{{*/
inline QString SSRecordset::sourceTable() const {
    return m_table;
}
/*}}}*/
// inline SSRecordset& SSRecordset::database(QSqlDatabase db);/*{{{*/
inline SSRecordset& SSRecordset::database(QSqlDatabase db) {
    m_db = db; return *this;
}
/*}}}*/
// inline SSRecordset& SSRecordset::defaultPrefix(const QString &prefix);/*{{{*/
inline SSRecordset& SSRecordset::defaultPrefix(const QString &prefix) {
    m_prefix = prefix; return *this;
}
/*}}}*/
// inline SSRecordset& SSRecordset::sourceTable(const QString &tableName);/*{{{*/
inline SSRecordset& SSRecordset::sourceTable(const QString &tableName) {
    m_table = tableName; return *this;
}
/*}}}*/
// Public: Recordset Properties }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTRST_HPP_DEFINED__ */
