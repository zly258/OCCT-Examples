#ifndef SIMPLE_ENTITY_H
#define SIMPLE_ENTITY_H

#include <QObject>
#include <QJsonObject>
#include <TopoDS_Shape.hxx>
#include <AIS_Shape.hxx>
#include <QDebug>
#include <gp_Pnt.hxx>

class SimpleEntity : public QObject
{
    Q_OBJECT
public:
    SimpleEntity(QObject *parent = nullptr);
    virtual ~SimpleEntity();

    // 外形相关
    TopoDS_Shape shape() const;
    void setShape(const TopoDS_Shape &shape);

    // 位置信息
    double x() const;
    double y() const;
    double z() const;
    void setPosition(double x, double y, double z);

    // 序列化与反序列化
    virtual void serialize(QJsonObject &json) const;
    virtual void deserialize(const QJsonObject &json);

    // 创建 AIS_Shape 对象
    Handle(AIS_Shape) createAISShape();

protected:
    virtual void updateShape() = 0;
    TopoDS_Shape m_shape; // 存储外形
    double m_x, m_y, m_z; // 存储位置信息
};

#endif // SIMPLE_ENTITY_H