#include <QApplication>
#include "MainWindow.h"
#include "actions/ActionManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 设置应用程序信息
    QApplication::setApplicationName("Sample03");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Sample");
    QApplication::setOrganizationDomain("sample.com");

    // 创建主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
} 