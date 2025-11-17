#pragma once

#include "Command.h"
#include <vector>

namespace occt_autocad {
namespace commands {

class CommandGroup : public Command {
public:
    using Ptr = std::shared_ptr<CommandGroup>;
    CommandGroup() = default;
    ~CommandGroup() override = default;

    void add(const Command::Ptr& cmd) { if (cmd) m_commands.push_back(cmd); }

    bool execute() override {
        for (auto &c : m_commands) {
            if (!c->execute()) return false;
        }
        return true;
    }

    void undo() override {
        // undo in reverse order
        for (auto it = m_commands.rbegin(); it != m_commands.rend(); ++it) {
            (*it)->undo();
        }
    }

private:
    std::vector<Command::Ptr> m_commands;
};

} // namespace commands
} // namespace occt_autocad
