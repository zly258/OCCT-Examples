#include "SimpleEntity.h"
#include <QDebug>

#include <BRepBuilderAPI_Transform.hxx>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

SimpleEntity::SimpleEntity(QObject *parent) : QObject(parent), m_x(0), m_y(0), m_z(0) {}

SimpleEntity::~SimpleEntity() {}

TopoDS_Shape SimpleEntity::shape() const
{
    return m_shape;
}

void SimpleEntity::setShape(const TopoDS_Shape &shape)
{
    m_shape = shape;
}

double SimpleEntity::x() const
{
    return m_x;
}

double SimpleEntity::y() const
{
    return m_y;
}

double SimpleEntity::z() const
{
    return m_z;
}

void SimpleEntity::setPosition(double x, double y, double z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

void SimpleEntity::serialize(QJsonObject &json) const
{
    json["shapeType"] = static_cast<int>(m_shape.ShapeType());
    json["x"] = m_x;
    json["y"] = m_y;
    json["z"] = m_z;
}

void SimpleEntity::deserialize(const QJsonObject &json)
{
    if (json.contains("shapeType"))
    {
        qDebug() << "Deserialized shape type:" << json["shapeType"].toInt();
    }
    if (json.contains("x") && json.contains("y") && json.contains("z"))
    {
        m_x = json["x"].toDouble();
        m_y = json["y"].toDouble();
        m_z = json["z"].toDouble();
    }
}