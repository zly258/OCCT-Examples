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

private:
    db::Database& m_db;
    std::string m_id;
    double m_dx{0}, m_dy{0};
    double m_prevX{0}, m_prevY{0};
};

} // namespace commands
} // namespace occt_autocad
