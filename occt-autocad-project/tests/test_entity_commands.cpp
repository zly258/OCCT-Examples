#include <catch2/catch.hpp>
#include "occt_autocad/core/Document.h"
#include "occt_autocad/commands/CreateEntityCommand.h"
#include "occt_autocad/commands/MoveEntityCommand.h"
#include "occt_autocad/commands/ModifyEntityCommand.h"
#include "occt_autocad/commands/DeleteEntityCommand.h"

using namespace occt_autocad::core;
using namespace occt_autocad::commands;
using namespace occt_autocad::db;

TEST_CASE("Entity lifecycle with Document CommandManager", "[entity_commands]") {
    Document doc("testdoc");

    // Create entity via command
    auto createCmd = std::make_shared<CreateEntityCommand>(doc.database());
    bool ok = doc.executeCommand(createCmd);
    REQUIRE(ok);

    // the created entity id is not directly exposed by command; find any entity in DB
    auto entities = doc.database().allEntities();
    REQUIRE(!entities.empty());
    auto e = entities.front();
    std::string id = e->id();

    // Move entity by (10,5)
    auto moveCmd = std::make_shared<MoveEntityCommand>(doc.database(), id, 10.0, 5.0);
    doc.executeCommand(moveCmd);
    auto pos = e->position();
    REQUIRE(pos.first == Approx(10.0));
    REQUIRE(pos.second == Approx(5.0));

    // Modify layer
    auto modCmd = std::make_shared<ModifyEntityCommand>(doc.database(), id, std::string("layer"), std::string("Layer1"));
    doc.executeCommand(modCmd);
    REQUIRE(e->layer() == "Layer1");

    // Undo modify
    doc.undo();
    REQUIRE(e->layer() != "Layer1");

    // Undo move
    doc.undo();
    pos = e->position();
    REQUIRE(pos.first == Approx(0.0));

    // Redo move
    doc.redo();
    pos = e->position();
    REQUIRE(pos.first == Approx(10.0));

    // Delete entity
    auto delCmd = std::make_shared<DeleteEntityCommand>(doc.database(), id);
    doc.executeCommand(delCmd);
    auto found = doc.database().findEntity(id);
    REQUIRE(found == nullptr);

    // Undo delete -> entity recreated (may have different id)
    doc.undo();
    // At least one entity exists now
    auto all = doc.database().EntityTable::all();
    REQUIRE(!all.empty());
}
