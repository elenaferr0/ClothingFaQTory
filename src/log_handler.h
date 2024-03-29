#ifndef LOG_HANDLER_H
#define LOG_HANDLER_H

#include <QDebug>

void logHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    const char* file = context.file ? context.file : "";
    const char* function = context.function ? context.function : "";
    // ANSI escape codes to print colored logs
    const char* red = "\033[0;31m";
    const char* orange = "\033[38;2;255;165;0m";
    const char* yellow = "\033[1;33m";
    const char* green = "\033[0;32m";
    const char* blue = "\033[0;34m";
    const char* nocolor = "\033[0;37m";

    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "%sDebug%s: %s (%s:%u, %s)\n", blue, nocolor, localMsg.constData(), file, context.line,
                    function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "%sInfo%s: %s (%s:%u, %s)\n", green, nocolor, localMsg.constData(), file, context.line,
                    function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "%sWarning%s: %s (%s:%u, %s)\n", yellow, nocolor, localMsg.constData(), file, context.line,
                    function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "%sCritical%s: %s (%s:%u, %s)\n", orange, nocolor, localMsg.constData(), file, context.line,
                    function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "%sFatal%s: %s (%s:%u, %s)\n", red, nocolor, localMsg.constData(), file, context.line,
                    function);
            break;
    }
}

#endif