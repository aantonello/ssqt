/**
 * \file
 * Debugging operations.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 07, 2014
 * \since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTDBG_HPP_DEFINED__
#define __SSQTDBG_HPP_DEFINED__

/**
 * \ingroup ssqt
 * \defgroup ssqt_debug Debugging operations
 * This module holds macros and functions for debugging output.
 * The Qt library has greate debugging operations but lack some facilities
 * that this set of macros will help to achieve.
 *
 * As off the standard debugging operations available in Qt, all macros will
 * be available in debug or release builds. Whe you no longer need then, just
 * define \c QT_NO_DEBUG then the macros will expand to nothing.
 *
 * Some macros uses variadics. The library will not compile when macro
 * variadics are not available.
 *
 * Notice that the standard debugging operations on Windows doesn't support
 * UTF-8 character set that is the default when working with Qt. Standard DOS
 * based debuggers only have support to OEM encodings, limited by the Windows
 * Shell prompt. That's way Qt supplies the \c qPrintable() function.
 * Officially, none of the functions declared here has support to UTF-8
 * characters. Only ASCII can be used. So, all strings passed to these
 * operations must use \c qPrintable() or \c SST() macro.
 * @{ *//* ---------------------------------------------------------------- */
#define SST(str)                qPrintable(str)
#define SSNAME(obj)             SST((obj)->metaObject()->className())

/**
 * \internal
 * Different break implementations according to the current compiler.
 * @{ *//* ---------------------------------------------------------------- */
#if defined(MSC_VER)
# define    ssbreak()           __debugbreak()
#else
# define    ssbreak()           asm("int $3")
#endif /* defined(MSC_VER) */
///@} internal

#if defined(QT_NO_DEBUG)
# define ssprint(...)
# define ssdebug(...)
# define sstrace(...)
# define ssflush(h, p, s, t)
# define ssassert(expr, msg)
#else
# define ssprint(fmt, ...)      __ss__debug(NULL, 0, (fmt), ##__VA_ARGS__)
# define ssdebug(fmt, ...)      __ss__debug(__FILE__, __LINE__, (fmt), ##__VA_ARGS__)
# define sstrace(fmt, ...)      __ss__trace(Q_FUNC_INFO, (fmt), ##__VA_ARGS__)
# define ssflush(h, p, s, t)    __ss__flush((h), (p), (s), (t))
# define ssassert(expr, msg)    while (!(expr)) { ssdebug(msg); ssbreak(); }
#endif  /* !defined(QT_NO_DEBUG) */
/* Documentation {{{ */
// #define SST(str) {{{
/**
 * \def SST(str)
 * Expands to \c qPrintable(str).
 * This macro is always available. It is just a short way to use the \c
 * qPrintable() Qt macro.
 * @param str The \c QString to get the pointer of. Read the documentation of
 * \c qPrintable() macro. The pointer returned is temporary and will not be
 * available when the execution point ends.
 **/// }}}
// #define SSNAME(obj) {{{
/**
 * \def SSNAME(obj)
 * Prints an \c QObject class name.
 * @param obj A pointer to a \c QObject class object.
 * @remarks Notice that this macro accepts only \c QObject objects or extended
 * classes. Also, the macro expects a pointer not a value or reference.
 * @note This macro is always available regardless of the presence of \c
 * QT_NO_DEBUG.
 **/// }}}
// #define ssprint(fmt, ...) {{{
/**
 * \def ssprint
 * Writes formated debugging output.
 * This macro expands to nothing when \c QT_NO_DEBUG is defined. Otherwise it
 * will expand to \c __ss_debug() function. Read its documentation to.
 **/// }}}
// #define ssdebug(fmt, ...) {{{
/**
 * \def ssdebug
 * Write formated debugging output.
 * This macro expands to nothing when \c QT_NO_DEBUG is defined. Otherwise it
 * will expand to \c __ss_debug() function.
 * @remarks This macro outputs the file name and line number where it is used
 * automatically. If you don't want that use \c ssprint() instead.
 **/ // }}}
// #define sstrace(fmt, ...) {{{
/**
 * \def sstrace
 * Write formated debugging output.
 * This macro expands to nothing when \c QT_NO_DEBUG is defined. Otherwise it
 * will expand to \c __ss_trace() function.
 * @remarks This macro outputs the current function name using the \c
 * Q_FUNC_INFO macro. If you don't want that use \c ssprint() instead.
 **/// }}}
// #define ssflush(h, p, s, t) {{{
/**
 * \def ssflush(h, p, s, t)
 * Writes binary data in the debugging output.
 * This macro expands to nothing when \c QT_NO_DEBUG is defined. Otherwise it
 * will expand to \c __ss_flush() function.
 * @param h An optional header text. Will be printed before the binary data.
 * Must be a pointer to a \c char array or \b NULL.
 * @param p The pointer to the binary array. Must be a \c void pointer. Can be
 * \b NULL.
 * @param s Size of the memory pointed by \a p. Ignored if \a p is \b NULL.
 * @param t An optional tail text. Will be printed after the binary data. Must
 * be a pointer to a \c char array or \b NULL.
 **/// }}}
// #define ssassert(expr, msg) {{{
/**
 * \def ssassert(expr, msg)
 * Throws an "Assertion Failed!" message.
 * @param expr An expression that evaluates to \b true or \b false.
 * @param msg A string with a message to be shown when the expression \a expr
 * evaluates to \b false.
 * @remarks
 * This macro expands to nothing when \c QT_NO_DEBUG is defined. Otherwise it
 * will check the result of \a expr. If the expression result is \b true the
 * nothing is done. When this expression evaluates to \b false the text passed
 * in the \a msg argument is written in the debugging output and the execution
 * will stopped with the `int 3` interruption.
 * @since 1.0
 **/// }}}
/* }}} Documentation */

/* ---------------------------------------------------------------------------
 * Functions
 * ------------------------------------------------------------------------ */
// void __ss_debug(const char *file, int line, const char *fmt, ...);/*{{{*/
/**
 * Writes formated debugging output.
 * @param file Current file or module name. Usually this is passed with the \c
 * __FILE__ standard C macro.
 * @param line Current line number. Usually this is passed with the \c
 * __LINE__ standard C macro.
 * @param fmt Pointer to a string with text and/or format specifications. This
 * accept any format specification accepted in \c printf() standard
 * C function.
 * @param ... List of parameters to format according to specifications in \a
 * fmt parameter. Can be empty if \a fmt doesn't has any format specification
 * mark.
 * @remarks This function has a limit of 1024 bytes. No string greater than
 * this will be written.
 * @since 1.0
 **/
void __ss_debug(const char *file, int line, const char *fmt, ...);
/*}}}*/
// void __ss_trace(const char *func, const char *fmt, ...);/*{{{*/
/**
 * Writes formated debugging output.
 * @param func Current function name. Usually this is passed with the \c
 * Q_FUNC_INFO Qt macro.
 * @param fmt Pointer to a string with text and/or format specifications. This
 * accept any format specification accepted in \c printf() standard
 * C function.
 * @param ... List of parameters to format according to specifications in \a
 * fmt parameter. Can be empty if \a fmt doesn't has any format specification
 * mark.
 * @remarks This function has a limit of 1024 bytes. No string greater than
 * this will be written.
 * @since 1.0
 **/
void __ss_trace(const char *func, const char *fmt, ...);
/*}}}*/
// void __ss_flush(const char *head, const void *ptr, size_t size, const char *tail);/*{{{*/
/**
 * Writes binary data in the debugging output.
 * @param head An optional header text. Will be printed before the binary
 * data. Must be a pointer to a \c char array or \b NULL.
 * @param ptr The pointer to the binary array. Must be a \c void pointer. Can
 * be \b NULL.
 * @param size Size of the memory pointed by \a p. Ignored if \a p is \b NULL.
 * @param tail An optional tail text. Will be printed after the binary data.
 * Must be a pointer to a \c char array or \b NULL.
 * @since 1.0
 **/
void __ss_flush(const char *head, const void *ptr, size_t size, const char *tail);
/*}}}*/
///@} ssqt_debug

#endif /* __SSQTDBG_HPP_DEFINED__ */

