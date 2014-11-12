/**
 * \file
 * Defines assets global functions.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 11, 2014
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
#include "ssqtasst.hpp"

namespace ss {
// QString asset_string(uint resID, size_t size = 1024);/*{{{*/
QString asset_string(uint resID, size_t size)
{
#ifndef Q_OS_WIN
    Q_UNUSED(resID);
    Q_UNUSED(size);
    return QString();
#else
    size_t   length   = size * sizeof(wchar_t);
    wchar_t *szBuffer = (wchar_t *)malloc( length );
    QString result;

    if (!szBuffer) return result;

    /* The 'LoadResString()' windows function does not add the terminator
     * NULL.
     */
    memset(szBuffer, 0, length);
    if (LoadStringW((HINSTANCE)GetModuleHandle(NULL), resID, szBuffer, size))
        result = QString::fromWCharArray(szBuffer);

    free(szBuffer);
    return result;
#endif
}
/*}}}*/
};

