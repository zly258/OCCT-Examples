#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "occt_autocad/commands/CommandManager.h"
#include "occt_autocad/commands/CreateEntityCommand.h"
#include "occt_autocad/db/Database.h"

using namespace occt_autocad::commands;
using namespace occt_autocad::db;

TEST_CASE("CommandManager execute/undo/redo create entity", "[commands]") {
    CommandManager mgr;
    Database db;

    REQUIRE(db.findEntity("nonexistent") == nullptr);

    auto createCmd = std::make_shared<CreateEntityCommand>(db);
    bool ok = mgr.executeCommand(createCmd);
    REQUIRE(ok == true);
    REQUIRE(mgr.canUndo() == true);
    REQUIRE(mgr.canRedo() == false);

    // undo should remove the created entity
    mgr.undo();
    REQUIRE(mgr.canUndo() == false);
    REQUIRE(mgr.canRedo() == true);

    // redo should recreate
    mgr.redo();
    REQUIRE(mgr.canUndo() == true);
}
