/*
 * Property template example 1.
 */
#ifndef __SFPROP01_H_DEFINED__
#define __SFPROP01_H_DEFINED__

#include <ssqtprop.hpp>

class AClassWithProperties
{
public:
    AClassWithProperties();

public:
    /* An integer property. */
    property_t<int> counter;

    /* A QString property. */
    property_t<QString> name;

private:
    /* The getter and setter for the 'counter' property. */
    int __internal_getCount();
    void __internal_setCount(const int &count);

    /* The getter and setter for the 'name' property. */
    QString __internal_getName();
    void __internal_setName(const QString &name);

    /* Member variables to hold the values. */
    QString m_name;
    int     m_count;
};

#endif /* __SFPROP01_H_DEFINED__ */

