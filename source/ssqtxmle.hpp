/**
 * \file
 * Declares the SSXMLElement class.
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
#ifndef __SSQTXMLE_HPP_DEFINED__
#define __SSQTXMLE_HPP_DEFINED__

#include <QString>
#include <QIODevice>
#include <QList>
#include <QHash>

/**
 * @ingroup ssqt_xml
 * An XML Element object.
 * An element can have any number of attributes and any number of children
 * elements. Also, it can have text, but only if it doesn't have children
 * elements. When an element has children the #text() member function returns
 * an empty string. In the same way, the #text(const QString&) member function
 * will fail when the element has children. Children elements has priority.
 * When you add a child element to an element that has text, the text will be
 * released. If you need to add text to some element that already has children
 * you need to remove all children before setting the text.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSXMLElement
{
public:
    explicit SSXMLElement(SSXMLElement *parent = NULL);
    SSXMLElement(const QString &name, SSXMLElement *parent = NULL);
    SSXMLElement(const SSXMLElement &other, SSXMLElement *parent = NULL);
    virtual ~SSXMLElement();

public:         // Attributes
    // bool hasAttributes() const;/*{{{*/
    /**
     * Checks whether this element has attributes.
     * @returns \b true when at least one attribute was defined. Otherwise \b
     * false.
     * @since 1.1
     **/
    bool hasAttributes() const;
    /*}}}*/
    // bool hasChildren() const;/*{{{*/
    /**
     * Checks if this element has some children elements.
     * @returns \b true when at least one child exists. Otherwise \b false.
     * @since 1.1
     **/
    bool hasChildren() const;
    /*}}}*/
    // bool has(const QString &attrName) const;/*{{{*/
    /**
     * Check when an attribute exists.
     * @param attrName \c QString with the attribute name.
     * @return \b true when the attribute exists. \b false otherwise.
     * @since 1.1
     **/
    bool has(const QString &attrName) const;
    /*}}}*/
    // size_t numberOfAttributes() const;/*{{{*/
    /**
     * Returns the number of attributes this element has.
     * @since 1.1
     **/
    size_t numberOfAttributes() const;
    /*}}}*/
    // size_t numberOfChildren() const;/*{{{*/
    /**
     * Returns the number of children elements this element has.
     * @since 1.1
     **/
    size_t numberOfChildren() const;
    /*}}}*/
    // QString text() const;/*{{{*/
    /**
     * Retrieves the text content of this element.
     * @return A \c QString object with the text of the element if it has one.
     * Otherwise an empty string.
     * @remarks The text content is always ignored if the element has
     * children. So, if this element has children this operation will return
     * an empty string.
     * @since 1.1
     **/
    QString text() const;
    /*}}}*/
    // bool    text(const QString &elementText);/*{{{*/
    /**
     * Sets or changes the text content of this element.
     * @param elementText \c QString with the text to be set.
     * @return \b true means the text was set. If this element has any child
     * the function will fail and return \b false.
     * @since 1.1
     **/
    bool    text(const QString &elementText);
    /*}}}*/

public:         // Attributes Operations
    // QString attribute(const QString &attrName) const;/*{{{*/
    /**
     * Gets the value of an attribute of this element.
     * @param attrName Name of the attribute.
     * @return The attribute's value as a \c QString object. If an attribute
     * with the passed name doesn't exists, the result is an empty string.
     * @remarks All attribute's values are kept in its string representation.
     * @since 1.1
     **/
    QString attribute(const QString &attrName) const;
    /*}}}*/
    // int     intValueOf(const QString &attrName, int defaultValue = 0) const;/*{{{*/
    /**
     * Converts an attribute's value to \b int.
     * @param attrName Name of the attribute.
     * @param defaultValue Optional. A default value to be returned when the
     * attribute named \a attrName doesn't exists or cannot be converted to an
     * integer.
     * @returns An integer value result of the convertion of the attribute's
     * value named at \a attrName.
     * @remarks The function can convert any numerical value to integer. It
     * recognizes values in octal or hexadecimal notation when the value
     * begins with \b 0 or \b 0x respectively. Also positive and negative
     * values ares recognized.
     * @since 1.1
     **/
    int intValueOf(const QString &attrName, int defaultValue = 0) const;
    /*}}}*/
    // bool    boolValueOf(const QString &attrName, bool defaultValue = false) const;/*{{{*/
    /**
     * Converts an attribute's value into \b boolean.
     * @param attrName Name of the attribute.
     * @param defaultValue Optional. A default value to be returned when the
     * attribute named \a attrName doesn't exists or cannot be converted to a
     * boolean value.
     * @returns \b true or \b false depend upon the conversion result.
     * @remarks The operation recognized strings "yes", "true" or any number
     * different from 0 as \b true. Values "no", "false" or 0 are identified
     * as \b false. If any of those are identified the result will be equals
     * to \a defaultValue.
     * @since 1.1
     **/
    bool boolValueOf(const QString &attrName, bool defaultValue = false) const;
    /*}}}*/
    // SSXMLElement& set(const QString &attrName, const QString &attrValue);/*{{{*/
    /**
     * Adds ore replaces an attribute in this element.
     * @param attrName Name for the attribute.
     * @param attrValue Value for the attribute.
     * @returns The operation returns \b this.
     * @remarks When an attribute with the same name already exists in this
     * element its value will be replaced. Otherwise a new attribute will be
     * created with the passed value.
     * @since 1.1
     **/
    SSXMLElement& set(const QString &attrName, const QString &attrValue);
    /*}}}*/
    // SSXMLElement& set(const QString &attrName, const int &attrValue);/*{{{*/
    /**
     * Adds or replaces an attribute with a numerical value.
     * @param attrName Name for the attribute.
     * @param attrValue Value for the attribute. A numerical value is always
     * written in decimal notation. Negative numbers are prefixed with less
     * sign.
     * @returns The operation returns \b this.
     * @remarks When an attribute with the same name already exists in this
     * element its value will be replaced. Otherwise a new attribute will be
     * created with the passed value.
     * @since 1.1
     **/
    SSXMLElement& set(const QString &attrName, const int &attrValue);
    /*}}}*/
    // SSXMLElement& set(const QString &attrName, const bool &attrValue);/*{{{*/
    /**
     * Adds or replaces an attribute with a boolean value.
     * Adds a new attribute to this element.
     * @param attrName Name for the attribute.
     * @param attrValue Value for the attribute. \b true values are converted
     * to the string "true". \b false values are converted to the string
     * "false".
     * @returns The operation returns \b this.
     * @remarks When an attribute with the same name already exists in this
     * element its value will be replaced. Otherwise a new attribute will be
     * created with the passed value.
     * @since 1.1
     **/
    SSXMLElement& set(const QString &attrName, const bool &attrValue);
    /*}}}*/
    // QString remove(const QString &attrName);/*{{{*/
    /**
     * Removes an attribute with the specified name.
     * @param attrName Name of the attribute to remove.
     * @returns When this element has an attribute with the specified name its
     * value will be returned. When not, the function returns an empty string.
     * @since 1.1
     **/
    QString remove(const QString &attrName);
    /*}}}*/
    // void removeAllAttributes();/*{{{*/
    /**
     * Remove all attributes of this element.
     * @since 1.1
     **/
    void removeAllAttributes();
    /*}}}*/

public:         // Child Element Operations
    // int indexOf(const SSXMLElement *element) const;/*{{{*/
    /**
     * Gets the index of a child element of this element.
     * @param element Pointer to the elemento whoose index should be returned.
     * @returns A value equals to or greater than 0 is the index of the
     * element. A values less than zero means that the passed element is not
     * a child of this element.
     * @since 1.1
     **/
    int indexOf(const SSXMLElement *element) const;
    /*}}}*/
    // SSXMLElement* elementAt(uint index) const;/*{{{*/
    /**
     * Returns a pointer to a child element at the specified index.
     * @param index Zero based index of the element to return.
     * @returns A pointer to the requested element or \b NULL when the
     * specified index is invalid.
     * @since 1.1
     **/
    SSXMLElement* elementAt(uint index) const;
    /*}}}*/
    // SSXMLElement* firstElement() const;/*{{{*/
    /**
     * Gets the pointer of the first child element of this element.
     * @returns The pointer of the first child element or \b NULL when this
     * element doesn't have children.
     * @sa firstElement()
     * @since 1.1
     **/
    SSXMLElement* firstElement() const;
    /*}}}*/
    // SSXMLElement* lastElement() const;/*{{{*/
    /**
     * Gets the pointer of the last child element of this element.
     * @returns The pointer of the last child element or \b NULL when this
     * element doesn't have children.
     * @sa lastElement()
     * @since 1.1
     **/
    SSXMLElement* lastElement() const;
    /*}}}*/
    // SSXMLElement& append(const SSXMLElement &element);/*{{{*/
    /**
     * Appends an element as child of this element.
     * @param element Reference to the element to append.
     * @returns The function returns \b this.
     * @remarks The function build a copy of the passed element and is
     * actually the copy that is held as child of this element.
     * @since 1.1
     **/
    SSXMLElement& append(const SSXMLElement &element);
    /*}}}*/
    // SSXMLElement& append(SSXMLElement *element);/*{{{*/
    /**
     * Appends an element as child of this element.
     * @param element Pointer to the element to append.
     * @returns The function returns \b this.
     * @remarks The proper argument \a element is held as child of this
     * element. So, this element takes ownership of the passed pointer.
     * @since 1.1
     **/
    SSXMLElement& append(SSXMLElement *element);
    /*}}}*/
    // bool remove(const SSXMLElement *element);/*{{{*/
    /**
     * Removes a child element from this element.
     * @param element Pointer to the element to remove.
     * @returns \b true if the passed element was a child of this element.
     * Otherwise \b false.
     * @remarks The \a element removed is not deleted. Is responsibility of
     * the caller to delete the object when it is no longer needed.
     * @note When the operation returns, the #parentElement member is set to
     * \b NULL since the element doesn't have a parent any more.
     * @since 1.1
     **/
    bool remove(const SSXMLElement *element);
    /*}}}*/
    // bool remove(uint index);/*{{{*/
    /**
     * Removes an element at the specified index.
     * @param index Zero based index of the child element to remove.
     * @returns \b true if a child element is removed. Otherwise \b false.
     * @remarks The object at the specified position is \e deleted in this
     * operation.
     * @since 1.1
     **/
    bool remove(uint index);
    /*}}}*/
    // void removeAllElements();/*{{{*/
    /**
     * Remove all children elements from this element.
     * @since 1.1
     **/
    void removeAllElements();
    /*}}}*/

public:         // Overridable Operations
    // virtual bool isEqualTo(const SSXMLElement *element) const;/*{{{*/
    /**
     * Checks whether this element is equal to the passed one.
     * @param element Other element to check for equality.
     * @returns \b true when both elements are equals. Otherwise \b false.
     * @remarks Two elements are equals if they have the same name, the same
     * list of attributes with values and all its children are also equals.
     * @note Depending uppon the number of children elements this function can
     * be very expensive.
     * @since 1.1
     **/
    virtual bool isEqualTo(const SSXMLElement *element) const;
    /*}}}*/
    // virtual void assign(const SSXMLElement *element);/*{{{*/
    /**
     * Copy operation.
     * @param element Element to copy all its attributes and children.
     * @remarks This operation can be expensive since all attributes and
     * children elements including its attributes and children elements will
     * be duplicated.
     * @since 1.1
     **/
    virtual void assign(const SSXMLElement *element);
    /*}}}*/
    // virtual QString toString() const;/*{{{*/
    /**
     * Converts this element to its textual notation.
     * @returns A \c QString object with the textual (XML) notation.
     * @remarks The operation will convert this element and all its children
     * into a well-formed XML element.
     * @since 1.1
     **/
    virtual QString toString() const;
    /*}}}*/
    // virtual QString toString(uint indent) const;/*{{{*/
    /**
     * Converts this element to its textual notation.
     * @param indent Identation level. The number passed here will be
     * multiplied by 2 spaces used as indentation level.
     * @returns A \c QString object with the textual (XML) notation.
     * @remarks The operation will convert this element and all its children
     * into a well-formed XML element. The difference of this version to
     * #toString() is that the string returned will be indented and a line
     * break will be added at each elements end.
     * @since 1.1
     **/
    virtual QString toString(uint indent) const;
    /*}}}*/
    // virtual bool write(QIODevice *device);/*{{{*/
    /**
     * Writes this element to a QIODevice object.
     * @param device Pointer to the target \c QIODevice object. Cannot be \b
     * NULL.
     * @return \b true when the device is written successful. \b false
     * otherwise.
     * @since 1.1
     **/
    virtual bool write(QIODevice *device);
    /*}}}*/

public:         // Overloaded Operators
    // bool operator ==(const SSXMLElement &other) const;/*{{{*/
    /**
     * Checks whether this element is equal to the passed one.
     * @param other Other element to check for equality.
     * @returns \b true when both elements are equals. Otherwise \b false.
     * @remarks Two elements are equals if they have the same name, the same
     * list of attributes with values and all its children are also equals.
     * @note Depending uppon the number of children elements this function can
     * be very expensive.
     * @since 1.1
     **/
    bool operator ==(const SSXMLElement &other) const;
    /*}}}*/
    // QString operator[](const QString &attrName) const;/*{{{*/
    /**
     * Gets the value of an attribute of this element.
     * @param attrName Name of the attribute.
     * @return The attribute's value as a \c QString object. If an attribute
     * with the passed name doesn't exists, the result is an empty string.
     * @remarks All attribute's values are kept in its string representation.
     * @since 1.1
     **/
    QString operator[](const QString &attrName) const;
    /*}}}*/
    // SSXMLElement& operator =(const SSXMLElement &other);/*{{{*/
    /**
     * Assignment operator.
     * @param other Another SSXMLElement to copy.
     * @returns The operation returns \b this.
     * @remarks All attributes and all children elements of the passed \a
     * other element will be copied.
     * @note Depending uppon the size of \a other element this operation can
     * be very expensive.
     * @since 1.1
     **/
    SSXMLElement& operator =(const SSXMLElement &other);
    /*}}}*/

public:         // Data Members
    QString elementName;                /**< Name of this element.          */
    SSXMLElement *parentElement;        /**< Parent element.                */

protected:
    QList<SSXMLElement*> m_nodes;       /**< List of children elements.     */
    QHash<QString, QString> m_attrs;    /**< Attributes of this element.    */
    QString m_text;                     /**< Text of this element.          */
};
/* Inlined Functions {{{ */
/* ------------------------------------------------------------------------ */
/*! \name Constructors & Destructor *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline SSXMLElement::SSXMLElement(SSXMLElement *parent);/*{{{*/
/**
 * Default constructor.
 * Builds an empty XML element.
 * @param parent Pointer to the parent element. Can be \b NULL. When this
 * element is added as a child of another element this parenthood relationship
 * is updated.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
inline SSXMLElement::SSXMLElement(SSXMLElement *parent) : parentElement(parent) { }
/*}}}*/
// inline SSXMLElement::SSXMLElement(const SSXMLElement &other, SSXMLElement *parent);/*{{{*/
/**
 * Copy constructor.
 * Builds a copy of other element.
 * @param other Other element to copy. All data will be copied including the
 * element's name, set of attributes and children elements.
 * @param parent Pointer to the parent element. Can be \b NULL. When this
 * element is added as a child of another element this parenthood relationship
 * is updated.
 * @remarks Notice that all child nodes of \a other will be duplicated.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
inline SSXMLElement::SSXMLElement(const SSXMLElement &other, SSXMLElement *parent) : 
    parentElement(parent) {
    assign(&other);
}
/*}}}*/
// inline SSXMLElement::SSXMLElement(const QString &name, SSXMLElement *parent);/*{{{*/
/**
 * Builds a new XML element with the specified name.
 * @param name Name for the element's tag.
 * @param parent Pointer to the parent element. Can be \b NULL. When this
 * element is added as a child of another element this parenthood relationship
 * is updated.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
inline SSXMLElement::SSXMLElement(const QString &name, SSXMLElement *parent) :
    elementName(name), parentElement(parent) { }
/*}}}*/
// inline SSXMLElement::~SSXMLElement();/*{{{*/
/**
 * Destructor.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
inline SSXMLElement::~SSXMLElement() {
    qDeleteAll(m_nodes);
}
/*}}}*/
///@} Constructors & Destructor /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Attributes *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline bool SSXMLElement::hasAttributes() const;/*{{{*/
inline bool SSXMLElement::hasAttributes() const {
    return !m_attrs.empty();
}
/*}}}*/
// inline bool SSXMLElement::hasChildren() const;/*{{{*/
inline bool SSXMLElement::hasChildren() const {
    return !m_nodes.empty();
}
/*}}}*/
// inline bool SSXMLElement::has(const QString &attrName) const;/*{{{*/
inline bool SSXMLElement::has(const QString &attrName) const {
    return m_attrs.contains(attrName);
}
/*}}}*/
// inline size_t SSXMLElement::numberOfAttributes() const;/*{{{*/
inline size_t SSXMLElement::numberOfAttributes() const {
    return m_attrs.count();
}
/*}}}*/
// inline size_t SSXMLElement::numberOfChildren() const;/*{{{*/
inline size_t SSXMLElement::numberOfChildren() const {
    return m_nodes.count();
}
/*}}}*/
// inline QString SSXMLElement::text() const;/*{{{*/
inline QString SSXMLElement::text() const {
    return (hasChildren() ? QString() : m_text);
}
/*}}}*/
// inline bool    SSXMLElement::text(const QString &elementText);/*{{{*/
inline bool SSXMLElement::text(const QString &elementText) {
    if (hasChildren()) return false;
    m_text = elementText; return true;
}
/*}}}*/
///@} Attributes /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Overloaded Operators *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// inline bool SSXMLElement::operator ==(const SSXMLElement &other) const;/*{{{*/
inline bool SSXMLElement::operator ==(const SSXMLElement &other) const {
    return isEqualTo(&other);
}
/*}}}*/
// inline QString SSXMLElement::operator[](const QString &attrName) const;/*{{{*/
inline QString SSXMLElement::operator[](const QString &attrName) const {
    return attribute(attrName);
}
/*}}}*/
// inline SSXMLElement& SSXMLElement::operator =(const SSXMLElement &other);/*{{{*/
inline SSXMLElement& SSXMLElement::operator =(const SSXMLElement &other) {
    assign( &other ); return *this;
}
/*}}}*/
///@} Overloaded Operators /*}}}*/
/* ------------------------------------------------------------------------ */
/* }}} Inlined Functions */
#endif /* __SSQTXMLE_HPP_DEFINED__ */
