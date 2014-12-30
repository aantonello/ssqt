/**
 * @file
 * Defines the SSRecord class.
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
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqtshrd.hpp"
#include "ssqtfld.hpp"
#include "ssqtrec.hpp"

/* ===========================================================================
 * Local Variables
 * ======================================================================== */
static SSField s__emptyField;

/* ===========================================================================
 * SSRecord class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Record Attributes
 * ------------------------------------------------------------------------ */

// int SSRecord::indexOf(const QString &fieldName) const;/*{{{*/
int SSRecord::indexOf(const QString &fieldName) const
{
    size_t limit = count();

    /* We use two separate loops to speed up things a little bit. */
    if (m_prefix.isEmpty())
    {
        for (size_t i = 0; i < limit; ++i)
            if (!fieldName.compare(m_fields[i].name(), Qt::CaseInsensitive))
                return (int)i;
    }
    else
    {
        QString prefixedName(m_prefix);
        QString name;

        prefixedName.append(fieldName);

        for (size_t i = 0; i < limit; ++i)
        {
            name = m_fields[i].name();
            if (!prefixedName.compare(name, Qt::CaseInsensitive) ||
                !fieldName.compare(name, Qt::CaseInsensitive))
                return (int)i;
        }
    }
    return -1;
}
/*}}}*/
// SSField& SSRecord::field(uint index);/*{{{*/
SSField& SSRecord::field(uint index)
{
    return ((index >= count()) ? s__emptyField : m_fields[index]);
}
/*}}}*/

