#include "MainWindow.h"
#include "core/Viewport.h"
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <TopoDS_Compound.hxx>
#include <QFileDialog>
#include <QMessageBox>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <gp_Circ.hxx>
#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <gp_Dir.hxx>
#include <gp_Elips.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <Geom_Line.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <random>
#include <QDebug>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置窗口标题和大小
    setWindowTitle("OCCT Qt Example");
    resize(800, 600);

    // 创建中央部件
    m_centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    m_viewport = new Viewport(m_centralWidget);
    layout->addWidget(m_viewport);

    setCentralWidget(m_centralWidget);

    // 初始化工具栏
    initToolBar();

    // 调整视图以显示所有内容
    m_viewport->fitAll();
}

MainWindow::~MainWindow()
{
    // 清理资源（如果需要）
}

void MainWindow::initToolBar()
{
    // 创建工具栏
    QToolBar *toolBar = addToolBar("Tools");

    // 添加线框模式按钮
    QAction *wireframeAction = toolBar->addAction("线框");
    connect(wireframeAction, &QAction::triggered, this, &MainWindow::setWireframeMode);

    // 添加填充模式按钮
    QAction *shadedAction = toolBar->addAction("填充");
    connect(shadedAction, &QAction::triggered, this, &MainWindow::setShadedMode);

    // 添加创建立方体按钮
    QAction *cubeAction = toolBar->addAction("立方体");
    connect(cubeAction, &QAction::triggered, this, &MainWindow::createCube);

    // 添加创建圆柱按钮
    QAction *cylinderAction = toolBar->addAction("圆柱");
    connect(cylinderAction, &QAction::triggered, this, &MainWindow::createCylinder);

    // 添加创建圆台按钮
    QAction *coneAction = toolBar->addAction("圆台");
    connect(coneAction, &QAction::triggered, this, &MainWindow::createCone);

    // 添加创建圆环按钮
    QAction *torusAction = toolBar->addAction("圆环");
    connect(torusAction, &QAction::triggered, this, &MainWindow::createTorus);

    // 添加创建球体按钮
    QAction *sphereAction = toolBar->addAction("球体");
    connect(sphereAction, &QAction::triggered, this, &MainWindow::createSphere);
    // 添加随机测试按钮
    QAction *randomTestAction = toolBar->addAction("随机测试");
    connect(randomTestAction, &QAction::triggered, this, &MainWindow::randomTest);
}

void MainWindow::setWireframeMode()
{
    if (m_viewport) {
        m_viewport->setDisplayMode(AIS_WireFrame);
    }
}

void MainWindow::setShadedMode()
{
    if (m_viewport) {
        m_viewport->setDisplayMode(AIS_Shaded);
    }
}

void MainWindow::createCube()
{
    if (m_viewport) {
        // 设置立方体位置 (200, 0, 0)
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(200.0, 0.0, 0.0));
        
        TopoDS_Shape cube = BRepPrimAPI_MakeBox(100.0, 100.0, 100.0).Shape();
        BRepBuilderAPI_Transform shapeTransform(cube, transform);
        cube = shapeTransform.Shape();
        
        Handle(AIS_Shape) aisCube = new AIS_Shape(cube);
        m_viewport->displayEntity(aisCube);
    }
}

void MainWindow::createCylinder()
{
    if (m_viewport) {
        // 设置圆柱体位置 (0, 200, 0)
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(0.0, 200.0, 0.0));
        
        TopoDS_Shape cylinder = BRepPrimAPI_MakeCylinder(50.0, 100.0).Shape();
        BRepBuilderAPI_Transform shapeTransform(cylinder, transform);
        cylinder = shapeTransform.Shape();
        
        Handle(AIS_Shape) aisCylinder = new AIS_Shape(cylinder);
        m_viewport->displayEntity(aisCylinder);
    }
}

void MainWindow::createCone()
{
    if (m_viewport) {
        // 设置圆锥位置 (-200, 0, 0)
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(-200.0, 0.0, 0.0));
        
        TopoDS_Shape cone = BRepPrimAPI_MakeCone(50.0, 25.0, 100.0).Shape();
        BRepBuilderAPI_Transform shapeTransform(cone, transform);
        cone = shapeTransform.Shape();
        
        Handle(AIS_Shape) aisCone = new AIS_Shape(cone);
        m_viewport->displayEntity(aisCone);
    }
}

void MainWindow::createTorus()
{
    if (m_viewport) {
        // 设置圆环位置 (0, -200, 0)
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(0.0, -200.0, 0.0));
        
        TopoDS_Shape torus = BRepPrimAPI_MakeTorus(50.0, 20.0).Shape();
        BRepBuilderAPI_Transform shapeTransform(torus, transform);
        torus = shapeTransform.Shape();
        
        Handle(AIS_Shape) aisTorus = new AIS_Shape(torus);
        m_viewport->displayEntity(aisTorus);
    }
}

void MainWindow::createSphere()
{
    if (m_viewport) {
        // 设置球体位置 (0, 0, 200)
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(0.0, 0.0, 200.0));
        
        TopoDS_Shape sphere = BRepPrimAPI_MakeSphere(50.0).Shape();
        BRepBuilderAPI_Transform shapeTransform(sphere, transform);
        sphere = shapeTransform.Shape();
        
        Handle(AIS_Shape) aisSphere = new AIS_Shape(sphere);
        m_viewport->displayEntity(aisSphere);
    }
}

void MainWindow::randomTest()
{
    if (!m_viewport) {
        return;
    }

    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> posDist(-500.0, 500.0);
    std::uniform_real_distribution<> sizeDist(10.0, 100.0);
    std::uniform_int_distribution<> typeDist(0, 10);

    // 用于存储所有生成的形状
    QList<Handle(AIS_Shape)> shapes;

    for (int i = 0; i < 1000; ++i) {
        // 随机位置
        double x = posDist(gen);
        double y = posDist(gen);
        double z = posDist(gen);
        gp_Trsf transform;
        transform.SetTranslation(gp_Vec(x, y, z));

        // 随机类型
        int type = typeDist(gen);
        TopoDS_Shape shape;

        switch (type) {
            case 0: { // 直线
                gp_Pnt p1(0, 0, 0);
                gp_Pnt p2(sizeDist(gen), sizeDist(gen), sizeDist(gen));
                shape = BRepBuilderAPI_MakeEdge(p1, p2).Shape();
                break;
            }
            case 1: { // 圆形
                gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), sizeDist(gen));
                shape = BRepBuilderAPI_MakeEdge(circle).Shape();
                break;
            }
            case 2: { // 多段线
                BRepBuilderAPI_MakePolygon poly;
                poly.Add(gp_Pnt(0, 0, 0));
                poly.Add(gp_Pnt(sizeDist(gen), 0, 0));
                poly.Add(gp_Pnt(sizeDist(gen), sizeDist(gen), 0));
                poly.Add(gp_Pnt(0, sizeDist(gen), 0));
                poly.Close();
                shape = poly.Shape();
                break;
            }
            case 3: { // 平面
                gp_Pln plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
                shape = BRepBuilderAPI_MakeFace(plane, 0, sizeDist(gen), 0, sizeDist(gen)).Shape();
                break;
            }
            case 4: { // 立方体
                shape = BRepPrimAPI_MakeBox(sizeDist(gen), sizeDist(gen), sizeDist(gen)).Shape();
                break;
            }
            case 5: { // 圆柱
                shape = BRepPrimAPI_MakeCylinder(sizeDist(gen), sizeDist(gen)).Shape();
                break;
            }
            case 6: { // 圆台
                shape = BRepPrimAPI_MakeCone(sizeDist(gen), sizeDist(gen)/2, sizeDist(gen)).Shape();
                break;
            }
            case 7: { // 圆环
                shape = BRepPrimAPI_MakeTorus(sizeDist(gen), sizeDist(gen)/4).Shape();
                break;
            }
            case 8: { // 球体
                shape = BRepPrimAPI_MakeSphere(sizeDist(gen)).Shape();
                break;
            }
            case 9: { // 拉伸体
                gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), sizeDist(gen));
                TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
                TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
                TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
                gp_Vec vec(sizeDist(gen), sizeDist(gen), sizeDist(gen));
                shape = BRepPrimAPI_MakePrism(face, vec).Shape();
                break;
            }
            case 10: { // 旋转体
                gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), sizeDist(gen));
                TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
                TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
                TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
                gp_Ax1 axis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
                shape = BRepPrimAPI_MakeRevol(face, axis, M_PI/2).Shape();
                break;
            }
        }

        // 应用随机变换
        BRepBuilderAPI_Transform shapeTransform(shape, transform);
        shape = shapeTransform.Shape();

        // 创建AIS_Shape并添加到列表
        Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
        shapes.append(aisShape);
    }

    // 一次性显示所有形状
    m_viewport->displayEntities(shapes);

    // 调整视图以显示所有内容
    m_viewport->fitAll();
} 