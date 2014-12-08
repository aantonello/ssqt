/**
 * \file
 * Defines assets global functions.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 11, 2014
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
#include "ssqtasst.hpp"
#include "ssqtcmn.hpp"
#include "ssqtxmle.hpp"
#include "ssqtxmld.hpp"
#include "ssqtmnui.hpp"
#include "ssqtmnup.hpp"
#include "ssqtmenu.hpp"

namespace ss {
/**
 * @internal
 * @{ *//* ---------------------------------------------------------------- */
static QString const sc__path(":/%1/#%2");
///@} internal

// QString asset_string(uint resID, size_t size = 1024);/*{{{*/
QString asset_string(uint resID, size_t size)
{
#ifndef Q_OS_WIN
    Q_UNUSED(resID);
    Q_UNUSED(size);
    return QString();
#else
    size_t   length   = size * sizeof(wchar_t);
    wchar_t *szBuffer = (wchar_t *)malloc( length );
    QString result;

    if (!szBuffer) return result;

    /* The 'LoadResString()' windows function does not add the terminator
     * NULL.
     */
    memset(szBuffer, 0, length);
    if (LoadStringW((HINSTANCE)GetModuleHandle(NULL), resID, szBuffer, size))
        result = QString::fromWCharArray(szBuffer);

    free(szBuffer);
    return result;
#endif
}
/*}}}*/
// QByteArray asset_file(const QString &resPath);/*{{{*/
QByteArray asset_file(const QString &resPath)
{
    QFile resFile( resPath );
    return resFile.readAll();
}
/*}}}*/
// QByteArray asset_file(uint resID, const char* type);/*{{{*/
QByteArray asset_file(uint resID, const char* type)
{
    return asset_file( sc__path.arg(type).arg(resID) );
}
/*}}}*/
// QIcon asset_icon(uint resID);/*{{{*/
QIcon asset_icon(uint resID)
{
    return QIcon(sc__path.arg("ico").arg(resID));
}
/*}}}*/
// QImage asset_image(uint resID, const char *type = "png");/*{{{*/
QImage asset_image(uint resID, const char *type)
{
    return QImage(sc__path.arg(type).arg(resID));
}
/*}}}*/
// QPixmap asset_pixmap(uint resID, const char* type = "png");/*{{{*/
QPixmap asset_pixmap(uint resID, const char* type)
{
    return QPixmap(sc__path.arg(type).arg(resID));
}
/*}}}*/
// SSXMLDocument asset_xml(uint resID, const char *type);/*{{{*/
SSXMLDocument asset_xml(uint resID, const char *type)
{
    return SSXMLDocument(sc__path.arg(type).arg(resID));
}
/*}}}*/
// SSMenu* asset_menu(uint resID);/*{{{*/
SSMenu* asset_menu(uint resID)
{
    SSXMLDocument xml(asset_xml(resID, "menu"));

    return new SSMenu(&xml);
}
/*}}}*/
// SSMenuPopup* asset_popup(uint resID);/*{{{*/
SSMenuPopup* asset_popup(uint resID)
{
    SSXMLDocument document(asset_xml(resID, "menu"));
    return new SSMenuPopup( &document );
}
/*}}}*/
};

