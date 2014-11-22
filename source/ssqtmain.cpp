/**
 * @file
 * Defines the SSMainWnd class.
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
#include "ssqtapp.hpp"
#include "ssqtmain.hpp"

/* ===========================================================================
 * SSMainWnd Class
 * ======================================================================== */

/* ---------------------------------------------------------------------------
 * Constructors & Destructor
 * ------------------------------------------------------------------------ */

// SSMainWnd::SSMainWnd(QWidget *parent = NULL, Qt::WindowFlags flags = 0);/*{{{*/
SSMainWnd::SSMainWnd(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
    if (ss::App != NULL) ss::App->m_mainWnd = this;
}
/*}}}*/

