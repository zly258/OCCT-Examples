#pragma once

#include "Command.h"
#include "../db/Database.h"

namespace occt_autocad {
namespace commands {

class MoveEntityCommand : public Command {
public:
    MoveEntityCommand(db::Database& db, const std::string& id, double dx, double dy)
        : m_db(db), m_id(id), m_dx(dx), m_dy(dy) {}

    bool execute() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return false;
        auto pos = e->position();
        m_prevX = pos.first;
        m_prevY = pos.second;
        e->moveBy(m_dx, m_dy);
        return true;
    }

    void undo() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return;
        e->setPosition(m_prevX, m_prevY);
    }

    bool canMergeWith(const Command::Ptr& other) const override {
        auto o = std::dynamic_pointer_cast<MoveEntityCommand>(other);
        if (!o) return false;
        return (o->m_id == m_id);
    }

    void mergeWith(const Command::Ptr& other) override {
        auto o = std::dynamic_pointer_cast<MoveEntityCommand>(other);
        if (!o) return;
        // accumulate movement delta
        m_dx += o->m_dx;
        m_dy += o->m_dy;
    }

    nlohmann::json serialize() const override {
        nlohmann::json j;
        j["type"] = "MoveEntity";
        j["id"] = m_id;
        j["dx"] = m_dx;
        j["dy"] = m_dy;
        return j;
    }

    double getDx() const { return m_dx; }
    double getDy() const { return m_dy; }

private:
    db::Database& m_db;
    std::string m_id;
    double m_dx{0}, m_dy{0};
    double m_prevX{0}, m_prevY{0};
};

} // namespace commands
} // namespace occt_autocad
