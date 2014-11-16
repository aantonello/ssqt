/**
 * @file
 * Declares the SSMenuPopup class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   novembro 16, 2014
 * @since  Super Simple for Qt 5 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTMNUP_HPP_DEFINED__
#define __SSQTMNUP_HPP_DEFINED__

/**
 * @ingroup ssqt_menus
 * Represents a popup menu.
 * The class extends \c QMenu providing standard behavior for a menu in Qt.
 * Items of a popup menu are \c SSMenuItem classes. The \c SSMenuItem extends
 * \c QAction also providing standard Qt behavior.
 *
 * Popup menus can be constructed manually or, more often, loaded from
 * a resource. Popup menu resources are XML files having a structure described
 * in the documentation of @ref ssqt_menus module.
 * @since 1.1
 *//* --------------------------------------------------------------------- */
class SSMenuPopup : public QMenu
{
    Q_OBJECT

public:
    explicit SSMenuPopup(QWidget *parent = NULL);
    SSMenuPopup(const QString &title, QWidget *parent = NULL);
    SSMenuPopup(SSXMLElement *element, QWidget *parent = NULL);

public:         // Attributes
    size_t size() const;
    int    indexOf(SSMenuItem *menuItem) const;
    int    indexOf(uint itemID) const;
    SSMenuItem* itemAt(uint position) const;
    SSMenuItem* itemWithID(uint itemID) const;
    SSMenuPopup* menuAt(uint position) const;

public:         // SSMenuItem Operations
    SSMenuItem* addItem(SSMenuItem *item);
    SSMenuItem* addItem(const QString *title, uint itemID);
    SSMenuItem* addItem(SSXMLElement *element);

public:         // SSMenuPopup Operations
    SSMenuPopup* addPopup(SSMenuPopup *popup);
    SSMenuPopup* addPopup(const QString *title);
    SSMenuPopup* addPopup(SSXMLElement *element);

public:         // Operations
    error_t loadMenu(SSXMLElement *element);
    error_t loadMenu(SSXMLDocument *document);
    error_t loadMenu(const QString &menuResource);
    error_t loadMenu(uint resID);

protected:      // Data Members
    QList<QObject *> m_items;       /**< Items of this popup menu. */
};
#endif /* __SSQTMNUP_HPP_DEFINED__ */
