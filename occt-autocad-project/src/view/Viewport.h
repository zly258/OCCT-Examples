#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>

class Viewport : public QWidget {
    Q_OBJECT

public:
    explicit Viewport(QWidget *parent = nullptr);
    void render(); // Method to render the viewport
    void setViewParameters(float zoom, float angle); // Set view parameters

protected:
    void paintEvent(QPaintEvent *event) override; // Override paint event for custom rendering

private:
    float m_zoom; // Zoom level
    float m_angle; // View angle
};

#endif // VIEWPORT_H