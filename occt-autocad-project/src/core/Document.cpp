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
    // TODO: implement save using Database serialization
}

} // namespace core
} // namespace occt_autocad