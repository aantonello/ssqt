/**
 * @file
 * Defines de SSMenu class.
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
#include "stdplx.hpp"
#include "ssqtmenu.hpp"
#include "ssqtasst.hpp"
#include "ssqterr.hpp"
#include "ssqtdbg.hpp"

/* ===========================================================================
 * SSMenu Class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * SSMenu Operations
 * ------------------------------------------------------------------------ */

// error_t SSMenu::loadMenu(SSXMLDocument *document);/*{{{*/
error_t SSMenu::loadMenu(SSXMLDocument *document)
{
    if (document == NULL)
    {
        sstrace("SSXMLDocument is NULL!");
        return SSE_INVAL;
    }

    if (document->elementName != SS_MENU_NODE_MENU)
    {
        sstrace("root element name:'%s' should be '%s'", sst(document->elementName), sst(SS_MENU_NODE_MENU));
        return SSE_FTYPE;
    }

    size_t limit = document->numberOfChildren();
    SSXMLElement *element;

    for (size_t i = 0; i < limit; ++i)
    {
        element = document->elementAt(i);
        if (element->elementName != SS_MENU_NODE_POPUP)
        {
            sstrace("element at %u is '%s'. Should be: '%s'", i, sst(element->elementName), sst(SS_MENU_NODE_POPUP));
            continue;
        }
        addPopup(element);
    }
    return SSNO_ERROR;
}
/*}}}*/

