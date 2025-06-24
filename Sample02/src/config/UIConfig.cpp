#include "UIConfig.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QDebug>

UIConfig* UIConfig::s_instance = nullptr;

UIConfig* UIConfig::instance()
{
    if (!s_instance) {
        s_instance = new UIConfig();
    }
    return s_instance;
}

UIConfig::UIConfig()
    : QObject(nullptr)
{
    // 尝试加载配置文件
    if (!loadConfig(":/config/ui_config.json")) {
        qWarning() << "无法加载UI配置文件，请检查配置文件是否存在且格式正确";
    }
}

UIConfig::~UIConfig()
{
    s_instance = nullptr;
}

void UIConfig::collectActions(const QJsonValue& value, QMap<QString, QJsonObject>& actions)
{
    if (value.isObject()) {
        QJsonObject obj = value.toObject();
        if (obj.contains("action")) {
            // 这是一个动作项
            QString actionId = obj["action"].toString();
            actions[actionId] = obj;
        } else if (obj.contains("items")) {
            // 这是一个菜单或子菜单，递归处理其items
            QJsonArray items = obj["items"].toArray();
            for (const QJsonValue& item : items) {
                collectActions(item, actions);
            }
        }
    } else if (value.isArray()) {
        // 处理数组
        QJsonArray array = value.toArray();
        for (const QJsonValue& item : array) {
            collectActions(item, actions);
        }
    }
}

bool UIConfig::loadConfig(const QString& configFile)
{
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开配置文件:" << configFile;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "配置文件格式错误:" << configFile;
        return false;
    }

    QJsonObject config = doc.object();
    
    // 加载菜单配置
    if (config.contains("menus") && config["menus"].isObject()) {
        m_menuConfig = config["menus"].toObject();
    } else {
        qWarning() << "配置文件缺少菜单配置";
        return false;
    }

    // 加载工具栏配置
    if (config.contains("toolbars") && config["toolbars"].isObject()) {
        m_toolBarConfig = config["toolbars"].toObject();
    }

    // 收集所有动作配置
    collectActions(m_menuConfig, m_actionConfigs);
    if (!m_toolBarConfig.isEmpty()) {
        collectActions(m_toolBarConfig, m_actionConfigs);
    }

    return true;
}

QJsonObject UIConfig::getMenuConfig() const
{
    return m_menuConfig;
}

QJsonObject UIConfig::getToolBarConfig() const
{
    return m_toolBarConfig;
}

QJsonObject UIConfig::getActionConfig(const QString& actionId) const
{
    return m_actionConfigs.value(actionId);
}

QList<QString> UIConfig::getRegisteredActions() const
{
    return m_actionConfigs.keys();
} 