#include "BoxEntity.h"
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>

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

SoSeparator* BoxEntity::createSceneGraph() {
    // 创建一个新的分隔节点
    SoSeparator* sep = new SoSeparator;
    
    // 添加变换节点
    SoTransform* transform = new SoTransform;
    transform->translation.setValue(m_x, m_y, m_z);
    sep->addChild(transform);
    
    // 添加材质
    SoMaterial* mat = new SoMaterial;
    mat->diffuseColor.setValue(0.8f, 0.8f, 0.8f);  // 灰色
    sep->addChild(mat);
    
    // 创建盒子几何体
    SoCube* cube = new SoCube;
    cube->width = m_width;
    cube->height = m_height;
    cube->depth = m_depth;
    sep->addChild(cube);
    
    return sep;
}