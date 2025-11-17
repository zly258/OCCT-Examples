#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include "../db/Database.h"
#include "../commands/CommandManager.h"

namespace occt_autocad {
namespace core {

class Document {
public:
    Document(const std::string& title = "Untitled");
    ~Document();

    db::Database& database() { return m_db; }
    commands::CommandManager& commandManager() { return m_cmdMgr; }

    // helpers to run commands via document
    bool executeCommand(const commands::Command::Ptr& cmd) { return m_cmdMgr.executeCommand(cmd); }
    void undo() { m_cmdMgr.undo(); }
    void redo() { m_cmdMgr.redo(); }

    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    std::string m_title;
    db::Database m_db;
    commands::CommandManager m_cmdMgr;
};

} // namespace core
} // namespace occt_autocad

#endif // DOCUMENT_H