#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QObject>

#include <vtkObject.h>

#include "GUI/MainWindow.h"

#define RELEASE

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
    
	QApplication app(argc, 0);

	QTranslator qtTranslator;
	qtTranslator.load(":/i18n/en_US");
	app.installTranslator(&qtTranslator);

	MainWindow window;
	window.show();

	return app.exec();
}
