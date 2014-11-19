/**
 * \file
 * Declares de SSXMLDocument class.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 08, 2014
 * \since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTXMLD_HPP_DEFINED__
#define __SSQTXMLD_HPP_DEFINED__

#include <QByteArray>
#include <QFile>

/**
 * @ingroup ssqt_xml
 * An XML document class.
 * This class extends \c SSXMLElement to also represent the root element of
 * the document.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSXMLDocument : public SSXMLElement
{
public:     // Constructors & Destructor
    // SSXMLDocument();/*{{{*/
    /**
     * Default constructor.
     * @since 1.1
     **/
    SSXMLDocument();
    /*}}}*/
    // SSXMLDocument(const QString &fileName);/*{{{*/
    /**
     * Loads a documento from a file.
     * @param fileName String with absolute file name. If this string starts
     * with a colon the file will be searched in the Qt resource stream.
     * @remarks This constructor call #open(const QString&, const char*).
     * @since 1.1
     **/
    SSXMLDocument(const QString &fileName);
    /*}}}*/
    // SSXMLDocument(const QFile &file);/*{{{*/
    /**
     * Loads a file from disk.
     * @param file The file to be loaded.
     * @remarks This constructor call #open(const QFile &, const char *).
     * @since 1.1
     **/
    SSXMLDocument(const QFile &file);
    /*}}}*/
    // SSXMLDocument(const QByteArray &byteArray);/*{{{*/
    /**
     * Loads a document from memory.
     * @param byteArray Memory containing the document data.
     * @remarks This constructo call #open(const QByteArray&, const char*).
     * @since 1.1
     **/
    SSXMLDocument(const QByteArray &byteArray);
    /*}}}*/
    // SSXMLDocument(const SSXMLDocument &document);/*{{{*/
    /**
     * Copy constructor.
     * @param document Another document to copy.
     * @since 1.1
     **/
    SSXMLDocument(const SSXMLDocument &document);
    /*}}}*/

public:     // Read Operations
    // error_t open(const QString &fileName, const char *encoding = NULL);/*{{{*/
    /**
     * Loads a file from disk or resource.
     * @param fileName String with absolute file name or resource identifier.
     * If this string starts with a colon character it is interpreted as
     * a resource identifier.
     * @param encoding Optional. The character encoding of the file to load.
     * When \b NULL the enconding will be chosen according to the default
     * locale and machine where the application is running. Otherwise the
     * value can be any codec name recognized by \c QTextCodec class. Some
     * values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c
     * SSNO_ERROR). Otherwize an error code will be returned. The
     * possible result codes are:
     * - \b SSE_FTYPE: When the file passed is ill-formed.
     * - \b SSE_IO: When the passed file is not finished. That is, until the end
     *      of the file all was right. But the file ended and elements was not
     *      closed correctly.
     * - \b SSE_FAULT: Any other kind of error.
     * .
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t open(const QString &fileName, const char *encoding = NULL);
    /*}}}*/
    // error_t open(const QFile &file, const char *encoding = NULL);/*{{{*/
    /**
     * Loads a file from disk or resource.
     * @param file \c QFile object with the file reference to be loaded.
     * @param encoding Optional. The character encoding of the file to load.
     * When \b NULL the enconding will be chosen according to the default
     * locale and machine where the application is running. Otherwise the
     * value can be any codec name recognized by \c QTextCodec class. Some
     * values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c
     * SSNO_ERROR). Otherwize an error code will be returned. The
     * possible result codes are:
     * - \b SSE_FTYPE: When the file passed is ill-formed.
     * - \b SSE_IO: When the passed file is not finished. That is, until the end
     *      of the file all was right. But the file ended and elements was not
     *      closed correctly.
     * - \b SSE_FAULT: Any other kind of error.
     * .
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t open(const QFile &file, const char *encoding = NULL);
    /*}}}*/
    // error_t open(const QByteArray &byteArray, const char *encoding = NULL);/*{{{*/
    /**
     * Loads an XML file from a memory buffer.
     * @param byteArray \c QByteArray object with XML data in memory.
     * @param encoding Optional. The character encoding of the file to load.
     * When \b NULL the enconding will be chosen according to the default
     * locale and machine where the application is running. Otherwise the
     * value can be any codec name recognized by \c QTextCodec class. Some
     * values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c
     * SSNO_ERROR). Otherwize an error code will be returned. The
     * possible result codes are:
     * - \b SSE_FTYPE: When the file passed is ill-formed.
     * - \b SSE_IO: When the passed file is not finished. That is, until the end
     *      of the file all was right. But the file ended and elements was not
     *      closed correctly.
     * - \b SSE_FAULT: Any other kind of error.
     * .
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t open(const QByteArray &byteArray, const char *encoding = NULL);
    /*}}}*/

public:     // Write Operations
    // error_t write(const char *encoding = NULL);/*{{{*/
    /**
     * Writes the contents of this document back to the original file.
     * @param encoding Optional. The character encoding to be used in the
     * written data.  When \b NULL the enconding will be chosen according to
     * the default locale and machine where the application is running.
     * Otherwise the value can be any codec name recognized by \c QTextCodec
     * class. Some values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c SSNO_ERROR).
     * Otherwize an error code will be returned.
     * @remarks This operation can be used when the XML data was loaded from
     * a file on disk with one of the constructors or \c open() functions that
     * accept a \c QString or \c QFile object. The original file will be
     * completly overwritten by this function.  When the document was created
     * from a file in memory, that is, no disk object was loaded in this
     * instance, the operation will fail with \c SSE_INVAL error code. This
     * error will also be returned when the XML data was loaded from
     * a resource file.
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t write(const char *encoding = NULL);
    /*}}}*/
    // error_t write(const QString &fileName, const char *encoding = NULL);/*{{{*/
    /**
     * Writes the contents of this document to a file.
     * @param fileName The file to be written. The path must exists. If the
     * file already exists it will be overwritten.
     * @param encoding Optional. The character encoding to be used in the
     * written file.  When \b NULL the enconding will be chosen according to
     * the default locale and machine where the application is running.
     * Otherwise the value can be any codec name recognized by \c QTextCodec
     * class. Some values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c SSNO_ERROR).
     * Otherwize an error code will be returned.
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t write(const QString &fileName, const char *encoding = NULL);
    /*}}}*/
    // error_t write(QFile &file, const char *encoding = NULL);/*{{{*/
    /**
     * Writes the contents of this document to a file.
     * @param file The file to be written. The path must exists. If the
     * file already exists it will be overwritten.
     * @param encoding Optional. The character encoding to be used in the
     * written file.  When \b NULL the enconding will be chosen according to
     * the default locale and machine where the application is running.
     * Otherwise the value can be any codec name recognized by \c QTextCodec
     * class. Some values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c SSNO_ERROR).
     * Otherwize an error code will be returned.
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t write(QFile &file, const char *encoding = NULL);
    /*}}}*/
    // error_t write(QIODevice *device, const char *encoding = NULL);/*{{{*/
    /**
     * Writes this document data to a device.
     * @param device Pointer to the target device. This can be any device,
     * a socket, a file, even the debugging output device stream is accepted.
     * The passed object should not be opened. It will be open inside the
     * function. Also, when writing ends, it will be closed.
     * @param encoding Optional. The character encoding to be used in the
     * written file.  When \b NULL the enconding will be chosen according to
     * the default locale and machine where the application is running.
     * Otherwise the value can be any codec name recognized by \c QTextCodec
     * class. Some values are listed in the @ref ssqt_encodings group.
     * @return If the function succeeded the result is \b 0 (\c SSNO_ERROR).
     * Otherwize an error code will be returned.
     * @sa ssqt_errors
     * @since 1.1
     **/
    error_t write(QIODevice *device, const char *encoding = NULL);
    /*}}}*/

public:     // Overloaded Operators
    // SSXMLDocument& operator=(const SSXMLDocument &document);/*{{{*/
    /**
     * Copy operator.
     * @param document Another document to copy.
     * @returns \b this.
     * @since 1.1
     **/
    SSXMLDocument& operator=(const SSXMLDocument &document);
    /*}}}*/

public:     // Data Members
    QString fileName;               /**< Original file name.    */
};
/* Inline Functions {{{ */
/* ------------------------------------------------------------------------ */
/*! \name Constructors & Destructor *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline SSXMLDocument::SSXMLDocument();/*{{{*/
inline SSXMLDocument::SSXMLDocument() : SSXMLElement() { }
/*}}}*/
// inline SSXMLDocument::SSXMLDocument(const QString &fileName);/*{{{*/
inline SSXMLDocument::SSXMLDocument(const QString &fileName) : SSXMLElement() {
    open(fileName);
}
/*}}}*/
// inline SSXMLDocument::SSXMLDocument(const QFile &file);/*{{{*/
inline SSXMLDocument::SSXMLDocument(const QFile &file) : SSXMLElement() {
    open(file);
}
/*}}}*/
// inline SSXMLDocument::SSXMLDocument(const QByteArray &byteArray);/*{{{*/
inline SSXMLDocument::SSXMLDocument(const QByteArray &byteArray) : SSXMLElement() {
    open(byteArray);
}
/*}}}*/
// inline SSXMLDocument::SSXMLDocument(const SSXMLDocument &document);/*{{{*/
inline SSXMLDocument::SSXMLDocument(const SSXMLDocument &document) : SSXMLElement() {
    this->operator=(document);
}
/*}}}*/
///@} Constructors & Destructor /*}}}*/
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTXMLD_HPP_DEFINED__ */
