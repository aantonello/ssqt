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
#ifndef __error_t_defined
typedef int      error_t;       /**< Type for error numbers.                */
#define __error_t_defined 1     /**< @internal                              */
#endif
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
 * \ingroup ssqt_dao
 * \defgroup ssqt_dao_constants Constants
 * Used for data access objects.
 * @{ *//* ---------------------------------------------------------------- */
// #define SS_DATA_TYPE_INT        0x00000001/*{{{*/
/**
 * Integer types.
 * Columns holding numbers with no floating point and no longer than 64 bits.
 * There is no difference between unsigned integers and signed integers in
 * this library. All columns holding fixed length numbers are translated to \c
 * QVariant::LongLong (e.g.: \b int64_t).
 * @since 1.2
 **/
#define SS_DATA_TYPE_INT        0x00000001
/*}}}*/
// #define SS_DATA_TYPE_FLOAT      0x00000002/*{{{*/
/**
 * Floating point numbers.
 * Columns of types \e float, \e double or \e real. Floating pointing numbers
 * with no more than 64 bits and no fixed precision. All those types are
 * translated to \c QVariant::Double (e.g.: \b double) data type.
 * @since 1.2
 **/
#define SS_DATA_TYPE_FLOAT      0x00000002
/*}}}*/
// #define SS_DATA_TYPE_FIXED      0x00000003/*{{{*/
/**
 * Fixed precision column types.
 * Columns holding floating point numbers with a fixed precision. The
 * implementation can vary but usually this type is set as \c DECIMAL or \c
 * NUMERIC in database servers. Usually they are used to hold monetary
 * information, having a fixed floating point precision and not limited in 64
 * bits boundary. Unfortunately, Qt doesn't support this kind of column yet,
 * and it will silently translate it to a \b double data type, constrained
 * into 64 bits and allowing only 16 digits tops. Solutions can be handle the
 * value as a stream (\c QByteArray) converting it to a <b>long double</b>
 * (not directly supported by Qt).
 * @since 1.2
 **/
#define SS_DATA_TYPE_FIXED      0x00000003
/*}}}*/
// #define SS_DATA_TYPE_DATE       0x00000004/*{{{*/
/**
 * Columns holding date information.
 * Not all databases supports this type. MySQL and MariaDB are good examples
 * of it. Usually they hold this information as a string in the format
 * year-month-day. To correctly insert dates into those databases this format
 * is mandatory. Qt can handle the conversion of these dates, both in strings
 * or \c QDate or \c QDateTime objects. It will use the string format
 * mentioned above (YYYY-MM-DD, ISO 8601) to parse the date and convert to one
 * of the objects.
 * @since 1.2
 **/
#define SS_DATA_TYPE_DATE       0x00000004
/*}}}*/
// #define SS_DATA_TYPE_TIME       0x00000005/*{{{*/
/**
 * Columns holding time information.
 * As of the \c SS_DATA_TYPE_DATE type this type is not supported on all
 * drivers. MySQL and MariaDB hold this information as strings with the format
 * hh:mm. Qt will handle this type as string. It will not parse the value as
 * a \c QDateTime object since the format is not an ISO 8601 standard. This
 * library has an workaround for it.
 * @see SSField::asTime()
 * @since 1.2
 **/
#define SS_DATA_TYPE_TIME       0x00000005
/*}}}*/
// #define SS_DATA_TYPE_DATETIME   0x00000006/*{{{*/
/**
 * Columns holding date and time information.
 * Database drivers hold this information in different ways. Microsoft SQL
 * uses double precision coluns to hold this kind of data while MySQL uses
 * fixed precisiona numeric columns. SQLite doesn't support this column type.
 * Depending upon the format used to write the data in the database Qt can
 * handle it directly. We also have a workaround.
 * @see SSField::asDateTime().
 * @since 1.2
 **/
#define SS_DATA_TYPE_DATETIME   0x00000006
/*}}}*/
// #define SS_DATA_TYPE_STAMP      0x00000007/*{{{*/
/**
 * Columns holding a timestamp.
 * Almost all database drivers support this type directly or not. On Microsoft
 * SQL or MySQL columns of this type are 64 bits integer columns. SQLite does
 * not support this type directly but it can be mimic using integer columns
 * because, in SQLite, an integer column has always 64 bits. Qt will not
 * convert this type as \c QDateTime object automatically. We have
 * a workaround.
 * @see SSField::asTimestamp()
 * @since 1.2
 **/
#define SS_DATA_TYPE_STAMP      0x00000007
/*}}}*/
// #define SS_DATA_TYPE_CHAR       0x00000008/*{{{*/
/**
 * Columns having a fixed length character array.
 * This is the most basic character array column type supported by most
 * database drivers. This is equivalent to \c CHAR or \c WCHAR column types.
 * Columns of this type are always converted to \c QVariant::String in this
 * library.
 * @since 1.2
 **/
#define SS_DATA_TYPE_CHAR       0x00000008
/*}}}*/
// #define SS_DATA_TYPE_TEXT       0x00000009/*{{{*/
/**
 * Columns holding variable length of character data.
 * This is usually the majority of data in a database. Any \c VARCHAR or \c
 * VARWCHAR column type is identified as this. Qt will automatically convert
 * it to \c QVariant::String (\c QMetaType::QString).
 * @since 1.2
 **/
#define SS_DATA_TYPE_TEXT       0x00000009
/*}}}*/
// #define SS_DATA_TYPE_BLOB       0x0000000A/*{{{*/
/**
 * Columns having arbitrary binary data.
 * Columns of this type doesn't have a fixed length. Qt can translate any
 * column to binary data.
 * @see SSField::asByteArray()
 * @since 1.2
 **/
#define SS_DATA_TYPE_BLOB       0x0000000A
/*}}}*/

#define SS_COLUMN_REQUIRED      0x00000100
#define SS_COLUMN_READONLY      0x00000200
#define SS_COLUMN_AUTO          0x00000400
#define SS_COLUMN_INDEXED       0x00000800
#define SS_COLUMN_PKEY          0x00001000

// #define SS_DB_DATE_FORMAT       "yyyy-MM-dd"/*{{{*/
/**
 * Standard date format for dates stored in database.
 * Used to format the information to store in the database. Also used to read
 * the information from the database using SSField#asDate() operation.
 * @since 1.2
 **/
#define SS_DB_DATE_FORMAT       "yyyy-MM-dd"
/*}}}*/
// #define SS_DB_TIME_FORMAT       "HH:mm"/*{{{*/
/**
 * Standard time format string.
 * Used to store time information in databases. Also used to retrieve the
 * information when used with SSField#asTime() operation.
 * @since 1.2
 **/
#define SS_DB_TIME_FORMAT       "HH:mm"
/*}}}*/
// #define SS_DB_DATETIME_FORMAT   "yyyy-MM-dd HH:mm:ss"/*{{{*/
/**
 * Standard date and time format string.
 * Used to store date and time information in databases that support this kind
 * of type. Also used to retrieve this information when used with
 * SSField#asDateTime() operation.
 * @since 1.2
 **/
#define SS_DB_DATETIME_FORMAT   "yyyy-MM-dd HH:mm:ss"
/*}}}*/

// #define SS_RECORDSET_FORWARDONLY    0/*{{{*/
/**
 * Builds a forwardonly recordset.
 * This is used in the \c SSRecordsetT constructors defining that the
 * recordset can move ahead only. In some database drivers a forward only
 * query has greater performance and saves much memory. This is the default
 * style when creating a \c SSRecordsetT instance.
 * @since 1.2
 **/
#define SS_RECORDSET_FORWARDONLY    0
/*}}}*/
// #define SS_RECORDSET_DYNAMIC        1/*{{{*/
/**
 * Builds a recordset that can be moved backwards.
 * When this style is used to instantiate an \c SSRecordsetT object all
 * retrieved records are stored enabling you to move back in the list when
 * needed.
 * @since 1.2
 **/
#define SS_RECORDSET_DYNAMIC        1
/*}}}*/

// #define SS_SEEK_SET             1/*{{{*/
/**
 * Start seeking from the beginning of data.
 * @since 1.2
 **/
#define SS_SEEK_SET             1
/*}}}*/
// #define SS_SEEK_CUR             0/*{{{*/
/**
 * Starts seeking from the current position.
 * @since 1.2
 **/
#define SS_SEEK_CUR             0
/*}}}*/
// #define SS_SEEK_END             -1/*{{{*/
/**
 * Starts seeking from the end of the data.
 * @since 1.2
 **/
#define SS_SEEK_END             -1
/*}}}*/
///@} ssqt_dao_constants

#endif /* __SSQTCMN_HPP_DEFINED__ */
