#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

class UIConfig : public QObject
{
    Q_OBJECT
public:
    static UIConfig* instance();

    bool loadConfig(const QString& configFile);
    QJsonObject getMenuConfig() const;
    QJsonObject getToolBarConfig() const;
    QJsonObject getActionConfig(const QString& actionId) const;
    QList<QString> getRegisteredActions() const;

private:
    UIConfig();
    ~UIConfig();
    void initMenuConfig();
    void initToolBarConfig();
    void collectActions(const QJsonValue& value, QMap<QString, QJsonObject>& actions);

    static UIConfig* s_instance;
    QJsonObject m_config;
    QJsonObject m_menuConfig;
    QJsonObject m_toolBarConfig;
    QMap<QString, QJsonObject> m_actionConfigs;
};

#endif // UI_CONFIG_H 