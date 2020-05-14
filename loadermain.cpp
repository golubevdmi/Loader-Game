#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <GridWindow.h>


int main(int argc, char *argv[])
{    
    //QGuiApplication app(argc, argv);

    QApplication app(argc, argv);
    GridWindow window;
    window.show();

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    qmlRegisterType<GridWindow>("GridWindow", 1, 0, "GridWindow");
//    //qmlRegisterType<FieldValue>("FieldValue", 1, 0, "fieldvalue");
//    QQmlApplicationEngine engine;
//    const QUrl url(QStringLiteral("qrc:/forms/resources/main.qml"));

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);

//    engine.load(url);

    return app.exec();
}
