#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <QObject>
#include <QJsonObject>
#include "SimpleEntity.h"

class EntityFactory : public QObject
{
    Q_OBJECT
public:
    static SimpleEntity* createEntity(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // ENTITY_FACTORY_H