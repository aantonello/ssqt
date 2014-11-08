/**
 * \file
 * Defines de SSXMLDocument class.
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
#include "stdplx.hpp"
#include "ssqtxmle.hpp"
#include "ssqtxmld.hpp"

/* ===========================================================================
 * SSXMLDocument class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Internal Functions
 * ------------------------------------------------------------------------ */
// static error_t __xml_readXmlStream(QXmlStreamReader *reader, SSXMLElement *root);/*{{{*/
/**
 * Reads XML data into a root element.
 * @param reader Pointer to a \c QXmlStreamReader object with the XML document
 * loaded.
 * @param root Pointer to the \c SSXMLElement that will receive the root XML
 * element in the document. All XML hierarchi will be applied to this object.
 * @returns An error code. \c SSNO_ERROR means success.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
static error_t __xml_readXmlStream(QXmlStreamReader *reader, SSXMLElement *root);
/*}}}*/

/* ------------------------------------------------------------------------ */
/*! \name Read Operations */ //@{
/* ------------------------------------------------------------------------ */
// error_t SSXMLDocument::open(const QString &fileName, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::open(const QString &fileName, const char *encoding)
{
    return open(QFile(fileName), encoding);
}
/*}}}*/
// error_t SSXMLDocument::open(const QFile &file, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::open(const QFile &file, const char *encoding)
{
    Q_UNUSED(encoding);

    QXmlStreamReader stream(&file);
    error_t result = SSNO_ERROR;

    result = __xml_readXmlStream(&stream, this);
    if (result == SSNO_ERROR)
        fileName = file.fileName();

    return result;
}
/*}}}*/
// error_t SSXMLDocument::open(const QByteArray &byteArray, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::open(const QByteArray &byteArray, const char *encoding)
{
    Q_UNUSED(encoding);

    QXmlStreamReader reader(byteArray);
    return __xml_readXmlStream(&reader, this);
}
/*}}}*/
///@} Read Operations

/* ------------------------------------------------------------------------ */
/*! \name Write Operations */ //@{
/* ------------------------------------------------------------------------ */
// error_t SSXMLDocument::write(const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::write(const char *encoding)
{
    if (fileName.isEmpty() || fileName.startsWith(':'))
        return EINVAL;

    QFile file(fileName);
    return write(&file, encoding);
}
/*}}}*/
// error_t SSXMLDocument::write(const QString &fileName, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::write(const QString &fileName, const char *encoding)
{
    this->fileName = fileName;
    return write(encoding);
}
/*}}}*/
// error_t SSXMLDocument::write(QFile &file, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::write(QFile &file, const char *encoding)
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return EIO;

    return write(&file, encoding);
}
/*}}}*/
// error_t SSXMLDocument::write(QIODevice *device, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::write(QIODevice *device, const char *encoding)
{
    if (!device->open(QIODevice::WriteOnly | QIODevice::Text))
        return EIO;

    QString xmlHeader;
    QTextCodec *codec = NULL;
    error_t result = SSNO_ERROR;

    /* We must add the XML header tag. */
    xmlHeader.sprintf("<?xml version=\"1.0\" encoding=\"%s\" ?>", encoding);
    if (encoding)
        codec = QTextCodec::codecForName(encoding);
    else
        codec = QTextCodec:codecForLocale();

    if (code)
        device->write( codec->fromUnicode(xmlHeader) );
    else
        device->write( xmlHeader.toUtf8() );

    if (!SSXMLElement::write(device))
        result = EIO;

    device->close();
    return result;
}
/*}}}*/
///@} Write Operations
