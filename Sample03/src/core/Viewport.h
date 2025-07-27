#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SoPickedPoint.h>
#include <QWidget>
#include <QList>

#include <TopoDS_Shape.hxx>
#include "SimpleEntity.h"

class Viewport : public SoQtExaminerViewer
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
    void displayShape(const TopoDS_Shape& shape);  // 显示OCCT几何体
    void displayShapes(const QList<TopoDS_Shape>& shapes);

    // 获取场景根节点
    SoSeparator* getSceneRoot() const { return m_sceneRoot; }

protected:
    // 事件回调
    static void selectionCB(void* userData, SoPath* path);
    static void mousePressCB(void* userData, SoEventCallback* cb);
    
private:
    // 初始化场景
    void initScene();
    // 将OCCT形状转换为Inventor节点
    SoSeparator* convertShapeToInventor(const TopoDS_Shape& shape);
    
    // Coin3D场景图相关成员
    SoSeparator* m_sceneRoot;        // 场景根节点
    SoSelection* m_selection;         // 选择节点
    SoEventCallback* m_eventCallback; // 事件回调节点

    // 保存SimpleEntity对象
    QList<SimpleEntity*> m_simpleEntities;
}; 

#endif // VIEWPORT_H