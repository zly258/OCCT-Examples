#include "Action.h"

Action::Action(QObject *parent) : QObject(parent)
{
}

QString Action::name() const
{
    return getConfigString("name", id());
}

QString Action::description() const
{
    return getConfigString("description");
}

QString Action::icon() const
{
    return getConfigString("icon");
}

bool Action::isEnabled() const
{
    return getConfigBool("enabled", true);
}

bool Action::isVisible() const
{
    return getConfigBool("visible", true);
}

void Action::setConfig(const QJsonObject& config)
{
    m_config = config;
}

QJsonObject Action::config() const
{
    return m_config;
}

QString Action::getConfigString(const QString& key, const QString& defaultValue) const
{
    return m_config.contains(key) ? m_config[key].toString() : defaultValue;
}

bool Action::getConfigBool(const QString& key, bool defaultValue) const
{
    return m_config.contains(key) ? m_config[key].toBool() : defaultValue;
}

QJsonObject Action::getConfigObject(const QString& key) const
{
    return m_config.contains(key) ? m_config[key].toObject() : QJsonObject();
}

QJsonArray Action::getConfigArray(const QString& key) const
{
    return m_config.contains(key) ? m_config[key].toArray() : QJsonArray();
} 