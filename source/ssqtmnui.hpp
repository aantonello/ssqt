/**
 * @file
 * Declares the SSMenuItem class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   novembro 16, 2014
 * @since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSMENUITEM_H_DEFINED__
#define __SSMENUITEM_H_DEFINED__

#include <QAction>
#include "ssqtcmn.hpp"
#include "ssqtxmle.hpp"
class SSMenuPopup;

/**
 * @ingroup ssqt_menus
 * Represents a menu item.
 * The class extends \c QAction providing the same functionality as a normal
 * menu item used by Qt. Also, the class adds the itemID() property allowing
 * menu itens to have numerical identifiers.
 *
 * Menu itens are defined in XML files loaded by the @ref ssqt_assets module.
 * The format of the XML file is defined in the documentation of the @ref
 * ssqt_menus module.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSMenuItem : public QAction
{
    Q_OBJECT
    Q_PROPERTY(uint itemID READ itemID)
    Q_PROPERTY(SSMenuPopup* subMenu READ subMenu WRITE subMenu)

public:
    // explicit SSMenuItem(QObject *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent The parent (owner) object. Can be \b NULL.
     * @since 1.1
     **/
    explicit SSMenuItem(QObject *parent = NULL);
    /*}}}*/
    // SSMenuItem(uint itemID, QObject *parent = NULL);/*{{{*/
    /**
     * Simple constructor.
     * @param itemID This item identifier.
     * @param parent The parent (owner) object. Can be \b NULL.
     * @remarks This constructor can be used to create a menu item manually.
     * Without needing an XML file.
     * @since 1.1
     **/
    SSMenuItem(uint itemID, QObject *parent = NULL);
    /*}}}*/
    // SSMenuItem(const SSMenuItem &item, QObject *parent = NULL);/*{{{*/
    /**
     * Copy constructor.
     * @param item An already defined \c SSMenuItem object to be copied.
     * @param parent The parent (owner) object. Can be \b NULL.
     * @since 1.1
     **/
    SSMenuItem(const SSMenuItem &item, QObject *parent = NULL);
    /*}}}*/
    // SSMenuItem(SSXMLElement *element, QObject *parent = NULL);/*{{{*/
    /**
     * Parametrized constructor.
     * @param element The \c SSXMLElement having the element to load this item
     * attributes and values. Must follow the rules described in @ref
     * ssqt_menus module.
     * @param parent The parent (owner) object. Can be \b NULL.
     * @since 1.1
     **/
    SSMenuItem(SSXMLElement *element, QObject *parent = NULL);
    /*}}}*/

public:         // Properties
    // uint itemID() const;/*{{{*/
    /**
     * Retrieves the identifier os this item.
     * @return An unsigned integer with the numerical identifier set in the
     * constructor or by the XML element.
     * @since 1.1
     **/
    uint itemID() const;
    /*}}}*/
    // SSMenuPopup* subMenu() const;/*{{{*/
    /**
     * Gets the sub menu shown by this item.
     * @returns A pointer to the popup menu class. Notice that this return
     * will be valid only when this item shows a popup menu. When not, the
     * result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* subMenu() const;
    /*}}}*/
    // void subMenu(SSMenuPopup *menu);/*{{{*/
    /**
     * Sets the sub menu shown by this item.
     * @param menu \c SSMenuPopup shown by this item. Can be \b NULL to remove
     * a sub menu reference. The popup menu ownership is not taken by this
     * item.
     * @since 1.1
     **/
    void subMenu(SSMenuPopup *menu);
    /*}}}*/

public:         // Operations
    // SSMenuItem& assign(const SSMenuItem &item);/*{{{*/
    /**
     * Copy the properties and values of another item.
     * @param item Menu item to copy from.
     * @returns \b this.
     * @since 1.1
     **/
    SSMenuItem& assign(const SSMenuItem &item);
    /*}}}*/

public:         // Overloaded Operators
    // SSMenuItem& operator=(const SSMenuItem &item);/*{{{*/
    /**
     * Copy operator.
     * @param item Menu item to copy from.
     * @returns \b this.
     * @since 1.1
     **/
    SSMenuItem& operator=(const SSMenuItem &item);
    /*}}}*/

protected:      // Implementation
    // void init(SSXMLElement *element);/*{{{*/
    /**
     * This item internal initialization.
     * @param element The XML element with the item's properties. Must follow
     * the format described in @ref ssqt_menus module.
     * @since 1.1
     **/
    void init(SSXMLElement *element);
    /*}}}*/

private:        // Data Members
    uint m_id;                  /**< Menu item unique identifier.   */
    SSMenuPopup *m_menu;        /**< When this item show a sub menu.    */
};
/* Inline Functions {{{ */
/* ------------------------------------------------------------------------ */
/*! @name Constructors *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline SSMenuItem::SSMenuItem(QObject *parent = NULL);/*{{{*/
inline SSMenuItem::SSMenuItem(QObject *parent) : QAction(parent),
    m_id(0), m_menu(NULL) { }
/*}}}*/
// inline SSMenuItem::SSMenuItem(uint itemID, QObject *parent = NULL);/*{{{*/
inline SSMenuItem::SSMenuItem(uint itemID, QObject *parent) : QAction(parent),
    m_id(itemID), m_menu(NULL) { }
/*}}}*/
// inline SSMenuItem::SSMenuItem(const SSMenuItem &item, QObject *parent = NULL);/*{{{*/
inline SSMenuItem::SSMenuItem(const SSMenuItem &item, QObject *parent) :
    QAction(parent), m_id(0), m_menu(NULL) { assign(item); }
/*}}}*/
// inline SSMenuItem::SSMenuItem(SSXMLElement *element, QObject *parent = NULL);/*{{{*/
inline SSMenuItem::SSMenuItem(SSXMLElement *element, QObject *parent) : QAction(parent),
    m_id(0), m_menu(NULL) { init(element); }
/*}}}*/
///@} Constructors /*}}}*/
/* ------------------------------------------------------------------------ */
/*! @name Properties *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline uint SSMenuItem::itemID() const;/*{{{*/
inline uint SSMenuItem::itemID() const {
    return m_id;
}
/*}}}*/
// inline SSMenuPopup* SSMenuItem::subMenu() const;/*{{{*/
inline SSMenuPopup* SSMenuItem::subMenu() const {
    return m_menu;
}
/*}}}*/
// inline void SSMenuItem::subMenu(SSMenuPopup *menu);/*{{{*/
inline void SSMenuItem::subMenu(SSMenuPopup *menu) {
    m_menu = menu;
}
/*}}}*/
///@} Properties /*}}}*/
/* ------------------------------------------------------------------------ */
/*! @name Overloaded Operators *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline SSMenuItem& SSMenuItem::operator=(const SSMenuItem &item);/*{{{*/
inline SSMenuItem& SSMenuItem::operator=(const SSMenuItem &item) {
    return assign(item);
}
/*}}}*/
///@} Overloaded Operators /*}}}*/
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSMENUITEM_H_DEFINED__ */

