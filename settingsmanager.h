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
        bool autostart;
        bool closeToTray;
        bool notifyStatus;
        bool soundEnabled;
        bool autoCheckUpdates;
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