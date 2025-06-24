#include "ViewportManager.h"
#include "Viewport.h"

ViewportManager* ViewportManager::s_instance = nullptr;

ViewportManager* ViewportManager::instance()
{
    if (!s_instance) {
        s_instance = new ViewportManager();
    }
    return s_instance;
}

ViewportManager::ViewportManager()
    : QObject(nullptr)
    , m_activeViewport(nullptr)
{
}

ViewportManager::~ViewportManager()
{
    s_instance = nullptr;
}

void ViewportManager::setActiveViewport(Viewport* viewport)
{
    if (m_activeViewport != viewport) {
        m_activeViewport = viewport;
        emit activeViewportChanged(viewport);
    }
}

Viewport* ViewportManager::activeViewport() const
{
    return m_activeViewport;
} 