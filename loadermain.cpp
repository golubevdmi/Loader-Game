#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MVC/GridModel.h>

#include <QQuickView>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<GridModel>("GridModel", 1, 0, "GridModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/forms/resources/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
