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
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqtdbg.hpp"
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
    QFile file(fileName);
    return open(file, encoding);
}
/*}}}*/
// error_t SSXMLDocument::open(QFile &file, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::open(QFile &file, const char *encoding)
{
    Q_UNUSED(encoding);

    if (!file.open(QIODevice::ReadOnly))
    {
        sstrace("Error: '%s'", SST(file.errorString()));
        return SSE_IO;
    }

    QXmlStreamReader stream(&file);
    error_t result = SSNO_ERROR;

    result = __xml_readXmlStream(&stream, this);
    file.close();
    if (result == SSNO_ERROR)
        fileName = file.fileName();
    else
        fileName = QString();

    return result;
}
/*}}}*/
// error_t SSXMLDocument::open(const QByteArray &byteArray, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::open(const QByteArray &byteArray, const char *encoding)
{
    Q_UNUSED(encoding);

    fileName = QString();
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
        return SSE_INVAL;

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
        return SSE_IO;

    return write(&file, encoding);
}
/*}}}*/
// error_t SSXMLDocument::write(QIODevice *device, const char *encoding = NULL);/*{{{*/
error_t SSXMLDocument::write(QIODevice *device, const char *encoding)
{
    if (!device->open(QIODevice::WriteOnly | QIODevice::Text))
        return SSE_IO;

    QString xmlHeader;
    QTextCodec *codec = NULL;
    error_t result = SSNO_ERROR;

    /* We must add the XML header tag. */
    xmlHeader.sprintf("<?xml version=\"1.0\" encoding=\"%s\" ?>", encoding);
    if (encoding)
        codec = QTextCodec::codecForName(encoding);
    else
        codec = QTextCodec::codecForLocale();

    if (codec)
        device->write( codec->fromUnicode(xmlHeader) );
    else
        device->write( xmlHeader.toUtf8() );

    if (!SSXMLElement::write(device))
        result = SSE_IO;

    device->close();
    return result;
}
/*}}}*/
///@} Write Operations

/* ------------------------------------------------------------------------ */
/*! @name Overloaded Operators */ //@{
/* ------------------------------------------------------------------------ */
// SSXMLDocument& SSXMLDocument::operator=(const SSXMLDocument &document);/*{{{*/
SSXMLDocument& SSXMLDocument::operator=(const SSXMLDocument &document)
{
    fileName = document.fileName;
    assign( &document );
    return *this;
}
/*}}}*/
///@} Overloaded Operators

// static error_t __xml_readXmlStream(QXmlStreamReader *reader, SSXMLElement *root);/*{{{*/
static error_t __xml_readXmlStream(QXmlStreamReader *reader, SSXMLElement *root)
{
    if (!reader || !root) return SSE_INVAL;

    QXmlStreamReader::TokenType type = QXmlStreamReader::EndDocument;
    QXmlStreamAttributes attributes;
    QXmlStreamAttribute  attribute;
    SSXMLElement *current = NULL;
    size_t limit;

    while (!reader->atEnd())
    {
        type = reader->readNext();
        if ((type == QXmlStreamReader::Invalid) || (type == QXmlStreamReader::EndDocument))
            break;

        if (type == QXmlStreamReader::EndElement)
            current = current->parentElement;
        else if ((type == QXmlStreamReader::Characters) && (current != NULL))
            current->text( reader->text().toString() );    /* Fails if 'current' has children. */
        else if (type == QXmlStreamReader::StartElement)
        {
            if (current)
            {
                current->append(new SSXMLElement(reader->name().toString()));
                current = current->lastElement();
            }
            else                        /* Current element is root. */
            {
                current = root;
                current->elementName = reader->name().toString();
            }

            attributes = reader->attributes();
            limit      = attributes.count();
            for (size_t i = 0; i < limit; ++i)
            {
                attribute = attributes[i];
                current->set(attribute.name().toString(), attribute.value().toString());
            }
        }
    };

    if (type == QXmlStreamReader::Invalid)
    {
        sstrace("%s\n", SST(reader->errorString()));
        ssprint("=> at line: %d, column: %d, char offset: %d", reader->lineNumber(), reader->columnNumber(), reader->characterOffset());
        switch (reader->error())
        {
        case QXmlStreamReader::NotWellFormedError:
        case QXmlStreamReader::UnexpectedElementError:
            return SSE_FTYPE;
        case QXmlStreamReader::PrematureEndOfDocumentError:
            return SSE_IO;
        default:
            return SSE_FAULT;
        }
    }
    return SSNO_ERROR;
}
/*}}}*/

