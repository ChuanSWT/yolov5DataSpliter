#include <QGuiApplication>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.loadFromModule("DataSpliter", "Main");

    //qmlRegisterType<Backend>("App", 1, 0, "Backend");
    return app.exec();
}
