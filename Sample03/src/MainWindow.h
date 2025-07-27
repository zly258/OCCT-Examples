#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <Inventor/Qt/SoQt.h>

class QAction;
class QMenu;
class Action;
class Viewport;
class QJsonArray;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Viewport* viewport() const { return m_viewport; }

private slots:
    void onActionRegistered(Action* action);
    void onActionStarted(Action* action);
    void onActionFinished(Action* action);
    void onActionError(const QString& actionId, const QString& error);

private:
    void setupUi();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createViewport();
    void addMenuItems(QMenu* parentMenu, const QJsonArray& items);

    // UI组件
    QMap<QString, QMenu*> m_menus;                 // 菜单映射表
    QMap<QString, QAction*> m_actions;             // 动作映射表
    Viewport* m_viewport;                          // 视口
};

#endif // MAINWINDOW_H 