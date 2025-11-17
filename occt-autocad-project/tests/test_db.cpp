#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "occt_autocad/db/Database.h"

using namespace occt_autocad::db;

TEST_CASE("Database create and find entity (mock)", "[db]") {
    Database db;

    // 由于 Entity 是抽象类，这里测试 Table 基本 API: 添加、查找、删除
    struct MockEntity : public Entity {
        MockEntity(const std::string& id) : m_id(id) {}
        std::string id() const override { return m_id; }
        Ptr clone() const override { return std::make_shared<MockEntity>(*this); }
        std::string serialize() const override { return m_id; }
        void deserialize(const std::string& data) override { m_id = data; }
        void draw() const override {}
        void boundingBox() const override {}
        std::string m_id;
    };

    auto e = db.createEntity<MockEntity>("e1");
    REQUIRE(e->id() == "e1");

    auto found = db.findEntity("e1");
    REQUIRE(found != nullptr);

    db.eraseEntity("e1");
    auto notfound = db.findEntity("e1");
    REQUIRE(notfound == nullptr);
}
