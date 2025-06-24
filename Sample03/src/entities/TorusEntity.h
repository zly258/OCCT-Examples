#ifndef TORUS_ENTITY_H
#define TORUS_ENTITY_H

#include "core/SimpleEntity.h"
#include <BRepPrimAPI_MakeTorus.hxx>

class TorusEntity : public SimpleEntity
{
    Q_OBJECT
public:
    TorusEntity(QObject *parent = nullptr);
    TorusEntity(double majorRadius, double minorRadius, QObject *parent = nullptr);

    void setDimensions(double majorRadius, double minorRadius);

    void serialize(QJsonObject &json) const override;
    void deserialize(const QJsonObject &json) override;

private:
    double m_majorRadius, m_minorRadius;
    void updateShape() override;
};

#endif // TORUS_ENTITY_H