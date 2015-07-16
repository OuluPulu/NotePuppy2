#include <QApplication>
#include <QQmlApplicationEngine>

#include "puppycore.h"
#include "puppyfile.h"
#include <QQmlContext>
#include <QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    PuppyCore *pc = new PuppyCore(&app);
    engine.rootContext()->setContextProperty("PuppyCore", pc);
    engine.rootContext()->setContextProperty("FileSystemModel", pc->fileSystemModel());

    qmlRegisterType<PuppyFile>("NotePuppy2", 2, 0, "PuppyFile");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
