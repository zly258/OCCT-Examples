#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// 前置声明
class Viewport;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setWireframeMode();  // 线框模式
    void setShadedMode();     // 填充模式
    void createCube();        // 创建立方体
    void createCylinder();    // 创建圆柱
    void createCone();        // 创建圆台
    void createTorus();       // 创建圆环
    void createSphere();      // 创建球体
    void randomTest();        // 随机测试

private:
    // 初始化工具栏
    void initToolBar();

    Viewport *m_viewport = nullptr;  // Viewport 指针
    QWidget *m_centralWidget = nullptr;
};

#endif // MAINWINDOW_H 