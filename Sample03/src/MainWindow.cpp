#include "MainWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QToolButton>
#include <QDebug>

#include "actions/Action.h"
#include "actions/ActionManager.h"
#include "core/Viewport.h"
#include "core/ViewportManager.h"
#include "config/UIConfig.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_viewport(nullptr)
{
    // 初始化Coin3D
    SoQt::init(this);

    setupUi();

    // 连接信号槽
    connect(ActionManager::instance(), &ActionManager::actionRegistered, this, &MainWindow::onActionRegistered);
    connect(ActionManager::instance(), &ActionManager::actionStarted, this, &MainWindow::onActionStarted);
    connect(ActionManager::instance(), &ActionManager::actionFinished, this, &MainWindow::onActionFinished);
    connect(ActionManager::instance(), &ActionManager::actionError, this, &MainWindow::onActionError);
}

MainWindow::~MainWindow()
{
    // 清理Coin3D
    SoQt::done();
}

void MainWindow::setupUi()
{
    setWindowTitle(tr("Sample03"));

    setMinimumSize(800, 600);
    
    // 创建中心部件
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // 创建布局
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    
    // 创建并添加视口
    createViewport();
    layout->addWidget(m_viewport->getWidget());
    
    // 创建其他UI元素
    createActions();
    createMenus();
    createStatusBar();
}

void MainWindow::createViewport()
{
    // 创建视口
    m_viewport = new Viewport(this);
    
    // 设置为活动视口
    ViewportManager::instance()->setActiveViewport(m_viewport);
}

void MainWindow::createActions()
{
    // 清理旧的动作
    qDeleteAll(m_actions);
    m_actions.clear();

    // 从ActionManager获取所有已注册的动作
    QList<Action*> actions = ActionManager::instance()->getActions();
    qDebug() << "actions" << actions;
    for (Action* action : actions) {
        if (action) {
            // 创建QAction
            QAction* qAction = new QAction(this);
            qAction->setObjectName(action->id()); // 设置对象名，用于后续查找
            qAction->setText(action->name());     // 设置默认文本
            qAction->setIcon(QIcon(action->icon()));
            qAction->setStatusTip(action->description());
            qAction->setEnabled(action->isEnabled());

            // 连接信号槽
            connect(qAction, &QAction::triggered, [action]() {
                ActionManager::instance()->executeAction(action->id());
            });

            // 存储QAction
            m_actions[action->id()] = qAction;
        }
    }
}

void MainWindow::createMenus()
{
    // 清理旧的菜单
    qDeleteAll(m_menus);
    m_menus.clear();

    // 从配置创建菜单
    QJsonObject menuConfig = UIConfig::instance()->getMenuConfig();
    for (auto it = menuConfig.begin(); it != menuConfig.end(); ++it) {
        const QString& menuId = it.key();
        const QJsonObject& config = it.value().toObject();
        
        // 创建顶层菜单
        QMenu* menu = menuBar()->addMenu(config["text"].toString());
        m_menus[menuId] = menu;

        // 添加菜单项
        if (config.contains("items")) {
            addMenuItems(menu, config["items"].toArray());
        }
    }
}

void MainWindow::addMenuItems(QMenu* parentMenu, const QJsonArray& items)
{
    for (const QJsonValue& item : items) {
        QJsonObject itemObj = item.toObject();
        
        if (itemObj.contains("items")) {
            // 这是一个子菜单
            QMenu* subMenu = parentMenu->addMenu(itemObj["text"].toString());
            if (itemObj.contains("icon")) {
                subMenu->setIcon(QIcon(itemObj["icon"].toString()));
            }
            addMenuItems(subMenu, itemObj["items"].toArray());
        } else if (itemObj.contains("action")) {
            // 这是一个动作
            QString actionId = itemObj["action"].toString();
            QAction* action = m_actions.value(actionId);
            if (action) {
                QAction* menuAction = parentMenu->addAction(itemObj["text"].toString());
                menuAction->setIcon(action->icon());
                menuAction->setStatusTip(action->statusTip());
                menuAction->setEnabled(action->isEnabled());
                connect(menuAction, &QAction::triggered, action, &QAction::trigger);
            }
        }
    }
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
}

void MainWindow::onActionRegistered(Action* action)
{
    if (!action) return;

    // 创建QAction
    QAction* qAction = new QAction(this);
    qAction->setObjectName(action->id()); // 设置对象名，用于后续查找
    qAction->setText(action->name());     // 设置默认文本
    qAction->setIcon(QIcon(action->icon()));
    qAction->setStatusTip(action->description());
    qAction->setEnabled(action->isEnabled());

    // 连接信号槽
    connect(qAction, &QAction::triggered, [action]() {
        ActionManager::instance()->executeAction(action->id());
    });

    // 存储QAction
    m_actions[action->id()] = qAction;
}

void MainWindow::onActionStarted(Action* action)
{
    if (action) {
        statusBar()->showMessage(tr("正在执行: %1").arg(action->name()));
    }
}

void MainWindow::onActionFinished(Action* action)
{
    if (action) {
        statusBar()->showMessage(tr("已完成: %1").arg(action->name()), 2000);
    }
}

void MainWindow::onActionError(const QString& actionId, const QString& error)
{
    statusBar()->showMessage(tr("错误: %1 - %2").arg(actionId, error), 5000);
    QMessageBox::warning(this, tr("命令错误"), tr("执行命令时出错:\n%1\n%2").arg(actionId, error));
} 