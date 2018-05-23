#include "UtilGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UtilGui w;
	w.show();
	return a.exec();
}
