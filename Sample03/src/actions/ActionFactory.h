#ifndef ACTION_FACTORY_H
#define ACTION_FACTORY_H

#include <QObject>
#include <QList>
#include <QMap>
#include <functional>
#include <QJsonObject>
#include "Action.h"

class Action;

// Action factory function type definition
using ActionFactoryFunc = std::function<Action *()>;

// 动作注册器
class ActionRegistrer {
public:
    ActionRegistrer(const QString& actionId, ActionFactoryFunc factoryFunc);
};

class ActionFactory : public QObject
{
    Q_OBJECT
public:
    static ActionFactory *instance();

    QList<Action*> createAllActions();

    void registerFactory(const QString& actionId, ActionFactoryFunc func);
    Action* createAction(const QString& actionId);
    bool hasAction(const QString& actionId) const;

private:
    ActionFactory();
    ~ActionFactory();

    static ActionFactory *s_instance;
    QMap<QString, ActionFactoryFunc> m_factories;
};

// Action registrar class declaration
class ActionRegistrar
{
public:
    ActionRegistrar(const QString& actionId, ActionFactoryFunc func)
    {
        ActionFactory::instance()->registerFactory(actionId, func);
    }
};

// Registration macro definition
#define REGISTER_ACTION(ActionClass) \
    static ActionRegistrar actionRegistrar##ActionClass(#ActionClass, []() -> Action* { return new ActionClass(); })

#endif // ACTION_FACTORY_H 