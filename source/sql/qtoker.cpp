/**
 * @file
 * Defines the query_toker class.
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

/* ===========================================================================
 * query_toker class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Static Data Members
 * ------------------------------------------------------------------------ */
QChar const token::backTick('`');
QChar const token::openExpr('(');
QChar const token::closeExpr(')');
QChar const token::openBrace('[');
QChar const token::closeBrace(']');
QChar const token::singleQuote('\'');
QChar const token::doubleQuote('"');
QChar const token::comma(',');
QChar const token::underscore('_');
QChar const token::dot('.');

/* ---------------------------------------------------------------------------
 * Public: Operations
 * ------------------------------------------------------------------------ */

// token query_toker::next();/*{{{*/
token query_toker::next()
{
    if (atEOF()) return token();

    QChar qchar = m_stmt.at(m_current++);

    if (qchar.isSpace())
        return match_spaces();

    if (qchar == comma)             /* Comma is a standard SQL separator. */
        return token(&m_stmt, (m_current - 1), 1, SS_TOKEN_TYPE_COMMA);

    if (qchar == dot)               /* Dot operator character. */
        return token(&m_stmt, (m_current - 1), 1, SS_TOKEN_TYPE_DOT);

    if (qchar == openExpr)          /* Sub expression. */
        return match_sub_expr();

    /* Identifiers can be enclosed in backticks or square brackets. */
    if ((qchar == backTick) || (qchar == openBrace))
        return match_until_char(((qchar == backTick) ? qchar : closeBrace), SS_TOKEN_TYPE_IDENT);

    /* We can have literal strings also. */
    if ((qchar == singleQuote) || (qchar == doubleQuote))
        return match_until_char(qchar, SS_TOKEN_TYPE_LITERAL);

    /* Symbols can be composed by more than one character. */
    if (qchar.isSymbol())
        return match_symbol();

    /* Everything else is handled as a identifier. */
    return match_word();
}
/*}}}*/
// bool  query_toker::back(size_t count);/*{{{*/
bool query_toker::back(size_t count)
{
    if ((count > m_current) || ((m_current - count) < m_start))
        return false;

    m_current -= count;
    return true;
}
/*}}}*/
// bool  query_toker::back(const token &tk);/*{{{*/
bool query_toker::back(const token &tk)
{
    if (!tk.valid() || (tk.startPos() < m_start))
        return false;

    m_current = tk.startPos();
    return true;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Private: Implementation
 * ------------------------------------------------------------------------ */

// token query_toker::match_spaces();/*{{{*/
token query_toker::match_spaces()
{
    size_t start = m_current - 1;

    while (!atEOF() && m_stmt.at(m_current).isSpace())
        m_current++;

    return token(&m_stmt, start, (m_current - start), SS_TOKEN_TYPE_SPACE);
}
/*}}}*/
// token query_toker::match_symbol();/*{{{*/
token query_toker::match_symbol()
{
    size_t start = m_current - 1;

    while (!atEOF())
    {
        QChar qchar = m_stmt.at(m_current);
        if (qchar.isSymbol() && !qchar.isSpace() &&
            (qchar != singleQuote) && (qchar != doubleQuote) &&
            (qchar != backTick) && (qchar != openBrace) &&
            (qchar != openExpr))
            m_current++;
        else
            break;
    }
    return token(&m_stmt, start, (m_current - start), SS_TOKEN_TYPE_SYMBOL);
}
/*}}}*/
// token query_toker::match_sub_expr();/*{{{*/
token query_toker::match_sub_expr()
{
    size_t start = (m_current - 1);

    while (!atEOF())
    {
        QChar qchar = m_stmt.at(m_current++);

        /* We can have expressions inside expressions. Also, we must be aware
         * that the user can place parentheses inside literal strings. So we
         * must handle literal strings first. Then sub-sub-expressions.
         *
         * We don't care about the resulting token. Just the advance of the
         * cursor.
         */
        if ((qchar == singleQuote) || (qchar == doubleQuote))
            match_until_char(qchar, 0);     /* eats the string literal. */
        else if (qchar == openExpr)
            match_sub_expr();
        else if (qchar == closeExpr)
            break;
    }
    return token(&m_stmt, start, (m_current - start), SS_TOKEN_TYPE_EXPR);
}
/*}}}*/
// token query_toker::match_word();/*{{{*/
token query_toker::match_word()
{
    size_t start = (m_current - 1);

    while (!atEOF())
    {
        QChar qchar = m_stmt.at(m_current);
        if (!qchar.isLetterOrNumber() && (qchar != underscore))
            break;

        m_current++;
    }
    return token(&m_stmt, start, (m_current - start), SS_TOKEN_TYPE_IDENT);
}
/*}}}*/
// token query_toker::match_until_char(const QChar &chr, uint type);/*{{{*/
token query_toker::match_until_char(const QChar &chr, uint type)
{
    size_t start = (m_current - 1);

    while (!atEOF() && (m_stmt.at(m_current++) != chr));

    return token(&m_stmt, start, (m_current - start), type);
}
/*}}}*/

