#pragma once

#include "DBObject.h"
#include <string>
#include "../util/UUID.h"
#include <nlohmann/json.hpp>

namespace occt_autocad {
namespace db {

class BaseDBObject : public DBObject {
public:
    using Ptr = std::shared_ptr<BaseDBObject>;

    BaseDBObject()
        : m_id(occt_autocad::util::generateUUID()), m_layer("0"), m_color(0) {}
    explicit BaseDBObject(const std::string& id)
        : m_id(id), m_layer("0"), m_color(0) {}

    ~BaseDBObject() override = default;

    std::string id() const override { return m_id; }

    // clone remains pure virtual to force concrete classes implement cloning
    virtual Ptr baseClone() const {
        return std::make_shared<BaseDBObject>(*this);
    }

    std::string serialize() const override {
        nlohmann::json j;
        j["id"] = m_id;
        j["layer"] = m_layer;
        j["color"] = m_color;
        j["x"] = m_x;
        j["y"] = m_y;
        j["rotation"] = m_rotation;
        return j.dump();
    }

    void deserialize(const std::string& data) override {
        try {
            auto j = nlohmann::json::parse(data);
            if (j.contains("id")) m_id = j["id"].get<std::string>();
            if (j.contains("layer")) m_layer = j["layer"].get<std::string>();
            if (j.contains("color")) m_color = j["color"].get<int>();
            if (j.contains("x")) m_x = j["x"].get<double>();
            if (j.contains("y")) m_y = j["y"].get<double>();
            if (j.contains("rotation")) m_rotation = j["rotation"].get<double>();
        } catch (...) {
            // ignore parse errors for now
        }
    }

    // metadata accessors
    void setLayer(const std::string& layer) { m_layer = layer; }
    std::string layer() const { return m_layer; }
    void setColor(int c) { m_color = c; }
    int color() const { return m_color; }

    // transform helpers (2D for now)
    void setPosition(double x, double y) { m_x = x; m_y = y; }
    void moveBy(double dx, double dy) { m_x += dx; m_y += dy; }
    std::pair<double,double> position() const { return {m_x, m_y}; }
    void setRotation(double r) { m_rotation = r; }
    double rotation() const { return m_rotation; }

protected:
    std::string m_id;
    std::string m_layer;
    int m_color;
    double m_x = 0.0;
    double m_y = 0.0;
    double m_rotation = 0.0; // degrees
};

} // namespace db
} // namespace occt_autocad
