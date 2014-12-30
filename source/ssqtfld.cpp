/**
 * @file
 * Defines the SSField class.
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
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqtshrd.hpp"
#include "ssqtfld.hpp"
#include "sql/column.hpp"

/* ===========================================================================
 * SSField class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Constructors & Destructor
 * ------------------------------------------------------------------------ */

// SSField::SSField(const SSField &field);/*{{{*/
SSField::SSField(const SSField &field) : value(field.value), m_column(NULL)
{
    m_column = ((field.m_column) ? field.m_column->retain() : NULL);
}
/*}}}*/
// SSField::SSField(ss::column_t *column, const QVariant &val);/*{{{*/
SSField::SSField(ss::column_t *column, const QVariant &val) : value(val),
    m_column(column)
{
    m_column = (column ? column->retain() : NULL);
}
/*}}}*/
// SSField::~SSField();/*{{{*/
SSField::~SSField()
{
    if (valid()) m_column->release();
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Attributes
 * ------------------------------------------------------------------------ */

// bool SSField::autoValue() const;/*{{{*/
bool SSField::autoValue() const {
    return (valid() && m_column->autoValue());
}
/*}}}*/
// bool SSField::isIndex() const;/*{{{*/
bool SSField::isIndex() const {
    return (valid() ? m_column->indexed() : false);
}
/*}}}*/
// bool SSField::required() const;/*{{{*/
bool SSField::required() const {
    return (valid() && m_column->required());
}
/*}}}*/
// bool SSField::empty() const;/*{{{*/
bool SSField::empty() const
{
    if (!valid() || isNull()) return true;

    if ((m_column->dataType() == SS_DATA_TYPE_CHAR) ||
        (m_column->dataType() == SS_DATA_TYPE_TEXT))
        return asString().isEmpty();

    if (m_column->dataType() == SS_DATA_TYPE_BLOB)
        return asByteArray().isEmpty();

    return false;
}
/*}}}*/
// QString SSField::name() const;/*{{{*/
QString SSField::name() const
{
    return (valid() ? m_column->name : QString());
}
/*}}}*/
// size_t  SSField::size() const;/*{{{*/
size_t SSField::size() const {
    return (valid() ? m_column->length : 0);
}
/*}}}*/
// size_t  SSField::length() const;/*{{{*/
size_t SSField::length() const
{
    if (value.isValid() && valid())
    {
        if ((m_column->dataType() == SS_DATA_TYPE_TEXT) ||
            (m_column->dataType() == SS_DATA_TYPE_CHAR))
            return asString().length();

        if (m_column->dataType() == SS_DATA_TYPE_BLOB)
            return asByteArray().length();
    }
    return 0;
}
/*}}}*/
// size_t  SSField::precision() const;/*{{{*/
size_t  SSField::precision() const {
    return (valid() ? m_column->precision() : 0);
}
/*}}}*/
// uint SSField::type() const;/*{{{*/
uint SSField::type() const {
    return (valid() ? m_column->dataType() : 0);
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Overloaded Operators
 * ------------------------------------------------------------------------ */

// SSField& SSField::operator =(const SSField &field);/*{{{*/
SSField& SSField::operator =(const SSField &field)
{
    if (valid()) m_column->release();

    m_column = (field.valid() ? field.m_column->retain() : NULL);
    value    = field.value;

    return *this;
}
/*}}}*/

