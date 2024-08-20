#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

class Logger
{
public:
    static void initialize();
    static void finalize();
    static void setOutputFilePath(const QString &filePath);
    static void log(const QString &output);
private:
    static Logger *s_instance;
    QString m_outputFilePath;

    Logger();
    virtual ~Logger();
};

#endif // LOGGER_H
