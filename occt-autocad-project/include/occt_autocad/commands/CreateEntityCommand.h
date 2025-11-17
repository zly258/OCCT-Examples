#pragma once

#include "Command.h"
#include "../db/Database.h"
#include "../db/SimpleEntity.h"

namespace occt_autocad {
namespace commands {

class CreateEntityCommand : public Command {
public:
    CreateEntityCommand(db::Database& db) : m_db(db) {}
    ~CreateEntityCommand() override = default;

    bool execute() override {
        // create a SimpleEntity and remember its id
        auto e = m_db.createEntity<db::SimpleEntity>();
        if (!e) return false;
        m_createdId = e->id();
        return true;
    }

    void undo() override {
        if (!m_createdId.empty()) {
            m_db.eraseEntity(m_createdId);
        }
    }

private:
    db::Database& m_db;
    std::string m_createdId;
};

} // namespace commands
} // namespace occt_autocad
