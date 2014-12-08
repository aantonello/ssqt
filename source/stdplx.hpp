/**
 * \file
 * Standard include file.
 * Used internally only.
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
#ifndef __STDPLX_HPP_DEFINED__
#define __STDPLX_HPP_DEFINED__

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

/**
 * \defgroup ssqt Super Simple library for Qt 5
 * This library adds some specific operations to Qt applications.
 **/

/**
 * \ingroup ssqt
 * \defgroup ssqt_xml XML Support
 * A super simple XML suport classes.
 **/

/**
 * \ingroup ssqt
 * \defgroup ssqt_funs Global Functions
 * The group contains all global declared functions provided by this library.
 * Notice that global functions are kept into the \c ss namespace.
 **/

/**
 * \ingroup ssqt
 * \defgroup ssqt_ui User Interface
 * Constants, classes, interfaces and templates for user interface
 * implementation.
 **/

/**
 * \ingroup ssqt_ui
 * \defgroup ssqt_menus Menus
 * Extended support for menu bars and popup menus.
 * This modules provides support for loading menus from resources. A menu
 * resource is a simple XML file where the menu structure is defined. The base
 * is a menu item, represented by the class \c SSMenuItem. This class extends
 * \c QAction providing the same functionality plus adding a numeric
 * identifier. Each item must have a unique numeric identifier or name, to be
 * recognized in the application. As a standard \c QAction object, the menu
 * item provides keyboard shortcuts and descriptions, shown in the status bar
 * of the main window. The XML element representing the menu item is as
 * follows:
 * \include menuitem.xml
 * All atributes are optional except \b id and \b name. If you provide an \b
 * id the \b name can be omited. In the same way, if you provide a \b name the
 * \b id is not needed. The \b id will fill the SSMenuItem::itemID() property.
 * The \b name atribute will be used to set the QObject::objectName() value.
 * The complete list of attributes are:
 * - \b id: The item numeric identifier. Must be unique for the entire menu at
 *   least. In the XML the value can be ser in decimal, octal or hexadecimal
 *   notation.
 * - \b name: The object name. Can be used instead of the \c id.
 * - \b text: Text that will be used as label to show in the popup menu.
 *   Notice that the ampersand character is invalid on XML files. You could
 *   use the entity name (&amp;) but that is too odd. As an aid the library
 *   supports the use of an underline character before the letter to show as
 *   keyboard "Alt"ernate shortcut. For example: "_Open" will present the
 *   letter 'O' underlinded when the "Alt" key is held.
 * - \b desc: Description to present in the status bar.
 * - \b keys: Keyboard shortcuts to activate the item. An item can have more
 *   than one. They are set specifying the keys names like <code>Ctrl+A</code>
 *   or <code>Ctrl+Shift+N</code>. The characters case doesn't matter. You can
 *   write <code>ctrl+o</code> or <code>CTRL+O</code>. The result will be the
 *   same. If more than one shortcut is provided you can separate then with
 *   commas: <code>Shift+Insert, Ctrl+V</code>. Spaces between keys names are
 *   ignored.
 * - \b icon: Menu items can have icons. Icons can be "ICO" images, "PNG"
 *   images, "BMP" images or any other type supported by Qt. Usually they are
 *   16 pixels wide by 16 pixels tall. You must provide the full path for the
 *   resource in this atribute. If you follow the guide for store imagens in
 *   this library the value of this attribute will be something like:
 *   <code>:/png/#1001</code>.
 * - \b checked: Should be set only if the item must show a checkbox. When
 *   this attribute is present the item is configured as checkable. The value
 *   is a string representing boolean values \b true or \b false.  This
 *   library accepts both "true" and "yes" as \e thruty values and "false" or
 *   "no" as \e falsy values. Again, character case doesn't matter.
 * - \b default: Used to set the default item of a popup menu. Available in
 *   some OSes. The item will be shown using a bold font to differenciate it
 *   from others items. Usually a default item mimics the action taken using
 *   a double click.
 * .
 * A separator is definded as an empty element called (guess) \c separator:
 * ~~~~~~~~~~~~~~~~{.xml}
 * <separator />
 * ~~~~~~~~~~~~~~~~
 * Separators can have all attributes set to a normal menu item. Separators
 * having icon and text will create sections as of the function \c
 * QMenu::addSection() was called. Others attributes are not used. Separators
 * can be found using the standard method SSMenuPopup::itemAt(). But will not
 * be found with the SSMenuPopup::itemWithID() method.
 * \par Popup Menus
 *
 * All items and separators must be children of an element called \b popup.
 * A \e popup can have a text and an identifier. When a \e popup menu is
 * added as children of another \e popup menu it will create an item having
 * the text and identifier defined in the \e popup element. Setting an
 * identifier to a popup menu is useful to search for it with the
 * SSMenuPopup::itemWithID() method, althouth popup menu items don't send
 * action signals when they are clicked by the user.
 * \include popupmenu.xml
 * Popup menus can be used alone, when you need a popup menu to show in
 * a widget, for example. So, a popup menu can reside on its own XML file, as
 * the root element. This allows you to reuse already defined popup menus in
 * the menu bar or in nested popup menus of popup menus. In those cases you
 * don't need to rewrite the popup menu in another XML file, you use the \e
 * ref attribute, as in the following example.
 * ~~~~~~~~~~~~~~~~{.xml}
 * <popup ref=":/menu/#2001" />
 * ~~~~~~~~~~~~~~~~
 * The library will load the popup menu in the file aliased by the \e #2001
 * identifier and totaly replace the \e popup element with the popup menu
 * loaded.
 * \par Menu
 *
 * The \b menu element is a special kind of element used only when you are
 * defining a list of \e popup menus to be used in the menu bar of the main
 * window (or another window) in your application. When the library finds the
 * \e menu element as root of a file it will automatically create a \c
 * QMenuBar object and add all \e popup menus defined in that menu bar.
 *
 * The \e menu element can have only \e popup elements as its children. When
 * you need to reuse already defined \e popup menus you can use the \e ref
 * attribute freely. The example below shows a (sort of) standard menu bar
 * where the "Edit" menu is reused.
 * \include menubar.xml
 *
 * And the "Edit" menu:
 * \include editmenu.xml
 **/

/**
 * \ingroup ssqt_ui
 * \defgroup ssqt_toolbar Toolbars
 * Support for toolbars and toolbar buttons.
 * The Qt library already provide support for advanced contruction of toolbars
 * with buttons and widgets of several forms including users extensions. The
 * \e ssqt library extends that funcionality providing the way to load toolbar
 * definitions from XML resources in the same way provided by \ref ssqt_menus
 * module.
 *
 * The basic class of this group is \c SSButtonItem. It is similar to \c
 * SSMenuItem. It has an \c itemID property holding its unique identifier.
 * This identifier can be set in the constructor or in the XML resource. When
 * the \c QToolBar::actionTriggered() signal is called this property can be
 * queried to assure the source button clicked.
 *
 * The XML format for specifying the toolbar resource is similar to the XML
 * used in menus. By the way, button itens can also have popup menus shown
 * when they are clicked. See the following example:
 * \include toolbar.xml
 * With this example you can see that the structure is almost the same as the
 * XML used to set menus. The root element is a "toolbar" element. It can have
 * only "button" and "separator" elements. The "button" element can be
 * identified by its unique identifier, defined in the "id" attribute, or by
 * its object name, defined in the "name" attribute. The attributes accepted
 * by the "button" element are:
 * - \b id: The unique identifier of the button. Can be retrieved by \c
 *   SSButtonItem::itemID() member function. It is a standard Qt property so
 *   it also can be retrieved using \c QObject::property() member function.
 * - \b name: If set will be used to define the object name. It must be
 *   a valid object name for this purpose.
 * - \b title: Toolbar buttons usually show icons so the user can identify its
 *   operations. Texts are shown in the button's tooltip window. This depends
 *   on the style set in the \c QToolBar object or \c QMainWindow object. See
 *   the documentation of those objects to understand how this works. This
 *   value will be used in the \c QAction::toolTip() member function. Notice
 *   that this text doesn't accept the "ALT" modifier like in the \c
 *   SSMenuItem structure.
 * - \b keys: Keyboard shortcut to this button. This works in the same way as
 *   in the \c SSMenuItem object. Set keyboard shortcuts for buttons that
 *   don't have menu counter parts.
 * - \b icon: Buttons usually have icons. You can set the icon image for
 * a button in two ways:
 *   -# Using the complete path to the image, like: <code>:/ico/#3001</code>.
 *   -# Using only the image alias, like: <code>#3001</code>. When set like
 *      this the image must lie in the "ico" resource group. See \ref
 *      ssqt_assets module.
 *   .
 * - \b checked: Sets this button as \e checkable. The presence of the
 *   attribute is enough to set the button as \e checkable. The attribute
 *   value, \b true or \b false, define if it will be first shown checked or
 *   not.
 * - \b enabled: Sets the button \e enabled or \e disabled. When this
 *   attribute is not set the button is enabled. The attribute's value can be
 *   \b true or \b false. Anything different and the attribute is treated as
 *   of it was \b false.
 * .
 * \c SSButtonItem can also show menus. So the "button" element accepts
 * "popup" elements as it's child. Only one "popup" element is accepted. The
 * menu will be shown when the button is clicked. If you need a button that
 * does an action when clicked and shows a menu by an attached down arrow key
 * you should use the \c QToolButton object. Create one, set it up and add it
 * using the \c QWidgetAction::setDefaultWidget() member function.
 **/

/**
 * @internal
 * @{ *//* ---------------------------------------------------------------- */
#define SS_MENU_NODE_ITEM           "item"
#define SS_MENU_NODE_SEPARATOR      "separator"
#define SS_MENU_NODE_POPUP          "popup"
#define SS_MENU_NODE_MENU           "menu"

#define SS_MENU_ATTR_ID             "id"
#define SS_MENU_ATTR_NAME           "name"
#define SS_MENU_ATTR_TEXT           "text"
#define SS_MENU_ATTR_DESC           "desc"
#define SS_MENU_ATTR_KEYS           "keys"
#define SS_MENU_ATTR_ICON           "icon"
#define SS_MENU_ATTR_CHECKED        "checked"
#define SS_MENU_ATTR_DEFAULT        "default"
#define SS_MENU_ATTR_REF            "ref"

#define SS_XML_NODE_TOOLBAR         "toolbar"
#define SS_XML_NODE_BUTTON          "button"
#define SS_XML_ATTR_ENABLED         "enabled"
///@} internal

#endif /* __STDPLX_HPP_DEFINED__ */
