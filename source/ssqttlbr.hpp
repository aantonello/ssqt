/**
 * @file
 * Declares de SSToolbar class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 08, 2014
 * @since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTTLBR_HPP_DEFINED__
#define __SSQTTLBR_HPP_DEFINED__

#include <QToolBar>
#include "ssqttlbi.hpp"
#include "ssqtxmld.hpp"

/**
 * \ingroup ssqt_toolbar
 * A toolbar class.
 * This class extends \c QToolBar allowing toolbar definitions to be loaded
 * from an XML resource file. When loaded from an XML resource each button is
 * a \c SSButtonItem object instance, providing an unique identifier for each
 * button. \c SSToolbar also accepts \c QAction, \c QWidgetAction and \c
 * QToolButton as buttons. You can set them directly.
 *//* --------------------------------------------------------------------- */
class SSToolbar : public QToolBar
{
    Q_OBJECT

public:
    /** @name Constructors & Destructor */ //@{
    // explicit SSToolbar(QWidget *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent Parent widget. Can be \b NULL.
     * @since 1.1
     **/
    explicit SSToolbar(QWidget *parent = NULL);
    /*}}}*/
    // SSToolbar(const QString &title, QWidget *parent = NULL);/*{{{*/
    /**
     * Constructs a toolbar widget.
     * @param title Used to name the window when the toolbar is shown in
     * a floating toolbox.
     * @param parent Parent widget. Can be \b NULL.
     * @since 1.1
     **/
    SSToolbar(const QString &title, QWidget *parent = NULL);
    /*}}}*/
    // SSToolbar(uint resID, QWidget *parent = NULL);/*{{{*/
    /**
     * Constructs a toolbar from an XML resource.
     * @param resID The XML identifier.
     * @param parent Parent widget. Can be \b NULL.
     * @since 1.1
     **/
    SSToolbar(uint resID, QWidget *parent = NULL);
    /*}}}*/
    //@}

public:
    /** @name Attributes */ //@{
    // SSButtonItem* buttonItem(uint buttonID) const;/*{{{*/
    /**
     * Search for a button with the specified identifier.
     * @param buttonID The button identifier.
     * @returns The \c SSButtonItem instance. If the identifier is not found
     * the result will be \b NULL.
     * @since 1.1
     **/
    SSButtonItem* buttonItem(uint buttonID) const;
    /*}}}*/
    // SSButtonItem* buttonAt(uint index) const;/*{{{*/
    /**
     * Gets a button at the specified index.
     * @param index Zero based index of the button to get.
     * @return The \c SSButtonItem instance or \b NULL if the value passed at
     * \a index is invalid.
     * @remarks The function uses the \c qobject_cast() Qt template function
     * to convert the \c QAction at the specified position in \c SSButtonItem.
     * When the \c QAction at the specified position is \b NULL or is not an
     * \c SSButtonItem object the result will be \b NULL.
     * @since 1.1
     **/
    SSButtonItem* buttonAt(uint index) const;
    /*}}}*/
    //@}

public:
    /** @name Operations */ //@{
    // bool init(uint resID);/*{{{*/
    /**
     * Initializes this object using the resource with specified identifier.
     * @param resID The identifier of the XML resource with the toolbar
     * structure. This value is converted to a number in decimal notation and
     * used to find the resource which alias is <code>:/toolbar/#resID</code>.
     * @return \b true when the function succeeds. Otherwise \b false.
     * @since 1.1
     **/
    bool init(uint resID);
    /*}}}*/
    // bool init(const QString &filePath);/*{{{*/
    /**
     * Initializes this object using the file specified.
     * @param filePath Path name of the file having the XML with the toolbar
     * structure. Can be a disk file or a resource file.
     * @return \b true when the function succeeds. Otherwise \b false.
     * @since 1.1
     **/
    bool init(const QString &filePath);
    /*}}}*/
    // bool init(SSXMLDocument *doc);/*{{{*/
    /**
     * Initializes this toolbar with the data from the passed document.
     * @param doc The document having the toolbar structure. The root element
     * of this object must be "toolbar".
     * @return \b true when the function succeeds. Otherwise \b false.
     * @since 1.1
     **/
    bool init(SSXMLDocument *doc);
    /*}}}*/
    //@}
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline SSToolbar::SSToolbar(QWidget *parent = NULL);/*{{{*/
inline SSToolbar::SSToolbar(QWidget *parent) : QToolBar(parent) { }
/*}}}*/
// inline SSToolbar::SSToolbar(const QString &title, QWidget *parent = NULL);/*{{{*/
inline SSToolbar::SSToolbar(const QString &title, QWidget *parent) : QToolBar(title, parent) { }
/*}}}*/
// inline SSToolbar::SSToolbar(uint resID, QWidget *parent = NULL);/*{{{*/
inline SSToolbar::SSToolbar(uint resID, QWidget *parent) : QToolBar(parent) {
    init(resID);
}
/*}}}*/
// Constructors & Destructor }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTTLBR_HPP_DEFINED__ */
