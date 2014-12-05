/**
 * @file
 * Declares the SSButtonItem class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   dezembro 05, 2014
 * @since  Super Simple for Qt 5 1.1
 *
 * @copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTTLBI_HPP_DEFINED__
#define __SSQTTLBI_HPP_DEFINED__

#include <QWidgetAction>
#include "ssqtxmle.hpp"
#include "ssqtmnup.hpp"

/**
 * \ingroup ssqt_toolbar
 * A toolbar button item class.
 * This class extends \c QWidgetAction providing a way to add button itens to
 * a toolbar object. The \c SSButtonItem works in the same way as a standard
 * \c QWidgetAction added to a toolbar. Plus, it adds the hability to define
 * a toolbar in an XML file added to the qresource bundled in the application
 * binary.
 *//* --------------------------------------------------------------------- */
class SSButtonItem : public QWidgetAction
{
    Q_OBJECT
    Q_PROPERTY(uint itemID READ itemID)
    Q_PROPERTY(SSMenuPopup* subMenu READ subMenu WRITE subMenu)

public:
    /** @name Constructors & Destructor */ //@{
    // explicit SSButtonItem(QObject *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent Optional. Owner object. Can be \b NULL.
     * @note This constructor builds a standard \c QWidgetAction object. There
     * is no way to set a unique identifier for this item when built with this
     * constructor.
     * @since 1.1
     **/
    explicit SSButtonItem(QObject *parent = NULL);
    /*}}}*/
    // SSButtonItem(uint itemID, QObject *parent = NULL);/*{{{*/
    /**
     * Parametrized constructor.
     * @param itemID The unique identifier of this button item.
     * @param parent Optional. Owner object. Can be \b NULL.
     * @since 1.1
     **/
    SSButtonItem(uint itemID, QObject *parent = NULL);
    /*}}}*/
    // SSButtonItem(const SSButtonItem &button, QObject *parent = NULL);/*{{{*/
    /**
     * Copy constructor.
     * @param button Reference to another \c SSButtonItem whose should be
     * copied.
     * @param parent Optional. Owner object. Can be \b NULL.
     * @since 1.1
     **/
    SSButtonItem(const SSButtonItem &button, QObject *parent = NULL);
    /*}}}*/
    // SSButtonItem(SSXMLElement *element, QObject *parent = NULL);/*{{{*/
    /**
     * Loads an item from the resource.
     * @param element The \c SSXMLElement object with data to configure the
     * button item.
     * @param parent Optional. Owner object. Can be \b NULL.
     * @since 1.1
     **/
    SSButtonItem(SSXMLElement *element, QObject *parent = NULL);
    /*}}}*/
    //@}

public:
    /** @name Properties */ //@{
    // uint itemID() const;/*{{{*/
    /**
     * Retrieves the identifier os this button item.
     * @return An unsigned integer with the numerical identifier set in the
     * constructor or by the XML element.
     * @since 1.1
     **/
    uint itemID() const;
    /*}}}*/
    // SSMenuPopup* subMenu() const;/*{{{*/
    /**
     * Gets the sub menu shown by this button item.
     * @returns A pointer to the popup menu class. Notice that this return
     * will be valid only when this item shows a popup menu. When not, the
     * result will be \b NULL.
     * @since 1.1
     **/
    SSMenuPopup* subMenu() const;
    /*}}}*/
    // void subMenu(SSMenuPopup *menu);/*{{{*/
    /**
     * Sets the sub menu shown by this button item.
     * @param menu \c SSMenuPopup shown by this button item. Can be \b NULL to
     * remove the sub menu reference. The popup menu ownership is not taken by
     * this object.
     * @since 1.1
     **/
    void subMenu(SSMenuPopup *menu);
    /*}}}*/
    //@}

public:
    /** @name Operations */ //@{
    // SSButtonItem& assign(const SSButtonItem &button);/*{{{*/
    /**
     * Copy the properties and values of another button.
     * @param button Button item to copy from.
     * @returns \b this.
     * @since 1.1
     **/
    SSButtonItem& assign(const SSButtonItem &button);
    /*}}}*/
    //@}

public:
    /** @name Overloaded Operators */ //@{
    // SSButtonItem& operator=(const SSButtonItem &button);/*{{{*/
    /**
     * Copy operator.
     * @param button Button item to copy from.
     * @returns \b this.
     * @since 1.1
     **/
    SSButtonItem& operator=(const SSButtonItem &button);
    /*}}}*/
    //@}

protected:
    /** @name Implementation */ //@{
    // void init(SSXMLElement *element);/*{{{*/
    /**
     * This button internal initialization.
     * @param element The XML element with the button's properties. Must follow
     * the format described in @ref ssqt_toolbar module.
     * @since 1.1
     **/
    void init(SSXMLElement *element);
    /*}}}*/
    //@}

private:
    // Data Members
    uint m_id;              /**< This button item unique identifier. */
};
/* Inline Functions {{{ */
/* ---------------------------------------------------------------------------
 * Constructors & Destructor {{{
 * ------------------------------------------------------------------------ */
// inline SSButtonItem::SSButtonItem(QObject *parent = NULL);/*{{{*/
inline SSButtonItem::SSButtonItem(QObject *parent) : QWidgetAction(parent),
    m_id(0) { }
/*}}}*/
// inline SSButtonItem::SSButtonItem(uint itemID, QObject *parent = NULL);/*{{{*/
inline SSButtonItem::SSButtonItem(uint itemID, QObject *parent) : QWidgetAction(parent),
    m_id(itemID) { }
/*}}}*/
// inline SSButtonItem::SSButtonItem(const SSButtonItem &button, QObject *parent = NULL);/*{{{*/
inline SSButtonItem::SSButtonItem(const SSButtonItem &button, QObject *parent) :
    QWidgetAction(parent), m_id(0) {
    assign(button);
}
/*}}}*/
// inline SSButtonItem::SSButtonItem(SSXMLElement *element, QObject *parent = NULL);/*{{{*/
inline SSButtonItem::SSButtonItem(SSXMLElement *element, QObject *parent) :
    QWidgetAction(parent), m_id(0) {
    init(element);
}
/*}}}*/
// Constructors & Destructor }}}
/* ---------------------------------------------------------------------------
 * Properties {{{
 * ------------------------------------------------------------------------ */
// inline uint SSButtonItem::itemID() const;/*{{{*/
inline uint SSButtonItem::itemID() const {
    return m_id;
}
/*}}}*/
// inline SSMenuPopup* SSButtonItem::subMenu() const;/*{{{*/
inline SSMenuPopup* SSButtonItem::subMenu() const {
    return qobject_cast<SSMenuPopup *>( menu() );
}
/*}}}*/
// inline void SSButtonItem::subMenu(SSMenuPopup *menu);/*{{{*/
inline void SSButtonItem::subMenu(SSMenuPopup *menu) {
    setMenu( menu );
}
/*}}}*/
// Properties }}}
/* ---------------------------------------------------------------------------
 * Overloaded Operations {{{
 * ------------------------------------------------------------------------ */
// inline SSButtonItem& SSButtonItem::operator=(const SSButtonItem &button);/*{{{*/
inline SSButtonItem& SSButtonItem::operator=(const SSButtonItem &button) {
    return assign( button );
}
/*}}}*/
// Overloaded Operations }}}
/* ------------------------------------------------------------------------ */
/* }}} Inline Functions */
#endif /* __SSQTTLBI_HPP_DEFINED__ */
