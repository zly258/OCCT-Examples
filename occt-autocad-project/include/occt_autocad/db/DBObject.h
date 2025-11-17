#pragma once

#include <string>
#include <memory>

namespace occt_autocad {
namespace db {

class DBObject {
public:
    using Ptr = std::shared_ptr<DBObject>;

    DBObject() = default;
    virtual ~DBObject() = default;

    // 返回对象全局唯一 ID（实现可用 UUID 或内部递增）
    virtual std::string id() const = 0;

    // 克隆用于 undo/redo 或复制操作
    virtual Ptr clone() const = 0;

    // 简单序列化接口（可扩展为二进制或 JSON）
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
    // Return runtime type name for factory/serialization
    virtual std::string typeName() const { return "DBObject"; }
};


} // namespace db
} // namespace occt_autocad
