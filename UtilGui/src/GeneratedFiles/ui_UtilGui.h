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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UtilGuiClass
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pBtChineseSupport;
    QLabel *m_pLbPath;
    QPushButton *m_pBtCompare;
    QPushButton *m_pBtJoyStick;
    QPushButton *m_pBtOpencvDemo;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_pBtZipFile;
    QPushButton *m_pBtUnzipFile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UtilGuiClass)
    {
        if (UtilGuiClass->objectName().isEmpty())
            UtilGuiClass->setObjectName(QStringLiteral("UtilGuiClass"));
        UtilGuiClass->resize(593, 720);
        centralWidget = new QWidget(UtilGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 1, 591, 137));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_pBtChineseSupport = new QPushButton(verticalLayoutWidget);
        m_pBtChineseSupport->setObjectName(QStringLiteral("m_pBtChineseSupport"));

        horizontalLayout->addWidget(m_pBtChineseSupport);

        m_pLbPath = new QLabel(verticalLayoutWidget);
        m_pLbPath->setObjectName(QStringLiteral("m_pLbPath"));

        horizontalLayout->addWidget(m_pLbPath);


        verticalLayout->addLayout(horizontalLayout);

        m_pBtCompare = new QPushButton(verticalLayoutWidget);
        m_pBtCompare->setObjectName(QStringLiteral("m_pBtCompare"));

        verticalLayout->addWidget(m_pBtCompare);

        m_pBtJoyStick = new QPushButton(verticalLayoutWidget);
        m_pBtJoyStick->setObjectName(QStringLiteral("m_pBtJoyStick"));

        verticalLayout->addWidget(m_pBtJoyStick);

        m_pBtOpencvDemo = new QPushButton(verticalLayoutWidget);
        m_pBtOpencvDemo->setObjectName(QStringLiteral("m_pBtOpencvDemo"));

        verticalLayout->addWidget(m_pBtOpencvDemo);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(70, 190, 195, 80));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        m_pBtZipFile = new QPushButton(horizontalLayoutWidget);
        m_pBtZipFile->setObjectName(QStringLiteral("m_pBtZipFile"));

        horizontalLayout_2->addWidget(m_pBtZipFile);

        m_pBtUnzipFile = new QPushButton(horizontalLayoutWidget);
        m_pBtUnzipFile->setObjectName(QStringLiteral("m_pBtUnzipFile"));

        horizontalLayout_2->addWidget(m_pBtUnzipFile);

        UtilGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UtilGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 593, 26));
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
        m_pBtOpencvDemo->setText(QApplication::translate("UtilGuiClass", "OpenCV\345\212\237\350\203\275\346\265\213\350\257\225-\344\275\277\347\224\2502.4.11", 0));
        m_pBtZipFile->setText(QApplication::translate("UtilGuiClass", "\345\216\213\347\274\251\346\226\207\344\273\266", 0));
        m_pBtUnzipFile->setText(QApplication::translate("UtilGuiClass", "\350\247\243\345\216\213\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class UtilGuiClass: public Ui_UtilGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILGUI_H
