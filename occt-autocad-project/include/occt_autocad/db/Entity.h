#pragma once

#include "DBObject.h"

namespace occt_autocad {
namespace db {

class Entity : public DBObject {
public:
    using Ptr = std::shared_ptr<Entity>;

    Entity() = default;
    ~Entity() override = default;

    // 绘制与几何相关接口（实现依赖于 view 层）
    virtual void draw() const = 0;
    // 轴对齐包围盒，返回 [xmin,ymin,xmax,ymax] 或其他适合的数据结构
    virtual void boundingBox() const = 0;
};

} // namespace db
} // namespace occt_autocad
