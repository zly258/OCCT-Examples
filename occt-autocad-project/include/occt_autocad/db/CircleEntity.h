#pragma once

#include "BaseDBObject.h"

namespace occt_autocad {
namespace db {

class CircleEntity : public BaseDBObject, public Entity {
public:
    CircleEntity() = default;
    CircleEntity(const std::string& id, double cx, double cy, double r)
        : BaseDBObject(id), m_cx(cx), m_cy(cy), m_r(r) {}

    Ptr clone() const override { return std::make_shared<CircleEntity>(*this); }
    void draw() const override {}
    void boundingBox() const override {}
    std::string typeName() const override { return "Circle"; }

    std::string serialize() const override {
        nlohmann::json j = nlohmann::json::parse(BaseDBObject::serialize());
        j["cx"] = m_cx; j["cy"] = m_cy; j["r"] = m_r;
        return j.dump();
    }

    void deserialize(const std::string& data) override {
        BaseDBObject::deserialize(data);
        try {
            auto j = nlohmann::json::parse(data);
            if (j.contains("cx")) m_cx = j["cx"].get<double>();
            if (j.contains("cy")) m_cy = j["cy"].get<double>();
            if (j.contains("r")) m_r = j["r"].get<double>();
        } catch (...) {}
    }

private:
    double m_cx{0}, m_cy{0}, m_r{0};
};

} // namespace db
} // namespace occt_autocad
