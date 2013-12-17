#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QtQml>
#include "conwaylistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ConwayListModel>("com.minimoog77", 1, 0, "ConwayListModel");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/quickconway/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
