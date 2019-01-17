#include "UtilGui.h"
#include <QtWidgets/QApplication>

#pragma comment(lib,"ws2_32.lib") 

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UtilGui w;
	w.show();
	return a.exec();
}
