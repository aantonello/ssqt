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

// SSField::SSField(const QString &fieldName = QString(), QVariant::Type type = QVariant::Invalid);/*{{{*/
SSField::SSField(const QString &fieldName, QVariant::Type type) :
    m_column(new ss::column_t(fieldName, type))
{
}
/*}}}*/
// SSField::SSField(const SSField &field);/*{{{*/
SSField::SSField(const SSField &field) :
    m_column(field.m_column->retain())
{
}
/*}}}*/
// SSField::SSField(const QSqlField &field);/*{{{*/
SSField::SSField(const QSqlField &field) : m_column(new ss::column_t(field))
{
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

// bool SSField::valid() const;/*{{{*/
bool SSField::valid() const
{
    return (m_column != NULL);
}
/*}}}*/
// bool SSField::autoValue() const;/*{{{*/
bool SSField::autoValue() const
{
    return (valid() && m_column->autoValue());
}
/*}}}*/
// bool SSField::readOnly() const;/*{{{*/
bool SSField::readOnly() const
{
    return (valid() && m_column->readOnly());
}
/*}}}*/
// bool SSField::required() const;/*{{{*/
bool SSField::required() const
{
    return (valid() && m_column->required());
}
/*}}}*/
// bool SSField::isNull() const;/*{{{*/
bool SSField::isNull() const
{
    return (valid() && !m_column->isNull());
}
/*}}}*/
// bool SSField::empty() const;/*{{{*/
bool SSField::empty() const
{
    if (!valid()) return true;

    if ((m_column->dataType() == SS_DATA_TYPE_CHAR) ||
        (m_column->dataType() == SS_DATA_TYPE_TEXT) ||
        (m_column->dataType() == SS_DATA_TYPE_TIME) ||
        (m_column->dataType() == SS_DATA_TYPE_DATE) ||
        (m_column->dataType() == SS_DATA_TYPE_DATETIME))
        return this->asString().isEmpty();

    return false;
}
/*}}}*/
// QString SSField::name() const;/*{{{*/
QString SSField::name() const
{
    return (valid() ? m_column->name : QString());
}
/*}}}*/
// size_t  SSField::length() const;/*{{{*/
size_t  SSField::length() const
{
    return (valid() ? m_column->length : 0);
}
/*}}}*/
// size_t  SSField::precision() const;/*{{{*/
size_t  SSField::precision() const
{
    return (valid() ? m_column->precision() : 0);
}
/*}}}*/
// uint SSField::type() const;/*{{{*/
uint SSField::type() const
{
    return (valid() ? m_column->dataType() : 0);
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Properties
 * ------------------------------------------------------------------------ */

// QVariant SSField::value() const;/*{{{*/
QVariant SSField::value() const
{
    return (valid() ? m_column->value : QVariant());
}
/*}}}*/
// void SSField::value(const QVariant &val);/*{{{*/
void SSField::value(const QVariant &val)
{
    if (!valid()) return;
    m_column->value = val;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Value Conversion
 * ------------------------------------------------------------------------ */


/* ---------------------------------------------------------------------------
 * Public: Overloaded Operators
 * ------------------------------------------------------------------------ */

// SSField& SSField::operator =(const SSField &field);/*{{{*/
SSField& SSField::operator =(const SSField &field)
{
    if (valid()) m_column->release();

    if (field.valid())
        m_column = new ss::column_t(*(field.m_column));
    else
        m_column = NULL;

    return *this;
}
/*}}}*/

