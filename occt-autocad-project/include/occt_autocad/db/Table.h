#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

namespace occt_autocad {
namespace db {

template<typename T>
class Table {
public:
    using Ptr = std::shared_ptr<Table<T>>;
    using ObjectPtr = std::shared_ptr<T>;

    Table() = default;
    ~Table() = default;

    void add(const ObjectPtr& obj) {
        m_objects.emplace(obj->id(), obj);
    }

    ObjectPtr find(const std::string& id) const {
        auto it = m_objects.find(id);
        if (it != m_objects.end()) return it->second;
        return nullptr;
    }

    std::vector<ObjectPtr> all() const {
        std::vector<ObjectPtr> out;
        out.reserve(m_objects.size());
        for (auto &p : m_objects) out.push_back(p.second);
        return out;
    }

    void remove(const std::string& id) {
        m_objects.erase(id);
    }

private:
    std::unordered_map<std::string, ObjectPtr> m_objects;
};

} // namespace db
} // namespace occt_autocad
