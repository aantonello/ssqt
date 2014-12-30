/**
 * @file
 * Declares the query_toker class.
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
#ifndef __QTOKER_HPP_DEFINED__
#define __QTOKER_HPP_DEFINED__

/* ===========================================================================
 * Constants
 * ======================================================================== */
#define SS_TOKEN_TYPE_UNKNOWN       0x00000000  /**< Unknown token.         */
// #define SS_TOKEN_TYPE_SPACE         0x00000001/*{{{*/
/**
 * An empty space token.
 * Can be composed of several characters representing white space including
 * tab characters, form feeds, line breaks, etc...
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_SPACE         0x00000001
/*}}}*/
// #define SS_TOKEN_TYPE_COMMA         0x00000002/*{{{*/
/**
 * A comma character.
 * Can be a column separator or a table name seprator depending of its
 * occurrency.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_COMMA         0x00000002
/*}}}*/
// #define SS_TOKEN_TYPE_QUOTED        0x00000003/*{{{*/
/**
 * A quoted text or identifier.
 * On SQL backticks or square brackets are used to quote identifiers. Tables
 * names or columns names are good examples of quoted identifiers. MySQL uses
 * backtick as its quote character while MS SQL uses square brackets. When
 * a token of this type is returned it has all data inside the quotes,
 * including the quotes it self.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_QUOTED        0x00000003
/*}}}*/
// #define SS_TOKEN_TYPE_EXPR          0x00000004/*{{{*/
/**
 * Identifies a sub expression.
 * A sub expression is one enclosed in parentheses. Usually its used to embed
 * a sub-select in the columns list or in a JOIN clause. Also can be used to
 * do mathematical calculations with columns values. In this library it also
 * identifies SQL server function calls.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_EXPR          0x00000004
/*}}}*/
// #define SS_TOKEN_TYPE_IDENT         0x00000005/*{{{*/
/**
 * An identifier.
 * An identifier is a sequence of characters or numbers separated by
 * underscore characters only.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_IDENT         0x00000005
/*}}}*/
// #define SS_TOKEN_TYPE_SYMBOL        0x00000006/*{{{*/
/**
 * Symbols are usually one or two characters.
 * They are used to perform operations between expressions or inside
 * expressions. When a expression is enclosed into parenthesis they are
 * handled as a single token with the \c SS_TOKEN_TYPE_EXPR type. When not,
 * expressions will be connected by symbol tokens. In this case maybe
 * expressions does not get the correct type. They can be literals eather.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_SYMBOL        0x00000006
/*}}}*/
// #define SS_TOKEN_TYPE_LITERAL       0x00000007/*{{{*/
/**
 * Literal texts or values.
 * This type will have values enclosed into single or double quotes. The
 * quotes will be the first and last caracter of the token.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_LITERAL       0x00000007
/*}}}*/
// #define SS_TOKEN_TYPE_DOT           0x00000008/*{{{*/
/**
 * Dot operator.
 * The dot operator is used to separate table names, or table aliases, from
 * column names.
 * @since 1.2
 **/
#define SS_TOKEN_TYPE_DOT           0x00000008
/*}}}*/

namespace ss {

/**
 * Represents a token in a statement.
 * A token is a special object in the statement. It can be a word, a number or
 * a symbol. Tokens are represented by its inicial position, total length and
 * its type.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class token
{
public:
    /** @name Static Data Members */ //@{
    static QChar const backTick;            /**< Backtick character: `.     */
    static QChar const openExpr;            /**< Open parentheses: (.       */
    static QChar const closeExpr;           /**< Close parentheses: ).      */
    static QChar const openBrace;           /**< Open square bracket: [.    */
    static QChar const closeBrace;          /**< Close square bracket: ].   */
    static QChar const singleQuote;         /**< Single quote character.    */
    static QChar const doubleQuote;         /**< Double quote character.    */
    static QChar const comma;               /**< Comma character.           */
    static QChar const underscore;          /**< Valid identifier character.*/
    static QChar const dot;                 /**< Dot operator.              */
    //@}
public:
    /** @name Constructors & Destructor */ //@{
    // token();/*{{{*/
    /**
     * Default constructor.
     * Builds an invaid token.
     * @since 1.2
     **/
    token();
    /*}}}*/
    // token(const QString *string, size_t start, size_t length, uint type);/*{{{*/
    /**
     * Builds a token object.
     * @param string Pointer to the original \c QString object. The \c token
     * object has only a reference to the string. Not a copy of it.
     * @param start The inicial position of the token data in the \a string
     * object.
     * @param length The lenght of characters in the \a string object,
     * starting at point \a start, of the token.
     * @param type The token type. One of the \c SS_TOKEN_TYPE_* constants.
     * @since 1.2
     **/
    token(const QString *string, size_t start, size_t length, uint type);
    /*}}}*/
    // token(const token &other);/*{{{*/
    /**
     * Copy constructor.
     * @param other Another \c token object to be copied.
     * @since 1.2
     **/
    token(const token &other);
    /*}}}*/
    // ~token();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~token();
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // bool valid() const;/*{{{*/
    /**
     * Identifies when this token is valid or not.
     * @return \b true when this token is valid. \b false otherwise.
     * @remarks A token is invalid when it has no data and its type is \c
     * SS_TOKEN_TYPE_UNKNOWN.
     * @since 1.2
     **/
    bool valid() const;
    /*}}}*/
    // size_t startPos() const;/*{{{*/
    /**
     * Retrieves the start position of this token in the original string.
     * @returns The position between 0 and the length of the original string.
     * @since 1.2
     **/
    size_t startPos() const;
    /*}}}*/
    // size_t length() const;/*{{{*/
    /**
     * Retrieves the length of this token.
     * @returns A \c size_t value of the length of this token in characters.
     * @since 1.2
     **/
    size_t length() const;
    /*}}}*/
    // const QChar* data() const;/*{{{*/
    /**
     * Retrieves the internal data of this token.
     * @returns Pointer to an array of \c QChar objects. This array is not
     * zero terminated. It's length is defined by the token::length() member
     * function. Can be \b NULL.
     * @since 1.2
     **/
    const QChar* data() const;
    /*}}}*/
    // const QString* origin() const;/*{{{*/
    /**
     * Retrieves a pointer to the original string.
     * @returns A pointer to the original \c QString object. Can be \b NULL.
     * @since 1.2
     **/
    const QString* origin() const;
    /*}}}*/
    // QString content() const;/*{{{*/
    /**
     * Retrives the content of this token.
     * @returns A \c QString object with this token content.
     * @since 1.2
     **/
    QString content() const;
    /*}}}*/
    // const QChar charAt(size_t index) const;/*{{{*/
    /**
     * Retrieves a copy of a charater in the specified position.
     * @param index Index position of the character inside this token. Zero is
     * the index of the first character. token::length() - 1 is the index
     * position of the last character. The passed parameter must lie in
     * between these two values.
     * @return The \c QChar object with the requested character representation
     * or a default constructed \c QChar object when the passed index position
     * is invalid or this \c token object is invalid.
     * @since 1.2
     **/
    const QChar charAt(size_t index) const;
    /*}}}*/
    // QStringRef stringRef() const;/*{{{*/
    /**
     * Retrieves the \c QStringRef with the data of this token.
     * @return A \c QStringRef object.
     * @since 1.2
     **/
    QStringRef stringRef() const;
    /*}}}*/
    // QStringRef unquote() const;/*{{{*/
    /**
     * Returns a unquoted reference string.
     * @return A \c QStringRef object with the unquoted reference string.
     * @remarks This operation can be used on quoted string portions to remove
     * the first and last characters (quotes). This function doesn't care of
     * what the quotes are. They can be any character. The resulting object
     * will have the same content of this token without the first and last
     * characters.
     * @since 1.2
     **/
    QStringRef unquote() const;
    /*}}}*/
    //@}
public:
    /** @name Properties */ //@{
    // uint type() const;/*{{{*/
    /**
     * Retrieves the type of this token.
     * @return One of the \c SS_TOKEN_TYPE_* constants.
     * @since 1.2
     **/
    uint type() const;
    /*}}}*/
    // void type(uint t);/*{{{*/
    /**
     * Changes the type of this token.
     * @param t To new type. One of the \c SS_TOKEN_TYPE_* constants.
     * @since 1.2
     **/
    void type(uint t);
    /*}}}*/
    //@}
public:
    /** @name Overloaded Operators */ //@{
    // token& operator =(const token &other);/*{{{*/
    /**
     * Assignment operator.
     * @param other Another \c token object to copy its properties.
     * @returns A reference of \b this.
     * @since 1.2
     **/
    token& operator=(const token &other);
    /*}}}*/
    // token& operator+=(const token &other);/*{{{*/
    /**
     * Appends the data of another token to this one.
     * @param other Another \c token object with data to append on.
     * @return \b this.
     * @remarks The resulting operation will be a token having all the content
     * of this instance, plus the value of the original string including the
     * content of the passed \a other token. This can include data that is not
     * in the tokens if they are not adjacent portions of the original string.
     *
     * This token will assume the type of the passed \a other token.
     * @note \a other token must a reference of a token that happens after
     * this instance token.
     * @since 1.2
     **/
    token& operator +=(const token &other);
    /*}}}*/
    // bool   operator==(const QString &value) const;/*{{{*/
    /**
     * Compare the content of this token with a string.
     * @param value String to compare with this token content.
     * @returns \b true if this token content and the passed string are
     * equals. The comparison is case insensitive.
     * @since 1.2
     **/
    bool operator ==(const QString &value) const;
    /*}}}*/
    //@}
private:
    /** @name Data Members */ //@{
    QStringRef m_data;          /**< Content of this token. */
    uint m_type;                /**< Token type.            */
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructors {{{
 * ------------------------------------------------------------------------ */
// inline token::token();/*{{{*/
inline token::token() : m_data(), m_type(SS_TOKEN_TYPE_UNKNOWN) { }
/*}}}*/
// inline token::token(const QString *string, size_t start, size_t length, uint type);/*{{{*/
inline token::token(const QString *string, size_t start, size_t length, uint type) :
    m_data(string, (int)start, (int)length), m_type(type) { }
/*}}}*/
// inline token::token(const token &other);/*{{{*/
inline token::token(const token &other) : m_data(other.m_data),
    m_type(other.m_type) { }
/*}}}*/
// inline token::~token();/*{{{*/
inline token::~token() { }
/*}}}*/
// Constructors & Destructors }}}
/* ---------------------------------------------------------------------------
 * Public: Attributes {{{
 * ------------------------------------------------------------------------ */
// inline bool token::valid() const;/*{{{*/
inline bool token::valid() const {
    return (m_type == SS_TOKEN_TYPE_UNKNOWN);
}
/*}}}*/
// inline size_t token::startPos() const;/*{{{*/
inline size_t token::startPos() const {
    return m_data.position();
}
/*}}}*/
// inline size_t token::length() const;/*{{{*/
inline size_t token::length() const {
    return m_data.length();
}
/*}}}*/
// inline const QChar* token::data() const;/*{{{*/
inline const QChar* token::data() const {
    return m_data.data();
}
/*}}}*/
// inline const QString* token::origin() const;/*{{{*/
inline const QString* token::origin() const {
    return m_data.string();
}
/*}}}*/
// inline QString token::content() const;/*{{{*/
inline QString token::content() const {
    return m_data.toString();
}
/*}}}*/
// inline const QChar token::charAt(size_t index) const;/*{{{*/
inline const QChar token::charAt(size_t index) const {
    return m_data.at((int)index);
}
/*}}}*/
// inline QStringRef token::stringRef() const;/*{{{*/
inline QStringRef token::stringRef() const {
    return m_data;
}
/*}}}*/
// inline QStringRef token::unquote() const;/*{{{*/
inline QStringRef token::unquote() const {
    return QStringRef(m_data.string(), (m_data.position() + 1), (m_data.length() - 2));
}
/*}}}*/
// Public: Attributes }}}
/* ---------------------------------------------------------------------------
 * Public: Properties {{{
 * ------------------------------------------------------------------------ */
// inline uint token::type() const;/*{{{*/
inline uint token::type() const {
    return m_type;
}
/*}}}*/
// inline void token::type(uint t);/*{{{*/
inline void token::type(uint t) {
    m_type = t;
}
/*}}}*/
// Public: Properties }}}
/* ---------------------------------------------------------------------------
 * Overloaded Operators {{{
 * ------------------------------------------------------------------------ */
// inline token& token::operator =(const token &other);/*{{{*/
inline token& token::operator=(const token &other) {
    m_data = other.m_data; m_type = other.m_type;
    return *this;
}
/*}}}*/
// inline token& token::operator+=(const token &other);/*{{{*/
inline token& token::operator +=(const token &other) {
    m_data = QStringRef(origin(), (int)startPos(), (int)(other.startPos() + other.length()));
    m_type = other.type(); return *this;
}
/*}}}*/
// inline bool   token::operator==(const QString &value) const;/*{{{*/
inline bool token::operator ==(const QString &value) const {
    return (m_data.compare(value, Qt::CaseInsensitive) == 0);
}
/*}}}*/
// Overloaded Operators }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */

/**
 * A tokenizer for SQL statements.
 * This is a simple implementation. Works in coorperation with other classes
 * in the <i>query parser</i> group.
 * @since 1.2
 *//* --------------------------------------------------------------------- */
class query_toker
{
public:
    /** @name Constructors & Destructor */ //@{
    // query_toker(const QString &stmt, size_t startPos);/*{{{*/
    /**
     * Default constructor.
     * @param stmt The \c QString statement.
     * @param startPos The start position. Usually after the initial keyword
     * 'SELECT', 'UPDATE', 'INSERT', 'DELETE' or 'REPLACE'.
     * @since 1.2
     **/
    query_toker(const QString &stmt, size_t startPos);
    /*}}}*/
    // ~query_toker();/*{{{*/
    /**
     * Default destructor.
     * @since 1.2
     **/
    ~query_toker();
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // bool atEOF() const;/*{{{*/
    /**
     * Retrieves then this tokenizer reached the end of the statement string.
     * @returns \b true when this object has processed all the string. \b
     * false when not.
     * @since 1.2
     **/
    bool atEOF() const;
    /*}}}*/
    // const QChar current() const;/*{{{*/
    /**
     * Retrieves the character at the current position.
     * @returns A \c QChar object with the character at the current position.
     * Notice that this can be the \b NULL character (char '\0') if the cursor
     * is positioned at the end of the string.
     * @since 1.2
     **/
    const QChar current() const;
    /*}}}*/
    // const QString* source() const;/*{{{*/
    /**
     * Retrieves a pointer to the original string data.
     * @return A pointer to a \c QString object.
     * @since 1.2
     **/
    const QString* source() const;
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // token next();/*{{{*/
    /**
     * Tries to identify the next token starting at the current position.
     * @return The found token or a token of an invalid type.
     * @since 1.2
     **/
    token next();
    /*}}}*/
    // bool  back(size_t count);/*{{{*/
    /**
     * Move the internal pointer back in the list of characters.
     * @param count Number of characters to move backward.
     * @returns \b true on success. \b false on failure. The operation can
     * fails when the movement is invalid. That is, the cursor will move to
     * a point before the starting position.
     * @since 1.2
     **/
    bool  back(size_t count);
    /*}}}*/
    // bool  back(const token &tk);/*{{{*/
    /**
     * Move the internal pointer back in the list of characters.
     * @param tk A \c token class to move backward. The cursor position will
     * be moved to the starting point of this token.
     * @returns \b true on success. \b false on failure. The operation will
     * fails when the passed \c token is invalid or its start position happens
     * before the start position of the internal statement.
     * @since 1.2
     **/
    bool  back(const token &tk);
    /*}}}*/
    //@}
private:
    /** @name Implementation */ //@{
    // token match_spaces();/*{{{*/
    /**
     * Matches a sequence of blank spaces in the parsed statement.
     * @return A \c token object having the sequence of blank spaces. Spaces
     * can be any character for which \c QChar::isSpace() returns \b true.
     * @since 1.2
     **/
    token match_spaces();
    /*}}}*/
    // token match_symbol();/*{{{*/
    /**
     * Matches sequences of symbol characters.
     * @return A \c token object having the sequence of symbols. Only adjacent
     * symbols are returned. Symbols separated by spaces are rarely accepted
     * as a valid expression.
     * @since 1.2
     **/
    token match_symbol();
    /*}}}*/
    // token match_sub_expr();/*{{{*/
    /**
     * Matches a sub-expression.
     * On SQL expressions are enclosed in parentheses.
     * @return A \c token object having anything that is inside the
     * parentheses, including the parentheses it self.
     * @since 1.2
     **/
    token match_sub_expr();
    /*}}}*/
    // token match_word();/*{{{*/
    /**
     * Matches a word.
     * A word is a sequence of alphanumeric characters including the
     * underscore (_) character.
     * @returns The \c token with the word found.
     * @since 1.2
     **/
    token match_word();
    /*}}}*/
    // token match_until_char(const QChar &chr, uint type);/*{{{*/
    /**
     * Search the input statement until the specified is found.
     * @param chr Character to search for.
     * @param type The token type to be used in the returned object.
     * @return The \c token object having anything that was found between the
     * starting position and the position the character was found.
     * @since 1.2
     **/
    token match_until_char(const QChar &chr, uint type);
    /*}}}*/
    //@}
private:
    /** @name Data Members */ //@{
    QString m_stmt;                 /**< The original string statement.     */
    size_t m_start;                 /**< The start index position.          */
    size_t m_current;               /**< The current token position.        */
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline query_toker::query_toker(const QString &stmt, size_t startPos);/*{{{*/
inline query_toker::query_toker(const QString &stmt, size_t startPos) :
    m_stmt(stmt), m_start(startPos), m_current(startPos) { }
/*}}}*/
// inline query_toker::~query_toker();/*{{{*/
inline query_toker::~query_toker() { }
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Public: Attributes {{{
 * ------------------------------------------------------------------------ */
// inline bool query_toker::atEOF() const;/*{{{*/
inline bool query_toker::atEOF() const {
    return (m_current >= (size_t)m_stmt.length());
}
/*}}}*/
// inline const QChar query_toker::current() const;/*{{{*/
inline const QChar query_toker::current() const {
    return m_stmt.at(m_current);
}
/*}}}*/
// inline const QString* query_toker::source() const;/*{{{*/
inline const QString* query_toker::source() const {
    return &m_stmt;
}
/*}}}*/
// Public: Attributes }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
};  /* namespace ss */
#endif /* __QTOKER_HPP_DEFINED__ */
