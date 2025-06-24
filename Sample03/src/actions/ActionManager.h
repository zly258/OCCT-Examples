#ifndef ACTION_MANAGER_H
#define ACTION_MANAGER_H

#include <QObject>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include "Action.h"

class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager *instance();

    // 注册和获取Action
    void registerAction(Action *action);
    Action *getAction(const QString &id) const;
    QList<Action*> getActions() const;
    Action* findActionById(const QString& id) const;

    // 执行动作
    bool executeAction(const QString &id);
    void cancelCurrentAction();
    void cleanupCurrentAction();

    // 菜单配置
    QJsonObject getMenuConfig() const;
    QList<Action*> getMenuActions(const QString& menuId) const;

    // 注册所有动作
    void registerAllActions();

signals:
    void actionRegistered(Action *action);
    void actionStarted(Action *action);
    void actionFinished(Action *action);
    void actionError(const QString &actionId, const QString &error);

private:
    ActionManager();
    ~ActionManager();

    static ActionManager *s_instance;
    QMap<QString, Action*> m_actions;
    Action* m_currentAction = nullptr;
    QJsonObject m_menuConfig;
};

#endif // ACTION_MANAGER_H 