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

QT_BEGIN_NAMESPACE

class Ui_JoyStickDialog
{
public:

    void setupUi(QDialog *JoyStickDialog)
    {
        if (JoyStickDialog->objectName().isEmpty())
            JoyStickDialog->setObjectName(QStringLiteral("JoyStickDialog"));
        JoyStickDialog->resize(400, 300);

        retranslateUi(JoyStickDialog);

        QMetaObject::connectSlotsByName(JoyStickDialog);
    } // setupUi

    void retranslateUi(QDialog *JoyStickDialog)
    {
        JoyStickDialog->setWindowTitle(QApplication::translate("JoyStickDialog", "JoyStickDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class JoyStickDialog: public Ui_JoyStickDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICKDIALOG_H
