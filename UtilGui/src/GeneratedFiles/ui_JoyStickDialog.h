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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JoyStickDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pBtCapture;
    QPushButton *m_pBtOpenCom;
    QPushButton *m_pBtCloseCom;
    QLabel *m_pLbStatu;

    void setupUi(QDialog *JoyStickDialog)
    {
        if (JoyStickDialog->objectName().isEmpty())
            JoyStickDialog->setObjectName(QStringLiteral("JoyStickDialog"));
        JoyStickDialog->resize(595, 383);
        horizontalLayoutWidget = new QWidget(JoyStickDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 40, 374, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_pBtCapture = new QPushButton(horizontalLayoutWidget);
        m_pBtCapture->setObjectName(QStringLiteral("m_pBtCapture"));

        horizontalLayout->addWidget(m_pBtCapture);

        m_pBtOpenCom = new QPushButton(horizontalLayoutWidget);
        m_pBtOpenCom->setObjectName(QStringLiteral("m_pBtOpenCom"));

        horizontalLayout->addWidget(m_pBtOpenCom);

        m_pBtCloseCom = new QPushButton(horizontalLayoutWidget);
        m_pBtCloseCom->setObjectName(QStringLiteral("m_pBtCloseCom"));

        horizontalLayout->addWidget(m_pBtCloseCom);

        m_pLbStatu = new QLabel(horizontalLayoutWidget);
        m_pLbStatu->setObjectName(QStringLiteral("m_pLbStatu"));

        horizontalLayout->addWidget(m_pLbStatu);


        retranslateUi(JoyStickDialog);

        QMetaObject::connectSlotsByName(JoyStickDialog);
    } // setupUi

    void retranslateUi(QDialog *JoyStickDialog)
    {
        JoyStickDialog->setWindowTitle(QApplication::translate("JoyStickDialog", "JoyStickDialog", 0));
        m_pBtCapture->setText(QApplication::translate("JoyStickDialog", "\350\216\267\345\217\226\350\256\276\345\244\207", 0));
        m_pBtOpenCom->setText(QApplication::translate("JoyStickDialog", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
        m_pBtCloseCom->setText(QApplication::translate("JoyStickDialog", "\345\205\263\351\227\255\344\270\262\345\217\243", 0));
        m_pLbStatu->setText(QApplication::translate("JoyStickDialog", "\347\212\266\346\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class JoyStickDialog: public Ui_JoyStickDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOYSTICKDIALOG_H
