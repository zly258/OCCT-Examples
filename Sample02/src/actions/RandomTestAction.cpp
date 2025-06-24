#include "RandomTestAction.h"
#include <random>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <gp_Circ.hxx>
#include <gp_Ax2.hxx>
#include <AIS_Shape.hxx>
#include "core/Viewport.h"
#include "core/ViewportManager.h"

RandomTestAction::RandomTestAction(QObject* parent)
    : Action(parent)
{
}

void RandomTestAction::execute()
{
    if (Viewport* viewport = ViewportManager::instance()->activeViewport()) {
        // 随机数生成器
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> posDist(-500.0, 500.0);
        std::uniform_real_distribution<> sizeDist(10.0, 100.0);
        std::uniform_int_distribution<> typeDist(0, 10);

        // 用于存储所有生成的形状
        QList<Handle(AIS_Shape)> shapes;

        // 生成1000个随机形状
        for (int i = 0; i < 1000; ++i) {
            // 随机位置
            double x = posDist(gen);
            double y = posDist(gen);
            double z = posDist(gen);
            gp_Trsf transform;
            transform.SetTranslation(gp_Vec(x, y, z));

            // 创建随机形状
            TopoDS_Shape shape = createRandomShape(typeDist(gen), sizeDist(gen));

            // 应用变换
            BRepBuilderAPI_Transform shapeTransform(shape, transform);
            shape = shapeTransform.Shape();

            // 创建AIS_Shape并添加到列表
            Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
            shapes.append(aisShape);
        }

        // 一次性显示所有形状
        viewport->displayEntities(shapes);
        viewport->fitAll();
    }
}

TopoDS_Shape RandomTestAction::createRandomShape(int type, double size) const
{
    switch (type) {
    case 0: { // 直线
        gp_Pnt p1(0, 0, 0);
        gp_Pnt p2(size, size, size);
        return BRepBuilderAPI_MakeEdge(p1, p2).Shape();
    }
    case 1: { // 圆形
        gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), size);
        return BRepBuilderAPI_MakeEdge(circle).Shape();
    }
    case 2: { // 多段线
        BRepBuilderAPI_MakePolygon poly;
        poly.Add(gp_Pnt(0, 0, 0));
        poly.Add(gp_Pnt(size, 0, 0));
        poly.Add(gp_Pnt(size, size, 0));
        poly.Add(gp_Pnt(0, size, 0));
        poly.Close();
        return poly.Shape();
    }
    case 3: { // 平面
        gp_Pln plane(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
        return BRepBuilderAPI_MakeFace(plane, 0, size, 0, size).Shape();
    }
    case 4: { // 立方体
        return BRepPrimAPI_MakeBox(size, size, size).Shape();
    }
    case 5: { // 圆柱
        return BRepPrimAPI_MakeCylinder(size/2, size).Shape();
    }
    case 6: { // 圆台
        return BRepPrimAPI_MakeCone(size, size/2, size).Shape();
    }
    case 7: { // 圆环
        return BRepPrimAPI_MakeTorus(size, size/4).Shape();
    }
    case 8: { // 球体
        return BRepPrimAPI_MakeSphere(size).Shape();
    }
    case 9: { // 拉伸体
        gp_Circ circle(gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), size/2);
        TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
        TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
        TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
        return BRepPrimAPI_MakePrism(face, gp_Vec(0, 0, size)).Shape();
    }
    case 10: { // 旋转体
        gp_Circ circle(gp_Ax2(gp_Pnt(size/2, 0, 0), gp_Dir(0, 0, 1)), size/4);
        TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
        TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge).Wire();
        TopoDS_Face face = BRepBuilderAPI_MakeFace(wire).Face();
        return BRepPrimAPI_MakeRevol(face, gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), M_PI/2).Shape();
    }
    default:
        return BRepPrimAPI_MakeBox(size, size, size).Shape();
    }
} 