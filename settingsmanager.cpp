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
    if (!QFile::exists(m_configPath))
    {
        qDebug() << "Config file not found, creating default...";
        setGeneralConfig(m_generalConfig);
    }

    QSettings s(m_configPath, QSettings::IniFormat);

    s.beginGroup("General");
    m_generalConfig.General.Startup.launchStartup = s.value("launch_startup", false).toBool();
    m_generalConfig.General.Window.closeToTray = s.value("close_to_tray", false).toBool();
    m_generalConfig.General.Notifications.notifyStatus = s.value("notify_status", true).toBool();
    m_generalConfig.General.Notifications.soundEnabled = s.value("notify_sound", true).toBool();
    m_generalConfig.General.Updates.autoCheckUpdates = s.value("check_updates", false).toBool();
    s.endGroup();

    s.beginGroup("Appearance");
    m_generalConfig.Appearance.Theme.mode = s.value("mode", "System").toString();
    m_generalConfig.Appearance.Theme.opacity = s.value("opacity", 100).toInt();
    m_generalConfig.Appearance.Font.family = s.value("font_family", "Segoe UI").toString();
    m_generalConfig.Appearance.Font.size = s.value("font_size", 12).toInt();
    m_generalConfig.Appearance.TrayIcon.style = s.value("tray_icon", "light").toString();
    s.endGroup();

    s.beginGroup("Connection");
    m_generalConfig.Connection.Protocol.mtuSize = s.value("mtu_size", 0).toInt();
    m_generalConfig.Connection.Protocol.udpMpde = s.value("udp_mode", false).toBool();
    m_generalConfig.Connection.Protocol.tcpMode = s.value("tcp_mode", false).toBool();
    m_generalConfig.Connection.Security.dnsProvider = s.value("dns_provider", "").toString();
    m_generalConfig.Connection.Security.killSwitch = s.value("kill_switch", false).toBool();
    m_generalConfig.Connection.Timeout.responseTimeout = s.value("response_timeout", 0).toInt();
    m_generalConfig.Connection.Timeout.autoReconnect = s.value("auto_reconnect", false).toInt();
    s.endGroup();

    s.beginGroup("Langauge");
    m_generalConfig.Language.locale = s.value("locale", "English").toString();
    m_generalConfig.Language.regionFormat = s.value("region_format", "en-US").toString();
    s.endGroup();

    qDebug() << "Settings init from:" << m_configPath;
}

void SettingsManager::setGeneralConfig(const GeneralConfig &config)
{
    m_generalConfig = config;

    QSettings s(m_configPath, QSettings::IniFormat);

    s.beginGroup("General");
    s.setValue("launch_startup", config.General.Startup.launchStartup);
    s.setValue("close_to_tray", config.General.Window.closeToTray);
    s.setValue("notify_status", config.General.Notifications.notifyStatus);
    s.setValue("notify_sound", config.General.Notifications.soundEnabled);
    s.setValue("check_updates", config.General.Updates.autoCheckUpdates);
    s.endGroup();

    s.beginGroup("Appearance");
    s.setValue("mode", config.Appearance.Theme.mode);
    s.setValue("opacity", config.Appearance.Theme.opacity);
    s.setValue("font_family", config.Appearance.Font.family);
    s.setValue("font_size", config.Appearance.Font.size);
    s.setValue("tray_icon", config.Appearance.TrayIcon.style);
    s.endGroup();

    s.beginGroup("Connection");
    s.setValue("mtu_size", config.Connection.Protocol.mtuSize);
    s.setValue("udp_mode", config.Connection.Protocol.udpMpde);
    s.setValue("tcp_mode", config.Connection.Protocol.tcpMode);
    s.setValue("dns_provider", config.Connection.Security.dnsProvider);
    s.setValue("kill_switch", config.Connection.Security.killSwitch);
    s.setValue("response_timeout", config.Connection.Timeout.responseTimeout);
    s.setValue("auto_reconnect", config.Connection.Timeout.autoReconnect);
    s.endGroup();

    s.beginGroup("Language");
    s.setValue("locale", config.Language.locale);
    s.setValue("region_format", config.Language.regionFormat);
    s.endGroup();

    s.sync();
}

SettingsManager::GeneralConfig SettingsManager::generalConfig() const
{
    return m_generalConfig;
}