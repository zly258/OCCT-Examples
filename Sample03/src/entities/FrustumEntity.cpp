#include "FrustumEntity.h"

FrustumEntity::FrustumEntity(QObject *parent) 
    : SimpleEntity(parent), m_bottomRadius(0), m_topRadius(0), m_height(0) {}

FrustumEntity::FrustumEntity(double bottomRadius, double topRadius, double height, QObject *parent)
    : SimpleEntity(parent), m_bottomRadius(bottomRadius), m_topRadius(topRadius), m_height(height) {
    updateShape();
}

void FrustumEntity::setDimensions(double bottomRadius, double topRadius, double height) {
    m_bottomRadius = bottomRadius;
    m_topRadius = topRadius;
    m_height = height;
    updateShape();
}

void FrustumEntity::updateShape() {
    m_shape = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), 
                                  m_bottomRadius, m_topRadius, m_height).Shape();
}

void FrustumEntity::serialize(QJsonObject &json) const {
    SimpleEntity::serialize(json);
    json["type"] = "Frustum";
    json["bottomRadius"] = m_bottomRadius;
    json["topRadius"] = m_topRadius;
    json["height"] = m_height;
}

void FrustumEntity::deserialize(const QJsonObject &json) {
    SimpleEntity::deserialize(json);
    if (json.contains("bottomRadius") && json.contains("topRadius") && json.contains("height")) {
        m_bottomRadius = json["bottomRadius"].toDouble();
        m_topRadius = json["topRadius"].toDouble();
        m_height = json["height"].toDouble();
        updateShape();
    }
}