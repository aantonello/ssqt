/**
 * @file
 * Defines the SSButtonItem class.
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
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqtdbg.hpp"
#include "ssqtasst.hpp"

/* ===========================================================================
 * SSButtonItem Class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Operations
 * ------------------------------------------------------------------------ */

// SSButtonItem& SSButtonItem::assign(const SSButtonItem &button);/*{{{*/
SSButtonItem& SSButtonItem::assign(const SSButtonItem &button)
{
    setActionGroup( button.actionGroup() );
    setAutoRepeat( button.autoRepeat() );
    setCheckable( button.isCheckable() );
    setData( button.data() );
    setIcon( button.icon() );
    setMenu( button.menu() );
    setPriority( button.priority() );
    setSeparator( button.isSeparator() );
    setShortcuts( button.shortcuts() );
    setStatusTip( button.statusTip() );
    setToolTip( button.toolTip() );
    setEnabled( button.isEnabled() );
    setVisible( button.isVisible() );
    if (isCheckable())
        setChecked( button.isChecked() );

    m_id = button.itemID();
    return *this;
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Protected: Implementation
 * ------------------------------------------------------------------------ */

// void SSButtonItem::init(SSXMLElement *element);/*{{{*/
void SSButtonItem::init(SSXMLElement *element)
{
    if (!element) return;
    if ((element->elementName != SS_MENU_NODE_SEPARATOR)
        && (element->elementName != SS_XML_NODE_BUTTON))
        return;

    if (element->elementName == SS_MENU_NODE_SEPARATOR)
        setSeparator(true);

    m_id = (uint)element->intValueOf(SS_MENU_ATTR_ID);
    setText( element->attribute(SS_MENU_ATTR_TEXT).replace('_', '&') );

    if (element->has(SS_MENU_ATTR_CHECKED))
    {
        setCheckable(true);
        setChecked( element->boolValueOf(SS_MENU_ATTR_CHECKED) );
    }

    if (element->has(SS_MENU_ATTR_ICON))
    {
        QString resIcon = element->attribute(SS_MENU_ATTR_ICON);
        QIcon   buttonIcon;

        if (resIcon.startsWith('#'))
            buttonIcon = ss:asset_icon(resIcon);
        else
            buttonIcon = QIcon( resIcon);

        setIcon( menuIcon );
    }

    if (element->has(SS_MENU_ATTR_KEYS))
    {
        QKeySequence keys( element->attribute(SS_MENU_ATTR_KEYS) );

        setShortcut( keys );
        setShortcutContext( Qt::WindowShortcut );
    }

    if (element->has(SS_MENU_ATTR_NAME))
        setObjectName( element->attribute(SS_MENU_ATTR_NAME) );

    if (element->hasChildren())
    {
        /* Only one child is allowed. */
        SSXMLElement *node = element->firstElement();

        if (node->elementName == SS_MENU_NODE_POPUP)
        {
            SSMenuPopup *popup = new SSMenuPopup(node);
            subMenu( popup );
        }
    }
}
/*}}}*/

