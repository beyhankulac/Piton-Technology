#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QDebug>

Logger::Logger(const LoggerConfig& config) : config(config) {
    QDir().mkpath(config.logDirectory);
}

QString Logger::getLogFileName() const {
    QDateTime now = QDateTime::currentDateTimeUtc();

    if (config.interval == "daily")
        return now.toString("yyyy-MM-dd") + ".log";
    else if (config.interval == "hourly")
        return now.toString("yyyy-MM-dd_HH") + ".log";
    else if (config.interval == "minutely")
        return now.toString("yyyy-MM-dd_HH-mm") + ".log";
    else
        return now.toString("yyyy-MM-dd_HH-mm-ss") + ".log";
}

void Logger::rotateLogsIfNeeded() {
    QDir dir(config.logDirectory);
    QStringList files = dir.entryList(QStringList() << "*.log", QDir::Files, QDir::Time | QDir::Reversed);

    while (files.size() > config.maxFiles) {
        QString oldestFile = files.first(); // en eski en başta
        QFile fileToRemove(dir.absoluteFilePath(oldestFile));

        if (fileToRemove.remove()) {
            qDebug() << "Silindi:" << oldestFile;
        } else {
            qWarning() << "Silinemedi:" << oldestFile;
        }

        files.removeFirst();
    }
}


void Logger::log(const QString& message) {
    rotateLogsIfNeeded();

    QString filePath = config.logDirectory + "/" + getLogFileName();
    QFile file(filePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTimeUtc().toString(Qt::ISODate) << " - " << message << "\n";
        file.close();

        qDebug() << "Log yazıldı:" << filePath;
    } else {
        qWarning() << "Log dosyası açılamadı:" << filePath;
    }
}
