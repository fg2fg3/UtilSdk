/********************************************************************************
** Form generated from reading UI file 'OpencvDemoDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENCVDEMODIALOG_H
#define UI_OPENCVDEMODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpencvDemoDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *m_pBtPic1;
    QLabel *m_pLbPic1Path;
    QPushButton *m_pBtPic2;
    QLabel *m_pLbPic2Path;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *m_pBtMergePic;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *m_pLbPic1;
    QLabel *m_pLbPic2;
    QLabel *m_pLbPicMerge;

    void setupUi(QDialog *OpencvDemoDialog)
    {
        if (OpencvDemoDialog->objectName().isEmpty())
            OpencvDemoDialog->setObjectName(QStringLiteral("OpencvDemoDialog"));
        OpencvDemoDialog->resize(1114, 932);
        verticalLayoutWidget = new QWidget(OpencvDemoDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1111, 921));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_pBtPic1 = new QPushButton(verticalLayoutWidget);
        m_pBtPic1->setObjectName(QStringLiteral("m_pBtPic1"));

        horizontalLayout->addWidget(m_pBtPic1);

        m_pLbPic1Path = new QLabel(verticalLayoutWidget);
        m_pLbPic1Path->setObjectName(QStringLiteral("m_pLbPic1Path"));

        horizontalLayout->addWidget(m_pLbPic1Path);

        m_pBtPic2 = new QPushButton(verticalLayoutWidget);
        m_pBtPic2->setObjectName(QStringLiteral("m_pBtPic2"));

        horizontalLayout->addWidget(m_pBtPic2);

        m_pLbPic2Path = new QLabel(verticalLayoutWidget);
        m_pLbPic2Path->setObjectName(QStringLiteral("m_pLbPic2Path"));

        horizontalLayout->addWidget(m_pLbPic2Path);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_pBtMergePic = new QPushButton(verticalLayoutWidget);
        m_pBtMergePic->setObjectName(QStringLiteral("m_pBtMergePic"));

        horizontalLayout_2->addWidget(m_pBtMergePic);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(verticalLayoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_pLbPic1 = new QLabel(verticalLayoutWidget);
        m_pLbPic1->setObjectName(QStringLiteral("m_pLbPic1"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_pLbPic1->sizePolicy().hasHeightForWidth());
        m_pLbPic1->setSizePolicy(sizePolicy);
        m_pLbPic1->setMaximumSize(QSize(640, 480));
        m_pLbPic1->setFrameShape(QFrame::Box);
        m_pLbPic1->setScaledContents(true);

        horizontalLayout_3->addWidget(m_pLbPic1);

        m_pLbPic2 = new QLabel(verticalLayoutWidget);
        m_pLbPic2->setObjectName(QStringLiteral("m_pLbPic2"));
        sizePolicy.setHeightForWidth(m_pLbPic2->sizePolicy().hasHeightForWidth());
        m_pLbPic2->setSizePolicy(sizePolicy);
        m_pLbPic2->setMaximumSize(QSize(640, 480));
        m_pLbPic2->setFrameShape(QFrame::Box);
        m_pLbPic2->setScaledContents(true);

        horizontalLayout_3->addWidget(m_pLbPic2);


        verticalLayout->addLayout(horizontalLayout_3);

        m_pLbPicMerge = new QLabel(verticalLayoutWidget);
        m_pLbPicMerge->setObjectName(QStringLiteral("m_pLbPicMerge"));
        sizePolicy.setHeightForWidth(m_pLbPicMerge->sizePolicy().hasHeightForWidth());
        m_pLbPicMerge->setSizePolicy(sizePolicy);
        m_pLbPicMerge->setMaximumSize(QSize(640, 480));
        m_pLbPicMerge->setFrameShape(QFrame::Box);
        m_pLbPicMerge->setScaledContents(true);

        verticalLayout->addWidget(m_pLbPicMerge);


        retranslateUi(OpencvDemoDialog);

        QMetaObject::connectSlotsByName(OpencvDemoDialog);
    } // setupUi

    void retranslateUi(QDialog *OpencvDemoDialog)
    {
        OpencvDemoDialog->setWindowTitle(QApplication::translate("OpencvDemoDialog", "OpencvDemoDialog", 0));
        m_pBtPic1->setText(QApplication::translate("OpencvDemoDialog", "\351\200\211\345\233\2761", 0));
        m_pLbPic1Path->setText(QApplication::translate("OpencvDemoDialog", "TextLabel", 0));
        m_pBtPic2->setText(QApplication::translate("OpencvDemoDialog", "\351\200\211\345\233\2762", 0));
        m_pLbPic2Path->setText(QApplication::translate("OpencvDemoDialog", "TextLabel", 0));
        m_pBtMergePic->setText(QApplication::translate("OpencvDemoDialog", "\345\217\240\345\233\276", 0));
        pushButton_2->setText(QApplication::translate("OpencvDemoDialog", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("OpencvDemoDialog", "PushButton", 0));
        m_pLbPic1->setText(QApplication::translate("OpencvDemoDialog", "TextLabel", 0));
        m_pLbPic2->setText(QApplication::translate("OpencvDemoDialog", "TextLabel", 0));
        m_pLbPicMerge->setText(QApplication::translate("OpencvDemoDialog", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class OpencvDemoDialog: public Ui_OpencvDemoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENCVDEMODIALOG_H
