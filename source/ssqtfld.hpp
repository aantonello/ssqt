/**
 * @file
 * Declares the SSField class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 09, 2014
 * @since  Super Simple for Qt 5 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTFLD_HPP_DEFINED__
#define __SSQTFLD_HPP_DEFINED__

namespace ss {
    class column_t;
};

/**
 * \ingroup ssqt_dao
 * Represents a column in the database or table.
 * A \c SSField object keeps its data apart of the original \c QSqlField
 * object. As of this the \c SSField class is much simpler. A \c SSField
 * object has only a reference to its column definition. All \c SSField for
 * the same column share this reference, saving much memory.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class SSField
{
public:
    /** @name Constructors & Destructor */ //@{
    // SSField(const SSField &field);/*{{{*/
    /**
     * Copy constructor.
     * @param field Another field to copy its properties and value.
     * @remarks An \c SSField object keeps its data localy and share it's
     * column information with all others \c SSField objects pointing to the
     * same column in a \c SSRecord object.
     * @since 1.2
     **/
    SSField(const SSField &field);
    /*}}}*/
    // SSField(ss::column_t *column, const QVariant &val);/*{{{*/
    /**
     * Constructs the field object with the specified column and value.
     * @param column Pointer to the column information for this field. Cannot
     * be \b NULL.
     * @param val The value of this field.
     * @since 1.2
     **/
    SSField(ss::column_t *column, const QVariant &val);
    /*}}}*/
    // SSField(const QSqlField &field, const QSqlIndex &index = QSqlIndex());/*{{{*/
    /**
     * Assignment constructor.
     * @param field The original \c QSqlField object.
     * @param index Index of the original table. Used to recognized this field
     * as index or not.
     * @since 1.2
     **/
    SSField(const QSqlField &field, const QSqlIndex &index = QSqlIndex());
    /*}}}*/
    // virtual ~SSField();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    virtual ~SSField();
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // bool valid() const;/*{{{*/
    /**
     * Checks the validity of this object.
     * @returns \b true when this object is valid. \b false otherwise.
     * @remarks The object becomes invalid when its column reference doesn't
     * exists.
     * @since 1.2
     **/
    bool valid() const;
    /*}}}*/
    // bool autoValue() const;/*{{{*/
    /**
     * Retrieves when the column represented by this field object has its
     * value authomatic generated by the database engine.
     * @returns \b true when the value is auto-generated. \b false otherwise.
     * @remarks The result of this operation is dependent of the database
     * driver and not always the returned information is accurate.
     * @note A column with auto-generated value is usually the table's primary
     * key.
     * @since 1.2
     **/
    bool autoValue() const;
    /*}}}*/
    // bool isIndex() const;/*{{{*/
    /**
     * Retrieves wheter the column referenced by this field participates in
     * the tables primary key index.
     * @returns \b true when the column participates in the primary key index.
     * Otherwise \b false.
     * @since 1.2
     **/
    bool isIndex() const;
    /*}}}*/
    // bool required() const;/*{{{*/
    /**
     * Checks whether a value for this field is required.
     * @return \b true when the user is obligated to set a value for this
     * field's column. Otherwise \b false.
     * @remarks The result of this operation is meaningful only in new records
     * when the field has no value yet.
     * @since 1.2
     **/
    bool required() const;
    /*}}}*/
    // bool isNull() const;/*{{{*/
    /**
     * Checks whether the value of this field's column is null.
     * @return \b true if the value has no meaning. Otherwise \b false.
     * @remarks Every database driver treats null values different. The Qt
     * library translates the database null value to the C++ \b NULL constant.
     * When a null field value is converted to other type, like an \b int or
     * \b QString the operation will return a suitable value like a \b
     * 0 (zero) or empty string.
     * @since 1.2
     **/
    bool isNull() const;
    /*}}}*/
    // bool empty() const;/*{{{*/
    /**
     * Checks whether the value of this field's column is empty.
     * @return \b true if the value is empty, otherwise \b false.
     * @remarks This operation is meaningful only when the data type of the
     * column is \c SS_DATA_TYPE_TEXT or \c SS_DATA_TYPE_BLOB, where the value
     * can be non null but still have an empty string or no binary data. This
     * function will take the following decisions:
     * - When this field is null (SSField::isNull() returns \b true), this
     *   operation returns \b true either.
     * - When the column is not of the types \c SS_DATA_TYPE_TEXT nor \c
     *   SS_DATA_TYPE_BLOB the operation returns \b false.
     * - The method checks the length of the data in the SSField::value member
     *   converting it to \c QString or \c QByteArray as needed, returning \b
     *   true if the convertion generates an empty object or \b false when
     *   not.
     * .
     * @since 1.2
     **/
    bool empty() const;
    /*}}}*/
    // QString name() const;/*{{{*/
    /**
     * Retrieves the column's name of this field.
     * The column name can be defined in the database, by the source table
     * structure. It can also be defined by the \c SELECT statement, using an
     * \c ALIAS keyword.
     * @returns \c QString with this field name. When this field is invalid
     * (SSField::valid() returns \b false) the result will be an empty \c
     * QString object.
     * @since 1.2
     **/
    QString name() const;
    /*}}}*/
    // size_t  size() const;/*{{{*/
    /**
     * Retrieves the size of the column as defined in the database.
     * Some columns type can have its length (or maximum length) defined on
     * its structure. This is the value returned by this method.
     * @returns The size of the data in this column. When this value cannot be
     * determined or the column type does not have a defined length the result
     * will be zero.
     * @since 1.2
     **/
    size_t  size() const;
    /*}}}*/
    // size_t  length() const;/*{{{*/
    /**
     * Retrieves this field's value length.
     * @return The length of the data held in this field when the column is of
     * type \c SS_DATA_TYPE_TEXT or \c SS_DATA_TYPE_BLOB. For other types the
     * result is always zero.
     * @remarks When the column type is \c SS_DATA_TYPE_TEXT the result is
     * counted in characters. When the column type is \c SS_DATA_TYPE_BLOB the
     * result is counted as bytes.
     * @since 1.2
     **/
    size_t  length() const;
    /*}}}*/
    // size_t  precision() const;/*{{{*/
    /**
     * Retrieves the precision of this field's value.
     * @returns An integer with this field's value precision.
     * @remarks This information is useful only for numeric columns that has
     * floating point data. For others types, the result of this operation is
     * always zero.
     * @since 1.2
     **/
    size_t  precision() const;
    /*}}}*/
    // uint    type() const;/*{{{*/
    /**
     * This field's column type.
     * @return A type constant declared in the @ref ssqt_dao_constants module.
     * @remarks When the member function #valid() returns \b false the result
     * of this operation is zero.
     * @since 1.2
     **/
    uint type() const;
    /*}}}*/
    //@}
public:
    /** @name Value Conversion */ //@{
    // QByteArray toByteArray() const;/*{{{*/
    /**
     * Gets the value of this field as a byte array.
     * @return A \c QByteArray object with the value of this field in binary
     * format. If this field is \b NULL or empty the result will be an empty
     * \c QByteArray object.
     * @remarks Can be used on columns of any type.
     * @since 1.2
     **/
    QByteArray toByteArray() const;
    /*}}}*/
    // QString    toString() const;/*{{{*/
    /**
     * Gets the value of this field as a string.
     * @return A \c QString object with the value of this field.
     * @remarks When the field value is numeric it will be converted to its
     * textual representation. That is, the number 10.1 will be converted to
     * the string "10.1".
     * @note The conversion doesn't take locale into account.
     * @since 1.2
     **/
    QString    toString() const;
    /*}}}*/
    // double     toFloat() const;/*{{{*/
    /**
     * Retrieves this field's value in a floating point number.
     * @return The value os the field as a \b double.
     * @remarks When the field type is not numeric the result is zero.
     * @since 1.2
     **/
    double     toFloat() const;
    /*}}}*/
    // int64_t    toLong() const;/*{{{*/
    /**
     * Retrieves this field's value as a 64 bits integer.
     * @returns The \c int64_t value of this field.
     * @remarks When the field type is not numeric the result is zero.
     * @note "Long" here have the same meaning as in Java where \b long is
     * a 64 bits integer.
     * @since 1.2
     **/
    int64_t    toLong() const;
    /*}}}*/
    // int        toInt() const;/*{{{*/
    /**
     * Retrieves this field's value as an integer number.
     * @return The value of this field as an \b int.
     * @remarks When the field type is not numeric the result is zero.
     * @since 1.2
     **/
    int        toInt() const;
    /*}}}*/
    // QDateTime  toDateTime(const char *format = SS_DB_DATETIME_FORMAT) const;/*{{{*/
    /**
     * Get the value of this field as a \c QDateTime object.
     * @param format The format of the value stored in the database. Usually
     * this is equals to \c SS_DB_DATETIME_FORMAT value. Can be \b NULL. In
     * this case the operation will not try to parse the value.
     * @returns When succeeded the result is a \c QDateTime object with the
     * date and time retrieved from this field's value. Otherwise a default
     * constructed \c QDateTime object will be returned.
     * @since 1.2
     **/
    QDateTime  toDateTime(const char *format = SS_DB_DATETIME_FORMAT) const;
    /*}}}*/
    // QDate      toDate(const char *format = SS_DB_DATE_FORMAT) const;/*{{{*/
    /**
     * Retrieves date information from this field's value.
     * @param format The format of the value stored in the database. Usually
     * this is equals to \c SS_DB_DATE_FORMAT value. Can be \b NULL. In
     * this case the operation will not try to parse the value.
     * @returns When succeeded the result is a \c QDate object with the
     * date and time retrieved from this field's value. Otherwise a default
     * constructed \c QDate object will be returned.
     * @since 1.2
     **/
    QDate      toDate(const char *format = SS_DB_DATE_FORMAT) const;
    /*}}}*/
    // QTime      toTime(const char *format = SS_DB_TIME_FORMAT) const;/*{{{*/
    /**
     * Retrieves time information from this field's value.
     * @param format The format of the value stored in the database. Usually
     * this is equals to \c SS_DB_TIME_FORMAT value. Can be \b NULL. In
     * this case the operation will not try to parse the value.
     * @returns When succeeded the result is a \c QTime object with the
     * date and time retrieved from this field's value. Otherwise a default
     * constructed \c QTime object will be returned.
     * @since 1.2
     **/
    QTime      toTime(const char *format = SS_DB_TIME_FORMAT) const;
    /*}}}*/
    // QDateTime  toTimestamp() const;/*{{{*/
    /**
     * Retrieves date and time information from this field's value.
     * The information must be stored in a column of type \c
     * SS_DATA_TYPE_STAMP or \c SS_DATA_TYPE_INT.
     * @return A \c QDateTime object resulting of this field's value
     * conversion.
     * @note No time zone or offset is applied to the original value. It will
     * be converted as is.
     * @since 1.2
     **/
    QDateTime  toTimestamp() const;
    /*}}}*/
    //@}
public:
    /** @name Overloaded Operators */ //@{
    // operator bool() const;/*{{{*/
    /**
     * Cast this object to a \b bool type.
     * The resulting value is the same as calling the function #isNull() with
     * its result inverted. That is, when \c isNull() returns \b true this
     * operator returns \b false. When \c isNull() returns \b false this
     * operator returns \b true. This is a shortcut operation that can be used
     * in constructions like:
     * ~~~~~~~~~~~~{.cpp}
     * if (field) { ... }
     * ~~~~~~~~~~~~
     * Is the same as:
     * ~~~~~~~~~~~~{.cpp}
     * if (!field.isNull()) { ... }
     * ~~~~~~~~~~~~
     * @since 1.2
     **/
    operator bool() const;
    /*}}}*/
    // bool operator ==(const SSField &field) const;/*{{{*/
    /**
     * Compares two \c SSField objects for equality.
     * @param field \c SSField object to compare with this one.
     * @returns \b true when the objects are equals. \b false otherwise.
     * @remarks Two fields are equal when they point to the same column
     * definition and has the same data.
     * @since 1.2
     **/
    bool operator ==(const SSField &field) const;
    /*}}}*/
    // SSField& operator =(const SSField &field);/*{{{*/
    /**
     * Copy operator.
     * @param field Another \c SSField instance to copy.
     * @returns \b this.
     * @since 1.2
     **/
    SSField& operator =(const SSField &field);
    /*}}}*/
    //@}
public:
    QVariant value;                     /**< Value is public available.     */

private:
    ss::column_t *m_column;             /**< Column information.            */
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Public: Attributes {{{
 * ------------------------------------------------------------------------ */
// inline bool SSField::valid() const;/*{{{*/
inline bool SSField::valid() const {
    return (m_column != NULL);
}
/*}}}*/
// inline bool SSField::isNull() const;/*{{{*/
inline bool SSField::isNull() const {
    return !value.isValid();
}
/*}}}*/
// Public: Attributes }}}
/* ---------------------------------------------------------------------------
 * Public: Value Conversion {{{
 * ------------------------------------------------------------------------ */
// inline QByteArray SSField::toByteArray() const;/*{{{*/
inline QByteArray SSField::toByteArray() const {
    return value.toByteArray();
}
/*}}}*/
// inline QString    SSField::toString() const;/*{{{*/
inline QString SSField::toString() const {
    return value.toString();
}
/*}}}*/
// inline double     SSField::toFloat() const;/*{{{*/
inline double SSField::toFloat() const {
    return value.toDouble();
}
/*}}}*/
// inline int64_t    SSField::toLong() const;/*{{{*/
inline int64_t SSField::toLong() const {
    return value.toLongLong();
}
/*}}}*/
// inline int        SSField::toInt() const;/*{{{*/
inline int SSField::toInt() const {
    return value.toInt();
}
/*}}}*/
// inline QDateTime  SSField::toDateTime(const char *format = SS_DB_DATETIME_FORMAT) const;/*{{{*/
inline QDateTime SSField::toDateTime(const char *format) const {
    return ((format) ? QDateTime::fromString(toString(), format) : value.toDateTime());
}
/*}}}*/
// inline QDate      SSField::toDate(const char *format = SS_DB_DATE_FORMAT) const;/*{{{*/
inline QDate SSField::toDate(const char *format) const {
    return ((!format) ? value.toDate() : QDate::fromString(toString(), format));
}
/*}}}*/
// inline QTime      SSField::toTime(const char *format = SS_DB_TIME_FORMAT) const;/*{{{*/
inline QTime SSField::toTime(const char *format) const {
    return ((!format) ? value.toTime() : QTime::fromString(toString(), format));
}
/*}}}*/
// inline QDateTime  SSField::toTimestamp() const;/*{{{*/
inline QDateTime SSField::toTimestamp() const {
    return QDateTime::fromMSecsSinceEpoch((qint64)toLong());
}
/*}}}*/
// Public: Value Conversion }}}
/* ---------------------------------------------------------------------------
 * Overloaded Operators {{{
 * ------------------------------------------------------------------------ */
// inline SSField::operator bool() const;/*{{{*/
inline SSField::operator bool() const {
    return !isNull();
}
/*}}}*/
// inline bool SSField::operator ==(const SSField &field) const;/*{{{*/
inline bool SSField::operator ==(const SSField &field) const {
    return ((m_column == field.m_column) && (value == field.value));
}
/*}}}*/
// Overloaded Operators }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTFLD_HPP_DEFINED__ */
