#pragma once

#include "Command.h"
#include "../db/Database.h"

namespace occt_autocad {
namespace commands {

class RotateEntityCommand : public Command {
public:
    RotateEntityCommand(db::Database& db, const std::string& id, double dangle)
        : m_db(db), m_id(id), m_dangle(dangle) {}

    bool execute() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return false;
        m_prev = e->rotation();
        e->setRotation(m_prev + m_dangle);
        return true;
    }

    void undo() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return;
        e->setRotation(m_prev);
    }

private:
    db::Database& m_db;
    std::string m_id;
    double m_dangle{0};
    double m_prev{0};
};

} // namespace commands
} // namespace occt_autocad
