#pragma once

#include "Command.h"
#include "../db/Database.h"

namespace occt_autocad {
namespace commands {

class DeleteEntityCommand : public Command {
public:
    DeleteEntityCommand(db::Database& db, const std::string& id)
        : m_db(db), m_id(id) {}

    bool execute() override {
        auto e = m_db.findEntity(m_id);
        if (!e) return false;
        // store serialized state for undo
        m_saved = e->serialize();
        // also store type
        try { auto j = nlohmann::json::parse(m_saved); if (j.contains("type")) m_type = j["type"].get<std::string>(); }
        catch(...){}
        m_db.eraseEntity(m_id);
        return true;
    }

    void undo() override {
        if (m_saved.empty()) return;
        // recreate entity with original id and deserialize state
        auto e = m_db.createEntityWithId<db::SimpleEntity>(m_id);
        e->deserialize(m_saved);
    }

private:
    db::Database& m_db;
    std::string m_id;
    std::string m_saved;
    std::string m_type;
};

} // namespace commands
} // namespace occt_autocad
