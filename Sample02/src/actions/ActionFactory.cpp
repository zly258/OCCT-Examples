#include "ActionFactory.h"
#include "Action.h"
#include "config/UIConfig.h"
#include <QDebug>
#include "CreateShapeAction.h"
#include "DisplayModeAction.h"
#include "RandomTestAction.h"

// ActionRegistrer implementation
ActionRegistrer::ActionRegistrer(const QString& actionId, ActionFactoryFunc factoryFunc)
{
    ActionFactory::instance()->registerFactory(actionId, factoryFunc);
}

// ActionFactory implementation
ActionFactory *ActionFactory::s_instance = nullptr;

ActionFactory *ActionFactory::instance()
{
    if (!s_instance) {
        s_instance = new ActionFactory();
    }
    return s_instance;
}

ActionFactory::ActionFactory() : QObject(nullptr)
{
}

ActionFactory::~ActionFactory()
{
    s_instance = nullptr;
}

void ActionFactory::registerFactory(const QString& actionId, ActionFactoryFunc func)
{
    if (actionId.isEmpty() || !func) {
        qWarning() << "Invalid action registration attempt";
        return;
    }
    m_factories[actionId.toLower()] = func;
}

Action* ActionFactory::createAction(const QString& actionId)
{
    auto it = m_factories.find(actionId.toLower());
    if (it != m_factories.end()) {
        return it.value()();
    }
    return nullptr;
}

QList<Action*> ActionFactory::createAllActions()
{
    QList<Action*> actions;

    // 创建形状动作
    actions.append(new CreateShapeAction(CreateShapeAction::Box));
    actions.append(new CreateShapeAction(CreateShapeAction::Cylinder));
    actions.append(new CreateShapeAction(CreateShapeAction::Cone));
    actions.append(new CreateShapeAction(CreateShapeAction::Torus));
    actions.append(new CreateShapeAction(CreateShapeAction::Sphere));

    // 显示模式动作
    actions.append(new DisplayModeAction(0)); // WireFrame
    actions.append(new DisplayModeAction(1)); // Shaded

    // 随机测试动作
    actions.append(new RandomTestAction());

    return actions;
}

bool ActionFactory::hasAction(const QString& actionId) const
{
    return m_factories.contains(actionId.toLower());
} 