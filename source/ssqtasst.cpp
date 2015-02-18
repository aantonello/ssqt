/**
 * \file
 * Defines assets global functions.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 11, 2014
 * \since  Super Simple for Qt 1.3
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

namespace assets {

// QString      buildPath(uint numericID, const QString &prefix);/*{{{*/
QString buildPath(uint numericID, const QString &prefix)
{
    return QString(":/%1/#%2").arg(prefix).arg(numericID);
}
/*}}}*/
// QByteArray   file(const QString &path);/*{{{*/
QByteArray   file(const QString &path)
{
    QFile theFile( path );
    return theFile.readAll();
}
/*}}}*/
// QByteArray   file(uint numericID, const QString &prefix);/*{{{*/
QByteArray   file(uint numericID, const QString &prefix)
{
    return file(buildPath(numericID, prefix));
}
/*}}}*/

// QImage       image(const QString &path);/*{{{*/
QImage       image(const QString &path)
{
    return QImage( path );
}
/*}}}*/
// QImage       image(uint numericID, const QString &prefix = QString("img"));/*{{{*/
QImage       image(uint numericID, const QString &prefix)
{
    return image( buildPath(numericID, prefix) );
}
/*}}}*/

// QPixmap      pixmap(const QString &path);/*{{{*/
QPixmap      pixmap(const QString &path)
{
    return QPixmap( path );
}
/*}}}*/
// QPixmap      pixmap(uint numericID, const QString &prefix = QString("png"));/*{{{*/
QPixmap      pixmap(uint numericID, const QString &prefix)
{
    return pixmap( buildPath(numericID, prefix) );
}
/*}}}*/

// QIcon        icon(const QString &path);/*{{{*/
QIcon        icon(const QString &path)
{
    return QIcon( path );
}
/*}}}*/
// QIcon        icon(uint numericID, const QString &prefix = QString("ico"));/*{{{*/
QIcon        icon(uint numericID, const QString &prefix)
{
    return icon( buildPath(numericID, prefix) );
}
/*}}}*/

// SSXMLDocument xml(const QString &path);/*{{{*/
SSXMLDocument xml(const QString &path)
{
    return SSXMLDocument( path );
}
/*}}}*/
// SSXMLDocument xml(uint numericID, const QString &prefix = QString("xml"));/*{{{*/
SSXMLDocument xml(uint numericID, const QString &prefix)
{
    return xml( buildPath(numericID, prefix) );
}
/*}}}*/

// SSMenu*      menu(const QString &path);/*{{{*/
SSMenu*      menu(const QString &path)
{
    SSXMLDocument document( xml(path) );
    return new SSMenu( &document );
}
/*}}}*/
// SSMenu*      menu(uint numericID, const QString &prefix = QString("menu"));/*{{{*/
SSMenu*      menu(uint numericID, const QString &prefix)
{
    return menu( buildPath(numericID, prefix) );
}
/*}}}*/

// SSMenuPopup* menuPopup(const QString &path);/*{{{*/
SSMenuPopup* menuPopup(const QString &path)
{
    SSXMLDocument document( xml(path) );
    return new SSMenuPopup( &document );
}
/*}}}*/
// SSMenuPopup* menuPopup(uint numericID, const QString &prefix = QString("menu"));/*{{{*/
SSMenuPopup* menuPopup(uint numericID, const QString &prefix)
{
    return menuPopup( buildPath(numericID, prefix) );
}
/*}}}*/

};

