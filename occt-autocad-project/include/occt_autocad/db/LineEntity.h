#pragma once

#include "BaseDBObject.h"

namespace occt_autocad {
namespace db {

class LineEntity : public BaseDBObject, public Entity {
public:
    LineEntity() = default;
    LineEntity(const std::string& id, double x1, double y1, double x2, double y2)
        : BaseDBObject(id), m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2) {}

    Ptr clone() const override { return std::make_shared<LineEntity>(*this); }
    void draw() const override {}
    void boundingBox() const override {}
    std::string typeName() const override { return "Line"; }

    std::string serialize() const override {
        nlohmann::json j = nlohmann::json::parse(BaseDBObject::serialize());
        j["x1"] = m_x1; j["y1"] = m_y1; j["x2"] = m_x2; j["y2"] = m_y2;
        return j.dump();
    }

    void deserialize(const std::string& data) override {
        BaseDBObject::deserialize(data);
        try {
            auto j = nlohmann::json::parse(data);
            if (j.contains("x1")) m_x1 = j["x1"].get<double>();
            if (j.contains("y1")) m_y1 = j["y1"].get<double>();
            if (j.contains("x2")) m_x2 = j["x2"].get<double>();
            if (j.contains("y2")) m_y2 = j["y2"].get<double>();
        } catch (...) {}
    }

private:
    double m_x1{0}, m_y1{0}, m_x2{0}, m_y2{0};
};

} // namespace db
} // namespace occt_autocad
