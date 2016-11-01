#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#define WINAPI __stdcall

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) 
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
