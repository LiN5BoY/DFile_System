#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QIcon>
#include "./handler/ButtonHandler.h"
#include "./handler/HcHandler.h"
#include "./models/OpenGLItem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 创造ButtonHandler对象
    ButtonHandler buttonHandler;
    // 将ButtonHandler对象注册到QML中
    engine.rootContext()->setContextProperty("buttonHandler", &buttonHandler);
    qmlRegisterType<ButtonHandler>("com.button.handler", 1, 0, "ButtonHandler");
    // 创造HcHandler对象注册到QML中
    HcHandler hcHandler;
    engine.rootContext()->setContextProperty("hcHandler", &hcHandler);
    qmlRegisterType<HcHandler>("com.hc.handler", 1, 0, "HcHandler");
    // 注册OpenGLItem对象到QML中
    qmlRegisterType<OpenGLItem>("com.models.openglitem",1, 0,"OpenGLItem");


    const QUrl url(QStringLiteral("qrc:/qt/qml/JXCqmlTools/qml/App.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
