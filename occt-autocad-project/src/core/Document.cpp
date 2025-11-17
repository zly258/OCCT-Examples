#include "Document.h"

namespace occt_autocad {
namespace core {

Document::Document(const std::string& title)
    : m_title(title), m_db(), m_cmdMgr() {}

Document::~Document() = default;

void Document::load(const std::string& filename) {
    // TODO: implement load using Database serialization
}

void Document::save(const std::string& filename) const {
    // Save database entities and undo history to JSON file
    try {
        nlohmann::json root;
        root["entities"] = nlohmann::json::parse(m_db.serialize());
        // serialize history
        root["history"] = m_cmdMgr.serializeHistory();
        std::ofstream ofs(filename);
        ofs << root.dump(2);
    } catch(...) {
        // ignore errors for now
    }
}

} // namespace core
} // namespace occt_autocad