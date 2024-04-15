#include <QDebug>
#include <QFile>
#include <QUuid>
#include <QStandardPaths>
#include <QCoreApplication>
#include <qt_windows.h>
#include "hurischemehandler.h"

// %1: uri scheme name, %2: display name
static const QString RegistNamePattern = "reg add HKEY_CLASSES_ROOT\\%1 /t REG_SZ /d \"%2\" /f";
// %1: uri scheme name, %2: icon eg. alert.exe,1
static const QString RegistIconPattern = "reg add HKEY_CLASSES_ROOT\\%1\\DefaultIcon /t REG_SZ /d \"%2\" /f";
// %1: uri scheme name
static const QString RegistUriSchemePattern = "reg add HKEY_CLASSES_ROOT\\%1 /v \"URL Protocol\" /t REG_SZ /d \"\" /f";
// %1: uri scheme name, %2: target exe full path, %3: %%1 (QString::arg bad dealing with %)
static const QString RegistCallbackCommandPattern = "reg add HKEY_CLASSES_ROOT\\%1\\shell\\open\\command /t REG_SZ /d \"\\\"%2\\\" \\\"%3\\\"\" /f";

// %1: uri scheme, also the parent path
static const QString RemoveRegistryPattern = "reg delete HKEY_CLASSES_ROOT\\%1 /f";

HUriSchemeHandler::HUriSchemeHandler(QObject *parent)
    : QObject{parent}
{
}

HUriSchemeHandler::Result HUriSchemeHandler::setUriProtocolHandler(const QString &displayName, const QString &URIScheme){
    QFile tempFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".bat");
    if(tempFile.open(QIODevice::WriteOnly)){
        QString exePath = QCoreApplication::applicationFilePath().replace("/", "\\");
        tempFile.write(QString(RegistNamePattern).arg(URIScheme, displayName).toLocal8Bit());
        tempFile.write("\r\n");
        tempFile.write(QString(RegistUriSchemePattern).arg(URIScheme).toLocal8Bit());
        tempFile.write("\r\n");
        tempFile.write(QString(RegistIconPattern).arg(URIScheme, exePath + ",1").toLocal8Bit());
        tempFile.write("\r\n");
        tempFile.write(QString(RegistCallbackCommandPattern).arg(URIScheme, exePath, "%%1").toLocal8Bit());
        tempFile.write("\r\n");
        tempFile.close();

        HINSTANCE instance = ShellExecuteA(nullptr, "runas", tempFile.fileName().toStdString().c_str(), NULL, NULL, SW_HIDE);
        if((INT_PTR)instance > 32){
            qDebug() << "设置成功";
            return Success;
        }else{
            qWarning() << "设置失败：" << instance ;
        }
        tempFile.remove();
    }else{
        qDebug() << "写入临时文件失败";
    }
    return Error;
}

HUriSchemeHandler::Result HUriSchemeHandler::removeUriProtocolHandler(const QString &URIScheme){
    QFile tempFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + QUuid::createUuid().toString(QUuid::WithoutBraces) + ".bat");
    if(tempFile.open(QIODevice::WriteOnly)){
        tempFile.write(QString(RemoveRegistryPattern).arg(URIScheme).toLocal8Bit());
        tempFile.write("\r\n");
        tempFile.close();

        HINSTANCE instance = ShellExecuteA(nullptr, "runas", tempFile.fileName().toStdString().c_str(), NULL, NULL, SW_HIDE);
        if((INT_PTR)instance > 32){
            qDebug() << "清除成功";
            return Success;
        }else{
            qWarning() << "清除失败：" << instance ;
        }
        tempFile.remove();
    }else{
        qDebug() << "写入临时文件失败";
    }
    return Error;
}


