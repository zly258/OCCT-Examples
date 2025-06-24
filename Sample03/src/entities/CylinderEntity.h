#ifndef CYLINDER_ENTITY_H
#define CYLINDER_ENTITY_H

#include "core/SimpleEntity.h"
#include <BRepPrimAPI_MakeCylinder.hxx>

class CylinderEntity : public SimpleEntity
{
    Q_OBJECT
public:
    CylinderEntity(QObject *parent = nullptr);
    CylinderEntity(double radius, double height, QObject *parent = nullptr);

    // 设置圆柱体尺寸
    void setDimensions(double radius, double height);

    // 序列化与反序列化
    void serialize(QJsonObject &json) const override;
    void deserialize(const QJsonObject &json) override;
    void updateShape() override;

private:
    double m_radius, m_height;
};

#endif // CYLINDER_ENTITY_H