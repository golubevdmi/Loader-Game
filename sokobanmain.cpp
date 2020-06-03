#include "Model/SokobanModel.h"
#include "StatStorage/StatStorage.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCursor>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Sokoban");

    QGuiApplication app(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    qmlRegisterType<SokobanModel>("SokobanModel", 1, 0, "SokobanModel");
    qmlRegisterType<StatStorage>("StatStorage", 1, 0, "StatStorage");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/forms/resources/sokoban.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
