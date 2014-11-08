/*
 * Property template example 1.
 * The class implementation.
 */
#include "sfprop01.h"

/* Constructor
 * Must pass the member functions to get and set the property value.
 */
AClassWithProperties::AClassWithProperties() : 
    counter(this, &AClassWithProperties::__internal_getCount,
                  &AClassWithProperties::__internal_setCount),
    name(this, &AClassWithProperties::__internal_getName,
               &AClassWithProperties::__internal_setName),
    m_count(0)
{
}

/* The getter for the "counter" property is very simple.
 * Could be declares "inline"
 */
int AClassWithProperties::__internal_getCount() {
    return m_count;
}

/* Same thing to the 'setter'. */
void AClassWithProperties::__internal_setCount(const int &count) {
    m_count = count;
}

/* The getter for the "name" property is also simple. */
QString AClassWithProperties::__internal_getName() {
    return m_name;
}

/* So the setter. */
void AClassWithProperties::__internal_setName(const QString &name) {
    m_name = name;
}

