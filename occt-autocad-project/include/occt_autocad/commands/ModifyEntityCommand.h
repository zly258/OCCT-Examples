#pragma once

#include "Command.h"
#include "../db/Database.h"

namespace occt_autocad {
namespace commands {

class ModifyEntityCommand : public Command {
public:
    ModifyEntityCommand(db::Database& db, const std::string& id, const std::string& key, const std::string& value)
        : m_db(db), m_id(id), m_key(key), m_value(value) {}

    bool execute() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return false;
        m_prev = e->serialize();
        // very simple: support layer and color keys
        if (m_key == "layer") e->setLayer(m_value);
        else if (m_key == "color") e->setColor(std::stoi(m_value));
        return true;
    }

    void undo() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return;
        e->deserialize(m_prev);
    }

private:
    db::Database& m_db;
    std::string m_id;
    std::string m_key;
    std::string m_value;
    std::string m_prev;
};

} // namespace commands
} // namespace occt_autocad
