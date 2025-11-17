#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "Table.h"
#include "Entity.h"

namespace occt_autocad {
namespace db {

class Database {
public:
    Database();
    ~Database();

    using EntityTable = Table<Entity>;

    // 创建并返回实体的 shared_ptr（简单工厂），实际构造由 caller 提供具体类型
    template<typename T, typename... Args>
    std::shared_ptr<T> createEntity(Args&&... args) {
        auto e = std::make_shared<T>(std::forward<Args>(args)...);
        m_entityTable.add(e);
        return e;
    }

    std::shared_ptr<Entity> findEntity(const std::string& id) const {
        return m_entityTable.find(id);
    }

    void eraseEntity(const std::string& id) {
        m_entityTable.remove(id);
    }

    // TODO: 事务、commit/rollback、serialization 辅助

private:
    EntityTable m_entityTable;
};

} // namespace db
} // namespace occt_autocad
