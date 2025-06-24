#include "ClearAction.h"
#include "core/ViewportManager.h"
#include "core/Viewport.h"

ClearAction::ClearAction(QObject* parent) : Action(parent) {}

QString ClearAction::id() const {
    return "ClearAll";
}

QString ClearAction::name() const {
    return tr("清空");
}

QString ClearAction::description() const {
    return tr("清空所有实体");
}

QString ClearAction::icon() const {
    return ":/icons/clear.png"; // 确保图标文件存在
}

void ClearAction::execute() {
    if (Viewport* viewport = ViewportManager::instance()->activeViewport()) {
        viewport->clearAllEntities();
    }
}