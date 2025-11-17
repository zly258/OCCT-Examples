#pragma once

#include <memory>

namespace occt_autocad {
namespace commands {

class Command {
public:
    using Ptr = std::shared_ptr<Command>;
    virtual ~Command() = default;

    // 执行命令，返回是否成功
    virtual bool execute() = 0;
    // 撤销命令
    virtual void undo() = 0;
    // optional merge support
    virtual bool canMergeWith(const Ptr& other) const { return false; }
    virtual void mergeWith(const Ptr& other) {}
    // optional serialization for history persistence
    virtual nlohmann::json serialize() const { return nlohmann::json(); }
};

} // namespace commands
} // namespace occt_autocad
