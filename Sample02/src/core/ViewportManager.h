#ifndef VIEWPORT_MANAGER_H
#define VIEWPORT_MANAGER_H

#include <QObject>

class Viewport;

class ViewportManager : public QObject
{
    Q_OBJECT
public:
    static ViewportManager* instance();

    void setActiveViewport(Viewport* viewport);
    Viewport* activeViewport() const;

signals:
    void activeViewportChanged(Viewport* viewport);

private:
    ViewportManager();
    ~ViewportManager();

    static ViewportManager* s_instance;
    Viewport* m_activeViewport;
};

#endif // VIEWPORT_MANAGER_H 