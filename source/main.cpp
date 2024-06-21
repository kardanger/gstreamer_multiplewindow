#include <QApplication>
#include <QLoggingCategory>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QFont>

#include <streamviewer.h>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ScreenViewer_qml);

    QApplication app(argc, argv);
    gst_init (NULL, NULL);

    StreamViewer* viewer1 = new StreamViewer(1, nullptr);
    viewer1->show();

    StreamViewer* viewer2 = new StreamViewer(2, nullptr);
    viewer2->show();

    return app.exec();
    return 0;
}
