#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QWidget>
#include <QList>
#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <V3d_View.hxx>
#include <AIS_RubberBand.hxx>
#include <AIS_Shape.hxx>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFocusEvent>
#include <Aspect_NeutralWindow.hxx>
#include <Graphic3d_TransformPers.hxx>
#include <Graphic3d_ZLayerId.hxx>
#include <Quantity_Color.hxx>
#include <gp_Pnt.hxx>

#include "SimpleEntity.h"

class Viewport : public QWidget
{
    Q_OBJECT

public:
    explicit Viewport(QWidget *parent = nullptr);
    ~Viewport();

    // 视图操作
    void fitAll();
    void zoom(float delta);
    void rotate(float x, float y);
    void pan(float x, float y);

    void clearAllEntities();
    void displaySimpleEntity(SimpleEntity* entity);
    QList<SimpleEntity*> getAllSimpleEntities() const { return m_simpleEntities; }
    void setDisplayMode(int mode);  // 设置显示模式
    void displayEntity(const Handle(AIS_Shape)& entity);  // 显示几何体
    void displayEntities(const QList<Handle(AIS_Shape)>& entities);

    // 坐标转换
    gp_Pnt convertWithProj(const QPoint &clickPos) const;

    QList<Handle(AIS_Shape)> getAllAISShapes() const;

protected:
    // 事件处理
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    QPaintEngine *paintEngine() const override { return nullptr; }
    
private:
    // 初始化视图
    void initViewer();
    // 初始化选择矩形
    void initSelectionRect();
    // 处理选择
    void handleSelection(const QPoint &pos);
    void handleSingleSelection(const QPoint &pos);
    void handleAreaSelection(const QPoint &p1, const QPoint &p2);
    void finishSelection(const QPoint &endPos);
    void previewSelectionRect(const QPoint &pos);
    
    // OCCT 相关成员
    Handle(AIS_RubberBand) m_selectionRect;

    Handle(V3d_Viewer) m_viewer;              // 视图管理器
    Handle(V3d_View) m_view;                  // 视图
    Handle(AIS_InteractiveContext) m_context; // 交互上下文
    Handle(Aspect_NeutralWindow) m_window;    // 窗口

    // 鼠标操作状态
    QPoint m_lastMousePos;
    bool m_isPanning = false;
    bool m_isRotating = false;
    bool m_isSelecting = false;
    bool m_isMultiSelecting = false;  // 是否正在框选
    QPoint m_selectStartPos;          // 框选起始位置
    QPoint m_selectEndPos;            // 框选结束位置

    // 保存 SimpleEntity 对象
    QList<SimpleEntity*> m_simpleEntities;
}; 

#endif // VIEWPORT_H