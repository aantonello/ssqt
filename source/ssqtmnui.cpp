/**
 * @file
 * Defines the SSMenuItem class.
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
#include "ssqtmnui.hpp"

/* ===========================================================================
 * SSMenuItem Class
 * ======================================================================== */

/* ------------------------------------------------------------------------ */
/*! @name Operations */ //@{
/* ------------------------------------------------------------------------ */
// SSMenuItem& SSMenuItem::assign(const SSMenuItem &item);/*{{{*/
SSMenuItem& SSMenuItem::assign(const SSMenuItem &item)
{
    setActionGroup( item.actionGroup() );
    setAutoRepeat( item.autoRepeat() );
    setCheckable( item.isCheckable() );
    setData( item.data() );
    setIcon( item.icon() );
    setMenu( item.menu() );
    setMenuRole( item.menuRole() );
    setPriority( item.priority() );
    setSeparator( item.isSeparator() );
    setShortcuts( item.shortcuts() );
    setStatusTip( item.statusTip() );
    setText( item.text() );
    setEnabled( item.isEnabled() );
    setVisible( item.isVisible() );
    if (isCheckable())
        setChecked( item.isChecked() );

    m_id = item.itemID();
    return *this;
}
/*}}}*/
///@} Operations

/* ------------------------------------------------------------------------ */
/*! @name Implementation */ //@{
/* ------------------------------------------------------------------------ */
// void SSMenuItem::init(SSXMLElement *element);/*{{{*/
void SSMenuItem::init(SSXMLElement *element)
{
    if (!element) return;
    if (element->elementName == "separator")
    {
        setSeparator(true);
        return;
    }

    if (element->elementName != "item") return;

    m_id = (uint)element->intValueOf("id");
    setText( element->attribute("title").replace('_', '&') );
    setStatusTip( element->attribute("desc") );

    if (element->has("checked"))
    {
        setCheckable(true);
        setChecked( element->boolValueOf("checked") );
    }

    if (element->has("icon"))
    {
        QIcon menuIcon( element->attribute("icon") );

        setIcon( menuIcon );
        setIconVisibleInMenu( true );
    }

    if (element->has("keys"))
    {
        QKeySequence keys( element->attribute("keys") );

        setShortcut( keys );
        setShortcutContext( Qt::WindowShortcut );
    }
}
/*}}}*/
///@} Implementation
