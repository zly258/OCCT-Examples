#include "CreateShapeAction.h"
#include "core/Viewport.h"
#include "core/ViewportManager.h"

CreateShapeAction::CreateShapeAction(ShapeType type, QObject* parent)
    : Action(parent)
    , m_type(type)
{
    // 设置不同形状的位置偏移
    switch (type) {
    case Box:
        m_position = gp_Vec(200.0, 0.0, 0.0);
        break;
    case Cylinder:
        m_position = gp_Vec(0.0, 200.0, 0.0);
        break;
    case Cone:
        m_position = gp_Vec(-200.0, 0.0, 0.0);
        break;
    case Torus:
        m_position = gp_Vec(0.0, -200.0, 0.0);
        break;
    case Sphere:
        m_position = gp_Vec(0.0, 0.0, 200.0);
        break;
    }
}

QString CreateShapeAction::id() const
{
    switch (m_type) {
    case Box: return "CreateBox";
    case Cylinder: return "CreateCylinder";
    case Cone: return "CreateCone";
    case Torus: return "CreateTorus";
    case Sphere: return "CreateSphere";
    default: return QString();
    }
}

QString CreateShapeAction::name() const
{
    switch (m_type) {
    case Box: return tr("立方体");
    case Cylinder: return tr("圆柱");
    case Cone: return tr("圆台");
    case Torus: return tr("圆环");
    case Sphere: return tr("球体");
    default: return QString();
    }
}

QString CreateShapeAction::description() const
{
    switch (m_type) {
    case Box: return tr("创建立方体");
    case Cylinder: return tr("创建圆柱");
    case Cone: return tr("创建圆台");
    case Torus: return tr("创建圆环");
    case Sphere: return tr("创建球体");
    default: return QString();
    }
}

QString CreateShapeAction::icon() const
{
    switch (m_type) {
    case Box: return ":/icons/box.png";
    case Cylinder: return ":/icons/cylinder.png";
    case Cone: return ":/icons/cone.png";
    case Torus: return ":/icons/torus.png";
    case Sphere: return ":/icons/sphere.png";
    default: return QString();
    }
}

void CreateShapeAction::execute()
{
    if (Viewport* viewport = ViewportManager::instance()->activeViewport()) {
        SimpleEntity* entity = nullptr;

        // 创建对应的实体
        switch (m_type) {
        case Box: entity = createBoxEntity(); break;
        case Cylinder: entity = createCylinderEntity(); break;
        case Cone: entity = createConeEntity(); break;
        case Torus: entity = createTorusEntity(); break;
        case Sphere: entity = createSphereEntity(); break;
        }

        if (entity) {
            // 设置位置
            entity->setPosition(m_position.X(), m_position.Y(), m_position.Z());
            viewport->displaySimpleEntity(entity);
        }
    }
}

SimpleEntity* CreateShapeAction::createBoxEntity() const
{
    BoxEntity* box = new BoxEntity(100.0, 100.0, 100.0);
    return box;
}

SimpleEntity* CreateShapeAction::createCylinderEntity() const
{
    CylinderEntity* cylinder = new CylinderEntity(50.0, 100.0);
    return cylinder;
}

SimpleEntity* CreateShapeAction::createConeEntity() const
{
    FrustumEntity* cone = new FrustumEntity(50.0, 25.0, 100.0);
    return cone;
}

SimpleEntity* CreateShapeAction::createTorusEntity() const
{
    TorusEntity* torus = new TorusEntity(50.0, 20.0);
    return torus;
}

SimpleEntity* CreateShapeAction::createSphereEntity() const
{
    SphereEntity* sphere = new SphereEntity(50.0);
    return sphere;
}