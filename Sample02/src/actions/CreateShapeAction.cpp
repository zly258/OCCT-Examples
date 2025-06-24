#include "CreateShapeAction.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <AIS_Shape.hxx>
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
        TopoDS_Shape shape;
        
        // 创建形状
        switch (m_type) {
        case Box: shape = createBox(); break;
        case Cylinder: shape = createCylinder(); break;
        case Cone: shape = createCone(); break;
        case Torus: shape = createTorus(); break;
        case Sphere: shape = createSphere(); break;
        }

        // 应用位置变换
        gp_Trsf transform;
        transform.SetTranslation(m_position);
        BRepBuilderAPI_Transform shapeTransform(shape, transform);
        shape = shapeTransform.Shape();

        // 显示形状
        Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
        viewport->displayEntity(aisShape);
    }
}

TopoDS_Shape CreateShapeAction::createBox() const
{
    return BRepPrimAPI_MakeBox(100.0, 100.0, 100.0).Shape();
}

TopoDS_Shape CreateShapeAction::createCylinder() const
{
    return BRepPrimAPI_MakeCylinder(50.0, 100.0).Shape();
}

TopoDS_Shape CreateShapeAction::createCone() const
{
    return BRepPrimAPI_MakeCone(50.0, 25.0, 100.0).Shape();
}

TopoDS_Shape CreateShapeAction::createTorus() const
{
    return BRepPrimAPI_MakeTorus(50.0, 20.0).Shape();
}

TopoDS_Shape CreateShapeAction::createSphere() const
{
    return BRepPrimAPI_MakeSphere(50.0).Shape();
} 