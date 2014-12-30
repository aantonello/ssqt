/**
 * @file
 * Defines the column_ref class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 23, 2014
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
#include "colref.hpp"

/* ===========================================================================
 * Internal Constants
 * ======================================================================== */
#define SS_COLUMN_STEP_NAME     1
#define SS_COLUMN_STEP_DOT      2

/* ===========================================================================
 * column_ref class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Operations
 * ------------------------------------------------------------------------ */

// bool column_ref::parse(query_toker &toker, token &tk);/*{{{*/
bool column_ref::parse(query_toker &toker, token &tk)
{
    QList<token> tokenList;
    token tempToken;

    tokenList << tk;

    while (!toker.atEOF())
    {
        tempToken = toker.next();
        if (tempToken.type() == SS_TOKEN_TYPE_COMMA)
            break;
        else if (tempToken == "from")
        {
            toker.back(tempToken);
            break;
        }

        tokenList << tempToken;
    }

    if (tokenList.count() == 1)     /* Must be the column name. */
    {
        columnName = tokenList[0].stringRef();
        columnAlias = columnName;
        return true;
    }
    else
    {
        /* When we have more than one token the last one is probably the
         * column alias (or column name) depending on the preceeding token, if
         * any.
         */
        int index = tokenList.count() - 1;
        columnAlias = tokenList[index].stringRef();
        columnName  = columnAlias;

        /* When the previous token is a dot the last one is the column name
         * and, before the dot, is the table alias or table name.
         */
        if (tokenList[index--].type() == SS_TOKEN_TYPE_DOT)
        {
            tableAlias = tokenList[index--].stringRef();
            tableName  = tableAlias;
        }
    }

    /* Grab all information and put it in the reference field. */
    tempToken = tokenList.back();
    reference = QStringRef(toker.source(), (int)tk.position(),
                           (int)(tempTokan.startPos() + tempToken.length()));
    return true;
}
/*}}}*/

