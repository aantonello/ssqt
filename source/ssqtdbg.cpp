/**
 * \file
 * Debugging operations definition.
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
#include "ssqtdbg.hpp"
#include <string.h>
#include <stdio.h>

// void __ss_debug(const char *file, int line, const char *fmt, ...);/*{{{*/
void __ss_debug(const char *file, int line, const char *fmt, ...)
{
    size_t length = 1024;
    char   buffer[length];
    int    pos = 0;

    buffer[0] = '\0';

    if (file != NULL)
    {
        const char *name  = file;
        char *slash = strrchr(file, '/');
        if (slash != NULL)
            name = (slash + 1);

        pos = snprintf(buffer, length, "%s @ %d: ", name, line);
    }

    if (fmt != NULL)
    {
        va_list args;

        va_start(args, fmt);
        vsnprintf((buffer + pos), (length - (size_t)pos), fmt, args);
        va_end(args);
    }

    if (buffer[0] != '\0')
        qDebug(buffer);
}
/*}}}*/
// void __ss_trace(const char *func, const char *fmt, ...);/*{{{*/
void __ss_trace(const char *func, const char *fmt, ...)
{
    size_t length = 1024;
    char   buffer[length];
    int    pos = 0;

    buffer[0] = '\0';

    if (func != NULL)
        pos = snprintf(buffer, length, "%s: ", func);

    if (fmt != NULL)
    {
        va_list args;

        va_start(args, fmt);
        vsnprintf((buffer + pos), (length - (size_t)pos), fmt, args);
        va_end(args);
    }

    if (buffer[0] != '\0')
        qDebug(buffer);
}
/*}}}*/
// void __ss_flush(const char *head, const void *ptr, size_t size, const char *tail);/*{{{*/
void __ss_flush(const char *head, const void *ptr, size_t size, const char *tail)
{
    size_t length = 0;
    char *buffer = NULL;
    int pos = 0;

    /* Calculating the buffer size. */
    if (head) length = strlen(head);
    if (tail) length += strlen(tail);
    if (ptr) length += (size * 3 + 1);

    if (length == 0) return;

    buffer = (char *)malloc(length * sizeof(char));
    if (buffer == NULL)
        return;         /* Not enough memory. */

    if (head)
        pos = snprintf(buffer, length, "%s", head);

    if (ptr)
    {
        uint8_t *data = (uint8_t *)ptr;
        uint8_t *end  = (data + size);
        int val;

        while (data < end) {
            val = (int)(0xFF & *data++);
            pos += snprintf((buffer + pos), (length - (size_t)pos), " %02X", val);
        }
    }

    if (tail)
        pos += snprintf((buffer + pos), (length - (size_t)pos), "%s", tail);

    qDebug(buffer);
    free(buffer);
}
/*}}}*/

