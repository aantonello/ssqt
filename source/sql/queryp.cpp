/**
 * @file
 * Defines the query_parser class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 22, 2014
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
#include "qtoker.hpp"
#include "queryp.hpp"

/* ===========================================================================
 * Local Constants
 * ======================================================================== */
static QString const s__select("select");
static QString const s__update("update");
static QString const s__delete("delete");
static QString const s__insert("insert");
static QString const s__replace("replace");
static QString const s__from("from");
static QString const s__where("where");
static QString const s__all("*");

namespace ss {

/* ===========================================================================
 * query_parser class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Operations
 * ------------------------------------------------------------------------ */

// bool query_parser::parse(const QString &stmt);/*{{{*/
bool query_parser::parse(const QString &stmt)
{
    QString strQuery( stmt.trimmed() );     /* Start removing unwanted white spaces. */

    if (strQuery.startsWith(s__select, Qt::CaseInsensitive))
        return parse_select( strQuery );     /* Continue. */
    else if (strQuery.startWith(s__update, Qt::CaseInsensitive))
        m_queryType = SS_QUERY_TYPE_UPDATE;
    else if (strQuery.startsWith(s__delete, Qt::CaseInsensitive))
        m_queryType = SS_QUERY_TYPE_DELETE;
    else if (strQuery.startsWith(s__insert, Qt::CaseInsensitive))
        m_queryType = SS_QUERY_TYPE_INSERT;
    else if (strQuery.startsWith(s__replace, Qt::CaseInsensitive))
        m_queryType = SS_QUERY_TYPE_REPLACE;    /* Supported on some drivers. */
    else
        return false;       /* Unknown statement type. */

    return true;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Private: Operations
 * ------------------------------------------------------------------------ */

// bool query_parser::parse_select(const QString &stmt);/*{{{*/
bool query_parser::parse_select(const QString &stmt)
{
    query_toker toker(stmt, s__select.length());
    token tk;

    while (!toker.atEOF())
    {
        tk = toker.next();
        if (!tk.valid())
            break;

        if (SS_TOKEN_TYPE_SPACE == tk.type())
            continue;

        if ((SS_TOKEN_TYPE_WORD == tk.type()) && ((tk == s__from) || (tk == s__all)))
            break;
    }
    return true;
}
/*}}}*/

};  /* namespace ss */
