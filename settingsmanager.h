#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QSettings>
#include <QString>


class SettingsManager : public QObject
{
    Q_OBJECT
public:
    struct GeneralConfig
    {
        struct General
        {
            struct Startup
            {
                bool launchStartup;
            } Startup;

            struct Window
            {
                bool closeToTray;
            } Window;

            struct Notifications
            {
                bool notifyStatus;
                bool soundEnabled;
            } Notifications;

            struct Updates
            {
                bool autoCheckUpdates;
            } Updates;
        } General;

        struct Appearance
        {
            struct Theme
            {
                QString mode;
                int opacity;
            } Theme;

            struct Font
            {
                QString family;
                int size;
            } Font;

            struct TrayIcon
            {
                QString style;
            } TrayIcon;
        } Appearance;

        struct Connection
        {
            struct Protocol
            {
                int mtuSize;
                bool udpMpde;
                bool tcpMode;
            } Protocol;

            struct Security
            {
                QString dnsProvider;
                bool killSwitch;
            } Security;

            struct Timeout
            {
                int responseTimeout;
                bool autoReconnect;
            } Timeout;
        } Connection;

        struct Language
        {
            QString locale;
            QString regionFormat;
        } Language;
    };

    static SettingsManager &instance();

    void init();
    void setGeneralConfig(const GeneralConfig &config);
    GeneralConfig generalConfig() const;
private:
    explicit SettingsManager(QObject *parent = nullptr);
    ~SettingsManager() = default;

    Q_DISABLE_COPY(SettingsManager)

    GeneralConfig m_generalConfig;
    QString m_configPath;
};

#endif // SETTINGSMANAGER_H