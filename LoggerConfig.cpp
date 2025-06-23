#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "LoggerConfig.h"

LoggerConfig::LoggerConfig()
    : maxFiles(7), interval("daily"), logDirectory("./logs") {}

bool LoggerConfig::loadFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Config dosyası açılamadı!";
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        qCritical() << "Config JSON formatı geçersiz!";
        return false;
    }

    QJsonObject obj = doc.object();
    maxFiles = obj["maxFiles"].toInt(7);
    interval = obj["interval"].toString("daily");
    logDirectory = obj["logDirectory"].toString("./logs");

    return true;
}
