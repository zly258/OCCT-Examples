#include <catch2/catch.hpp>
#include "occt_autocad/core/Document.h"
#include "occt_autocad/commands/CreateEntityCommand.h"
#include "occt_autocad/commands/CommandGroup.h"

using namespace occt_autocad::core;
using namespace occt_autocad::commands;
using namespace occt_autocad::db;

TEST_CASE("CommandGroup creates multiple entities and is undoable as single unit", "[commandgroup]") {
    Document doc("groupdoc");

    auto group = std::make_shared<CommandGroup>();
    group->add(std::make_shared<CreateEntityCommand>(doc.database()));
    group->add(std::make_shared<CreateEntityCommand>(doc.database()));

    bool ok = doc.executeCommand(group);
    REQUIRE(ok);

    auto all = doc.database().allEntities();
    REQUIRE(all.size() >= 2);

    doc.undo();
    auto all2 = doc.database().allEntities();
    // After undo the two created entities should be removed (may be others preexisting)
    REQUIRE(all2.size() < all.size());
}
