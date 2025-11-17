#pragma once

#include "BaseDBObject.h"
#include <string>

namespace occt_autocad {
namespace db {

class TextEntity : public BaseDBObject, public Entity {
public:
    TextEntity() = default;
    TextEntity(const std::string& id, const std::string& text, double x, double y)
        : BaseDBObject(id), m_text(text) { m_x = x; m_y = y; }

    Ptr clone() const override { return std::make_shared<TextEntity>(*this); }
    void draw() const override {}
    void boundingBox() const override {}
    std::string typeName() const override { return "Text"; }

    std::string serialize() const override {
        nlohmann::json j = nlohmann::json::parse(BaseDBObject::serialize());
        j["text"] = m_text;
        return j.dump();
    }

    void deserialize(const std::string& data) override {
        BaseDBObject::deserialize(data);
        try {
            auto j = nlohmann::json::parse(data);
            if (j.contains("text")) m_text = j["text"].get<std::string>();
        } catch (...) {}
    }

private:
    std::string m_text;
};

} // namespace db
} // namespace occt_autocad
