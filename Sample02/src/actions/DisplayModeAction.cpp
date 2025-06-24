#include "DisplayModeAction.h"
#include <AIS_InteractiveContext.hxx>
#include "core/Viewport.h"
#include "core/ViewportManager.h"

DisplayModeAction::DisplayModeAction(int mode, QObject* parent)
    : Action(parent)
    , m_mode(mode)
{
}

void DisplayModeAction::execute()
{
    if (Viewport* viewport = ViewportManager::instance()->activeViewport()) {
        viewport->setDisplayMode(m_mode == 0 ? AIS_WireFrame : AIS_Shaded);
    }
} 