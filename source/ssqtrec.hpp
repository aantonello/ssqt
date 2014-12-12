/**
 * @file
 * Declares the SSRecordT class template.
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

/**
 * Class template representing a data record.
 * Instances of this class template are backed by a list of \c SSSField
 * objects. Each \c SSField is a copy of the original. Despite that, each \c
 * SSField has a reference to the original data extracted from the database.
 * This means that changing the value of one instance will be reflected on all
 * copies.
 *
 * \c SSRecordT is provided as a template so you can build a structure or
 * class to hold the data using standard Qt properties or more clever
 * implementations. You can bind the data with your structure or class in the
 * #reset() member function. The other way around, to pass the data of your
 * structure or class to the underling \c SSField object can be done in the
 * #commit() member function.
 * \par Default Prefix
 *
 * Some people like to prefix column's names with some common characters. For
 * example, a "users" table can have all its column's prefixed with the
 * substring "user_". Then the column "name" would become "user_name", the
 * column "age" would become "user_age", and so on. The \c SSRecordT has
 * a feature around this usage. When opening a query or table you can define
 * a default prefix for all columns loaded. This is done in the
 * SSRecordsetT::defaultPrefix() method. When defined, columns can be searched
 * by its suffix name only. That is, the \c SSRecordT::field(const QString&)
 * method will accept the string "name" and recognize it as the column
 * "user_name".
 * \tparam _Typ Your base class or structure specialized to use the data of
 * this record. Must provide a default constructor that will be called on any
 * constructor of this template.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
template <typename _Typ>
class SSRecordT : public _Typ
{
    typedef super _Typ;             /**< The super type. */

public:
    /** @name Constructors & Destructors */ //@{
    // SSRecordT();/*{{{*/
    /**
     * Default constructor.
     * Builds an empty \c SSRecordT object. This constructor will call
     * #reset() even so there is no data to load.
     * @since 1.2
     **/
    SSRecordT() : super(), m_fields() {
        reset();
    }
    /*}}}*/
    // SSRecordT(const SSRecordT<_Typ> &record);/*{{{*/
    /**
     * Copy constructor.
     * @param record Another \c SSRecordT instance of the same type. All
     * fields of it will be copied. Which, in the end, has only references to
     * the original fields.
     * @remarks The #reset() member function is called to provide the
     * specialization to load the data.
     * @since 1.2
     **/
    SSRecordT(const SSRecordT<_Typ> &record) :
        super(), m_fields(record.m_fields), m_prefix(record.m_prefix)
    { reset(); }
    /*}}}*/
    // SSRecordT(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString());/*{{{*/
    /**
     * Builds the \c SSRecordT instance with data from the provided record.
     * @param record \c QSqlRecord object with the data. It will be used to
     * load the columns in the list of fields.
     * @param index \c QSqlIndex with the indexes of the query or table.
     * Optional.
     * @param prefix Optional, Default prefix for columns names.
     * @remarks This constructor is not meant to be called by the user. It is
     * used to load a record from the \c SSRecordsetT template class.
     * @note The #reset() method will be called after the list of fields
     * has been mounted.
     * @since 1.2
     **/
    SSRecordT(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(),
              const QString &prefix = QString()) : super(), m_prefix(prefix)
    { apply(record, index, prefix); }
    /*}}}*/
    //@}
public:
    /** @name Record Attributes */ //@{
    // size_t count() const;/*{{{*/
    /**
     * Retrieves the number of fields in this record.
     * @return A unsigned long integer counting the number of fields in this
     * record.
     * @since 1.2
     **/
    size_t count() const {
        return m_fields.count();
    }
    /*}}}*/
    // bool   empty() const;/*{{{*/
    /**
     * Checks whether this record is empty (has no columns).
     * @returns \b true when this record has no fields. Otherwise \b false.
     * @since 1.2
     **/
    bool   empty() const {
        return m_fields.isEmpty();
    }
    /*}}}*/
    // bool   has(const QString &fieldName) const;/*{{{*/
    /**
     * Checks whether this record has a field named \e fieldName.
     * @param fieldName \c QString with the field name to be queried. If
     * a default prefix was defined, this parameter can be only the suffix
     * part of the column name.
     * @return \b true if the field exists, otherwise \b false.
     * @since 1.2
     **/
    bool has(const QString &fieldName) const {
        return (indexOf(fieldName) >= 0);
    }
    /*}}}*/
    // int    indexOf(const QString &fieldName) const;/*{{{*/
    /**
     * Query the index of a field by its name.
     * @param fieldName \c QString with the field name to be queried. If
     * a default prefix was defined, this parameter can be only the suffix
     * part of the column name.
     * @return A value equals to or greater than zero is the field index.
     * A value less than zero when the name was not found.
     * @since 1.2
     **/
    int indexOf(const QString &fieldName) const
    {
        size_t limit = count();

        if (m_prefix.isEmpty())
        {
            for (size_t i = 0; i < limit; ++i)
            {
                if (fieldName == m_fields.at(i).name())
                    return (int)i;
            }
        }
        else
        {
            QString prefixedName(m_prefix).append(fieldName);
            SSField field;

            for (size_t i = 0; i < limit; ++i)
            {
                field = m_fields.at(i);
                if ((fieldName == field.name()) || (prefixedName == field.name()))
                    return (int)i;
            }
        }
        return -1;
    }
    /*}}}*/
    // SSField& field(uint index);/*{{{*/
    /**
     * Gets a non-const reference to a field in this record.
     * @param index Zero based index of the field.
     * @return A non-const reference to the specified field. If the value of
     * \a index is invalid an empty (invalid) \c SSField object will be
     * returned.
     * @since 1.2
     **/
    SSField& field(uint index) {
        return ((index >= count()) ? SSField::invalidField : m_list[index]);
    }
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
    SSField& field(const QString &fieldName) {
        int index = indexOf(fieldName);
        return field(index);
    }
    /*}}}*/
    // const SSField& field(uint index) const;/*{{{*/
    /**
     * Gets a const reference to a field in this record.
     * @param index Zero based index of the field.
     * @return A const reference to the specified field. If the value of
     * \a index is invalid an empty (invalid) \c SSField object will be
     * returned.
     * @since 1.2
     **/
    const SSField& field(uint index) const {
        return ((index >= count()) ? SSField::invalidField : m_list.at(index));
    }
    /*}}}*/
    // const SSField& field(const QString &fieldName) const;/*{{{*/
    /**
     * Gets a const reference to a field in this record.
     * @param fieldName \c QString with the field name to be retrieved. If
     * a default prefix was defined, this parameter can be only the suffix
     * part of the column name.
     * @return A const reference to the specified field. If the value of
     * \a fieldName is invalid (not found in the list of fields) an empty
     * (invalid) field will be returned.
     * @since 1.2
     **/
    const SSField& field(const QString &fieldName) const {
        int index = indexOf(fieldName);
        return field(index);
    }
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // size_t  apply(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString());/*{{{*/
    /**
     * Reset this object to read the data in the passed record.
     * @param record \c QSqlRecord object having the data to be copied.
     * @param index Optional. List of indexes of the origin table. Used to
     * properly configure the fields.
     * @param prefix Optional. Common prefix of the fields names. If not
     * passed no prefix will be used.
     * @return The number of fields read.
     * @remarks This member function is called from the result of \c
     * SSRecordsetT template class in response to a read operation.
     * @since 1.2
     **/
    size_t  apply(const QSqlRecord &record, const QSqlIndex &index = QSqlIndex(), const QString &prefix = QString())
    {
        m_fields.clear();
        m_prefix = prefix;

        int limit = record.count();
        QSqlField qtField;

        for (int i = 0; i < limit; ++i)
        {
            qtField = record.field(i);
            m_fields.append(SSField(qtField, index));
        }

        reset();
        return (size_t)m_fields.count();
    }
    /*}}}*/
    // error_t commit(QSqlRecord *record);/*{{{*/
    /**
     * Commit changed data back to the origin record.
     * @param record \c QSqlRecord to be populated with the data in this
     * object.
     * @returns \c SSNO_ERROR when everything goes Ok. Otherwise, an error
     * code will be returned.
     * @remarks This operation is called from the owner \c SSRecordsetT
     * instance when it needs to update the database. This operation calls the
     * virtual function #commit() and then populates the \a record parameter
     * with the data in the fields. If the \c commit() is overloaded by the
     * user and returns an error code, the operation is aborted.
     * @since 1.2
     **/
    error_t commit(QSqlRecord *record)
    {
        error_t result = commit();

        if (result != SSNO_ERROR) return result;
        SSField field;
        size_t  limit = count();

        for (size_t i = 0; i < limit; ++i)
        {
            field = m_fields.at(i);
            record->setValue(field.name(), field.value());
        }
        return result;
    }
    /*}}}*/
    // void    clear();/*{{{*/
    /**
     * Clear the list of fields of this record.
     * @since 1.2
     **/
    void clear() {
        m_list.clear();
    }
    /*}}}*/
    //@}
public:
    /** @name Overloaded Operators */ //@{
    // SSRecordT<_Typ>& operator =(const SSRecordT<_Typ> &record);/*{{{*/
    /**
     * Copy operator.
     * @param record Other \c SSRecordT instance to copy its data.
     * @return \b this.
     * @since 1.2
     **/
    SSRecordT<_Typ>& operator =(const SSRecordT<_Typ> &record) {
        m_fields = record.m_fields;
        m_prefix = record.m_prefix;
        return *this;
    }
    /*}}}*/
    // SSField& operator()(uint index);/*{{{*/
    /**
     * Gets a reference to a field of this record.
     * @param index Zero based index of the field.
     * @return A non-const reference to the specified field. If the value of
     * \a index is invalid an empty (invalid) \c SSField object will be
     * returned.
     * @remarks Internally this operator calls #field(uint).
     * @since 1.2
     **/
    SSField& operator()(uint index) {
        return field(index);
    }
    /*}}}*/
    // SSField& operator()(const QString &fieldName);/*{{{*/
    /**
     * Gets a reference to a field of this record.
     * @param fieldName \c QString with the field name to be retrieved. If
     * a default prefix was defined, this parameter can be only the suffix
     * part of the column name.
     * @return A non-const reference to the specified field. If the value of
     * \a fieldName is invalid (not found in the list of fields) an empty
     * (invalid) field will be returned.
     * @remarks Internally this operator calls #field(const QString&).
     * @since 1.2
     **/
    SSField& operator()(const QString &fieldName) {
        return field(fieldName);
    }
    /*}}}*/
    //@}
protected:
    /** @name Overridables */ //@{
    // virtual void reset();/*{{{*/
    /**
     * Called so the implementors can reset its member variables.
     * This operation is called after the #apply() function resets the
     * internal list of fields.
     * @note The default implementation does nothing.
     * @since 1.2
     **/
    virtual void reset() {
    }
    /*}}}*/
    // virtual error_t commit();/*{{{*/
    /**
     * Called so the implementors update the list of fields.
     * This operation is called before the #commit(QSqlRecord*) member
     * function pass the fields values to the \e record argument.
     * @return Function should return \c SSNO_ERROR on success. An error code
     * on failure. When an error code is returned the \c commit(QSqlRecord*)
     * operation is aborted. The result of that function will be the same as
     * this one.
     * @note The default implementation simply returns \c SSNO_ERROR.
     * @since 1.2
     **/
    virtual error_t commit() {
        return SSNO_ERROR;
    }
    /*}}}*/
    //@}
protected:
    /** @name Data Members */ //@{
    QList<SSField> m_fields;            /**< List of fields in this record. */
    QString m_prefix;                   /**< Default columns prefix name.   */
    //@}
};

/**
 * Dummy structure allowing the creation of \c SSRecord instances.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
typedef struct ss_record_t {
    intptr_t noValue;
} record_t;

/**
 * Default \c SSRecordT implementation.
 * Uses the dummy \c record_t structure as it biases.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
typedef SSRecordT<record_t> SSRecord;

#endif /* __SSQTREC_HPP_DEFINED__ */
