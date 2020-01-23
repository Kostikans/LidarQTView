#include <QtWidgets\qapplication.h>
#include <QtWidgets\qwidget.h>
#include "OpenglWidget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    LidarViewWidget w;
    w.resize(1000, 800);
    w.show();
    return a.exec();
}