#ifndef HURISCHEMEHANDLER_H
#define HURISCHEMEHANDLER_H

#include <QObject>

#include <QtCore/qglobal.h>

#if defined(QT_URL_SCHEME_HANDLER_LIB)
#define LIB_EXPORT Q_DECL_EXPORT
#else
#define LIB_EXPORT Q_DECL_IMPORT
#endif

class LIB_EXPORT HUriSchemeHandler : public QObject
{
    Q_OBJECT
public:
    enum Result{
        Success,
        Error,
    };
    Q_ENUM(Result);

    static Result setUriProtocolHandler(const QString &displayName, const QString &URIScheme);
    static Result removeUriProtocolHandler(const QString &URIScheme);

private:
    explicit HUriSchemeHandler(QObject *parent = nullptr);

signals:
};

#endif // HURISCHEMEHANDLER_H
