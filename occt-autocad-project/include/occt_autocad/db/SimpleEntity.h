#pragma once

#include "BaseDBObject.h"

namespace occt_autocad {
namespace db {

class SimpleEntity : public BaseDBObject, public Entity {
public:
    SimpleEntity() = default;
    ~SimpleEntity() override = default;

    Ptr clone() const override { return std::make_shared<SimpleEntity>(*this); }
    void draw() const override {}
    void boundingBox() const override {}
};

} // namespace db
} // namespace occt_autocad
