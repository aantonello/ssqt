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
 * in the application executable. Assets means resources and this class has
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
 * QIcon appIcon = asset_icon(IDI_APPICON);
 * ~~~~~~~~~~~~~~~~
 * The ".qrc" file would be written as shown in the following fragment.
 * ~~~~~~~~~~~~~~~~~~{.xml}
 * <RCC>
 *   <qresource prefix="/ico">
 *     <file alias="#10">icons/application_icon.ico</file>
 *   </qresource>
 * </RCC>
 * ~~~~~~~~~~~~~~~~~~
 * The standard groups recognized by the assets functions are:
 * - \b ico: List all icon files. Image files with ".ico" extension for
 *   Windows, ".icns" for Mac or ".pxm" for Linux. Can be loaded with \c
 *   ss::asset_icon() function.
 * - \b bmp: Standard image format for Windows applications. List of "bitmap"
 *   files. Can be loaded with \c ss::asset_image() or \c ss::asset_pixmap().
 * - \b png: List of images in Portable Network Graphics format. Works in all
 *   platforms. Can be loaded with \c ss::asset_image() or \c
 *   ss::asset_pixmap().
 * - \b svg: Scalable Vector Graphics. As the name says, is a vector graphic
 *   format. Is a drawing format that can be scaled to any size without
 *   loosing quality. Works on all platforms. Can be loaded with \c
 *   ss::asset_image() or \c ss::asset_pixmap().
 * - \b menu: Prefix used to group all menu resources written in XML format.
 *   Works on all platforms. Can be loaded with \c ss::asset_menu() or \c
 *   ss::asset_popup().
 * - \b string: Prefix used to group all string table resources in XML format.
 *   Works on all platforms. Not implemented yet.
 * .
 * @{ *//* ---------------------------------------------------------------- */
namespace ss {
// QString       asset_string(uint resID, size_t size = 1024);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads a string from the executable resource.
 * @param resID The identifier of the string in the resource. Despite be an
 * unsigned integer number this value is limited in 16 bits. This limit is
 * imposed by the Windows resource format.
 * @param size Length of the string resource, in characters. Strings are
 * compiled in the resource using UTF-16 encoding. Each character occupies
 * 2 byte in memory. Qt handles Unicode strings natively. So, the returned
 * string will be in Qt's internal encoding. This argument is optional and, if
 * not passed, the default length is 1024 characters. Strings greater than
 * this length needs to have this value passed or it will be loaded truncated.
 * @return If the string is found in the executable resource it is returned in
 * a \c QString object. Otherwise an empty \c QString object is returned.
 * @remarks This operation works only on Windows when a standard resource (rc
 * file) is compiled into the executable. In others operating systems the
 * result will be always an empty \c QString object.
 * @since 1.1
 **/
QString asset_string(uint resID, size_t size = 1024);
/*}}}*/
// QByteArray    asset_file(uint resID, const char* type);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads a file stream from the assets resource.
 * @param resID Resource numerical alias.
 * @param type Resource type. All kind of types can be defined here.
 * @return A \c QByteArray with the stream data loaded in memory.
 * @remarks The \a type argument refers to the \b prefix set to a group of
 * resources in a ".qrc" file. Common used prefixes are:
 * - \b ico: List all icon files. Image files with ".ico" extension for
 *   Windows, ".icns" for Mac or ".pxm" for Linux.
 * - \b bmp: Standard image format for Windows applications. List of "bitmap"
 *   files.
 * - \b png: List of images in Portable Network Graphics format. Works in all
 *   platforms.
 * - \b svg: Scalable Vector Graphics. As the name says, is a vector graphic
 *   format. Is a drawing format that can be scaled to any size without
 *   loosing quality. Works on all platforms.
 * - \b menu: Prefix used to group all menu resources written in XML format.
 *   Works on all platforms.
 * - \b string: Prefix used to group all string table resources in XML format.
 *   Works on all platforms.
 * .
 * These are only examples of common used prefixes. This function does not do
 * any parsing or checking against the prefix (type) specification and its
 * content. All kinds of resources will be loaded in binary format and
 * returned as a \c QByteArray object.
 *
 * The combination of \a type and \a resID will build the path for the
 * resource in the ".qrc" file. We use numbered resources becouse its more
 * common and simple to set numeric constants in C/C++ code than string
 * constants. To name a resource using a number put a '#' sign in front of the
 * number, in decimal notation, as an alias of the file. For example, lets
 * name the application icon following the examples above.
 * ~~~~~~~~~~~~~~~{.xml}
 * <RCC>
 *   <qresource prefix="/ico">
 *     <file alias="#10">res/icon/app.ico</file>
 *   </qresource>
 * </RCC>
 * ~~~~~~~~~~~~~~~
 * When loading this icon file you will use the following code.
 * ~~~~~~~~~~~~~~~~
 * #define IDI_APPICON  10      // Defined somehere.
 *
 * QByteArray data = asset_file(IDI_APPICON, "ico");
 * ~~~~~~~~~~~~~~~~
 * Internally the \c asset_file() function will build the path for the
 * resource putting together \a resID and \a type parameters in a simple \e
 * sprintf way, ending with the string ":/ico/#10". Peace of cake.
 * @since 1.1
 **/
QByteArray asset_file(uint resID, const char* type);
/*}}}*/
// QIcon         asset_icon(uint resID);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads an ico file from a numeric labeled resource.
 * @param resID Resource numerical alias.
 * @returns A \c QIcon object having the data loaded from the resource. If the
 * resource is not an image or is not found the returned object's method \c
 * isNull() will return \b true.
 * @remarks As stated in \c asset_file() function documentation, this
 * operation relies on the resource file be in a "qresource" group prefixed
 * with the type "ico". For example:
 * ~~~~~~~~~~~~~~~{.xml}
 * <RCC>
 *   <qresource prefix="/ico">
 *     <file alias="#10">res/icon/app.ico</file>
 *   </qresource>
 * </RCC>
 * ~~~~~~~~~~~~~~~
 * @sa asset_file()
 * @since 1.1
 **/
QIcon asset_icon(uint resID);
/*}}}*/
// QImage        asset_image(uint resID, const char *type = "png");/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads an image from the assets resource.
 * @param resID Resource numerical alias.
 * @param type Resource type. All kind of types can be defined here. The
 * default value is "png" that is the common group used for imagens.
 * @returns A \c QImage object having the image data. If the image file
 * cannot be found the returned object will be \b NULL.
 * @sa asset_file()
 * @sa asset_pixmap()
 * @since 1.1
 **/
QImage asset_image(uint resID, const char *type = "png");
/*}}}*/
// QPixmap       asset_pixmap(uint resID, const char *type = "png");/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads a pixmap from the assets resource.
 * @param resID Resource numerical alias.
 * @param type Resource type. All kind of types can be defined here. The
 * default value is "png" that is the common group used for imagens.
 * @returns A \c QPixmap object having the image data. If the image file
 * cannot be found the returned object will be \b NULL.
 * @sa asset_file()
 * @sa asset_image()
 * @since 1.1
 **/
QPixmap asset_pixmap(uint resID, const char* type = "png");
/*}}}*/
// SSXMLDocument asset_xml(uint resID, const char *type);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads an XML document from the assets resource.
 * @param resID Resource numerical alias.
 * @param type Resource type. All kinds of types can be defined here.
 * @return An \c SSXMLDocument object with the file contents. If the resource
 * doesn't contains a well-formed XML or cannot be found the returned object
 * will be empty.
 * @sa asset_file()
 * @since 1.1
 **/
SSXMLDocument asset_xml(uint resID, const char *type);
/*}}}*/
// SSMenu*       asset_menu(uint resID);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads a menu bar from a XML resource.
 * @param resID The numeric resource alias. This must be in a group of type
 * named "menu".
 * @returns A \c SSMenu object pointer with the resource contents. Notice that
 * the resource must be in an XML format as of stated in the @ref ssqt_menus
 * documentation. The caller is responsible of deleting this object with it is
 * non longer needed.
 * @remarks The resource is first loaded with the function \c asset_xml() and
 * then parsed with the \c SSMenu object.
 * @sa asset_popup()
 * @since 1.1
 **/
SSMenu* asset_menu(uint resID);
/*}}}*/
// SSMenuPopup*  asset_popup(uint resID);/*{{{*/
/**
 * \ingroup ssqt_assets
 * Loads a popup menu from an XML resource assets.
 * @param resID The numeric resource alias. This must be in a group of type
 * named "menu".
 * @returns A \c SSMenuPopup object pointer with the resource contents. Notice
 * that the resource must be in an XML format as of stated in the @ref
 * ssqt_menus documentation. The caller is responsible of deleting this object
 * with it is non longer needed.
 * @remarks The resource is first loaded with the function \c asset_xml() and
 * then parsed with the \c SSMenuPopup object.
 * @sa asset_menu()
 * @since 1.1
 **/
SSMenuPopup* asset_popup(uint resID);
/*}}}*/
};
///@} ssqt_assets

#endif /* __SSQTASST_HPP_DEFINED__ */
