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
#include "stdplx.hpp"
#include "ssqtmain.hpp"
#include "ssqtapp.hpp"
#include "ssqtmsgb.hpp"

/* ===========================================================================
 * SSMsgBox Class Implementation
 * ======================================================================== */

// Constructors & Destructor
// SSMsgBox::SSMsgBox(const QString &text, QWidget *owner = NULL, int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);/*{{{*/
SSMsgBox::SSMsgBox(const QString &text, QWidget *owner, int type, int buttons) :
    QMessageBox(owner)
{
    setIcon((QMessageBox::Icon)type);
    setStandardButtons((QMessageBox::StandardButton)buttons);
    setText( text );
}
/*}}}*/

// Public Slots: Overrides
// virtual int SSMsgBox::exec();/*{{{*/
int SSMsgBox::exec()
{
    /* First we must change the label of buttons. */
    QAbstractButton *btn = button(QMessageBox::Yes);
    if (btn) btn->setText("Sim");
    if ((btn = button(QMessageBox::Open))) btn->setText("Abrir");
    if ((btn = button(QMessageBox::Save))) btn->setText("Salvar");
    if ((btn = button(QMessageBox::Cancel))) btn->setText("Cancelar");
    if ((btn = button(QMessageBox::Close))) btn->setText("Fechar");
    if ((btn = button(QMessageBox::Discard))) btn->setText("Descartar");
    if ((btn = button(QMessageBox::Apply))) btn->setText("Aplicar");
    if ((btn = button(QMessageBox::RestoreDefaults))) btn->setText("Restaurar Padrão");
    if ((btn = button(QMessageBox::Help))) btn->setText("Ajuda");
    if ((btn = button(QMessageBox::SaveAll))) btn->setText("Salvar Tudo");
    if ((btn = button(QMessageBox::YesToAll))) btn->setText("Sim para Todos");
    if ((btn = button(QMessageBox::No))) btn->setText("Não");
    if ((btn = button(QMessageBox::NoToAll))) btn->setText("Não à Todos");
    if ((btn = button(QMessageBox::Abort))) btn->setText("Abortar");
    if ((btn = button(QMessageBox::Retry))) btn->setText("Tentar Novamente");
    if ((btn = button(QMessageBox::Ignore))) btn->setText("Ignorar");

    return QMessageBox::exec();
}
/*}}}*/

// Static Member Functions
// SSMsgBox* SSMsgBox::create(QWidget *owner, const QString &text, const QString &title = QString(), const QString &info = QString(), const QString &details = QString(), int type = SSMsgBox::Info, int buttons = QMessageBox::Ok);/*{{{*/
SSMsgBox* SSMsgBox::create(QWidget *owner, const QString &text, const QString &title, const QString &info, const QString &details, int type, int buttons)
{
    if (!owner) owner = ss::App->mainWindow();

    QString dialogTitle( title );

    if (dialogTitle.isEmpty()) dialogTitle = owner->windowTitle();
    if (dialogTitle.isEmpty()) dialogTitle = QCoreApplication::applicationName();

    SSMsgBox *msgBox = new SSMsgBox(owner);

    msgBox->setWindowTitle( dialogTitle );
    msgBox->setText( text );
    msgBox->setInformativeText( info );
    msgBox->setDetailedText( details );
    msgBox->setIcon((QMessageBox::Icon)type);
    msgBox->setStandardButtons((QMessageBox::StandardButton)buttons);

    return msgBox;
}
/*}}}*/
// int SSMsgBox::alert(QWidget *owner, const QString &text, int type = SSMsgBox::Info, const QString &title = QString(), const QString &info = QString());/*{{{*/
int SSMsgBox::alert(QWidget *owner, const QString &text, int type, const QString &title, const QString &info)
{
    int buttons = QMessageBox::Ok;
    QString dialogTitle( title );

    if (dialogTitle.isEmpty()) dialogTitle = owner->windowTitle();
    if (dialogTitle.isEmpty()) dialogTitle = QCoreApplication::applicationName();

    if (!owner) owner = ss::App->mainWindow();
    if ((type == SSMsgBox::Warn) || (type == SSMsgBox::Error))
        buttons = QMessageBox::Close;
    else if (type == SSMsgBox::Question)
        buttons = QMessageBox::Yes | QMessageBox::No;

    SSMsgBox mb(owner);

    mb.setWindowTitle( dialogTitle );
    mb.setText( text );
    mb.setInformativeText( info );
    mb.setIcon((QMessageBox::Icon)type);
    mb.setStandardButtons((QMessageBox::StandardButton)buttons);

    return mb.exec();
}
/*}}}*/
// int SSMsgBox::confirm(QWidget *owner, const QString &text, int buttons = 0, const QString &title = QString(), const QString &info = QString());/*{{{*/
int SSMsgBox::confirm(QWidget *owner, const QString &text, int buttons, const QString &title, const QString &info)
{
    QString dialogTitle( title );

    if (dialogTitle.isEmpty()) dialogTitle = owner->windowTitle();
    if (dialogTitle.isEmpty()) dialogTitle = QCoreApplication::applicationName();

    if (!owner) owner = ss::App->mainWindow();
    if (!buttons) buttons = QMessageBox::Yes | QMessageBox::No;

    SSMsgBox mb(owner);

    mb.setIcon( QMessageBox::Question );
    mb.setWindowTitle( dialogTitle );
    mb.setText( text );
    mb.setInformativeText( info );
    mb.setStandardButtons((QMessageBox::StandardButton)buttons);

    return mb.exec();
}
/*}}}*/

