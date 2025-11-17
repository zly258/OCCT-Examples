#pragma once

#include "DBObject.h"
#include <string>
#include "../util/UUID.h"

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
        // very small key=value;key=value format for now
        return std::string("id=") + m_id + ";layer=" + m_layer + ";color=" + std::to_string(m_color);
    }

    void deserialize(const std::string& data) override {
        // parse simple key=value; pairs
        size_t start = 0;
        while (start < data.size()) {
            auto pos = data.find(';', start);
            std::string token = data.substr(start, (pos==std::string::npos)?std::string::npos:pos-start);
            auto eq = token.find('=');
            if (eq != std::string::npos) {
                std::string k = token.substr(0, eq);
                std::string v = token.substr(eq+1);
                if (k == "id") m_id = v;
                else if (k == "layer") m_layer = v;
                else if (k == "color") m_color = std::stoi(v);
            }
            if (pos == std::string::npos) break;
            start = pos + 1;
        }
    }

    // metadata accessors
    void setLayer(const std::string& layer) { m_layer = layer; }
    std::string layer() const { return m_layer; }
    void setColor(int c) { m_color = c; }
    int color() const { return m_color; }

protected:
    std::string m_id;
    std::string m_layer;
    int m_color;
};

} // namespace db
} // namespace occt_autocad
