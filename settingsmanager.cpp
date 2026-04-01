#include "settingsmanager.h"

#include <QCoreApplication>
#include <QDir>
#include <QDebug>


SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    m_configPath = QCoreApplication::applicationDirPath() + "/config.ini";
}

SettingsManager &SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

void SettingsManager::init()
{
    QSettings s(m_configPath, QSettings::IniFormat);

    s.beginGroup("General");
    m_generalConfig.autostart = s.value("autostart", true).toBool();
    m_generalConfig.closeToTray = s.value("close_to_tray", true).toBool();
    s.endGroup();

    s.beginGroup("Notifications");
    m_generalConfig.notifyStatus = s.value("notify_status", true).toBool();
    m_generalConfig.soundEnabled = s.value("sound_enabled", true).toBool();
    s.endGroup();

    s.beginGroup("Updates");
    m_generalConfig.autoCheckUpdates = s.value("auto_check", true).toBool();
    s.endGroup();

    qDebug() << "Settings init from:" << m_configPath;
}

void SettingsManager::setGeneralConfig(const GeneralConfig &config)
{
    m_generalConfig = config;

    QSettings s(m_configPath, QSettings::IniFormat);

    s.beginGroup("General");
    s.setValue("autostart", m_generalConfig.autostart);
    s.setValue("close_to_tray", m_generalConfig.closeToTray);
    s.endGroup();

    s.beginGroup("Notifications");
    s.setValue("notify_status", m_generalConfig.notifyStatus);
    s.setValue("sound_enabled", m_generalConfig.soundEnabled);
    s.endGroup();

    s.beginGroup("Updates");
    s.setValue("auto_check", m_generalConfig.autoCheckUpdates);
    s.endGroup();

    s.sync();
}

SettingsManager::GeneralConfig SettingsManager::generalConfig() const
{
    return m_generalConfig;
}