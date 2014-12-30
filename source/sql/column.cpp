/**
 * @file
 * Defines the ss::column_t class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 11, 2014
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
#include "../ssqtshrd.hpp"
#include "column.hpp"

namespace ss {
/* ===========================================================================
 * column_t class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Properties
 * ------------------------------------------------------------------------ */

// void column_t::setType(QVariant::Type type);/*{{{*/
void column_t::setType(QVariant::Type type)
{
    switch (type)
    {
    case QVariant::Invalid:
        dataType(0);
        break;
    case QVariant::ByteArray:
        dataType(SS_DATA_TYPE_BLOB);
        break;
    case QVariant::Char:
        dataType(SS_DATA_TYPE_CHAR);
        break;
    case QVariant::Date:
        dataType(SS_DATA_TYPE_DATE);
        break;
    case QVariant::DateTime:
        dataType(SS_DATA_TYPE_DATETIME);
        break;
    case QVariant::Double:
        dataType(SS_DATA_TYPE_FLOAT);
        break;
    case QVariant::Int:
    case QVariant::LongLong:
    case QVariant::UInt:
    case QVariant::ULongLong:
        dataType(SS_DATA_TYPE_INT);
        break;
    case QVariant::String:
        dataType(SS_DATA_TYPE_TEXT);
        break;
    case QVariant::Time:
        dataType(SS_DATA_TYPE_TIME);
        break;
    default:
        dataType(0);
    }
}
/*}}}*/
// void column_t::precision(int precis);/*{{{*/
void column_t::precision(int precis)
{
    if (precis < 0)
        flags = (flags & 0x0000FFFF);       /* No precision information. */
    else
    {
        uint16_t number = (uint16_t)precis;
        flags |= (uint)((number << 16) & 0xFFFF0000);
    }
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Operations
 * ------------------------------------------------------------------------ */

// void column_t::reset(const QSqlField &field, const QSqlIndex &index = QSqlIndex());/*{{{*/
void column_t::reset(const QSqlField &field, const QSqlIndex &index)
{
    this->name   = field.name();
    this->length = field.length();
    setType( field.type() );

    this->flags = 0;

    if (field.isAutoValue()) flags |= SS_COLUMN_AUTO;
    if (field.isReadOnly()) flags |= SS_COLUMN_READONLY;
    if (field.requiredStatus() == QSqlField::Required)
        flags |= SS_COLUMN_REQUIRED;

    if (!index.isEmpty())
    {
        if (index.contains(this->name))
            flags |= SS_COLUMN_INDEXED;

        QSqlField indexedField = index.field(this->name);
        if (indexedField.isAutoValue())
            flags |= SS_COLUMN_PKEY;
    }

    this->precision( field.precision() );
}
/*}}}*/

};
