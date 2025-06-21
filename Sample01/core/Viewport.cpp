#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Aspect_NeutralWindow.hxx>
#include <Quantity_Color.hxx>
#include <QDebug>
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <NCollection_List.hxx>

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{
    // 设置Qt窗口属性
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    // 初始化视图
    initViewer();
    initSelectionRect();
}

Viewport::~Viewport()
{
}

void Viewport::initViewer()
{
    // 创建显示连接和图形驱动
    Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
    Handle(Graphic3d_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection);

    // 创建查看器
    m_viewer = new V3d_Viewer(graphicDriver);
    m_viewer->SetDefaultViewSize(1000.);
    m_viewer->SetDefaultViewProj(V3d_XnegYnegZpos);
    m_viewer->SetDefaultLights();
    m_viewer->SetLightOn();

    // 创建视图
    m_view = m_viewer->CreateView();
    m_view->SetImmediateUpdate(Standard_True);

    // 创建窗口并绑定Qt窗口句柄
    m_window = new Aspect_NeutralWindow();
    m_window->SetNativeHandles((Aspect_Drawable)winId(), 0, 0);
    m_window->SetSize(width(), height());
    m_view->SetWindow(m_window);
    if (!m_window->IsMapped()) {
        m_window->Map();
    }

    // 创建交互上下文
    m_context = new AIS_InteractiveContext(m_viewer);
    m_context->SetPixelTolerance(10);
    m_view->SetBackgroundColor(Quantity_NOC_GRAY40);
    m_view->MustBeResized();  // 确保视图调整大小
    m_view->FitAll();         // 确保视图显示所有内容
}

void Viewport::initSelectionRect()
{
    m_selectionRect = new AIS_RubberBand(Quantity_NOC_YELLOW1, Aspect_TOL_DASH);
    m_selectionRect->SetTransformPersistence(
        new Graphic3d_TransformPers(Graphic3d_TMF_2d, Aspect_TOTP_LEFT_LOWER));
    m_selectionRect->SetZLayer(Graphic3d_ZLayerId_TopOSD);
}

void Viewport::paintEvent(QPaintEvent *event)
{
    if (!m_view.IsNull()) {
        m_view->Redraw();
    }
    QWidget::paintEvent(event);
}

void Viewport::resizeEvent(QResizeEvent *event)
{
    if (!m_view.IsNull() && !m_window.IsNull()) {
        m_window->SetSize(event->size().width(), event->size().height());
        m_view->MustBeResized();
    }
    update();
    QWidget::resizeEvent(event);
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    setFocus(); // 确保点击时获得焦点

    // 处理中键操作
    if (event->button() == Qt::MiddleButton) {
        if (event->modifiers() & Qt::ShiftModifier) {
            m_view->StartRotation(event->pos().x(), event->pos().y());
            m_isRotating = true;
            setCursor(Qt::ClosedHandCursor); // 设置旋转光标
            return;
        } else {
            m_isPanning = true;
            setCursor(Qt::SizeAllCursor); // 设置平移光标
            m_lastMousePos = event->pos();
            return;
        }
    }

    // 处理左键选择
    if (event->button() == Qt::LeftButton) {
        if (!(event->modifiers() & Qt::ShiftModifier)) {
            m_selectStartPos = event->pos();
            m_isMultiSelecting = true;
            return;
        }
    }

    m_lastMousePos = event->pos();
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    if (!event || m_view.IsNull() || m_context.IsNull()) {
        return;
    }

    setFocus(); // 确保移动时获得焦点

    // 获取鼠标位置
    const QPoint pos = event->pos();
    gp_Pnt worldPoint = convertWithProj(pos);

    if (m_isPanning) {
        const int dx = (event->x() - m_lastMousePos.x());
        const int dy = (m_lastMousePos.y() - event->y());
        m_view->Pan(dx, dy);
        m_lastMousePos = event->pos();
        return;
    }

    if (m_isRotating) {
        m_view->Rotation(event->x(), event->y());
        m_lastMousePos = event->pos();
        return;
    }

    // 移动触发高亮
    m_context->MoveTo(pos.x(), pos.y(), m_view, Standard_True);

    // 框选预览
    if (m_isMultiSelecting) {
        previewSelectionRect(event->pos());
        return;
    }
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isPanning || m_isRotating) {
        setCursor(Qt::ArrowCursor);
    }
    m_isPanning = false;
    m_isRotating = false;

    if (m_isMultiSelecting) {
        finishSelection(event->pos());
        m_isMultiSelecting = false;
        return;
    }
}

void Viewport::wheelEvent(QWheelEvent *event)
{
    m_view->StartZoomAtPoint(event->x(), event->y());
    // 缩放灵敏度
    double zoomSensitivity = 0.2;
    zoomSensitivity = qMin(qMax(0.2, zoomSensitivity), 0.8);
    m_view->ZoomAtPoint(0, 0, event->angleDelta().y() * zoomSensitivity, 0);
}

void Viewport::fitAll()
{
    if (!m_view.IsNull()) {
        m_view->FitAll();
        m_view->ZFitAll();
        m_view->Redraw();
    }
}

void Viewport::setDisplayMode(int mode)
{
    if (!m_context.IsNull()) {
        m_context->SetDisplayMode(mode, Standard_True);
        m_view->Redraw();
    }
}

void Viewport::displayEntity(const Handle(AIS_Shape)& entity)
{
    if (!m_context.IsNull()) {
        m_context->Display(entity, Standard_True);
        m_view->Redraw();
    }
}

void Viewport::displayEntities(const QList<Handle(AIS_Shape)>& entities)
{
    if (!m_context.IsNull()) {
        // 遍历所有实体并显示
        for (const Handle(AIS_Shape)& entity : entities) {
            if (!entity.IsNull()) {
                m_context->Display(entity, Standard_False);
            }
        }
        // 更新视图
        m_view->Redraw();
    }
}

void Viewport::previewSelectionRect(const QPoint &pos)
{
    m_selectEndPos = pos;
    // 更新框选矩形
    if (!m_selectionRect.IsNull()) {
        Standard_Integer xMin = qMin(m_selectStartPos.x(), m_selectEndPos.x());
        Standard_Integer xMax = qMax(m_selectStartPos.x(), m_selectEndPos.x());
        
        // 转换Y坐标（Qt和OCCT的Y轴方向相反）
        Standard_Integer height = this->height();
        Standard_Integer yMin = height - qMax(m_selectStartPos.y(), m_selectEndPos.y());
        Standard_Integer yMax = height - qMin(m_selectStartPos.y(), m_selectEndPos.y());
        
        if (fabs(yMax - yMin) < Precision::Confusion()) return;
        if (fabs(xMax - xMin) < Precision::Confusion()) return;
        
        m_selectionRect->SetRectangle(xMin, yMin, xMax, yMax);
        
        if (!m_context->IsDisplayed(m_selectionRect)) {
            m_context->Display(m_selectionRect, Standard_False);
        } else {
            m_context->Redisplay(m_selectionRect, Standard_False);
        }
        m_view->Redraw();
    }
}

void Viewport::finishSelection(const QPoint &endPos)
{
    // 移除框选矩形
    if (!m_selectionRect.IsNull() && m_context->IsDisplayed(m_selectionRect)) {
        m_context->Remove(m_selectionRect, Standard_False);
    }

    // 如果拖动距离太小，当作点选处理
    if ((endPos - m_selectStartPos).manhattanLength() <= 3) {
        handleSingleSelection(endPos);
    } else {
        // 否则作为框选处理
        handleAreaSelection(m_selectStartPos, endPos);
    }

    // 更新显示
    m_view->Redraw();
}

void Viewport::handleSingleSelection(const QPoint &pos)
{
    m_context->MoveTo(pos.x(), pos.y(), m_view, Standard_True);

    bool isCtrl = QApplication::keyboardModifiers() & Qt::ControlModifier;
    AIS_SelectionScheme scheme = isCtrl ? AIS_SelectionScheme_Add : AIS_SelectionScheme_Replace;

    if (m_context->HasDetected()) {
        m_context->SelectDetected(scheme);
    } else {
        if (!isCtrl)
            m_context->ClearSelected(Standard_True);
    }

    m_context->UpdateCurrentViewer();
}

void Viewport::handleAreaSelection(const QPoint &p1, const QPoint &p2)
{
    Standard_Integer xMin = qMin(p1.x(), p2.x());
    Standard_Integer xMax = qMax(p1.x(), p2.x());
    Standard_Integer yMin = qMin(p1.y(), p2.y());
    Standard_Integer yMax = qMax(p1.y(), p2.y());
    bool isCtrl = QApplication::keyboardModifiers() & Qt::ControlModifier;

    // 确保选择区域有效
    if (xMax - xMin < 2 || yMax - yMin < 2) return;

    m_context->SelectRectangle(Graphic3d_Vec2i(xMin, yMin), Graphic3d_Vec2i(xMax, yMax), m_view,
                               isCtrl ? AIS_SelectionScheme_Add : AIS_SelectionScheme_Replace);
    m_context->UpdateCurrentViewer();
}

gp_Pnt Viewport::convertWithProj(const QPoint &clickPos) const
{
    if (m_view.IsNull())
        return gp_Pnt();

    // 转换为3D点和射线方向
    Standard_Real X, Y, Z;    // 投影点坐标
    Standard_Real Vx, Vy, Vz; // 射线方向向量
    
    // 使用OCCT的ConvertWithProj方法进行转换
    m_view->ConvertWithProj(clickPos.x(), clickPos.y(), X, Y, Z, Vx, Vy, Vz);
    
    // 创建并返回投影点
    return gp_Pnt(X, Y, Z);
}

QList<Handle(AIS_Shape)> Viewport::getAllAISShapes() const
{
    QList<Handle(AIS_Shape)> shapes;
    
    if (!m_context.IsNull()) {
        // 获取所有显示的交互对象
        AIS_ListOfInteractive displayedObjects;
        m_context->DisplayedObjects(displayedObjects);
        
        // 遍历并筛选
        for (AIS_ListOfInteractive::Iterator it(displayedObjects); it.More(); it.Next()) {
            if (Handle(AIS_Shape) shape = Handle(AIS_Shape)::DownCast(it.Value())) {
                shapes.append(shape);
            }
        }
    } else {
        qDebug() << "Context is null!";
    }
    
    qDebug() << "Total shapes found:" << shapes.size();
    return shapes;
} 