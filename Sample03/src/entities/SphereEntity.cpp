#include "SphereEntity.h"

SphereEntity::SphereEntity(QObject *parent) 
    : SimpleEntity(parent), m_radius(0) {}

SphereEntity::SphereEntity(double radius, QObject *parent)
    : SimpleEntity(parent), m_radius(radius) {
    updateShape();
}

void SphereEntity::setRadius(double radius) {
    m_radius = radius;
    updateShape();
}

void SphereEntity::updateShape() {
    m_shape = BRepPrimAPI_MakeSphere(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), m_radius).Shape();
}

void SphereEntity::serialize(QJsonObject &json) const {
    SimpleEntity::serialize(json);
    json["type"] = "Sphere";
    json["radius"] = m_radius;
}

void SphereEntity::deserialize(const QJsonObject &json) {
    SimpleEntity::deserialize(json);
    if (json.contains("radius")) {
        m_radius = json["radius"].toDouble();
        updateShape();
    }
}