/**
 * @file
 * Declares the SSRecord class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 10, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTREC_HPP_DEFINED__
#define __SSQTREC_HPP_DEFINED__

namespace ss {
    class column_t;
};

/**
 * \ingroup ssqt_dao
 * A class representing a row of data.
 * An \c SSRecord class is intended to be used as a shared pointer. That is,
 * no instances of this class are created in the stack. All are heap allocated
 * to be shared among all \c SSRecordset objects that need them. To allow the
 * control of usage an \c SSRecord class extends \c SSSharedT template class
 * that provides a reference counting mechanism. You should never keep
 * a pointer to a \c SSRecord object directly. Instead you should access it
 * through the \c SSRecordset object. But, if you really need to do so, you
 * must retain (SSSharedT::retain()) your pointer reference while you need it.
 * In the same way, you must never delete a pointer to a \c SSRecord object by
 * your self. When you non longer need you pointer reference you release it by
 * calling SSSharedT::release(). You could also use a \c SSAutoSharedT
 * template class. It is a value class and automatically releases the pointer
 * reference when it goes out of scope.
 * ~~~~~~~~~~~~~~~{.cpp}
 * SSAutoSharedT<SSRecord> sharedRecord;
 * ...
 * sharedRecord = recordset.record();   // Retain the SSRecord pointer.
 * sharedRecord->field(0).value = 0;    // Use the SSRecord pointer.
 * ...
 * // When the 'sharedRecord' object goes out of scope the SSRecord pointer
 * // reference is released.
 * ...
 * sharedRecord = NULL;     // Setting to NULL also releases the pointer.
 * ~~~~~~~~~~~~~~~
 *
 * A data row is a list of \c SSField objects. Each \c SSField object has
 * a reference to its column definition and holds the field data. This
 * structure is liter than the Qt implementation where each \c QSqlField
 * object has both definition and value.
 *
 * You can extend a \c SSRecord class to hold the database data using standard
 * Qt properties or more clever implementations. The loaded data can be bound
 * the instance members in the SSRecord::onRead() virtual function. If the
 * record is changed and the data needs to be wrote in the database, the
 * SSRecord::onWrite() virtual function is called so you can pass the values
 * in your extension to the fields held by the \c SSRecord object. Just don't
 * forget that an \c SSRecord object is used only in the heap as a shared
 * pointer.
 * \par Columns Names
 *
 * Is common to name columns of a table using a standard prefix. For
 * example, a "users" table can have all its columns prefixed with the
 * string "user_". The \c SSRecord object has the SSRecord::defaultPrefix()
 * property that is inherited from \c SSRecordset object. This allows you to
 * find a field by using its \e shorter name, without the prefix. Using the
 * previous example, you can find the "user_name" field by searching for the
 * string "name" only, or search for the field named "user_id" by using the
 * string "id" or "user_id", which ever you like.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class SSRecord : public SSSharedT<SSRecord>
{
public:
    /** @name Constructors & Destructors */ //@{
    // SSRecord();/*{{{*/
    /**
     * Default constructor.
     * Builds an empty \c SSRecord object. This constructor does not call
     * SSRecord::onRead(). There is no data to read.
     * @since 1.2
     **/
    SSRecord();
    /*}}}*/
    // SSRecord(const SSRecord &record) = delete;/*{{{*/
    /**
     * Copy constructor.
     * @param record Another \c SSRecord instance.
     * @remarks The copy constructor is disabled in this class.
     * @since 1.2
     **/
    SSRecord(const SSRecord &record) = delete;
    /*}}}*/
    // SSRecord(const QList<SSField> &fields, const QString &prefix = QString());/*{{{*/
    /**
     * Builds the \c SSRecord instance with data from the provided record.
     * @param fields List of fields for this record.
     * @param prefix Optional, Default prefix for columns names.
     * @remarks This constructor is not meant to be called by the user. It is
     * used to load a record in the \c SSRecordset class. Extended classes
     * must provide a constructor with this signature.
     * @note The SSRecord::onRead() method will be called after the list of
     * fields has been mounted.
     * @since 1.2
     **/
    SSRecord(const QList<SSField> &fields, const QString &prefix = QString());
    /*}}}*/
    // ~SSRecord();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~SSRecord();
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // size_t count() const;/*{{{*/
    /**
     * Retrieves the number of fields in this record.
     * @return A unsigned long integer counting the number of fields in this
     * record.
     * @since 1.2
     **/
    size_t count() const;
    /*}}}*/
    // bool   empty() const;/*{{{*/
    /**
     * Checks whether this record is empty (has no columns).
     * @returns \b true when this record has no fields. Otherwise \b false.
     * @since 1.2
     **/
    bool   empty() const;
    /*}}}*/
    // bool   has(const QString &fieldName) const;/*{{{*/
    /**
     * Checks whether this record has a field named \e fieldName.
     * @param fieldName \c QString with the field name to be queried. If
     * a default prefix was defined, this parameter may be the suffix part of
     * the column name.
     * @return \b true if the field exists, otherwise \b false.
     * @since 1.2
     **/
    bool has(const QString &fieldName) const;
    /*}}}*/
    // int    indexOf(const QString &fieldName) const;/*{{{*/
    /**
     * Query the index of a field by its name.
     * @param fieldName \c QString with the field name to be queried. If
     * a default prefix was defined, this parameter can be the suffix part of
     * the column name.
     * @return A value equals to or greater than zero is the field index.
     * A value less than zero when the name was not found.
     * @since 1.2
     **/
    int indexOf(const QString &fieldName) const;
    /*}}}*/
    // QString  defaultPrefix() const;/*{{{*/
    /**
     * Retrieves the default prefix defined for this record.
     * @return A \c QString object with the default prefix defined. When
     * a default prefix is not in use the result is an empty object.
     * @since 1.2
     **/
    QString  defaultPrefix() const;
    /*}}}*/
    // SSField& field(uint index);/*{{{*/
    /**
     * Gets a non-const reference to a field in this record.
     * @param index Zero based index of the field.
     * @return A non-const reference to the specified field. If the value of
     * \a index is invalid, an empty (invalid) \c SSField object will be
     * returned.
     * @since 1.2
     **/
    SSField& field(uint index);
    /*}}}*/
    // SSField& field(const QString &fieldName);/*{{{*/
    /**
     * Gets a non-const reference to a field in this record.
     * @param fieldName \c QString with the field name to be retrieved. If
     * a default prefix was defined, this parameter can be only the suffix
     * part of the column name.
     * @return A non-const reference to the specified field. If the value of
     * \a fieldName is invalid (not found in the list of fields) an empty
     * (invalid) field will be returned.
     * @since 1.2
     **/
    SSField& field(const QString &fieldName);
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // void clear();/*{{{*/
    /**
     * Clear the list of fields of this record.
     * @since 1.2
     **/
    void clear();
    /*}}}*/
    //@}
public:
    /** @name Record Lock */ //@{
    // bool lock(void *context);/*{{{*/
    /**
     * Locks this record for a given context.
     * @param context Pointer to the context where this record is locked.
     * @returns \b true if the operation succeeds. Otherwise \b false.
     * @remarks The operation can fail if this record is already locked by
     * another context.
     * @note A context is simply a way to differenciate lockers. It is not
     * changed nor used in the \c SSRecord class.
     * @since 1.2
     **/
    bool lock(void *context);
    /*}}}*/
    // bool locked() const;/*{{{*/
    /**
     * Checks whether this record is locked.
     * @returns \b true when this record object is locked. \b false otherwise.
     * @since 1.2
     **/
    bool locked() const;
    /*}}}*/
    // bool unlock(void *context);/*{{{*/
    /**
     * Unlock this record.
     * @param context The same context used to lock this record.
     * @returns \b true if the record was unlocked. \b false otherwise.
     * @remarks The operation can fail if the passed \a context is not the
     * same used to lock this record. When the record wasn't locked, the
     * result will be \b true.
     * @note A context is simply a way to differenciate lockers. It is not
     * changed nor used in the \c SSRecord class.
     * @since 1.2
     **/
    bool unlock(void *context);
    /*}}}*/
    // bool lockedContext(void *context);/*{{{*/
    /**
     * Checks whether the locked context is equals to the passed one.
     * @param context A context pointer to check for the current lock.
     * @returns \b true when this record is locked using the context pointed
     * at \a context. Otherwise \b false. This operation also returns \b false
     * when the record is not locked at all.
     * @note A context is simply a way to differenciate lockers. It is not
     * changed nor used in the \c SSRecord class.
     * @since 1.2
     **/
    bool lockedContext(void *context);
    /*}}}*/
    //@}
public:
    /** @name Overloaded Operators */ //@{
    // SSRecord& operator =(const SSRecord &record) = delete;/*{{{*/
    /**
     * Copy operator.
     * @param record Other \c SSRecord instance to copy its data.
     * @return \b this.
     * @remarks This operator is deleted.
     * @since 1.2
     **/
    SSRecord& operator =(const SSRecord &record) = delete;
    /*}}}*/
    //@}
public:
    /** @name Overridables */ //@{
    // virtual void onRead();/*{{{*/
    /**
     * Called so the implementors can read the new data.
     * This operation is called when this record object has new data.
     * @note The default implementation does nothing.
     * @since 1.2
     **/
    virtual void onRead();
    /*}}}*/
    // virtual error_t onWrite();/*{{{*/
    /**
     * Called so the implementors update the list of fields.
     * Called when this class needs the most recent data on its list of
     * fields. If extended classes keeps fields data on member variables, for
     * example, this is the time to copy the values in the correspondent \c
     * SSField object.
     * @return This function should return \c SSNO_ERROR on success or an
     * error code on failure.
     * @note The default implementation simply returns \c SSNO_ERROR.
     * @since 1.2
     **/
    virtual error_t onWrite();
    /*}}}*/
    //@}
protected:
    /** @name Data Members */ //@{
    QList<SSField> m_fields;            /**< List of fields in this record. */
    QString m_prefix;                   /**< Default columns prefix name.   */
    void *m_lock;                       /**< When this record is locked.    */
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline SSRecord::SSRecord();/*{{{*/
inline SSRecord::SSRecord() { }
/*}}}*/
// inline SSRecord::SSRecord(const QList<SSField> &fields, const QString &prefix = QString());/*{{{*/
inline SSRecord::SSRecord(const QList<SSField> &fields, const QString &prefix) :
    m_fields(fields), m_prefix(prefix) { onRead(); }
/*}}}*/
// inline SSRecord::~SSRecord();/*{{{*/
inline SSRecord::~SSRecord() { }
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Attributes {{{
 * ------------------------------------------------------------------------ */
// inline size_t SSRecord::count() const;/*{{{*/
inline size_t SSRecord::count() const {
    return m_fields.count();
}
/*}}}*/
// inline bool   SSRecord::empty() const;/*{{{*/
inline bool SSRecord::empty() const {
    return m_fields.isEmpty();
}
/*}}}*/
// inline bool   SSRecord::has(const QString &fieldName) const;/*{{{*/
inline bool SSRecord::has(const QString &fieldName) const {
    return (indexOf(fieldName) >= 0);
}
/*}}}*/
// inline QString  SSRecord::defaultPrefix() const;/*{{{*/
inline QString SSRecord::defaultPrefix() const {
    return m_prefix;
}
/*}}}*/
// inline SSField& SSRecord::field(const QString &fieldName);/*{{{*/
inline SSField& SSRecord::field(const QString &fieldName) {
    return field(indexOf(fieldName));
}
/*}}}*/
// Attributes }}}
/* ---------------------------------------------------------------------------
 * Operations {{{
 * ------------------------------------------------------------------------ */
// inline void SSRecord::clear();/*{{{*/
inline void SSRecord::clear() {
    m_fields.clear();
}
/*}}}*/
// Operations }}}
/* ---------------------------------------------------------------------------
 * Record Lock {{{
 * ------------------------------------------------------------------------ */
// inline bool SSRecord::lock(void *context);/*{{{*/
inline bool SSRecord::lock(void *context) {
    if ((m_lock != NULL) && (m_lock != context)) return false;
    m_lock = context; return true;
}
/*}}}*/
// inline bool SSRecord::locked() const;/*{{{*/
inline bool SSRecord::locked() const {
    return (m_lock != NULL);
}
/*}}}*/
// inline bool SSRecord::unlock(void *context);/*{{{*/
inline bool SSRecord::unlock(void *context) {
    if ((m_lock != NULL) && (m_lock != context)) return false;
    m_lock = NULL; return true;
}
/*}}}*/
// inline bool SSRecord::lockedContext(void *context);/*{{{*/
inline bool SSRecord::lockedContext(void *context) {
    return (m_lock == context);
}
/*}}}*/
// Record Lock }}}
/* ---------------------------------------------------------------------------
 * Public: Overridables {{{
 * ------------------------------------------------------------------------ */
// inline void SSRecord::onRead();/*{{{*/
inline void SSRecord::onRead() { }
/*}}}*/
// inline error_t SSRecord::onWrite();/*{{{*/
inline error_t SSRecord::onWrite() {
    return SSNO_ERROR;
}
/*}}}*/
// Public: Overridables }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTREC_HPP_DEFINED__ */
