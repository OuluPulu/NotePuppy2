#include <QApplication>
#include <QQmlApplicationEngine>

#include <puppycore.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    PuppyCore *pc = new PuppyCore(&app);
    engine.rootContext()->setContextProperty("PuppyCore", pc);
    engine.rootContext()->setContextProperty("FileSystemModel", pc->fileSystemModel());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
