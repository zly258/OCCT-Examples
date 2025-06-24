#ifndef RANDOM_TEST_ACTION_H
#define RANDOM_TEST_ACTION_H

#include "Action.h"
#include <TopoDS_Shape.hxx>

class RandomTestAction : public Action
{
    Q_OBJECT
public:
    explicit RandomTestAction(QObject* parent = nullptr);

    QString id() const override { return "RandomTest"; }
    QString name() const override { return tr("随机测试"); }
    QString description() const override { return tr("创建随机形状进行测试"); }
    QString icon() const override { return ":/icons/random.png"; }

    void execute() override;

private:
    TopoDS_Shape createRandomShape(int type, double size) const;
};

#endif // RANDOM_TEST_ACTION_H 