/********************************************************************************
** Form generated from reading UI file 'JoyStickDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOYSTICKDIALOG_H
#define UI_JOYSTICKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_JoyStickDialog
{
public:
    QPushButton *m_pBtCapture;

    void setupUi(QDialog *JoyStickDialog)
    {
        if (JoyStickDialog->objectName().isEmpty())
            JoyStickDialog->setObjectName(QStringLiteral("JoyStickDialog"));
        JoyStickDialog->resize(400, 300);
        m_pBtCapture = new QPushButton(JoyStickDialog);
        m_pBtCapture->setObjectName(QStringLiteral("m_pBtCapture"));
        m_pBtCapture->setGeometry(QRect(70, 140, 191, 41));

        retranslateUi(JoyStickDialog);

        QMetaObject::connectSlotsByName(JoyStickDialog);
    } // setupUi

    void retranslateUi(QDialog *JoyStickDialog)
    {
        JoyStickDialog->setWindowTitle(QApplication::translate("JoyStickDialog", "JoyStickDialog", 0));
        m_pBtCapture->setText(QApplication::translate("JoyStickDialog", "\351\207\215\346\226\260\350\216\267\345\217\226\350\256\276\345\244\207", 0));
    } // retranslateUi

};

namespace Ui {
    class JoyStickDialog: public Ui_JoyStickDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICKDIALOG_H
