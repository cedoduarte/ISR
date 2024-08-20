#include "logger.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

Logger *Logger::s_instance = nullptr;

void Logger::initialize()
{
    s_instance = new Logger();
}

void Logger::finalize()
{
    delete s_instance;
    s_instance = nullptr;
}

void Logger::setOutputFilePath(const QString &filePath)
{
    s_instance->m_outputFilePath = filePath;
}

void Logger::log(const QString &output)
{
    QFile file(s_instance->m_outputFilePath);
    file.open(QIODevice::Text | QIODevice::Append);
    if (file.isOpen())
    {
        QTextStream stream(&file);
        stream << output << "\n";
        file.flush();
        file.close();
        return;
    }
    qDebug().noquote().nospace() << "Log error: File is not writtable";
}

Logger::Logger()
{
}

Logger::~Logger()
{
}
