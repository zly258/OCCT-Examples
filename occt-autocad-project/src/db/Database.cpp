#include "occt_autocad/db/Database.h"

namespace occt_autocad {
namespace db {

Database::Database() = default;
Database::~Database() = default;

// Simple serialization of the whole database (entities)
std::string Database::serialize() const {
	nlohmann::json a = nlohmann::json::array();
	for (auto &e : m_entityTable.all()) {
		try {
			auto je = nlohmann::json::parse(e->serialize());
			a.push_back(je);
		} catch(...) {}
	}
	return a.dump();
}

void Database::clear() {
	// replace with new empty table
	m_entityTable = EntityTable();
}

} // namespace db
} // namespace occt_autocad
