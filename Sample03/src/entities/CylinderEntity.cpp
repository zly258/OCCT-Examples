#include "CylinderEntity.h"

CylinderEntity::CylinderEntity(QObject *parent) : SimpleEntity(parent), m_radius(0), m_height(0) {}

CylinderEntity::CylinderEntity(double radius, double height, QObject *parent)
    : SimpleEntity(parent), m_radius(radius), m_height(height) {
    updateShape();
}

void CylinderEntity::setDimensions(double radius, double height) {
    m_radius = radius;
    m_height = height;
    updateShape();
}

void CylinderEntity::updateShape() {
    m_shape = BRepPrimAPI_MakeCylinder(m_radius, m_height).Shape();
}

void CylinderEntity::serialize(QJsonObject &json) const {
    SimpleEntity::serialize(json);
    json["type"] = "Cylinder";
    json["radius"] = m_radius;
    json["height"] = m_height;
}

void CylinderEntity::deserialize(const QJsonObject &json) {
    SimpleEntity::deserialize(json);
    if (json.contains("radius") && json.contains("height")) {
        m_radius = json["radius"].toDouble();
        m_height = json["height"].toDouble();
        updateShape();
    }
}