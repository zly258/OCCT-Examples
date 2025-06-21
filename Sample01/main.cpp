#include <QApplication>
#include <QFont>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // 初始化Qt应用程序
    QApplication app(argc, argv);

    // 设置全局字体为微软雅黑 10号
    QFont font("Microsoft YaHei", 10);
    app.setFont(font);

    // 创建主窗口
    MainWindow mainWindow;
    mainWindow.show();

    // 运行应用程序
    return app.exec();
} 