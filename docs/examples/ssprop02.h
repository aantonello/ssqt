/*
 * Property template example 2.
 */
#ifndef __SFPROP02_H_DEFINED__
#define __SFPROP02_H_DEFINED__

#include <ssqtprop.hpp>

class ArrayList
{
public:
    ArrayList();

    property_t<size_t> count;

private:
    size_t get_count();
    QStringList *m_list;
};
#endif /* __SFPROP02_H_DEFINED__ */

