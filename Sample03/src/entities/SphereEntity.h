#ifndef SPHERE_ENTITY_H
#define SPHERE_ENTITY_H

#include "core/SimpleEntity.h"
#include <BRepPrimAPI_MakeSphere.hxx>

class SphereEntity : public SimpleEntity
{
    Q_OBJECT
public:
    SphereEntity(QObject *parent = nullptr);
    SphereEntity(double radius, QObject *parent = nullptr);

    void setRadius(double radius);

    void serialize(QJsonObject &json) const override;
    void deserialize(const QJsonObject &json) override;

private:
    double m_radius;
    void updateShape() override;
};

#endif // SPHERE_ENTITY_H