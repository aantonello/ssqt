/**
 * \file
 * Defines the SSApplication class.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 07, 2014
 * \since  Super Simple for Qt 5 1.1
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

/* ===========================================================================
 * SSApplication Class
 * ======================================================================== */

/* ------------------------------------------------------------------------ */
/*! \name Operations */ //@{
/* ------------------------------------------------------------------------ */
// bool SSApplication::ensureSingleInstance(const QString &applicationKey);/*{{{*/
bool SSApplication::ensureSingleInstance(const QString &applicationKey)
{
    if (m_shared != NULL) return true;

    m_shared = new QSharedMemory(applicationKey, this);

    /* We must allocate some memory otherwise the function will fail with
     * 'invalid size' error. We don't care about the error. If this operation
     * fails the application should not run at all.
     */
    return m_shared->create(sizeof(int));
}
/*}}}*/
///@} Operations
