#include "TorusEntity.h"

TorusEntity::TorusEntity(QObject *parent) 
    : SimpleEntity(parent), m_majorRadius(0), m_minorRadius(0) {}

TorusEntity::TorusEntity(double majorRadius, double minorRadius, QObject *parent)
    : SimpleEntity(parent), m_majorRadius(majorRadius), m_minorRadius(minorRadius) {
    updateShape();
}

void TorusEntity::setDimensions(double majorRadius, double minorRadius) {
    m_majorRadius = majorRadius;
    m_minorRadius = minorRadius;
    updateShape();
}

void TorusEntity::updateShape() {
    m_shape = BRepPrimAPI_MakeTorus(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 
                                   m_majorRadius, m_minorRadius).Shape();
}

void TorusEntity::serialize(QJsonObject &json) const {
    SimpleEntity::serialize(json);
    json["type"] = "Torus";
    json["majorRadius"] = m_majorRadius;
    json["minorRadius"] = m_minorRadius;
}

void TorusEntity::deserialize(const QJsonObject &json) {
    SimpleEntity::deserialize(json);
    if (json.contains("majorRadius") && json.contains("minorRadius")) {
        m_majorRadius = json["majorRadius"].toDouble();
        m_minorRadius = json["minorRadius"].toDouble();
        updateShape();
    }
}