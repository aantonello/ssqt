/**
 * @file
 * Declares the SSMainWnd class.
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
#ifndef __SSQTMAIN_HPP_DEFINED__
#define __SSQTMAIN_HPP_DEFINED__

#include <QMainWindow>
#include "ssqtcmn.hpp"
#include "ssqtxmle.hpp"
#include "ssqtxmld.hpp"
#include "ssqtmnui.hpp"
#include "ssqtmnup.hpp"
#include "ssqtmenu.hpp"

/**
 * \ingroup ssqt_ui
 * Main window application class.
 * This class extends \c QMainWindow providing some facilities used with menu
 * classes and others objects defined in this library. The default constructor
 * register the class instance in the SSApplication class instance if it was
 * created. This makes possible to get the SSMainWnd instance through its
 * member function SSApplication::mainWindow().
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSMainWnd : public QMainWindow
{
    Q_OBJECT

public:
    /** @name Constructors & Destructor */ //@{
    // explicit SSMainWnd(QWidget *parent = NULL, Qt::WindowFlags flags = 0);/*{{{*/
    /**
     * Default constructor.
     * Extends the standard constructor of \c QMainWindow.
     * @param parent Optional. Parent object.
     * @param flags Set of window flags. If not set Qt will define the default
     * value of \c Qt::Window.
     * @since 1.1
     **/
    explicit SSMainWnd(QWidget *parent = NULL, Qt::WindowFlags flags = 0);
    /*}}}*/
    //@}
public:
    /** @name SSMenu Operations */ //@{
    // SSMenu* loadMenu(uint resID);/*{{{*/
    /**
     * Loads a menu from a resource.
     * @param resID The numeric resource identifier. See the documentation of
     * \c SSMenu and the \c ss::asset_menu() function. Also read the XML
     * format specification at @ref ssqt_menus module.
     * @returns The created \c SSMenu object pointer. It will already been set
     * as the menu bar of this window.
     * @remarks The ownership of the menu is taken by this window.
     * @since 1.1
     **/
    SSMenu* loadMenu(uint resID);
    /*}}}*/
    // SSMenu* mainMenu() const;/*{{{*/
    /**
     * Retrieves the \c SSMenu instance bound to this window.
     * @return The \c SSMenu object pointer added as menu bar of this window.
     * @remarks This operations uses the \c qobject_cast() template function
     * to find out if the current \c QMenuBar instance is really an \c SSMenu
     * class. When not the result will be \b NULL.
     * @since 1.1
     **/
    SSMenu* mainMenu() const;
    /*}}}*/
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * SSMenu Operations {{{
 * ------------------------------------------------------------------------ */
// inline SSMenu* SSMainWnd::loadMenu(uint resID);/*{{{*/
inline SSMenu* SSMainWnd::loadMenu(uint resID) {
    SSMenu* menu = ss::asset_menu(resID);
    setMenuBar( menu ); return menu;
}
/*}}}*/
// inline SSMenu* SSMainWnd::mainMenu() const;/*{{{*/
inline SSMenu* SSMainWnd::mainMenu() const {
    return qobject_cast<SSMenu *>(menuBar());
}
/*}}}*/
// SSMenu Operations }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTMAIN_HPP_DEFINED__ */
