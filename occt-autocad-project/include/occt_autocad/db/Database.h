#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "Table.h"
#include "Entity.h"
#include "LineEntity.h"
#include "CircleEntity.h"
#include "ArcEntity.h"
#include "PolylineEntity.h"
#include "TextEntity.h"

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

    // Create entity with a specific id (T must support constructor taking id)
    template<typename T>
    std::shared_ptr<T> createEntityWithId(const std::string& id) {
        auto e = std::make_shared<T>(id);
        m_entityTable.add(e);
        return e;
    }

    std::shared_ptr<Entity> findEntity(const std::string& id) const {
        return m_entityTable.find(id);
    }

    void eraseEntity(const std::string& id) {
        m_entityTable.remove(id);
    }

    std::vector<std::shared_ptr<Entity>> allEntities() const {
        return m_entityTable.all();
    }

    // insert an existing entity (keeps its id)
    void insertEntity(const std::shared_ptr<Entity>& e) {
        m_entityTable.insert(e);
    }

    // Factory to create entity instance by type with a specific id
    std::shared_ptr<Entity> createEntityOfTypeWithId(const std::string& type, const std::string& id) {
        if (type == "SimpleEntity") return createEntityWithId<SimpleEntity>(id);
        if (type == "Line") return createEntityWithId<LineEntity>(id);
        if (type == "Circle") return createEntityWithId<CircleEntity>(id);
        if (type == "Arc") return createEntityWithId<ArcEntity>(id);
        if (type == "Polyline") return createEntityWithId<PolylineEntity>(id);
        if (type == "Text") return createEntityWithId<TextEntity>(id);
        // default fallback
        return createEntityWithId<SimpleEntity>(id);
    }

    // TODO: 事务、commit/rollback、serialization 辅助

private:
    EntityTable m_entityTable;
};

} // namespace db
} // namespace occt_autocad
