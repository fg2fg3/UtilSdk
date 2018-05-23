/********************************************************************************
** Form generated from reading UI file 'UtilGui.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UTILGUI_H
#define UI_UTILGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UtilGuiClass
{
public:
    QWidget *centralWidget;
    QPushButton *m_pBtChineseSupport;
    QLabel *m_pLbPath;
    QPushButton *m_pBtCompare;
    QPushButton *m_pBtJoyStick;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UtilGuiClass)
    {
        if (UtilGuiClass->objectName().isEmpty())
            UtilGuiClass->setObjectName(QStringLiteral("UtilGuiClass"));
        UtilGuiClass->resize(600, 400);
        centralWidget = new QWidget(UtilGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        m_pBtChineseSupport = new QPushButton(centralWidget);
        m_pBtChineseSupport->setObjectName(QStringLiteral("m_pBtChineseSupport"));
        m_pBtChineseSupport->setGeometry(QRect(10, 40, 93, 28));
        m_pLbPath = new QLabel(centralWidget);
        m_pLbPath->setObjectName(QStringLiteral("m_pLbPath"));
        m_pLbPath->setGeometry(QRect(110, 50, 421, 16));
        m_pBtCompare = new QPushButton(centralWidget);
        m_pBtCompare->setObjectName(QStringLiteral("m_pBtCompare"));
        m_pBtCompare->setGeometry(QRect(10, 80, 93, 28));
        m_pBtJoyStick = new QPushButton(centralWidget);
        m_pBtJoyStick->setObjectName(QStringLiteral("m_pBtJoyStick"));
        m_pBtJoyStick->setGeometry(QRect(10, 110, 93, 28));
        UtilGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UtilGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        UtilGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UtilGuiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UtilGuiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(UtilGuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UtilGuiClass->setStatusBar(statusBar);

        retranslateUi(UtilGuiClass);

        QMetaObject::connectSlotsByName(UtilGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *UtilGuiClass)
    {
        UtilGuiClass->setWindowTitle(QApplication::translate("UtilGuiClass", "UtilGui", 0));
        m_pBtChineseSupport->setText(QApplication::translate("UtilGuiClass", "\344\270\255\346\226\207\346\224\257\346\214\201", 0));
        m_pLbPath->setText(QApplication::translate("UtilGuiClass", "\350\267\257\345\276\204", 0));
        m_pBtCompare->setText(QApplication::translate("UtilGuiClass", "\345\255\227\347\254\246\346\257\224\350\276\203", 0));
        m_pBtJoyStick->setText(QApplication::translate("UtilGuiClass", "\346\270\270\346\210\217\346\211\213\346\237\204", 0));
    } // retranslateUi

};

namespace Ui {
    class UtilGuiClass: public Ui_UtilGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILGUI_H
