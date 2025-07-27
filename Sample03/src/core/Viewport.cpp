#include "Viewport.h"
#include "ViewportManager.h"

#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCylinder.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoPointLight.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoNormal.h>
#include <Inventor/nodes/SoNormalBinding.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/SbViewportRegion.h>

#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Tool.hxx>
#include <Poly_Triangulation.hxx>
#include <Poly_Array1OfTriangle.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <gp_Pnt.hxx>

Viewport::Viewport(QWidget *parent)
    : SoQtExaminerViewer(parent, nullptr, TRUE)
{
    // 初始化场景
    initScene();

    // 设置背景颜色为灰色
    setBackgroundColor(SbColor(0.4f, 0.4f, 0.4f));

    // 设置相机类型为透视
    setStereoViewing(FALSE);
    setViewing(TRUE);
    
    // 设置装饰器（坐标轴等）
    setDecoration(TRUE);
}

Viewport::~Viewport()
{
    if (ViewportManager::instance()->activeViewport() == this) {
        ViewportManager::instance()->setActiveViewport(nullptr);
    }
    
    // 释放场景图
    if (m_sceneRoot) {
        m_sceneRoot->unref();
    }
    if (m_selection) {
        m_selection->unref();
    }
    if (m_eventCallback) {
        m_eventCallback->unref();
    }
}

void Viewport::initScene()
{
    // 创建场景根节点
    m_sceneRoot = new SoSeparator;
    m_sceneRoot->ref();

    // 创建光源
    SoDirectionalLight* light = new SoDirectionalLight;
    light->direction.setValue(0.5f, 0.5f, -1.0f);
    m_sceneRoot->addChild(light);

    // 创建选择节点
    m_selection = new SoSelection;
    m_selection->ref();
    m_selection->policy = SoSelection::SINGLE;
    m_selection->addSelectionCallback(selectionCB, this);
    m_sceneRoot->addChild(m_selection);

    // 创建事件回调节点
    m_eventCallback = new SoEventCallback;
    m_eventCallback->ref();
    m_eventCallback->addEventCallback(
        SoMouseButtonEvent::getClassTypeId(),
        mousePressCB,
        this);
    m_selection->addChild(m_eventCallback);

    // 设置场景
    setSceneGraph(m_sceneRoot);
}

void Viewport::selectionCB(void* userData, SoPath* path)
{
    Viewport* viewport = static_cast<Viewport*>(userData);
    if (!viewport || !path) return;

    // 这里可以处理选择回调
    // 例如高亮显示选中的对象
    SoNode* node = path->getTail();
    if (node) {
        // 处理选中的节点
    }
}

void Viewport::mousePressCB(void* userData, SoEventCallback* cb)
{
    Viewport* viewport = static_cast<Viewport*>(userData);
    if (!viewport) return;

    const SoEvent* event = cb->getEvent();
    if (!event) return;

    if (event->isOfType(SoMouseButtonEvent::getClassTypeId())) {
        const SoMouseButtonEvent* mbe = static_cast<const SoMouseButtonEvent*>(event);
        if (mbe->getButton() == SoMouseButtonEvent::BUTTON1 && 
            mbe->getState() == SoButtonEvent::DOWN) {
            // 处理鼠标点击事件
            const SoPickedPoint* pick = cb->getPickedPoint();
            if (pick) {
                // 处理拾取点
            }
        }
    }
}

void Viewport::fitAll()
{
    viewAll();
}

void Viewport::zoom(float delta)
{
    // Coin3D的ExaminerViewer已经处理了缩放
}

void Viewport::rotate(float x, float y)
{
    // Coin3D的ExaminerViewer已经处理了旋转
}

void Viewport::pan(float x, float y)
{
    // Coin3D的ExaminerViewer已经处理了平移
}

void Viewport::clearAllEntities()
{
    // 清除所有实体
    while (m_selection->getNumChildren() > 1) {  // 保留事件回调节点
        m_selection->removeChild(1);
    }
    m_simpleEntities.clear();
}

void Viewport::displaySimpleEntity(SimpleEntity* entity)
{
    if (!entity) return;

    // 创建一个新的分隔节点
    SoSeparator* sep = new SoSeparator;
    
    // 添加材质
    SoMaterial* mat = new SoMaterial;
    mat->diffuseColor.setValue(0.8f, 0.8f, 0.8f);
    sep->addChild(mat);

    // 添加变换
    SoTransform* transform = new SoTransform;
    // 设置变换参数...
    sep->addChild(transform);

    // 根据实体类型添加几何体
    switch (entity->type()) {
        case SimpleEntity::Box: {
            SoCube* cube = new SoCube;
            // 设置尺寸...
            sep->addChild(cube);
            break;
        }
        case SimpleEntity::Sphere: {
            SoSphere* sphere = new SoSphere;
            // 设置半径...
            sep->addChild(sphere);
            break;
        }
        case SimpleEntity::Cylinder: {
            SoCylinder* cylinder = new SoCylinder;
            // 设置参数...
            sep->addChild(cylinder);
            break;
        }
        // 添加其他类型...
    }

    // 将分隔节点添加到选择节点
    m_selection->addChild(sep);
    m_simpleEntities.append(entity);
}

void Viewport::setDisplayMode(int mode)
{
    // 在Coin3D中设置显示模式
    // 可以通过材质属性来实现不同的显示效果
}

void Viewport::displayShape(const TopoDS_Shape& shape)
{
    if (shape.IsNull()) return;

    // 将OCCT形状转换为Inventor节点
    SoSeparator* shapeSep = convertShapeToInventor(shape);
    if (shapeSep) {
        m_selection->addChild(shapeSep);
    }
}

void Viewport::displayShapes(const QList<TopoDS_Shape>& shapes)
{
    for (const TopoDS_Shape& shape : shapes) {
        displayShape(shape);
    }
}

SoSeparator* Viewport::convertShapeToInventor(const TopoDS_Shape& shape)
{
    if (shape.IsNull()) return nullptr;

    // 创建一个新的分隔节点
    SoSeparator* sep = new SoSeparator;
    
    // 添加材质
    SoMaterial* mat = new SoMaterial;
    mat->diffuseColor.setValue(0.8f, 0.8f, 0.8f);
    sep->addChild(mat);

    // 对OCCT形状进行三角化
    BRepMesh_IncrementalMesh mesh(shape, 0.1); // 0.1是网格精度

    // 遍历所有面
    TopExp_Explorer explorer(shape, TopAbs_FACE);
    for (; explorer.More(); explorer.Next()) {
        const TopoDS_Face& face = TopoDS::Face(explorer.Current());
        
        // 获取三角化数据
        TopLoc_Location loc;
        Handle(Poly_Triangulation) triangulation = BRep_Tool::Triangulation(face, loc);
        
        if (triangulation.IsNull()) continue;

        // 创建坐标节点
        SoCoordinate3* coords = new SoCoordinate3;
        SoIndexedFaceSet* faceSet = new SoIndexedFaceSet;
        
        // 获取顶点数据
        const TColgp_Array1OfPnt& nodes = triangulation->Nodes();
        const Poly_Array1OfTriangle& triangles = triangulation->Triangles();
        
        // 设置顶点坐标
        coords->point.setNum(nodes.Length());
        for (Standard_Integer i = nodes.Lower(); i <= nodes.Upper(); i++) {
            gp_Pnt p = nodes(i).Transformed(loc);
            coords->point.set1Value(i-1, p.X(), p.Y(), p.Z());
        }
        
        // 设置三角形索引
        int numTriangles = triangles.Length();
        faceSet->coordIndex.setNum(numTriangles * 4); // 每个三角形4个索引（3个顶点+分隔符-1）
        
        int idx = 0;
        for (Standard_Integer i = triangles.Lower(); i <= triangles.Upper(); i++) {
            Standard_Integer n1, n2, n3;
            triangles(i).Get(n1, n2, n3);
            
            // 考虑面的方向
            if (face.Orientation() == TopAbs_REVERSED) {
                faceSet->coordIndex.set1Value(idx++, n1-1);
                faceSet->coordIndex.set1Value(idx++, n3-1);
                faceSet->coordIndex.set1Value(idx++, n2-1);
            } else {
                faceSet->coordIndex.set1Value(idx++, n1-1);
                faceSet->coordIndex.set1Value(idx++, n2-1);
                faceSet->coordIndex.set1Value(idx++, n3-1);
            }
            faceSet->coordIndex.set1Value(idx++, -1); // 三角形分隔符
        }
        
        // 添加法线
        SoNormal* normals = new SoNormal;
        SoNormalBinding* normalBinding = new SoNormalBinding;
        normalBinding->value = SoNormalBinding::PER_FACE;
        
        // 计算每个面的法线
        normals->vector.setNum(numTriangles);
        for (Standard_Integer i = 0; i < numTriangles; i++) {
            Standard_Integer n1, n2, n3;
            triangles(i+1).Get(n1, n2, n3);
            
            gp_Pnt p1 = nodes(n1).Transformed(loc);
            gp_Pnt p2 = nodes(n2).Transformed(loc);
            gp_Pnt p3 = nodes(n3).Transformed(loc);
            
            gp_Vec v1(p1, p2);
            gp_Vec v2(p1, p3);
            gp_Vec normal = v1.Crossed(v2);
            normal.Normalize();
            
            if (face.Orientation() == TopAbs_REVERSED) {
                normal.Reverse();
            }
            
            normals->vector.set1Value(i, normal.X(), normal.Y(), normal.Z());
        }
        
        // 将所有节点添加到分隔节点
        sep->addChild(normalBinding);
        sep->addChild(normals);
        sep->addChild(coords);
        sep->addChild(faceSet);
    }

    return sep;
}