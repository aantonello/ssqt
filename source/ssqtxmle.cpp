/**
 * \file
 * Defines the SSXMLElement class.
 *
 * \author Alessandro Antonello <aantonello@paralaxe.com.br>
 * \date   novembro 08, 2014
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

/* ===========================================================================
 * SSXMLElement class
 * ======================================================================== */

/* ------------------------------------------------------------------------ */
/*! \name Attributes Operations */ //@{
/* ------------------------------------------------------------------------ */
// QString SSXMLElement::attribute(const QString &attrName) const;/*{{{*/
QString SSXMLElement::attribute(const QString &attrName) const
{
    return m_attrs.value(attrName, QString());
}
/*}}}*/
// int     SSXMLElement::intValueOf(const QString &attrName, int defaultValue = 0) const;/*{{{*/
int SSXMLElement::intValueOf(const QString &attrName, int defaultValue) const
{
    QString value = attribute(attrName);
    bool success  = true;
    int  result   = value.toInt(&success, 0);

    return (success ? result : defaultValue);
}
/*}}}*/
// bool    SSXMLElement::boolValueOf(const QString &attrName, bool defaultValue = false) const;/*{{{*/
bool SSXMLElement::boolValueOf(const QString &attrName, bool defaultValue) const
{
    QString value = attribute(attrName);
    bool   result = defaultValue;

    if ((value == "true") || (value == "yes") || (value.toInt() != 0))
        result = true;
    else if ((value == "false") || (value == "no") || (value.toInt() == 0))
        result = false;

    return result;
}
/*}}}*/
// SSXMLElement& SSXMLElement::set(const QString &attrName, const QString &attrValue);/*{{{*/
SSXMLElement& SSXMLElement::set(const QString &attrName, const QString &attrValue)
{
    m_attrs[attrName] = attrValue;
    return *this;
}
/*}}}*/
// SSXMLElement& SSXMLElement::set(const QString &attrName, const int &attrValue);/*{{{*/
SSXMLElement& SSXMLElement::set(const QString &attrName, const int &attrValue)
{
    return set(attrName, QString::number(attrValue));
}
/*}}}*/
// SSXMLElement& SSXMLElement::set(const QString &attrName, const bool &attrValue);/*{{{*/
SSXMLElement& SSXMLElement::set(const QString &attrName, const bool &attrValue)
{
    return set(attrName, (attrValue ? QString("true") : QString("false")));
}
/*}}}*/
// QString SSXMLElement::remove(const QString &attrName);/*{{{*/
QString SSXMLElement::remove(const QString &attrName)
{
    return m_attrs.take(attrName);
}
/*}}}*/
///@} Attributes Operations

/* ------------------------------------------------------------------------ */
/*! \name Child Element Operations */ //@{
/* ------------------------------------------------------------------------ */
// int SSXMLElement::indexOf(const SSXMLElement *element) const;/*{{{*/
int SSXMLElement::indexOf(const SSXMLElement *element) const
{
    return m_nodes.indexOf(const_cast<SSXMLElement*>(element));
}
/*}}}*/
// SSXMLElement* SSXMLElement::elementAt(uint index) const;/*{{{*/
SSXMLElement* SSXMLElement::elementAt(uint index) const
{
    if (index >= (uint)m_nodes.count()) return NULL;
    return m_nodes.at(index);
}
/*}}}*/
// SSXMLElement& SSXMLElement::append(const SSXMLElement &element);/*{{{*/
SSXMLElement& SSXMLElement::append(const SSXMLElement &element)
{
    SSXMLElement *node = new SSXMLElement(element, this);
    return append(node);
}
/*}}}*/
// SSXMLElement& SSXMLElement::append(SSXMLElement *element);/*{{{*/
SSXMLElement& SSXMLElement::append(SSXMLElement *element)
{
    m_nodes.append(element);
    return *this;
}
/*}}}*/
// bool SSXMLElement::remove(const SSXMLElement *element);/*{{{*/
bool SSXMLElement::remove(const SSXMLElement *element)
{
    int index = indexOf(element);
    if (index < 0) return false;

    m_nodes.removeAt(index);
    return true;
}
/*}}}*/
// bool SSXMLElement::remove(uint index);/*{{{*/
bool SSXMLElement::remove(uint index)
{
    if (index >= (uint)m_nodes.count())
        return false;

    SSXMLElement *element = m_nodes.takeAt(index);
    delete element;

    return true;
}
/*}}}*/
///@} Child Element Operations

/* ------------------------------------------------------------------------ */
/*! \name Overridable Operations */ //@{
/* ------------------------------------------------------------------------ */
// bool SSXMLElement::isEqualTo(const SSXMLElement *element) const;/*{{{*/
bool SSXMLElement::isEqualTo(const SSXMLElement *element) const
{
    if (!element) return false;
    if (element == this) return true;

    if (elementName != element->elementName)
        return false;

    if (numberOfAttributes() != element->numberOfAttributes())
        return false;

    if (numberOfChildren() != element->numberOfChildren())
        return false;

    if (m_attrs != element->m_attrs)
        return false;

    return (m_nodes == element->m_nodes);
}
/*}}}*/
// void SSXMLElement::assign(const SSXMLElement *element);/*{{{*/
void SSXMLElement::assign(const SSXMLElement *element)
{
    elementName = element->elementName;
    m_attrs     = element->m_attrs;

    /* The child element list must be duplicated. */
    qDeleteAll(m_nodes);
    m_nodes.clear();

    size_t limit = element->numberOfChildren();

    for (size_t i = 0; i < limit; ++i)
        append( *(element->elementAt(i)) );
}
/*}}}*/
// QString SSXMLElement::toString() const;/*{{{*/
QString SSXMLElement::toString() const
{
    return toString(0);
}
/*}}}*/
// QString SSXMLElement::toString(uint indent) const;/*{{{*/
QString SSXMLElement::toString(uint indent) const
{
    QString xmlElement;

    if (indent > 0) xmlElement.fill(' ', indent * 2);

    xmlElement.append(QString("<%1").arg(elementName));

    QString attrFormat(" %1=\"%2\"");
    QHash<QString, QString>::const_iterator it = m_attrs.cbegin();
    while (it != m_attrs.cend())
    {
        xmlElement.append(attrFormat.arg(it.key(), it.value()));
        ++it;
    }

    if (m_nodes.empty())
        xmlElement.append("/>\n");
    else
    {
        size_t limit = m_nodes.count();
        SSXMLElement *node;

        xmlElement.append(">\n");
        for (size_t i = 0; i < limit; ++i)
        {
            node = m_nodes.at(i);
            xmlElement.append(node->toString(indent + 1));
        }
        xmlElement.append(QString("</%1>\n").arg(elementName));
    }
    return xmlElement;
}
/*}}}*/
// bool SSXMLElement::write(QIODevice *device);/*{{{*/
bool SSXMLElement::write(QIODevice *device)
{
    QString xml(QString("<%1").arg(elementName));

    if (!m_attrs.empty())
    {
        QString fmt(" %1=\"%2\"");
        QHash<QString, QString>::const_iterator it = m_attrs.cbegin();

        while (it != m_attrs.cend())
        {
            xml.append(fmt.arg(it.key(), it.value()));
            ++it;
        }
    }

    xml.append((m_nodes.empty() ? "/>" : ">"));

    device->write(xml.toUtf8());
    xml.clear();

    if (!m_nodes.empty())
    {
        size_t limit = m_nodes.count();
        SSXMLElement *node;

        for (size_t i = 0; i < limit; ++i)
        {
            node = m_nodes.at(i);
            node->write(device);
        }
        device->write("</", 2);
        device->write(elementName.toUtf8());
        device->write(">", 1);
    }
    return true;
}
/*}}}*/
///@} Overridable Operations

