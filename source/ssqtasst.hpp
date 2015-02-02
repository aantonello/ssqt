/**
 * \file
 * Declares assets global functions.
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
#ifndef __SSQTASST_HPP_DEFINED__
#define __SSQTASST_HPP_DEFINED__

#include "ssqtcmn.hpp"
/**
 * @internal
 * Forward declarations.
 * @{ *//* ---------------------------------------------------------------- */
class SSXMLElement;
class SSXMLDocument;
class SSMenuItem;
class SSMenuPopup;
class SSMenu;
///@} internal

/**
 * \ingroup ssqt_funs
 * \defgroup ssqt_assets Assets
 * Provides access to application assets.
 * We call assets any resource that are in the application bundle or compiled
 * in the application executable. Assets means resources and this module has
 * some operations to aid find these resources easily.
 *
 * Most functions relies on a standard way of data organization within the
 * ".qrc" Qt's cross platform format. Files are grouped in "qresource"
 * elements with some prefix set. Then each resource file is aliased with an
 * integer number prefixed with a '#' character. This allows you to define
 * integer constants in the code to be used as resource names. For example,
 * lets pretend that the application icon is defined with the integer 10. As
 * it is an ".ico" file the resource is put in the "qresource" element
 * identified with "/ico" prefix. The code would look like this:
 * ~~~~~~~~~~~~~~~~
 * #define IDI_APPICON  10  // Defined in a header somewhere.
 *
 * QIcon appIcon = assets::icon(IDI_APPICON);
 * ~~~~~~~~~~~~~~~~
 * The ".qrc" file would be written as shown in the following fragment.
 * ~~~~~~~~~~~~~~~~~~{.xml}
 * <RCC>
 *   <qresource prefix="/ico">
 *     <file alias="#10">res/icons/application_icon.ico</file>
 *   </qresource>
 * </RCC>
 * ~~~~~~~~~~~~~~~~~~
 * By following these standards you can organize and work with Qt resources
 * very proficiently.
 *
 * All functions to work with Qt resources are in the "assets" namespace. This
 * namespace was not meant to be imported since the function names are too
 * common. The functions are all meant to be prefixed with the namespace name.
 * \par Standard Prefixes
 *
 * As stated before the function \c assets::icon() will look for an image with
 * the prefix "/ico" and a numeric alias prefixed with a '#' character. The
 * path is built with \c assets::buildPath() function that you can use if you
 * some resource the doesn't fit in the list below. In this list we show all
 * the prefixes that are recognized by the assets functions.
 *
 * <dl>
 * <dt>ico</dt>
 * <dd>You can put all the icons in this prefix. Doesn't matter if the images
 * has ".ico" extension or ".png" or ".gif". Even ".svg" files are supported
 * by Qt when the appropriate plugin is present. These images can be loaded
 * using the \c assets::icon() function that will return a \c QIcon
 * object.</dd>
 * <dt>png</dt>
 * <dd>All Portable Network Graphics images can be listed in using this
 * prefix. Notice that this is only to organize the images. Images of any type
 * can be listed here. They are loaded using the \c assets::pixmap() function
 * that will return a \c QPixmap object.</dd>
 * <dt>img</dt>
 * <dd>A general purpose image prefix. Can hold any type of image. They are
 * loaded using \c assets::image() function that returns a \c QImage
 * object.</dd>
 * <dt>xml</dt>
 * <dd>This is a special prefix to hold XML files. These files can be loaded
 * using \c assets::xml() function that will return an \c SSXMLDocument
 * object.</dd>
 * <dt>menu</dt>
 * <dd>Special prefix to hold menubars and popup menus in XML format. They are
 * documented in the @ref ssqt_menus module. There are two functions to work
 * with these kind of files: \c assets::menu() to load a menu bar and returns
 * an \c SSMenu object, and \c assets::menuPopup() that load a popup menu
 * returning a \c SSMenuPopup object.</dd>
 * </dl>
 * @{ *//* ---------------------------------------------------------------- */
namespace assets {

// QString      buildPath(uint numericID, const QString &prefix);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Build the path for a resource using the conventions of this module.
 * @param numericID The numeric alias used to name the resource file. In the
 * "file" tag of the RCC resource it should be written prefixed with an '#'
 * character. Example:
 * <pre>
 * <file alias="#10">res/path/file.ext</file>
 * </pre>
 * @param prefix Name prefix of the group. This is only the name used in the
 * prefix attribute of the qresource tag. In the following example the value
 * of this parameter should be "ico".
 * <pre>
 * <qresource prefix="/ico">...</qresource>
 * </pre>
 * @returns A \c QString object with the complete resource path built. The
 * operation doesn't check if the resource exists or if the path is valid. It
 * just build it with the passed parts.
 * @since 1.3
 **/
QString buildPath(uint numericID, const QString &prefix);
/*}}}*/
// QByteArray   file(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a file.
 * @param path Path for the file to load. Usually this is a resource path but
 * can be any valid path for Qt.
 * @return A \c QByteArray object with the file loaded. Or an empty \c
 * QByteArray object if the file could not be loaded.
 * @since 1.3
 **/
QByteArray   file(const QString &path);
/*}}}*/
// QByteArray   file(uint numericID, const QString &prefix);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a file in the resource bundle.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix The resource group prefix.
 * @returns A \c QByteArray object with the contents of the loaded file or
 * empty, if the file could not be loaded.
 * @remarks This function uses assets::buildPath() to build the path to the
 * resource file and then calls assets::file(const QString&) to load it.
 * @since 1.3
 **/
QByteArray   file(uint numericID, const QString &prefix);
/*}}}*/

// QImage       image(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an image from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid image path.
 * @returns A \c QImage object with the contents of the file or a \b NULL
 * image object (\c QImage::isNull() is \b true) if the file could not be
 * loaded or has an image not supported by Qt.
 * @since 1.3
 **/
QImage       image(const QString &path);
/*}}}*/
// QImage       image(uint numericID, const QString &prefix = QString("img"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an image from a resource file.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * generic images is "img".
 * @returns A \c QImage object with the contents of the file or a \b NULL
 * image object (\c QImage::isNull() is \b true) if the file could not be
 * loaded or has an image not supported by Qt.
 * @remarks This function uses assets::buildPath() to build the path to the
 * resource file and then calls assets::image(const QString&) to load it.
 * @since 1.3
 **/
QImage       image(uint numericID, const QString &prefix = QString("img"));
/*}}}*/

// QPixmap      pixmap(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an image from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid image path.
 * @returns A \c QPixmap object with the contents of the file or a \b NULL
 * image object (\c QPixmap::isNull() is \b true) if the file could not be
 * loaded or has an image not supported by Qt.
 * @since 1.3
 **/
QPixmap      pixmap(const QString &path);
/*}}}*/
// QPixmap      pixmap(uint numericID, const QString &prefix = QString("png"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an image from a resource file.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * pixmaps is "png".
 * @returns A \c QPixmap object with the contents of the file or a \b NULL
 * image object (\c QPixmap::isNull() is \b true) if the file could not be
 * loaded or has an image not supported by Qt.
 * @remarks This function uses assets::buildPath() to build the path to the
 * resource file and then calls assets::pixmap(const QString&) to load it.
 * @since 1.3
 **/
QPixmap      pixmap(uint numericID, const QString &prefix = QString("png"));
/*}}}*/

// QIcon        icon(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an icon image from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid image path.
 * @returns A \c QIcon object with the contents of the file or a \b NULL
 * icon object (\c QIcon::isNull() is \b true) if the file could not be
 * loaded or has a format not supported by Qt.
 * @since 1.3
 **/
QIcon        icon(const QString &path);
/*}}}*/
// QIcon        icon(uint numericID, const QString &prefix = QString("ico"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads an icon image from a resource file.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * icons is "ico".
 * @returns A \c QIcon object with the contents of the file or a \b NULL
 * icon object (\c QIcon::isNull() is \b true) if the file could not be
 * loaded or has a format not supported by Qt.
 * @remarks This function uses assets::buildPath() to build the path to the
 * resource file and then calls assets::icon(const QString&) to load it.
 * @since 1.3
 **/
QIcon        icon(uint numericID, const QString &prefix = QString("ico"));
/*}}}*/

// SSXMLDocument xml(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a XML document from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid path.
 * @returns A \c SSXMLDocument object with the contents of the file or an
 * empty object if the file could not be loaded.
 * @since 1.3
 **/
SSXMLDocument xml(const QString &path);
/*}}}*/
// SSXMLDocument xml(uint numericID, const QString &prefix = QString("xml"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a XML document from a resource.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * XML files is "xml".
 * @returns A \c SSXMLDocument object with the contents of the file or an
 * empty object if the file could not be loaded.
 * @remarks This function uses assets::buildPath() to build the path to the
 * resource file and then calls assets::xml(const QString&) to load it.
 * @since 1.3
 **/
SSXMLDocument xml(uint numericID, const QString &prefix = QString("xml"));
/*}}}*/

// SSMenu*      menu(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a menu from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid path.
 * @returns A pointer to a \c SSMenu object with the menu bar structure or \b
 * NULL when the menu could not be loaded. The caller is responsible to delete
 * this pointer after using it.
 * @since 1.3
 **/
SSMenu*      menu(const QString &path);
/*}}}*/
// SSMenu*      menu(uint numericID, const QString &prefix = QString("menu"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a menu from a resource.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * menu resources is "menu".
 * @returns A pointer to a \c SSMenu object with the menu bar structure or \b
 * NULL when the menu could not be loaded. The caller is responsible to delete
 * this pointer after using it. This function is implemented calling
 * assets::buildPath() to build the resource path the call
 * assets::menu(const QString&) to load it.
 * @since 1.3
 **/
SSMenu*      menu(uint numericID, const QString &prefix = QString("menu"));
/*}}}*/

// SSMenuPopup* menuPopup(const QString &path);/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a menu popup from a file or resource.
 * @param path Path to the file. Usually this is a resource path but can be
 * any valid path.
 * @returns A pointer to a \c SSMenuPopup object with the popup menu structure
 * or \b NULL when the menu could not be loaded. The caller is responsible to
 * delete this pointer after using it.
 * @since 1.3
 **/
SSMenuPopup* menuPopup(const QString &path);
/*}}}*/
// SSMenuPopup* menuPopup(uint numericID, const QString &prefix = QString("menu"));/*{{{*/
/**
 * @ingroup ssqt_assets
 * Loads a popup menu from a resource.
 * @param numericID The numeric identifier of the resource, follows the
 * standards in this module.
 * @param prefix Optional. The resource group prefix. The standard prefix for
 * popup menu resources is "menu".
 * @returns A pointer to a \c SSMenuPopup object with the popup menu structure
 * or \b NULL when the menu could not be loaded. The caller is responsible to
 * delete this pointer after using it. This function is implemented calling
 * assets::buildPath() to build the resource path the call
 * assets::menuPopup(const QString&) to load it.
 * @since 1.3
 **/
SSMenuPopup* menuPopup(uint numericID, const QString &prefix = QString("menu"));
/*}}}*/

}
///@} ssqt_assets

#endif /* __SSQTASST_HPP_DEFINED__ */
