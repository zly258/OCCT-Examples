#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "occt_autocad/db/Database.h"
#include "occt_autocad/db/BaseDBObject.h"

using namespace occt_autocad::db;

TEST_CASE("Database create and find entity (mock using BaseDBObject)", "[db]") {
    Database db;

    struct MockEntity : public BaseDBObject, public Entity {
        MockEntity() = default;
        std::string id() const override { return m_id; }
        Ptr clone() const override { return std::make_shared<MockEntity>(*this); }
        std::string serialize() const override { return BaseDBObject::serialize(); }
        void deserialize(const std::string& data) override { BaseDBObject::deserialize(data); }
        void draw() const override {}
        void boundingBox() const override {}
    };

    auto e = db.createEntity<MockEntity>();
    REQUIRE(!e->id().empty());

    auto found = db.findEntity(e->id());
    REQUIRE(found != nullptr);

    db.eraseEntity(e->id());
    auto notfound = db.findEntity(e->id());
    REQUIRE(notfound == nullptr);
}
