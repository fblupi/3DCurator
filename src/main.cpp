#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include "GUI/mainwindow.h"

#define WINAPI __stdcall

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) 
//int main()
{
	int argc = 0;

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    
	QApplication a(argc, 0);

	a.installTranslator(&qtTranslator);

	MainWindow w;
	w.show();

	return a.exec();
}
