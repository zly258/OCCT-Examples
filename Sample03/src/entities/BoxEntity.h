#ifndef BOX_ENTITY_H
#define BOX_ENTITY_H

#include "core/SimpleEntity.h"
#include <BRepPrimAPI_MakeBox.hxx>

class BoxEntity : public SimpleEntity
{
    Q_OBJECT
public:
    BoxEntity(QObject *parent = nullptr);
    BoxEntity(double width, double height, double depth, QObject *parent = nullptr);

    // 设置盒子尺寸
    void setDimensions(double width, double height, double depth);

    // 序列化与反序列化
    void serialize(QJsonObject &json) const override;
    void deserialize(const QJsonObject &json) override;
    void updateShape() override;

private:
    double m_width, m_height, m_depth;
};

#endif // BOX_ENTITY_H