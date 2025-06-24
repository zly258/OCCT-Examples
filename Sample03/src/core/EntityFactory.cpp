#include "EntityFactory.h"
#include "entities/BoxEntity.h"
#include "entities/CylinderEntity.h"
#include "entities/FrustumEntity.h"
#include "entities/TorusEntity.h"
#include "entities/SphereEntity.h"

SimpleEntity* EntityFactory::createEntity(const QJsonObject &json, QObject *parent) {
    if (!json.contains("type")) {
        return nullptr;
    }

    QString type = json["type"].toString();
    if (type == "Box") {
        BoxEntity *box = new BoxEntity(parent);
        box->deserialize(json);
        return box;
    } else if (type == "Cylinder") {
        CylinderEntity *cylinder = new CylinderEntity(parent);
        cylinder->deserialize(json);
        return cylinder;
    } else if (type == "Frustum") {
        FrustumEntity *frustum = new FrustumEntity(parent);
        frustum->deserialize(json);
        return frustum;
    } else if (type == "Torus") {
        TorusEntity *torus = new TorusEntity(parent);
        torus->deserialize(json);
        return torus;
    } else if (type == "Sphere") {
        SphereEntity *sphere = new SphereEntity(parent);
        sphere->deserialize(json);
        return sphere;
    }

    return nullptr;
}