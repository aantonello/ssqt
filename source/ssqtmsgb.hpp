/**
 * @file
 * SSMsgBox class.
 *
 * @author Alessandro Antonello <aantonello@paralaxe.com.br>
 * @date   março 24, 2015
 * @since  Super Simple Library for Qt 1.3
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#ifndef __SSQTMSGB_HPP_DEFINED__
#define __SSQTMSGB_HPP_DEFINED__

#include <QMessageBox>

/**
 * \ingroup ssqt_ui
 * Extends the \c QMessageBox class adding usage facilities.
 * Before the dialog is created this class changes the title of added buttons
 * to match the Portuguese language. The class also brings static member
 * functions that easelly constructs simple messages.
 * @since 1.3
 *//* --------------------------------------------------------------------- */
class SSMsgBox : public QMessageBox
{
public:
    // Types
    // enum MsgBoxTypes { Info = 1, Warn, Error, Question };/*{{{*/
    /**
     * Type of the message box to show.
     * Also defines the kind of icon to be added to the message box window.
     * @since 1.3
     **/
    enum MsgBoxTypes {
        Info = 1,               /**< Same as \c QMessageBox::Information.   */
        Warn,                   /**< Same as \c QMessageBox::Warning.       */
        Error,                  /**< Same as \c QMessageBox::Critical       */
        Question                /**< Same as \c QMessageBox::Question.      */
    };
    /*}}}*/

public:
    /** @name Constructors & Destructor */ //@{
    // explicit SSMsgBox(QWidget *parent = NULL);/*{{{*/
    /**
     * Default constructor.
     * @param parent Optional. The parent widget.
     * @since 1.3
     **/
    explicit SSMsgBox(QWidget *parent = NULL);
    /*}}}*/
    // SSMsgBox(const QString &text, QWidget *owner = NULL, int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);/*{{{*/
    /**
     * Parametrized constructor.
     * @param text Text to show in the message box.
     * @param owner Optional. The owner widget.
     * @param type Optional. Type of the message box to show. Also defines the
     * kind of icon to be used. The default value is \c SSMsgBox::Info.
     * @param buttons Optional. Set of buttons to put in the dialog. The
     * default value is \c QMessageBox::Ok.
     * @since 1.3
     **/
    SSMsgBox(const QString &text, QWidget *owner = NULL, int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);
    /*}}}*/
    // virtual ~SSMsgBox();/*{{{*/
    /**
     * Default destructor.
     * @since 1.3
     **/
    virtual ~SSMsgBox();
    /*}}}*/
    //@}
public slots:
    /** @name Overrides */ //@{
    // virtual int exec();/*{{{*/
    /**
     * Builds the dialog showing it to the user.
     * @returns The value of the button selected by the user.
     * @since 1.3
     **/
    virtual int exec();
    /*}}}*/
    //@}
public:
    // Static Member Functions
    // static SSMsgBox* create(QWidget *owner, const QString &text, const QString &title = QString(), const QString &info = QString(), const QString &details = QString(), int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);/*{{{*/
    /**
     * Builds and returns an \c SSMsgBox object.
     * @param owner Optional. The dialog owner widget. Can be \b NULL. In this
     * case the application main window will be used.
     * @param text The message text. May have format included.
     * @param title Optional. Title for the dialog box. If not passed and the
     * \p owner argument is not \b NULL then the string returned by its \c
     * windowTitle() member function will be used. If the \c windowTitle()
     * returns an empty string or the \p owner argument is \b NULL then the
     * string returned by \c QCoreApplication::applicationName() will be used.
     * @param info Optional. Informative text. Usually is appended to the
     * normal message text. Cannot have format. If not passed noting will be
     * used.
     * @param details Optional. Detailed information. Usually appended to the
     * normal text. Cannot have format. If not passed nothing will be used.
     * @param type Optional. Message box type. The default value is \c
     * SSMsgBox::Info.
     * @param buttons Optional. Buttons to be shown. Must be one or
     * a combination of the standard \c QMessageBox::StandardButtons. The
     * default value is \c QMessageBox::Ok.
     * @return The newly created SSMsgBox object. You can show the dialog
     * using its \c exec() member function. The object should be deleted when
     * it is not needed.
     * @see
     * [QMessageBox::Icon](http://doc.qt.io/qt-5/qmessagebox.html#Icon-enum)
     * [QMessageBox::StandardButton](http://doc.qt.io/qt-5/qmessagebox.html#StandardButton-enum)
     * @since 1.3
     **/
    static SSMsgBox* create(QWidget *owner, const QString &text, const QString &title = QString(), const QString &info = QString(), const QString &details = QString(), int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);
    /*}}}*/
    // static int  alert(QWidget *owner, const QString &text, int type = SSMsgBox::Info, const QString &title = QString(), const QString &info = QString());/*{{{*/
    /**
     * Builds and shows a message box.
     * @param owner Pointer to the dialog owner. Can be \b NULL. In this case
     * the main window will be used.
     * @param text The message box text.
     * @param type Optional. Message box type. The default value is \c
     * SSMsgBox::Info. The type defined here will set the buttons applied to
     * the dialog box. There are four options:
     * - \c SSMsgBox::Info: Only \c QMessageBox::Ok button.
     * - \c SSMsgBox::Warn: Only \c QMessageBox::Close button.
     * - \c SSMsgBox::Error: Only \c QMessageBox::Close button.
     * - \c SSMsgBox::Question:: \c QMessageBox::Yes and \c QMessageBox::No
     *   buttons.
     * .
     * @param title Optional. Title for the dialog box. If not passed and the
     * \p owner argument is not \b NULL then the string returned by its \c
     * windowTitle() member function will be used. If the \c windowTitle()
     * returns an empty string or the \p owner argument is \b NULL then the
     * string returned by \c QCoreApplication::applicationName() will be used.
     * @param info Optional. Informative text. Usually is appended to the
     * normal message text. Cannot have format. If not passed noting will be
     * used.
     * @return The result value is the button selected by the user.
     * @since 1.3
     **/
    static int  alert(QWidget *owner, const QString &text, int type = SSMsgBox::Info, const QString &title = QString(), const QString &info = QString());
    /*}}}*/
    // static int  confirm(QWidget *owner, const QString &text, int buttons = 0, const QString &title = QString(), const QString &info = QString());/*{{{*/
    /**
     * Builds and shows a confirmation message box.
     * @param owner Pointer to the dialog owner. Can be \b NULL. In this case
     * the main window will be used.
     * @param text The message box text.
     * @param buttons Optional. Set of buttons in the dialog box. If 0 the
     * dialog will show the \c QMessageBox::Yes and \c QMessageBox::No
     * buttons.
     * @param title Optional. Title for the dialog box. If not passed and the
     * \p owner argument is not \b NULL then the string returned by its \c
     * windowTitle() member function will be used. If the \c windowTitle()
     * returns an empty string or the \p owner argument is \b NULL then the
     * string returned by \c QCoreApplication::applicationName() will be used.
     * @param info Optional. Informative text. Usually is appended to the
     * normal message text. Cannot have format. If not passed noting will be
     * used.
     * @return The result value is the button selected by the user.
     * @since 1.3
     **/
    static int  confirm(QWidget *owner, const QString &text, int buttons = 0, const QString &title = QString(), const QString &info = QString());
    /*}}}*/
};
/* ---------------------------------------------------------------------------
 * Inline Functions
 * ------------------------------------------------------------------------ */
// Constructors & Destructor
// inline SSMsgBox::SSMsgBox(QWidget *parent = NULL);/*{{{*/
inline SSMsgBox::SSMsgBox(QWidget *parent) : QMessageBox(parent) {
}
/*}}}*/
// inline SSMsgBox::~SSMsgBox();/*{{{*/
inline SSMsgBox::~SSMsgBox() {
}
/*}}}*/

#endif /* __SSQTMSGB_HPP_DEFINED__ */
