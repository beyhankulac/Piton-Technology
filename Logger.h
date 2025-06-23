#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include "LoggerConfig.h"

class Logger {
public:
    Logger(const LoggerConfig& config);
    void log(const QString& message);

private:
    QString getLogFileName() const;
    void rotateLogsIfNeeded();

    LoggerConfig config;
};

#endif
