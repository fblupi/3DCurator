#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QObject>
#include <QSurfaceFormat> 

#include <QVTKOpenGLNativeWidget.h> 
#include <vtkObject.h>

#include "GUI/MainWindow.h"

#define RELEASE

#if defined RELEASE && defined _WIN32
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

	QSurfaceFormat format = QVTKOpenGLNativeWidget::defaultFormat();
	format.setSamples(0);
	QSurfaceFormat::setDefaultFormat(format);
    
	QApplication app(argc, 0);

	QTranslator qtTranslator;
	qtTranslator.load(":/i18n/en_US");
	app.installTranslator(&qtTranslator);

	MainWindow window;
	window.show();

	return app.exec();
}
