#ifndef LOGGERCONFIG_H
#define LOGGERCONFIG_H

#include <QString>

class LoggerConfig {
public:
    LoggerConfig();
    bool loadFromFile(const QString& filePath);

    int maxFiles;
    QString interval;
    QString logDirectory;
};

#endif
