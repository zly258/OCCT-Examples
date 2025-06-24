#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

#include "ActionFactory.h"

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action(QObject *parent = nullptr);
    virtual ~Action() = default;

    // 基本属性
    virtual QString id() const = 0;
    virtual QString name() const;
    virtual QString description() const;
    virtual QString icon() const;
    virtual bool isEnabled() const;
    virtual bool isVisible() const;

    // 配置相关
    void setConfig(const QJsonObject& config);
    QJsonObject config() const;

    // 执行接口
    virtual void execute() = 0;
    virtual void cleanup() {}  // 默认实现为空

protected:
    QString getConfigString(const QString& key, const QString& defaultValue = QString()) const;
    bool getConfigBool(const QString& key, bool defaultValue = true) const;
    QJsonObject getConfigObject(const QString& key) const;
    QJsonArray getConfigArray(const QString& key) const;

private:
    QJsonObject m_config;
};

#endif // ACTION_H 