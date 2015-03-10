/**
 * @file
 * Defines de SSToolbar class.
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
#include "stdplx.hpp"
#include "ssqtcmn.hpp"
#include "ssqterr.hpp"
#include "ssqttlbr.hpp"

/* ===========================================================================
 * SSToolbar Class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Public: Attributes
 * ------------------------------------------------------------------------ */

// SSButtonItem* SSToolbar::buttonItem(uint buttonID) const;/*{{{*/
SSButtonItem* SSToolbar::buttonItem(uint buttonID) const
{
    QList<QAction *> list = actions();
    SSButtonItem *button = NULL;
    size_t limit = list.size();

    for (size_t i = 0; i < limit; ++i)
    {
        button = qobject_cast<SSButtonItem *>( list.at(i) );
        if ((button != NULL) && (button->itemID() == buttonID))
            return button;
    }
    return NULL;
}
/*}}}*/
// SSButtonItem* SSToolbar::buttonAt(uint index) const;/*{{{*/
SSButtonItem* SSToolbar::buttonAt(uint index) const
{
    QList<QAction *> list = actions();
    if (index >= (uint)list.size())
        return NULL;

    return qobject_cast<SSButtonItem *>( list.at(index) );
}
/*}}}*/

/* ---------------------------------------------------------------------------
 * Public: Operations
 * ------------------------------------------------------------------------ */

// bool SSToolbar::init(uint resID);/*{{{*/
bool SSToolbar::init(uint resID)
{
    QString filePath(":/toolbar/#%1");

    return init(filePath.arg(resID));
}
/*}}}*/
// bool SSToolbar::init(const QString &filePath);/*{{{*/
bool SSToolbar::init(const QString &filePath)
{
    SSXMLDocument doc( filePath );
    return init( &doc );
}
/*}}}*/
// bool SSToolbar::init(SSXMLDocument *doc);/*{{{*/
bool SSToolbar::init(SSXMLDocument *doc)
{
    if (doc == NULL) return false;
    if (doc->elementName != SS_XML_NODE_TOOLBAR) return false;

    size_t limit = doc->numberOfChildren();
    SSXMLElement *node;
    SSButtonItem *button;

    for (size_t i = 0; i < limit; ++i)
    {
        node = doc->elementAt(i);
        if (node->elementName == SS_MENU_NODE_SEPARATOR)
            addSeparator();
        else if (node->elementName == SS_XML_NODE_BUTTON)
        {
            button = new SSButtonItem(node);
            addAction( button );
        }
    }
    return true;
}
/*}}}*/

