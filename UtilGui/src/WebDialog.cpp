#include "WebDialog.h"

WebDialog::WebDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//ui.m_pWebView->load(QUrl("http://www.baidu.com"));
	ui.m_pWebView->load(QUrl("file:///d/hello.html"));
}

WebDialog::~WebDialog()
{

}
