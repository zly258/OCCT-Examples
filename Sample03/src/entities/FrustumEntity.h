#ifndef FRUSTUM_ENTITY_H
#define FRUSTUM_ENTITY_H

#include "core/SimpleEntity.h"
#include <BRepPrimAPI_MakeCone.hxx>

class FrustumEntity : public SimpleEntity
{
    Q_OBJECT
public:
    FrustumEntity(QObject *parent = nullptr);
    FrustumEntity(double bottomRadius, double topRadius, double height, QObject *parent = nullptr);

    void setDimensions(double bottomRadius, double topRadius, double height);

    void serialize(QJsonObject &json) const override;
    void deserialize(const QJsonObject &json) override;

private:
    double m_bottomRadius, m_topRadius, m_height;
    void updateShape() override;
};

#endif // FRUSTUM_ENTITY_H