#pragma once

#include "Command.h"
#include <vector>
#include <memory>

namespace occt_autocad {
namespace commands {

class CommandManager {
public:
    CommandManager(size_t max_undo = 100) : m_maxUndo(max_undo) {}
    ~CommandManager() = default;

    bool executeCommand(const Command::Ptr& cmd) {
        if (!cmd) return false;
        if (cmd->execute()) {
            m_undoStack.push_back(cmd);
            // clear redo stack
            m_redoStack.clear();
            if (m_undoStack.size() > m_maxUndo) m_undoStack.erase(m_undoStack.begin());
            return true;
        }
        return false;
    }

    bool canUndo() const { return !m_undoStack.empty(); }
    bool canRedo() const { return !m_redoStack.empty(); }

    void undo() {
        if (!canUndo()) return;
        auto cmd = m_undoStack.back();
        m_undoStack.pop_back();
        cmd->undo();
        m_redoStack.push_back(cmd);
    }

    void redo() {
        if (!canRedo()) return;
        auto cmd = m_redoStack.back();
        m_redoStack.pop_back();
        cmd->execute();
        m_undoStack.push_back(cmd);
    }

    void clear() {
        m_undoStack.clear();
        m_redoStack.clear();
    }

private:
    size_t m_maxUndo;
    std::vector<Command::Ptr> m_undoStack;
    std::vector<Command::Ptr> m_redoStack;
};

} // namespace commands
} // namespace occt_autocad
