/**
 * \file
 * General use constants, defines and macros.
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
#ifndef __SSQTCMN_HPP_DEFINED__
#define __SSQTCMN_HPP_DEFINED__

/**
 * \ingroup ssqt
 * \defgroup ssqt_types Scalar Types
 * Useful to keep compatibility between 32 and 64 bits applications.
 * @{ *//* ---------------------------------------------------------------- */
typedef intptr_t error_t;       /**< Type for error numbers.                */
///@} ssqt_types

/**
 * \ingroup ssqt
 * \defgroup ssqt_consts Constants
 * Defines setting some constant values.
 **/

/**
 * \ingroup ssqt_consts
 * \defgroup ssqt_encodings String Encodings
 * Defines with string encodings names.
 * Qt uses the \c QTextCodec class to convert between string encodings. This
 * class has some defaults according to the current locale the application is
 * running. Also, the \c QString object works with UNICODE strings internally.
 * This set of defines has some encodings names that can be used to build \c
 * QTextCodec instances when using the function \c codecForName().
 * @{ *//* ---------------------------------------------------------------- */
#define SSENC_UTF8          "UTF-8"         /**< UTF-8 string encoding.     */
// #define SSENC_UTF16BE       "UTF-16BE"/*{{{*/
/**
 * UTF-16 string enconding.
 * This encoding should be used when converting from <b>big-endian</b>
 * organized streams.
 * @since 1.1
 **/
#define SSENC_UTF16BE       "UTF-16BE"
/*}}}*/
// #define SSENC_UTF16LE       "UTF-16LE"/*{{{*/
/**
 * UTF-16 string enconding.
 * This encoding should be used when converting from <b>little-endian</b>
 * organized streams.
 * @since 1.1
 **/
#define SSENC_UTF16LE       "UTF-16LE"
/*}}}*/
// #define SSENC_UTF32BE       "UTF-32BE"/*{{{*/
/**
 * UTF-32 string enconding.
 * This encoding should be used when converting from <b>big-endian</b>
 * organized streams.
 * @since 1.1
 **/
#define SSENC_UTF32BE       "UTF-32BE"
/*}}}*/
// #define SSENC_UTF32LE       "UTF-32LE"/*{{{*/
/**
 * UTF-32 string enconding.
 * This encoding should be used when converting from <b>little-endian</b>
 * organized streams.
 * @since 1.1
 **/
#define SSENC_UTF32LE       "UTF-32LE"
/*}}}*/
// #define SSENC_UTF16         "UTF-16"/*{{{*/
/**
 * UTF-16 String encoding.
 * This will choose between \c SSENC_UTF16BE or \c SSENC_UTF16LE according to
 * the memory organization of the machine where the application is running.
 * @since 1.1
 **/
#define SSENC_UTF16         "UTF-16"
/*}}}*/
// #define SSENC_UTF32         "UTF-32"/*{{{*/
/**
 * UTF-32 String encoding.
 * This will choose between \c SSENC_UTF32BE or \c SSENC_UTF32LE according to
 * the memory organization of the machine where the application is running.
 * @since 1.1
 **/
#define SSENC_UTF32         "UTF-32"
/*}}}*/
///@} 

/**
 * \defgroup ssqt_errors Error Codes
 * List of error codes used in this library.
 * Notice that we prefer error codes against exceptions since this library,
 * and Qt it self, uses a bunch of C libraries that doesn't support
 * exceptions. Error codes are good enough to tell the application that
 * something went wrong so, exceptions are used only when they are really
 * required.
 *
 * Most of operations in this library will return standard C error codes like
 * \c ENOENT, \c ENOMEM or \c EINVAL. When no error occurs the library uses
 * the value of \c SSNO_ERROR constant. The library also define a specific
 * type for those values, called \c error_t, that is an signed integer type.
 * Will have 32 or 64 bits depending upon the compiler used.
 * @{ *//* ---------------------------------------------------------------- */
#define SSNO_ERROR      0       /**< Used when no errors occurs.            */
///@} ssqt_errors

#endif /* __SSQTCMN_HPP_DEFINED__ */
