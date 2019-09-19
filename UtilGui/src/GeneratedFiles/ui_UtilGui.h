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
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_pBtCompare;
    QPushButton *m_pBtHexString;
    QPushButton *m_pBtSerialPort;
    QPushButton *m_pBtCloseSerialPort;
    QPushButton *m_pBtJoyStick;
    QPushButton *m_pBtOpencvDemo;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *m_pBtSqlite;
    QPushButton *m_pBtJson2Db;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_pBtZipFile;
    QPushButton *m_pBtUnzipFile;
    QPushButton *m_pBtStartQueue;
    QPushButton *m_pBtStopQueue;
    QPushButton *m_pBtQueueSize;
    QPushButton *m_pBtPrint;
    QPushButton *m_pBtWeb;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *m_pBtStartThread;
    QPushButton *m_pBtStopThread;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *m_pBtRapidJsonRead;
    QPushButton *m_pBtRapidJsonWrite;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *m_pBtBoostServer;
    QPushButton *m_pBtBoostClient;
    QPushButton *m_pBtStopBoostCS;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *m_pBtCharTest;
    QPushButton *m_pBtConIOCPServer;
    QPushButton *m_pBtDisconIOCPServer;
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
        verticalLayoutWidget->setGeometry(QRect(0, 1, 591, 431));
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

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_pBtCompare = new QPushButton(verticalLayoutWidget);
        m_pBtCompare->setObjectName(QStringLiteral("m_pBtCompare"));

        horizontalLayout_3->addWidget(m_pBtCompare);

        m_pBtHexString = new QPushButton(verticalLayoutWidget);
        m_pBtHexString->setObjectName(QStringLiteral("m_pBtHexString"));

        horizontalLayout_3->addWidget(m_pBtHexString);

        m_pBtSerialPort = new QPushButton(verticalLayoutWidget);
        m_pBtSerialPort->setObjectName(QStringLiteral("m_pBtSerialPort"));

        horizontalLayout_3->addWidget(m_pBtSerialPort);

        m_pBtCloseSerialPort = new QPushButton(verticalLayoutWidget);
        m_pBtCloseSerialPort->setObjectName(QStringLiteral("m_pBtCloseSerialPort"));

        horizontalLayout_3->addWidget(m_pBtCloseSerialPort);


        verticalLayout->addLayout(horizontalLayout_3);

        m_pBtJoyStick = new QPushButton(verticalLayoutWidget);
        m_pBtJoyStick->setObjectName(QStringLiteral("m_pBtJoyStick"));

        verticalLayout->addWidget(m_pBtJoyStick);

        m_pBtOpencvDemo = new QPushButton(verticalLayoutWidget);
        m_pBtOpencvDemo->setObjectName(QStringLiteral("m_pBtOpencvDemo"));

        verticalLayout->addWidget(m_pBtOpencvDemo);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        m_pBtSqlite = new QPushButton(verticalLayoutWidget);
        m_pBtSqlite->setObjectName(QStringLiteral("m_pBtSqlite"));

        horizontalLayout_4->addWidget(m_pBtSqlite);

        m_pBtJson2Db = new QPushButton(verticalLayoutWidget);
        m_pBtJson2Db->setObjectName(QStringLiteral("m_pBtJson2Db"));

        horizontalLayout_4->addWidget(m_pBtJson2Db);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_pBtZipFile = new QPushButton(verticalLayoutWidget);
        m_pBtZipFile->setObjectName(QStringLiteral("m_pBtZipFile"));

        horizontalLayout_2->addWidget(m_pBtZipFile);

        m_pBtUnzipFile = new QPushButton(verticalLayoutWidget);
        m_pBtUnzipFile->setObjectName(QStringLiteral("m_pBtUnzipFile"));

        horizontalLayout_2->addWidget(m_pBtUnzipFile);

        m_pBtStartQueue = new QPushButton(verticalLayoutWidget);
        m_pBtStartQueue->setObjectName(QStringLiteral("m_pBtStartQueue"));

        horizontalLayout_2->addWidget(m_pBtStartQueue);

        m_pBtStopQueue = new QPushButton(verticalLayoutWidget);
        m_pBtStopQueue->setObjectName(QStringLiteral("m_pBtStopQueue"));

        horizontalLayout_2->addWidget(m_pBtStopQueue);

        m_pBtQueueSize = new QPushButton(verticalLayoutWidget);
        m_pBtQueueSize->setObjectName(QStringLiteral("m_pBtQueueSize"));

        horizontalLayout_2->addWidget(m_pBtQueueSize);


        verticalLayout->addLayout(horizontalLayout_2);

        m_pBtPrint = new QPushButton(verticalLayoutWidget);
        m_pBtPrint->setObjectName(QStringLiteral("m_pBtPrint"));

        verticalLayout->addWidget(m_pBtPrint);

        m_pBtWeb = new QPushButton(verticalLayoutWidget);
        m_pBtWeb->setObjectName(QStringLiteral("m_pBtWeb"));

        verticalLayout->addWidget(m_pBtWeb);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        m_pBtStartThread = new QPushButton(verticalLayoutWidget);
        m_pBtStartThread->setObjectName(QStringLiteral("m_pBtStartThread"));

        horizontalLayout_5->addWidget(m_pBtStartThread);

        m_pBtStopThread = new QPushButton(verticalLayoutWidget);
        m_pBtStopThread->setObjectName(QStringLiteral("m_pBtStopThread"));

        horizontalLayout_5->addWidget(m_pBtStopThread);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        m_pBtRapidJsonRead = new QPushButton(verticalLayoutWidget);
        m_pBtRapidJsonRead->setObjectName(QStringLiteral("m_pBtRapidJsonRead"));

        horizontalLayout_6->addWidget(m_pBtRapidJsonRead);

        m_pBtRapidJsonWrite = new QPushButton(verticalLayoutWidget);
        m_pBtRapidJsonWrite->setObjectName(QStringLiteral("m_pBtRapidJsonWrite"));

        horizontalLayout_6->addWidget(m_pBtRapidJsonWrite);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        m_pBtBoostServer = new QPushButton(verticalLayoutWidget);
        m_pBtBoostServer->setObjectName(QStringLiteral("m_pBtBoostServer"));

        horizontalLayout_7->addWidget(m_pBtBoostServer);

        m_pBtBoostClient = new QPushButton(verticalLayoutWidget);
        m_pBtBoostClient->setObjectName(QStringLiteral("m_pBtBoostClient"));

        horizontalLayout_7->addWidget(m_pBtBoostClient);

        m_pBtStopBoostCS = new QPushButton(verticalLayoutWidget);
        m_pBtStopBoostCS->setObjectName(QStringLiteral("m_pBtStopBoostCS"));

        horizontalLayout_7->addWidget(m_pBtStopBoostCS);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        m_pBtCharTest = new QPushButton(verticalLayoutWidget);
        m_pBtCharTest->setObjectName(QStringLiteral("m_pBtCharTest"));

        horizontalLayout_8->addWidget(m_pBtCharTest);

        m_pBtConIOCPServer = new QPushButton(verticalLayoutWidget);
        m_pBtConIOCPServer->setObjectName(QStringLiteral("m_pBtConIOCPServer"));

        horizontalLayout_8->addWidget(m_pBtConIOCPServer);

        m_pBtDisconIOCPServer = new QPushButton(verticalLayoutWidget);
        m_pBtDisconIOCPServer->setObjectName(QStringLiteral("m_pBtDisconIOCPServer"));

        horizontalLayout_8->addWidget(m_pBtDisconIOCPServer);


        verticalLayout->addLayout(horizontalLayout_8);

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
        m_pBtHexString->setText(QApplication::translate("UtilGuiClass", "16\350\277\233\345\210\266\345\222\214\345\255\227\347\254\246\344\270\262", 0));
        m_pBtSerialPort->setText(QApplication::translate("UtilGuiClass", "\344\270\262\345\217\243\350\260\203\350\257\225", 0));
        m_pBtCloseSerialPort->setText(QApplication::translate("UtilGuiClass", "\345\205\263\351\227\255\344\270\262\345\217\243", 0));
        m_pBtJoyStick->setText(QApplication::translate("UtilGuiClass", "\346\270\270\346\210\217\346\211\213\346\237\204", 0));
        m_pBtOpencvDemo->setText(QApplication::translate("UtilGuiClass", "OpenCV\345\212\237\350\203\275\346\265\213\350\257\225-\344\275\277\347\224\2502.4.11", 0));
        m_pBtSqlite->setText(QApplication::translate("UtilGuiClass", "\346\265\213\350\257\225sqlite", 0));
        m_pBtJson2Db->setText(QApplication::translate("UtilGuiClass", "Json\344\270\255\346\226\207\345\216\213\345\205\245\346\225\260\346\215\256\345\272\223", 0));
        m_pBtZipFile->setText(QApplication::translate("UtilGuiClass", "\345\216\213\347\274\251\346\226\207\344\273\266", 0));
        m_pBtUnzipFile->setText(QApplication::translate("UtilGuiClass", "\350\247\243\345\216\213\346\226\207\344\273\266", 0));
        m_pBtStartQueue->setText(QApplication::translate("UtilGuiClass", "\345\220\257\345\212\250\351\230\237\345\210\227", 0));
        m_pBtStopQueue->setText(QApplication::translate("UtilGuiClass", "\346\265\213\350\257\225\347\273\223\346\236\204\344\275\223\345\216\213\345\205\245\351\230\237\345\210\227", 0));
        m_pBtQueueSize->setText(QApplication::translate("UtilGuiClass", "\346\237\245\347\234\213\351\230\237\345\210\227\345\244\247\345\260\217", 0));
        m_pBtPrint->setText(QApplication::translate("UtilGuiClass", "\346\211\223\345\215\260", 0));
        m_pBtWeb->setText(QApplication::translate("UtilGuiClass", "\346\211\223\345\274\200QtWeb", 0));
        m_pBtStartThread->setText(QApplication::translate("UtilGuiClass", "\345\274\200\345\220\257\347\272\277\347\250\213", 0));
        m_pBtStopThread->setText(QApplication::translate("UtilGuiClass", "\345\201\234\346\255\242\347\272\277\347\250\213", 0));
        m_pBtRapidJsonRead->setText(QApplication::translate("UtilGuiClass", "RapidJsonRead", 0));
        m_pBtRapidJsonWrite->setText(QApplication::translate("UtilGuiClass", "RapidJsonWrite", 0));
        m_pBtBoostServer->setText(QApplication::translate("UtilGuiClass", "\345\220\257\345\212\250BoostServer", 0));
        m_pBtBoostClient->setText(QApplication::translate("UtilGuiClass", "\345\220\257\345\212\250BoostClient", 0));
        m_pBtStopBoostCS->setText(QApplication::translate("UtilGuiClass", "\345\201\234\346\255\242Boost\345\256\242\346\210\267\347\253\257\346\234\215\345\212\241\345\231\250", 0));
        m_pBtCharTest->setText(QApplication::translate("UtilGuiClass", "\345\255\227\347\254\246\346\265\213\350\257\225", 0));
        m_pBtConIOCPServer->setText(QApplication::translate("UtilGuiClass", "\350\277\236\346\216\245IOCP\346\234\215\345\212\241\347\253\257", 0));
        m_pBtDisconIOCPServer->setText(QApplication::translate("UtilGuiClass", "\346\226\255\345\274\200\350\277\236\346\216\245IOCP\346\234\215\345\212\241\347\253\257", 0));
    } // retranslateUi

};

namespace Ui {
    class UtilGuiClass: public Ui_UtilGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UTILGUI_H
