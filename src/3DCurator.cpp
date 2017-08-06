#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include <vtkObject.h>

#include "GUI/MainWindow.h"

//#define RELEASE

#ifdef RELEASE
#define WINAPI __stdcall
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) 
#else
int main()
#endif
{
	int argc = 0;

	#ifdef RELEASE
	vtkObject::GlobalWarningDisplayOff(); // disable VTK warnings
	#endif

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    
	QApplication a(argc, 0);

	a.installTranslator(&qtTranslator);

	MainWindow w;
	w.show();

	return a.exec();
}
