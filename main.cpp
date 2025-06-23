#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "Logger.h"
#include "LoggerConfig.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    LoggerConfig config;
    if (!config.loadFromFile("config.json")) {
        qCritical() << "Config dosyası okunamadı!";
        return -1;
    }

    Logger logger(config);

    logger.log("Birinci test logu.");

    QTimer::singleShot(3000, &app, &QCoreApplication::quit);

    return app.exec();
}
