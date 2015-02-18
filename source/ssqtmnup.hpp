/**
 * @file
 * Declares the SSMenuPopup class.
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
#ifndef __SSQTMNUP_HPP_DEFINED__
#define __SSQTMNUP_HPP_DEFINED__

#include <QMenu>
#include <QWidget>
#include "ssqtmnui.hpp"
#include "ssqtxmld.hpp"

/**
 * @ingroup ssqt_menus
 * Represents a popup menu.
 * The class extends \c QMenu providing standard behavior for a menu in Qt.
 * Items of a popup menu are \c SSMenuItem classes. The \c SSMenuItem extends
 * \c QAction also providing standard Qt behavior.
 *
 * Popup menus can be constructed manually or, more often, loaded from
 * a resource. Popup menu resources are XML files having a structure described
 * in the documentation of @ref ssqt_menus module.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSMenuPopup : public QMenu
{
    /** @internal *//// @{
    Q_OBJECT
    Q_PROPERTY(uint itemID READ itemID)
    ///@}

public:
    // explicit SSMenuPopup(QWidget *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent The parent widget of the popup menu. If not set the
     * parent child relationship will be set when this popup menu is used.
     * @since 1.1
     **/
    explicit SSMenuPopup(QWidget *parent = NULL);
    /*}}}*/
    // SSMenuPopup(const QString &text, QWidget *parent = NULL);/*{{{*/
    /**
     * Loads a popup menu to be appended in another popup menu.
     * @param text Text to be shown in the item that will expose this popup
     * menu.
     * @param parent The parent widget of the popup menu. If not set the
     * parent child relationship will be set when this popup menu is used.
     * @since 1.1
     **/
    SSMenuPopup(const QString &text, QWidget *parent = NULL);
    /*}}}*/
    // SSMenuPopup(SSXMLElement *element, QWidget *parent = NULL);/*{{{*/
    /**
     * Loads a popup menu from an XML element.
     * @param element \c SSXMLElement with the popup menu especification.
     * @param parent The parent widget of the popup menu. If not set the
     * parent child relationship will be set when this popup menu is used.
     * @since 1.1
     **/
    SSMenuPopup(SSXMLElement *element, QWidget *parent = NULL);
    /*}}}*/
    // virtual ~SSMenuPopup();/*{{{*/
    /**
     * Default destructor.
     * @since 1.1
     **/
    virtual ~SSMenuPopup();
    /*}}}*/

public:
    /** @name Properties */ //@{    
    // uint itemID() const;/*{{{*/
    /**
     * Retrieves this popup identifier.
     * @return A unsigned integer value, if one was set in the XML file.
     * Otherwise the result will be \b 0.
     * @since 1.1
     **/
    uint itemID() const;
    /*}}}*/
    //@}
public:
    /** @name Attributes */ //@{
    // size_t size() const;/*{{{*/
    /**
     * Number of items in this popup menu.
     * @return The number of items in this popup menu. All items are counted,
     * including items that shows others popup menus.
     * @since 1.1
     **/
    size_t size() const;
    /*}}}*/
    // int    indexOf(SSMenuPopup *popup) const;/*{{{*/
    /**
     * Search for an item that shows a popup menu in this popup menu.
     * @param popup Pointer to the popup menu hose item will show. Cannot be
     * \b NULL.
     * @return If the function succeeds the result is the index position, zero
     * based, of the item that shows the popup menu. If the function fails,
     * the result will be -1.
     * @remarks When a popup menu is added to another popup menu this library
     * creates a \c SSMenuItem object to hold the popup menu. The index
     * returned by this function is the index of the \c SSMenuItem created.
     * Through it you can retrieve the popup menu using the method
     * SSMenuItem::subMenu().
     * @since 1.1
     **/
    int    indexOf(SSMenuPopup *popup) const;
    /*}}}*/
    // int    indexOf(SSMenuItem *menuItem) const;/*{{{*/
    /**
     * Search for an item in this popup menu.
     * @param menuItem Pointer to the item to be searched.
     * @return When succeeded the result is the index position, zero based, of
     * the item in the list. If the function fails the result is \b -1.
     * @since 1.1
     **/
    int    indexOf(SSMenuItem *menuItem) const;
    /*}}}*/
    // int    indexOf(uint itemID) const;/*{{{*/
    /**
     * Search for an item with the specified identifier.
     * @param itemID Identifier of the item to search for.
     * @return When succeeded the result is the index position, zero based, of
     * the item in the list. If the function fails the result is \b -1.
     * @since 1.1
     **/
    int    indexOf(uint itemID) const;
    /*}}}*/
    // SSMenuItem* itemAt(uint position) const;/*{{{*/
    /**
     * Gets a pointer to an item in the list.
     * @param position Zero based position of the item requested.
     * @return A pointer to the item in the specified position means success.
     * If the passed position is invalid the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuItem* itemAt(uint position) const;
    /*}}}*/
    // SSMenuItem* itemWithID(uint itemID) const;/*{{{*/
    /**
     * Gets a pointer of an item with the specified identifier.
     * @param itemID Identifier of the item requested.
     * @return A pointer to an item with the specified identifier means
     * success. If the identifier could not be found the result will be \b
     * NULL.
     * @since 1.1
     **/
    SSMenuItem* itemWithID(uint itemID) const;
    /*}}}*/
    // SSMenuItem* itemWithName(const QString &name) const;/*{{{*/
    /**
     * Finds an item having the specified name.
     * @param name Name of the item. This must be equals the value of the
     * "name" attribute used in the XML file where the item was defined. Names
     * are case sensitive.
     * @return The \c SSMenuItem object pointer means success. If no item was
     * found the result is \b NULL.
     * @since 1.1
     **/
    SSMenuItem* itemWithName(const QString &name) const;
    /*}}}*/
    // SSMenuPopup* menuAt(uint position) const;/*{{{*/
    /**
     * Gets a pointer of a popup menu show by an item in this popup menu.
     * @param position Zero based position of the popup menu in the list.
     * @return The pointer of the popup menu means success. When the position
     * is invalid or doesn't have a popup menu object the result will be \b
     * NULL.
     * @since 1.1
     **/
    SSMenuPopup* menuAt(uint position) const;
    /*}}}*/
    //@}
public:
    /** @name SSMenuItem Operations */ //@{
    // SSMenuItem* addItem(SSMenuItem *item);/*{{{*/
    /**
     * Adds an item in this popup menu.
     * @param item Item to be added. It will be appended at the end of the
     * list.
     * @return When succeeded the result is the same value passed in the \a
     * item argument. If the function fails, the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuItem* addItem(SSMenuItem *item);
    /*}}}*/
    // SSMenuItem* addItem(const QString &text, uint itemID);/*{{{*/
    /**
     * Adds a new item in this popup menu.
     * @param text Text for the new item.
     * @param itemID Identifier of the item.
     * @return When succeeded the result is the item created. If the function
     * fails, the result will be \b NULL.
     * @remarks The function creates a new object \c SSMenuItem and add it to
     * the end of the list.
     * @since 1.1
     **/
    SSMenuItem* addItem(const QString &text, uint itemID);
    /*}}}*/
    // SSMenuItem* addItem(SSXMLElement *element);/*{{{*/
    /**
     * Adds an item to the list of this popup menu.
     * @param element \c SSXMLElement with the item configuration.
     * @return When succeeded the result is the item created. If the function
     * fails, the result will be \b NULL.
     * @remarks The item will be created based on the XML element passed. This
     * XML cannot be related to a popup menu. If an XML element having a popup
     * menu configuration is passed to this function the result will be \b
     * NULL and nothing will be added. Use the #addPopup(SSXMLElement*) then.
     * @since 1.1
     **/
    SSMenuItem* addItem(SSXMLElement *element);
    /*}}}*/
    //@}
public:
    /** @name SSMenuPopup Operations */ //@{
    // SSMenuPopup* addPopup(SSMenuPopup *popup);/*{{{*/
    /**
     * Append a popup menu to this popup menu.
     * @param popup The popup menu to be appended.
     * @return If the function succeeds the result is the same object pointer
     * passed through the \a popup argument. Otherwise the result is \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(SSMenuPopup *popup);
    /*}}}*/
    // SSMenuPopup* addPopup(const QString &text);/*{{{*/
    /**
     * Adds a new popup menu to this popup menu.
     * @param text Text of the item that will open the popup menu.
     * @return A pointer to the popup menu created. \b NULL if the function
     * fails.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(const QString &text);
    /*}}}*/
    // SSMenuPopup* addPopup(SSXMLElement *element);/*{{{*/
    /**
     * Adds a popup menu to the list of this popup menu.
     * @param element XML element having the popup menu configuration.
     * @return If the function succeeds the result the a pointer of the popup
     * menu object created. Otherwise the result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* addPopup(SSXMLElement *element);
    /*}}}*/
    //@}
public:
    /** @name Operations */ //@{
    // error_t loadMenu(SSXMLElement *element);/*{{{*/
    /**
     * Loads a popup menu from an XML element.
     * @param element \c SSXMLElement having the configuration of the popup
     * menu.
     * @returns An error code if the function succeeds the result will be \c
     * SSNO_ERROR.
     * @since 1.1
     **/
    error_t loadMenu(SSXMLElement *element);
    /*}}}*/
    // error_t loadMenu(SSXMLDocument *document);/*{{{*/
    /**
     * Loads a popup menu from an XML document.
     * @param document \c SSXMLDocument with the popup menu configuration.
     * @returns An error code if the function succeeds the result will be \c
     * SSNO_ERROR.
     * @since 1.1
     **/
    error_t loadMenu(SSXMLDocument *document);
    /*}}}*/
    // error_t loadMenu(const QString &menuResource);/*{{{*/
    /**
     * Loads a popup menu from a resource or file on disk.
     * @param menuResource String with the path of the file or resource. If
     * this is a file the path must be absolute. If it is a resource the
     * string must start with colons. A possible value for a popup menu in
     * a resource is ":/menus/\#2001".
     * @returns An error code if the function succeeds the result will be \c
     * SSNO_ERROR.
     * @since 1.1
     **/
    error_t loadMenu(const QString &menuResource);
    /*}}}*/
    // error_t loadMenu(uint resID);/*{{{*/
    /**
     * Loads a menu from a resource.
     * @param resID Resource identifier. Number used as alias of the resource.
     * The resource must be putted in a group with the "/menus" prefix. The
     * value will be used to mount the resource path as in the following
     * schema:
     * <pre>
     * /menus/\#resID
     * </pre>
     * @returns An error code if the function succeeds the result will be \c
     * SSNO_ERROR.
     * @since 1.1
     **/
    error_t loadMenu(uint resID);
    /*}}}*/
    //@}
private:
    /** @name Internal Operations */ //@{
    // void    removeAll();/*{{{*/
    /**
     * Releases all items in this popup menu.
     * @since 1.1
     **/
    void    removeAll();
    /*}}}*/
    //@}
protected:      // Data Members
    QList<SSMenuItem *> m_items;    /**< Items of this popup menu. */
    uint m_id;                      /**< Item identifier.          */
};
/* Inline Functions {{{ */
/* ------------------------------------------------------------------------ */
/*! @name Constructors & Destructor *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline SSMenuPopup::SSMenuPopup(QWidget *parent = NULL);/*{{{*/
inline SSMenuPopup::SSMenuPopup(QWidget *parent) : QMenu(parent), m_id(0) { }
/*}}}*/
// inline SSMenuPopup::SSMenuPopup(const QString &text, QWidget *parent = NULL);/*{{{*/
inline SSMenuPopup::SSMenuPopup(const QString &text, QWidget *parent) : QMenu(parent),
    m_id(0) { setTitle(text); }
/*}}}*/
// inline SSMenuPopup::SSMenuPopup(SSXMLElement *element, QWidget *parent = NULL);/*{{{*/
inline SSMenuPopup::SSMenuPopup(SSXMLElement *element, QWidget *parent) : QMenu(parent),
    m_id(0) { loadMenu(element); }
/*}}}*/
// inline SSMenuPopup::~SSMenuPopup();/*{{{*/
inline SSMenuPopup::~SSMenuPopup() {
    removeAll();
}
/*}}}*/
///@} Constructors & Destructor /*}}}*/
/* ---------------------------------------------------------------------------
 * Properties {{{
 * ------------------------------------------------------------------------ */
// inline uint SSMenuPopup::itemID() const;/*{{{*/
inline uint SSMenuPopup::itemID() const {
    return m_id;
}
/*}}}*/
// Properties }}}
/* ---------------------------------------------------------------------------
 * Attributes {{{
 * ------------------------------------------------------------------------ */
// inline size_t SSMenuPopup::size() const;/*{{{*/
inline size_t SSMenuPopup::size() const {
    return m_items.size();
}
/*}}}*/
// inline int    SSMenuPopup::indexOf(SSMenuItem *menuItem) const;/*{{{*/
inline int SSMenuPopup::indexOf(SSMenuItem *menuItem) const {
    return m_items.indexOf(menuItem);
}
/*}}}*/
// inline SSMenuItem* SSMenuPopup::itemAt(uint position) const;/*{{{*/
inline SSMenuItem* SSMenuPopup::itemAt(uint position) const {
    if (position >= (uint)m_items.size()) return NULL;
    return m_items.at(position);
}
/*}}}*/
// inline SSMenuItem* SSMenuPopup::itemWithID(uint itemID) const;/*{{{*/
inline SSMenuItem* SSMenuPopup::itemWithID(uint itemID) const {
    int index = indexOf(itemID);
    if (index < 0) return NULL;
    return m_items.at(index);
}
/*}}}*/
// inline SSMenuPopup* SSMenuPopup::menuAt(uint position) const;/*{{{*/
inline SSMenuPopup* SSMenuPopup::menuAt(uint position) const {
    SSMenuItem *item = itemAt(position);
    if (item == NULL) return NULL;
    return item->subMenu();
}
/*}}}*/
// Attributes }}}
/* ---------------------------------------------------------------------------
 * SSMenuItem Operations {{{
 * ------------------------------------------------------------------------ */
// inline SSMenuItem* SSMenuPopup::addItem(SSMenuItem *item);/*{{{*/
inline SSMenuItem* SSMenuPopup::addItem(SSMenuItem *item) {
    m_items.append(item); addAction(item);
    return item;
}
/*}}}*/
// inline SSMenuItem* SSMenuPopup::addItem(const QString &text, uint itemID);/*{{{*/
inline SSMenuItem* SSMenuPopup::addItem(const QString &text, uint itemID) {
    SSMenuItem *item = addItem(new SSMenuItem(itemID));
    item->setText( text ); return item;
}
/*}}}*/
// inline SSMenuItem* SSMenuPopup::addItem(SSXMLElement *element);/*{{{*/
inline SSMenuItem* SSMenuPopup::addItem(SSXMLElement *element) {
    return addItem(new SSMenuItem(element));
}
/*}}}*/
// SSMenuItem Operations }}}
/* ---------------------------------------------------------------------------
 * SSMenuPopup Operations {{{
 * ------------------------------------------------------------------------ */
// inline SSMenuPopup* SSMenuPopup::addPopup(const QString &text);/*{{{*/
inline SSMenuPopup* SSMenuPopup::addPopup(const QString &text) {
    return addPopup(new SSMenuPopup(text));
}
/*}}}*/
// inline SSMenuPopup* SSMenuPopup::addPopup(SSXMLElement *element);/*{{{*/
inline SSMenuPopup* SSMenuPopup::addPopup(SSXMLElement *element) {
    return addPopup(new SSMenuPopup(element));
}
/*}}}*/
// SSMenuPopup Operations }}}
/* ---------------------------------------------------------------------------
 * Operations {{{
 * ------------------------------------------------------------------------ */
// inline error_t SSMenuPopup::loadMenu(SSXMLDocument *document);/*{{{*/
inline error_t SSMenuPopup::loadMenu(SSXMLDocument *document) {
    return loadMenu((SSXMLElement*)document);
}
/*}}}*/
// Operations }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTMNUP_HPP_DEFINED__ */
