#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "hurischemehandler.h"
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    QPushButton *setHandlerButton = new QPushButton("设置handler", this);
    QPushButton *unsetHandlerButton = new QPushButton("取消设置handler", this);
    rootLayout->addWidget(setHandlerButton);
    rootLayout->addWidget(unsetHandlerButton);

    QObject::connect(setHandlerButton, &QPushButton::clicked, this, [this](){
        if(HUriSchemeHandler::Result::Success == HUriSchemeHandler::setUriProtocolHandler("示例程序", "myscheme")){
            QMessageBox::information(this, "成功", "已设置URI Scheme handler，浏览器打开 “myscheme:随意内容”，来查看效果。");
        }else{
            QMessageBox::warning(this, "失败", "设置失败");
        }
    });
    QObject::connect(unsetHandlerButton, &QPushButton::clicked, this, [this](){
        if(HUriSchemeHandler::Result::Success == HUriSchemeHandler::removeUriProtocolHandler("myscheme")){
            QMessageBox::information(this, "成功", "取消成功。");
        }else{
            QMessageBox::warning(this, "失败", "取消设置失败");
        }
    });

    resize(400, 200);
}

Widget::~Widget() {}
