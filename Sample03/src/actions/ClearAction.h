#ifndef CLEAR_ACTION_H
#define CLEAR_ACTION_H

#include "Action.h"

class ClearAction : public Action
{
    Q_OBJECT
public:
    explicit ClearAction(QObject* parent = nullptr);

    QString id() const override;
    QString name() const override;
    QString description() const override;
    QString icon() const override;

    void execute() override;
};

#endif // CLEAR_ACTION_H