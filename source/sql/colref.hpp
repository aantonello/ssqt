/**
 * @file
 * Declares the column_ref class.
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
#ifndef __COLREF_HPP_DEFINED__
#define __COLREF_HPP_DEFINED__

namespace ss {

/**
 * A column reference class.
 * This class is used in the \c query_parser class to list all columns
 * references included in a SQL statement.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class column_ref
{
public:
    /** @name Constructors & Destructor */ //@{
    // column_ref();/*{{{*/
    /**
     * Default constructor.
     * @since 1.2
     **/
    column_ref();
    /*}}}*/
    // ~column_ref();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~column_ref();
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // bool parse(query_toker &toker, token &tk);/*{{{*/
    /**
     * Starts the parser of a column specification.
     * @param toker The \c query_toker object with the full statement.
     * @param tk The initial \c token object. It will be checked for a valid
     * column specification starting point. The parser will continue the
     * parsing until its found a comma character, signal that ends a column
     * specification, or a \c FROM clause. This token must be of types \c
     * SS_TOKEN_TYPE_QUOTE, \c SS_TOKEN_TYPE_WORD or \c SS_TOKEN_TYPE_EXPR.
     * @returns \b true when valid column specification was found. \b false
     * otherwise.
     * @remarks When a \c FROM clause is found, the \c query_toker object is
     * rewind so its cursor is positioned exactly at the first character of
     * the 'FROM' keyword.
     * @note Actually, this function never fails. This is because there is
     * a pre-verification made in the \c query_parser class before calling
     * this function. So, it will always succeed.
     * @since 1.2
     **/
    bool parse(query_toker &toker, token &tk);
    /*}}}*/
    //@}
public:
    /** @name Data Members */ //@{
    // QStringRef reference;/*{{{*/
    /**
     * A complete reference of the column specification in the statement.
     * This will have all the column specification including sub expressions,
     * aliases, calculus, function calls, etc.
     * @since 1.2
     **/
    QStringRef reference;
    /*}}}*/
    // QStringRef columnName;/*{{{*/
    /**
     * Holds the column name.
     * When the column is the result of a function call or sub-expression this
     * string will have the sub-expression or function call text.
     * @since 1.2
     **/
    QStringRef columnName;
    /*}}}*/
    // QStringRef columnAlias;/*{{{*/
    /**
     * The column alias.
     * This member will have the column alias when one is found. When a column
     * is aliased in a statement the name returned by the query execution is
     * the alias. Not the original column name.
     * @since 1.2
     **/
    QStringRef columnAlias;
    /*}}}*/
    // QStringRef sourceTable;/*{{{*/
    /**
     * Name of the source table.
     * The source table can be found in the column specification using the
     * form 'table.column' or '`table`.`column`'.
     * @since 1.2
     **/
    QStringRef sourceTable;
    /*}}}*/
    // QStringRef tableAlias;/*{{{*/
    /**
     * The source table alias.
     * Holds the source table alias when one is used. This member starts with
     * the same value as column_ref::sourceTable. When the \c query_parser
     * resolves the aliased table to a table name this member keeps the alias
     * becouse it is was will be used in the query result.
     * @since 1.2
     **/
    QStringRef tableAlias;
    /*}}}*/
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructors {{{
 * ------------------------------------------------------------------------ */
// inline column_ref::column_ref();/*{{{*/
inline column_ref::column_ref() { }
/*}}}*/
// inline column_ref::~column_ref();/*{{{*/
inline column_ref::~column_ref();
/*}}}*/
// Constructors & Destructors }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
};  /* namespace ss */
#endif /* __COLREF_HPP_DEFINED__ */
