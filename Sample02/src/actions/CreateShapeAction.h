#ifndef CREATE_SHAPE_ACTION_H
#define CREATE_SHAPE_ACTION_H

#include "Action.h"
#include <gp_Vec.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

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

    // 创建不同类型的形状
    TopoDS_Shape createBox() const;
    TopoDS_Shape createCylinder() const;
    TopoDS_Shape createCone() const;
    TopoDS_Shape createTorus() const;
    TopoDS_Shape createSphere() const;
};

#endif // CREATE_SHAPE_ACTION_H 