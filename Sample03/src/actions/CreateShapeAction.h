#ifndef CREATE_SHAPE_ACTION_H
#define CREATE_SHAPE_ACTION_H

#include "Action.h"
#include "entities/BoxEntity.h"
#include "entities/CylinderEntity.h"
#include "entities/FrustumEntity.h"
#include "entities/TorusEntity.h"
#include "entities/SphereEntity.h"
#include <gp_Vec.hxx>

class CreateShapeAction : public Action
{
    Q_OBJECT
public:
    enum ShapeType {
        Box,
        Cylinder,
        Cone,
        Torus,
        Sphere
    };

    explicit CreateShapeAction(ShapeType type, QObject* parent = nullptr);

    QString id() const override;
    QString name() const override;
    QString description() const override;
    QString icon() const override;

    void execute() override;

private:
    ShapeType m_type;
    gp_Vec m_position;  // 形状的位置偏移

    // 创建不同类型的实体
    SimpleEntity* createBoxEntity() const;
    SimpleEntity* createCylinderEntity() const;
    SimpleEntity* createConeEntity() const;
    SimpleEntity* createTorusEntity() const;
    SimpleEntity* createSphereEntity() const;
};

#endif // CREATE_SHAPE_ACTION_H