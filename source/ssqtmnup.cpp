/**
 * @file
 * Defines the SSMenuPopup class.
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
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqtxmle.hpp"
#include "ssqtxmld.hpp"
#include "ssqtmnui.hpp"
#include "ssqtmnup.hpp"

/* ===========================================================================
 * SSMenuPopup Class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Attributes
 * ------------------------------------------------------------------------ */

// int SSMenuPopup::indexOf(SSMenuPopup *popup) const;/*{{{*/
int SSMenuPopup::indexOf(SSMenuPopup *popup) const
{
    if (!popup) return -1;

    size_t limit = m_items.size();
    SSMenuItem *item;

    for (size_t i = 0; i < limit; ++i)
    {
        item = m_items.at(i);
        if (popup == item->subMenu())
            return (int)i;
    }
    return -1;
}
/*}}}*/
// int SSMenuPopup::indexOf(uint itemID) const;/*{{{*/
int SSMenuPopup::indexOf(uint itemID) const
{
    SSMenuItem *item;
    size_t limit = m_items.size();

    for (size_t i = 0; i < limit; ++i)
    {
        item = m_items.at(i);
        if (itemID == item->itemID())
            return (int)i;
    }
    return -1;
}
/*}}}*/
// SSMenuItem* SSMenuPopup::itemWithName(const QString &name) const;/*{{{*/
SSMenuItem* SSMenuPopup::itemWithName(const QString &name) const
{
    SSMenuItem *item;
    size_t limit = m_items.size();

    for (size_t i = 0; i < limit; ++i)
    {
        item = m_items.at(i);
        if (name == item->objectName())
            return item;
    }
    return NULL;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * SSMenuPopup Operations
 * ------------------------------------------------------------------------ */

// SSMenuPopup* SSMenuPopup::addPopup(SSMenuPopup *popup);/*{{{*/
SSMenuPopup* SSMenuPopup::addPopup(SSMenuPopup *popup)
{
    if (popup)
    {
        SSMenuItem *item = new SSMenuItem(popup->itemID());
        item->setText( popup->title() );
        item->subMenu( popup );

        m_items.append( item );
        addMenu( popup );
    }
    return popup;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Operations
 * ------------------------------------------------------------------------ */

// error_t SSMenuPopup::loadMenu(SSXMLElement *element);/*{{{*/
error_t SSMenuPopup::loadMenu(SSXMLElement *element)
{
    if (!element) return SSE_INVAL;
    if (element->elementName != SS_MENU_NODE_POPUP)
        return SSE_INVAL;

    if (element->has(SS_MENU_ATTR_REF))
    {
        SSMenuPopup *subMenu = new SSMenuPopup();
        error_t result = subMenu->loadMenu(element->attribute(SS_MENU_ATTR_REF));

        if (result != SSNO_ERROR)
        {
            delete subMenu;
            return result;
        }
        addPopup(subMenu);
        return SSNO_ERROR;
    }

    m_id = element->intValueOf(SS_MENU_ATTR_ID);
    setTitle( element->attribute(SS_MENU_ATTR_TEXT) );

    if (element->has(SS_MENU_ATTR_NAME))
        setObjectName( element->attribute(SS_MENU_ATTR_NAME) );

    if (element->hasChildren())
    {
        size_t limit = element->numberOfChildren();
        SSXMLElement *node;

        for (size_t i = 0; i < limit; ++i)
        {
            node = element->elementAt(i);
            if (node->elementName == SS_MENU_NODE_POPUP)
                addPopup( node );
            else
                addItem( node );
        }
    }
    return SSNO_ERROR;
}
/*}}}*/
// error_t SSMenuPopup::loadMenu(const QString &menuResource);/*{{{*/
error_t SSMenuPopup::loadMenu(const QString &menuResource)
{
    SSXMLDocument xmlDoc;
    error_t result;

    result = xmlDoc.open(menuResource);
    if (result != SSNO_ERROR)
        return result;

    return loadMenu( &xmlDoc );
}
/*}}}*/
// error_t SSMenuPopup::loadMenu(uint resID);/*{{{*/
error_t SSMenuPopup::loadMenu(uint resID)
{
    QString resMenu(":/menus/#%1");

    return loadMenu(resMenu.arg(resID));
}
/*}}}*/
// void    SSMenuPopup::removeAll();/*{{{*/
void SSMenuPopup::removeAll()
{
    /* We should remove only the items having sub-menus. */
    size_t limit = m_items.size();
    SSMenuItem *item;

    while (limit > 0)
    {
        item = m_items.at(limit - 1);
        if (item->subMenu())
            delete m_items.takeAt(limit - 1);

        --limit;
    };
}
/*}}}*/

