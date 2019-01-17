/********************************************************************************
** Form generated from reading UI file 'WebDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBDIALOG_H
#define UI_WEBDIALOG_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebDialog
{
public:
    QWebView *m_pWebView;

    void setupUi(QWidget *WebDialog)
    {
        if (WebDialog->objectName().isEmpty())
            WebDialog->setObjectName(QStringLiteral("WebDialog"));
        WebDialog->resize(962, 755);
        m_pWebView = new QWebView(WebDialog);
        m_pWebView->setObjectName(QStringLiteral("m_pWebView"));
        m_pWebView->setGeometry(QRect(10, 10, 931, 701));
        m_pWebView->setUrl(QUrl(QStringLiteral("about:blank")));

        retranslateUi(WebDialog);

        QMetaObject::connectSlotsByName(WebDialog);
    } // setupUi

    void retranslateUi(QWidget *WebDialog)
    {
        WebDialog->setWindowTitle(QApplication::translate("WebDialog", "WebDialog", 0));
    } // retranslateUi

};

namespace Ui {
    class WebDialog: public Ui_WebDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBDIALOG_H
