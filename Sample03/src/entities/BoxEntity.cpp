#include "BoxEntity.h"

BoxEntity::BoxEntity(QObject *parent) : SimpleEntity(parent), m_width(0), m_height(0), m_depth(0) {}

BoxEntity::BoxEntity(double width, double height, double depth, QObject *parent)
    : SimpleEntity(parent), m_width(width), m_height(height), m_depth(depth) {
    updateShape();
}

void BoxEntity::setDimensions(double width, double height, double depth) {
    m_width = width;
    m_height = height;
    m_depth = depth;
    updateShape();
}

void BoxEntity::updateShape() {
    m_shape = BRepPrimAPI_MakeBox(m_width, m_height, m_depth).Shape();
}

void BoxEntity::serialize(QJsonObject &json) const {
    SimpleEntity::serialize(json);
    json["type"] = "Box";
    json["width"] = m_width;
    json["height"] = m_height;
    json["depth"] = m_depth;
}

void BoxEntity::deserialize(const QJsonObject &json) {
    SimpleEntity::deserialize(json);
    if (json.contains("width") && json.contains("height") && json.contains("depth")) {
        m_width = json["width"].toDouble();
        m_height = json["height"].toDouble();
        m_depth = json["depth"].toDouble();
        updateShape();
    }
}