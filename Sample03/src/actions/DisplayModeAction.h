#ifndef DISPLAY_MODE_ACTION_H
#define DISPLAY_MODE_ACTION_H

#include "Action.h"

class DisplayModeAction : public Action
{
    Q_OBJECT
public:
    explicit DisplayModeAction(int mode, QObject* parent = nullptr);

    QString id() const override { return m_mode == 0 ? "WireframeMode" : "ShadedMode"; }
    QString name() const override { return m_mode == 0 ? tr("线框") : tr("填充"); }
    QString description() const override { return m_mode == 0 ? tr("切换到线框模式") : tr("切换到填充模式"); }
    QString icon() const override { return m_mode == 0 ? ":/icons/wireframe.png" : ":/icons/shaded.png"; }

    void execute() override;

private:
    int m_mode;  // 0: 线框模式, 1: 填充模式
};

#endif // DISPLAY_MODE_ACTION_H 