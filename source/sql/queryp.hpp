/**
 * @file
 * Declares the query_parser class.
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
#ifndef __QUERYP_HPP_DEFINED__
#define __QUERYP_HPP_DEFINED__

/* ===========================================================================
 * Constants
 * ======================================================================== */
#define SS_QUERY_TYPE_UNKNOWN   0       /**< Unknown statement.             */
#define SS_QUERY_TYPE_SELECT    1       /**< 'SELECT' statement.            */
#define SS_QUERY_TYPE_UPDATE    2       /**< 'UPDATE' statement.            */
#define SS_QUERY_TYPE_DELETE    3       /**< 'DELETE' statement.            */
#define SS_QUERY_TYPE_INSERT    4       /**< 'INSERT' statement.            */
#define SS_QUERY_TYPE_REPLACE   5       /**< 'REPLACE' statement.           */

namespace ss {

/**
 * Parser for SQL statements.
 * This class implements a simple parser. It is able to parse the most kind of
 * \c SELECT statements but only simple ones. Statements having multiple joins
 * or unions cannot be handled. This class is used as a helper to another
 * classes that needs to know some information about the statements.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class query_parser
{
public:
    /** @name Constructors & Destructor */ //@{
    // query_parser();/*{{{*/
    /**
     * Default constructor.
     * @since 1.2
     **/
    query_parser();
    /*}}}*/
    // ~query_parser();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~query_parser();
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // uint queryType() const;/*{{{*/
    /**
     * Retrieves the type of the statement parsed.
     * @return One of the following values:
     * - \c SS_QUERY_TYPE_SELECT: A 'SELECT' statement was parsed.
     * - \c SS_QUERY_TYPE_UPDATE: A 'UPDATE' statement was parsed.
     * - \c SS_QUERY_TYPE_DELETE: A 'DELETE' statement was parsed.
     * - \c SS_QUERY_TYPE_INSERT: A 'INSERT' statement was parsed.
     * - \c SS_QUERY_TYPE_REPLACE: A 'REPLACE' statement was parsed.
     * .
     * When the parser could not determine the type of the statement the
     * result of this operation will be \c SS_QUERY_TYPE_UNKNOWN.
     * @since 1.2
     **/
    uint queryType() const;
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // bool parse(const QString &stmt);/*{{{*/
    /**
     * Starts the parsing process.
     * @param stmt Statement to be parsed.
     * @returns \b true on success. \b false on failure.
     * @remarks Usually the operation doesn't fail since the parser is mostly
     * used after a query is already executed successfuly.
     * @since 1.2
     **/
    bool parse(const QString &stmt);
    /*}}}*/

private:
    // bool parse_select(const QString &stmt);/*{{{*/
    /**
     * Starts the parser for a 'SELECT' statement.
     * @param stmt String with the statement.
     * @returns \b true on success. \b false on failure.
     * @since 1.2
     **/
    bool parse_select(const QString &stmt);
    /*}}}*/
    //@}
private:
    /** @name Data Members */ //@{
    uint m_queryType;               /**< Holds the type of the statement.   */
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline query_parser::query_parser();/*{{{*/
inline query_parser::query_parser() { }
/*}}}*/
// inline query_parser::~query_parser();/*{{{*/
inline query_parser::~query_parser() { }
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Public: Attributes {{{
 * ------------------------------------------------------------------------ */
// inline uint query_parser::queryType() const;/*{{{*/
inline uint query_parser::queryType() const {
    return m_queryType;
}
/*}}}*/
// Public: Attributes }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
};  /* namespace ss */
#endif /* __QUERYP_HPP_DEFINED__ */
