/**
 * @file
 * Declares de SSMenu class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   novembro 19, 2014
 * @since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTMENU_HPP_DEFINED__
#define __SSQTMENU_HPP_DEFINED__

#include <QList>
#include <QMenuBar>
#include <QWidget>
#include "ssqtcmn.hpp"
#include "ssqtxmle.hpp"
#include "ssqtxmld.hpp"
#include "ssqtmnup.hpp"
#include "ssqtasst.hpp"

/**
 * \ingroup ssqt_menus
 * Implements a menu bar.
 * The class extends the \c QMenuBar class providing the standard operation
 * already used in Qt. Despite been backup up by a file in XML format, the
 * format is not the same as used by Qt. Qt uses a format, included in the
 * ".ui" files, used only by the compiler to generate the code needed to build
 * the menu. This library has a different approach. The XML file is kept on
 * its original form and added as a resource in the application. We believe
 * that keeping the data in a text format is the most easiest way to maintain
 * the data and make changes.
 *
 * In a \c SSMenu class each menu is kept as a \c SSMenuPopup object, that
 * extends \c QMenu also providing standard Qt functioning. On a \c
 * SSMenuPopup object each item is kept as a \c SSMenuItem object, that
 * extends \c QAction. So, in the end, the menu bar, popup menus and items
 * will look and behave exactly as any other menu bar in any other Qt
 * application.
 *
 * \par Handling Signals
 *
 * As a common \c QMenuBar object the \c SSMenu supports connections to the
 * inherited signals \c hovered(QAction*) and \c triggered(QAction*). The \c
 * QAction argument can be casted to a \c SSMenuItem object since is
 * really it. As in the following example:
 * ~~~~~~~~~~~~~~~
 * void MyObject::handle_MainMenuBarTriggeredSignal(QAction *action)
 * {
 *     SSMenuItem *item = static_cast<SSMenuItem *>(action);
 *
 *     // Get the item identifier and check it.
 *     switch (item->itemID())
 *     {
 *     case IDM_FILE_OPEN:
 *         // Code to open a file...
 *         break;
 *         // etc...
 *     }
 * }
 * ~~~~~~~~~~~~~~~
 *
 * \par Using Menus
 *
 * If you already has a \c QMainWindow object and want to use a \c SSMenu with
 * it you are already covered. Just load your XML menu using the \c
 * ss::asset_menu() function and set it in your \c QMainWindow instance. Check
 * the example:
 * ~~~~~~~~~~~~~~~
 * QMainWindow mainWindow;
 *
 * mainWindow.setMenuBar( ss::asset_menu(IDM_MY_MENU_RESOURCE) );
 * ~~~~~~~~~~~~~~~
 * The ownership of the pointer returned by \c ss::asset_menu() is passed to
 * \c QMainWindow that will release the pointer when its go out of scope.
 *
 * You could also use the \c SSMainWnd class and use its \c loadMenu() method:
 * ~~~~~~~~~~~~~~~
 * SSMainWnd mainWnd;
 *
 * mainWnd.loadMenu(IDM_MY_MENU_RESOURCE);
 * ~~~~~~~~~~~~~~~
 * In both cases the \c QMainWindow::menuBar() member function will return
 * a pointer to the \c SSMenu instance created. When you use the \c
 * QMainWindow::menuBar() you will need to cast the returned pointer. You can
 * avoid this if you use the \c SSMainWnd::mainMenu() member function.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSMenu : public QMenuBar
{
    Q_OBJECT

public:
    /** @name Constructor & Destructor */ //@{
    // explicit SSMenu(QWidget *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent Pointer to the object that is the parent widget of the
     * menu bar. Can be \b NULL. The parenthood will be applied when the menu
     * bar is added to a widget.
     * @since 1.1
     **/
    explicit SSMenu(QWidget *parent = NULL);
    /*}}}*/
    // SSMenu(SSXMLDocument *document, QWidget *parent = NULL);/*{{{*/
    /**
     * Builds a menu bar from an XML document.
     * @param document The XML document having the menu bar especification.
     * The format of the XML file is defined in the @ref ssqt_menus module.
     * @param parent Pointer to the object that is the parent widget of the
     * menu bar. Can be \b NULL. The parenthood will be applied when the menu
     * bar is added to a widget.
     * @since 1.1
     **/
    SSMenu(SSXMLDocument *document, QWidget *parent = NULL);
    /*}}}*/
    // SSMenu(const QString &fileName,  QWidget *parent = NULL);/*{{{*/
    /**
     * Builds a menu bar from a XML file on disc or resource.
     * @param fileName XML file name. If this file is on a disc must be an
     * absolute path. If it is a resource file the path must start with
     * a colon character. The XML format especification is defined in the @ref
     * ssqt_menus module documentation.
     * @param parent Pointer to the object that is the parent widget of the
     * menu bar. Can be \b NULL. The parenthood will be applied when the menu
     * bar is added to a widget.
     * @since 1.1
     **/
    SSMenu(const QString &fileName,  QWidget *parent = NULL);
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // size_t size() const;/*{{{*/
    /**
     * Size of this menu bar.
     * @returns Number of popup menus present in this menu bar.
     * @since 1.1
     **/
    size_t size() const;
    /*}}}*/
    // SSMenuPopup* menuAt(uint index) const;/*{{{*/
    /**
     * Gets an item of this menu bar.
     * @param index Zero based index of the popup menu requested.
     * @returns A pointer to the \c SSMenuPopup object positioned at the index
     * \a index. If \a index is not valid the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* menuAt(uint index) const;
    /*}}}*/
    //@}
public:
    /** @name SSMenuPopup Operations */ //@{
    // SSMenuPopup* addPopup(SSMenuPopup *popup);/*{{{*/
    /**
     * Append a popup menu to the end of this menu bar.
     * @param popup Pointer to the object to be added.
     * @return When succeeded the result is the same value passed through \a
     * popup. Otherwise the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(SSMenuPopup *popup);
    /*}}}*/
    // SSMenuPopup* addPopup(SSXMLElement *element);/*{{{*/
    /**
     * Build and add a popup menu to the end of this menu bar.
     * @param element Object with the menu structure. This object must be
     * a "popup" element. Check the documentation for a popup menu in an XML
     * file in the @ref ssqt_menus module.
     * @return On success a pointer to the \c SSMenuPopup object created.
     * Otherwise the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(SSXMLElement *element);
    /*}}}*/
    // SSMenuPopup* addPopup(const QString &fileName);/*{{{*/
    /**
     * Build and add a popup menu to the end of this menu bar.
     * @param fileName XML file name. If this file is on a disc must be an
     * absolute path. If it is a resource file the path must start with
     * a colon character. The XML format especification is defined in the @ref
     * ssqt_menus module documentation.
     * @remarks The root element of this file must be a "popup" element.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(const QString &fileName);
    /*}}}*/
    //@}
public:
    /** @name SSMenu Operations */ //@{
    // error_t loadMenu(SSXMLDocument *document);/*{{{*/
    /**
     * Loads a menu from an XML document.
     * @param document The XML document having the menu bar especification.
     * The format of the XML file is defined in the @ref ssqt_menus module.
     * @returns On success the result is \c SSNO_ERROR. Otherwise an error
     * code will be returned.
     * @remarks The root element of the XML document must be a "menu" element.
     * @since 1.1
     **/
    error_t loadMenu(SSXMLDocument *document);
    /*}}}*/
    // error_t loadMenu(const QString &fileName);/*{{{*/
    /**
     * Loads a menu from an XML file.
     * @param fileName XML file name. If this file is on a disc must be an
     * absolute path. If it is a resource file the path must start with
     * a colon character. The XML format especification is defined in the @ref
     * ssqt_menus module documentation.
     * @returns On success the result is \c SSNO_ERROR. Otherwise an error
     * code will be returned.
     * @remarks The root element of the XML document must be a "menu" element.
     * @since 1.1
     **/
    error_t loadMenu(const QString &fileName);
    /*}}}*/
    // error_t loadMenu(uint resID);/*{{{*/
    /**
     * Loads a menu from an XML resource file.
     * @param resID The numerical resource identifier. This is used to load an
     * XML file through the assets standard using the type "menu". The
     * standard build a path using the numerical identifier as the resource
     * alias: <code>:/menu/\#resID</code>.
     * @returns On success the result is \c SSNO_ERROR. Otherwise an error
     * code will be returned.
     * @remarks The root element of the XML document must be a "menu" element.
     * @sa ss::asset_menu()
     * @since 1.1
     **/
    error_t loadMenu(uint resID);
    /*}}}*/
    //@}
protected:
    QList<SSMenuPopup*> m_list;
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructor & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline SSMenu::SSMenu(QWidget *parent = NULL);/*{{{*/
inline SSMenu::SSMenu(QWidget *parent) : QMenuBar(parent) { }
/*}}}*/
// inline SSMenu::SSMenu(SSXMLDocument *document, QWidget *parent = NULL);/*{{{*/
inline SSMenu::SSMenu(SSXMLDocument *document, QWidget *parent) : QMenuBar(parent) {
    loadMenu(document);
}
/*}}}*/
// inline SSMenu::SSMenu(const QString &fileName,  QWidget *parent = NULL);/*{{{*/
inline SSMenu::SSMenu(const QString &fileName,  QWidget *parent) : QMenuBar(parent) {
    loadMenu(fileName);
}
/*}}}*/
// Constructor & Destructor }}}
/* ---------------------------------------------------------------------------
 * Attributes {{{
 * ------------------------------------------------------------------------ */
// inline size_t SSMenu::size() const;/*{{{*/
inline size_t SSMenu::size() const {
    return m_list.size();
}
/*}}}*/
// inline SSMenuPopup* SSMenu::menuAt(uint index) const;/*{{{*/
inline SSMenuPopup* SSMenu::menuAt(uint index) const {
    if (index >= (uint)m_list.size()) return NULL;
    return m_list.at(index);
}
/*}}}*/
// Attributes }}}
/* ---------------------------------------------------------------------------
 * SSMenuPopup Operations {{{
 * ------------------------------------------------------------------------ */
// inline SSMenuPopup* SSMenu::addPopup(SSMenuPopup *popup);/*{{{*/
inline SSMenuPopup* SSMenu::addPopup(SSMenuPopup *popup) {
    addMenu((QMenu*)popup); m_list.append(popup);
    return popup;
}
/*}}}*/
// inline SSMenuPopup* SSMenu::addPopup(SSXMLElement *element);/*{{{*/
inline SSMenuPopup* SSMenu::addPopup(SSXMLElement *element) {
    return addPopup(new SSMenuPopup(element));
}
/*}}}*/
// inline SSMenuPopup* SSMenu::addPopup(const QString &fileName);/*{{{*/
inline SSMenuPopup* SSMenu::addPopup(const QString &fileName) {
    SSMenuPopup *popup = addPopup(new SSMenuPopup());
    popup->loadMenu(fileName);
    return popup;
}
/*}}}*/
// SSMenuPopup Operations }}}
/* ---------------------------------------------------------------------------
 * SSMenu Operations {{{
 * ------------------------------------------------------------------------ */
// inline error_t SSMenu::loadMenu(const QString &fileName);/*{{{*/
inline error_t SSMenu::loadMenu(const QString &fileName) {
    SSXMLDocument document(fileName);
    return loadMenu( &document );
}
/*}}}*/
// inline error_t SSMenu::loadMenu(uint resID);/*{{{*/
inline error_t SSMenu::loadMenu(uint resID) {
    SSXMLDocument document = assets::xml(resID, "menu");
    return loadMenu(&document);
}
/*}}}*/
// SSMenu Operations }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTMENU_HPP_DEFINED__ */
