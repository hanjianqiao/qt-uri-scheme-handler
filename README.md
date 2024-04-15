# qt-uri-scheme-handler

> 通过浏览器启动Qt应用

## 实现原理（Windows）

参考[Registering the Application Handling the Custom URI Scheme](https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa767914(v=vs.85)?redirectedfrom=MSDN)。
通过浏览器启动，需要修改注册表。本项目通过生成临时的.bat文件，然后调用`ShellExecuteA`（需要管理员权限）来修改注册表。

## 自带示例程序

![image](https://github.com/hanjianqiao/qt-uri-scheme-handler/assets/7146341/123900f2-6fc8-4f86-8d88-741439d4d07b)

* 点击“设置handler”后会弹出权限确认，因为是通过修改windows注册表实现的功能，所以需要管理员权限。
* 然后就可以通过浏览器输入：“myscheme:自带任意参数”，来启动当前的Qt应用。
  
![image](https://github.com/hanjianqiao/qt-uri-scheme-handler/assets/7146341/c80ac18a-c7ab-49ef-addf-4c57de70ae0c)

* 如果你是使用QtCreator运行本示例，应该会弹出找不到Qt*.dll的错误，这是正常的。因为直接运行.exe确实是找不到这些dll的。
  
![image](https://github.com/hanjianqiao/qt-uri-scheme-handler/assets/7146341/11f25486-749c-47c0-8610-8423c2cf0a34)

## API说明
* `static Result setUriProtocolHandler(const QString &displayName, const QString &URIScheme);`
* `static Result removeUriProtocolHandler(const QString &URIScheme);`
