#pragma once

#include "BaseDBObject.h"
#include <vector>

namespace occt_autocad {
namespace db {

class PolylineEntity : public BaseDBObject, public Entity {
public:
    PolylineEntity() = default;
    PolylineEntity(const std::string& id, const std::vector<std::pair<double,double>>& pts)
        : BaseDBObject(id), m_points(pts) {}

    Ptr clone() const override { return std::make_shared<PolylineEntity>(*this); }
    void draw() const override {}
    void boundingBox() const override {}
    std::string typeName() const override { return "Polyline"; }

    std::string serialize() const override {
        nlohmann::json j = nlohmann::json::parse(BaseDBObject::serialize());
        nlohmann::json arr = nlohmann::json::array();
        for (auto &p : m_points) arr.push_back({p.first, p.second});
        j["points"] = arr;
        return j.dump();
    }

    void deserialize(const std::string& data) override {
        BaseDBObject::deserialize(data);
        try {
            auto j = nlohmann::json::parse(data);
            if (j.contains("points")) {
                m_points.clear();
                for (auto &it : j["points"]) m_points.emplace_back(it[0].get<double>(), it[1].get<double>());
            }
        } catch (...) {}
    }

private:
    std::vector<std::pair<double,double>> m_points;
};

} // namespace db
} // namespace occt_autocad
