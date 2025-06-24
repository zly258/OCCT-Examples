#include "ActionManager.h"
#include "ActionFactory.h"
#include "config/UIConfig.h"
#include <QDebug>

ActionManager *ActionManager::s_instance = nullptr;

ActionManager *ActionManager::instance()
{
    if (!s_instance) {
        s_instance = new ActionManager();
        s_instance->registerAllActions();
    }
    return s_instance;
}

ActionManager::ActionManager() : QObject(nullptr)
{
}

ActionManager::~ActionManager()
{
    qDeleteAll(m_actions);
    m_actions.clear();
}

void ActionManager::registerAllActions()
{
    auto actions = ActionFactory::instance()->createAllActions();
    for (auto action : actions) {
        if (action) {
            registerAction(action);
        }
    }
}

void ActionManager::registerAction(Action *action)
{
    if (!action || action->id().isEmpty()) {
        return;
    }

    // 检查是否已存在
    if (m_actions.contains(action->id().toLower())) {
        qWarning() << QString("动作%1已存在").arg(action->id());
        return;
    }

    // 存储Action
    m_actions[action->id().toLower()] = action;
    emit actionRegistered(action);
}

Action *ActionManager::getAction(const QString &id) const
{
    return m_actions.value(id.toLower());
}

QList<Action*> ActionManager::getActions() const
{
    return m_actions.values();
}

bool ActionManager::executeAction(const QString &id)
{
    Action *action = getAction(id);
    if (!action) {
        emit actionError(id, "未知动作");
        return false;
    }

    if (!action->isEnabled()) {
        emit actionError(id, "动作已禁用");
        return false;
    }

    emit actionStarted(action);
    try {
        action->execute();
        emit actionFinished(action);
        return true;
    } catch (const std::exception &e) {
        emit actionError(id, e.what());
        return false;
    }
}

void ActionManager::cancelCurrentAction()
{
    cleanupCurrentAction();
}

Action *ActionManager::findActionById(const QString &id) const
{
    QString lower = id.toLower();

    // Exact match
    auto it = m_actions.find(lower);
    if (it != m_actions.end()) {
        return it.value();
    }

    // Prefix match
    for (auto it = m_actions.begin(); it != m_actions.end(); ++it) {
        if (it.key().startsWith(lower)) {
            return it.value();
        }
    }

    return nullptr;
}

void ActionManager::cleanupCurrentAction()
{
    if (m_currentAction) {
        m_currentAction->cleanup();
        emit actionFinished(m_currentAction);
        m_currentAction = nullptr;
    }
}

QJsonObject ActionManager::getMenuConfig() const
{
    return UIConfig::instance()->getMenuConfig();
}

QList<Action*> ActionManager::getMenuActions(const QString& menuId) const
{
    QList<Action*> menuActions;
    QJsonObject menuConfig = getMenuConfig();
    
    if (menuConfig.contains(menuId) && menuConfig[menuId].isArray()) {
        QJsonArray actionIds = menuConfig[menuId].toArray();
        for (const QJsonValue& value : actionIds) {
            QString actionId = value.toString();
            Action* action = getAction(actionId);
            if (action && action->isVisible()) {
                menuActions.append(action);
            }
        }
    }
    
    return menuActions;
} 