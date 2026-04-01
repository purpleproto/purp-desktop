#include "settingsdialog.h"
#include "settingsmanager.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->listSettings->setCurrentRow(0);
    ui->labelCurrentVersion->setText("Version: " APP_VERSION);

    loadSettingsToUI();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_rejected()
{
    this->reject();
}


void SettingsDialog::on_listSettings_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int currentIndex = ui->listSettings->row(current);
    ui->stackedWidget->setCurrentIndex(currentIndex);
}

void SettingsDialog::loadSettingsToUI()
{
    auto config = SettingsManager::instance().generalConfig();

    ui->chkLaunchStartup->setChecked(config.General.Startup.launchStartup);
    ui->chkCloseSysTray->setChecked(config.General.Window.closeToTray);
    ui->chkNotifyStatusChng->setChecked(config.General.Notifications.notifyStatus);
    ui->chkSoundAlerts->setChecked(config.General.Notifications.soundEnabled);
    ui->chkAutoCheckUpdates->setChecked(config.General.Updates.autoCheckUpdates);

    // TODO: Theme Combo Box
    ui->opacitySliderH->setValue(config.Appearance.Theme.opacity);
    // TODO: Font Combo Box
    ui->fontSizeSpinBox->setValue(config.Appearance.Font.size);
    // TODO: Tray Icon Style Combo Box

    ui->MTUSizeSpinBox->setValue(config.Connection.Protocol.mtuSize);
    ui->chkUDPMode->setChecked(config.Connection.Protocol.udpMpde);
    ui->chkTCPMode->setChecked(config.Connection.Protocol.tcpMode);
    // TODO: DNS Provider Combo Box

    ui->chkKillSwitch->setChecked(config.Connection.Security.killSwitch);
    ui->responseTimeoutSpinBox->setValue(config.Connection.Timeout.responseTimeout);
    ui->chkAutoReconnect->setChecked(config.Connection.Timeout.autoReconnect);

    // TODO: Locale Combo Box
    // TODO: Region Format Combo Box
}

void SettingsDialog::saveUItoSettings()
{
    SettingsManager::GeneralConfig config;

    config.General.Startup.launchStartup = ui->chkLaunchStartup->isChecked();
    config.General.Window.closeToTray = ui->chkCloseSysTray->isChecked();
    config.General.Notifications.notifyStatus = ui->chkNotifyStatusChng->isChecked();
    config.General.Notifications.soundEnabled = ui->chkSoundAlerts->isChecked();
    config.General.Updates.autoCheckUpdates = ui->chkAutoCheckUpdates->isChecked();

    config.Appearance.Theme.opacity = ui->opacitySliderH->value();
    config.Appearance.Font.size = ui->fontSizeSpinBox->value();

    config.Connection.Protocol.mtuSize = ui->MTUSizeSpinBox->value();
    config.Connection.Protocol.udpMpde = ui->chkUDPMode->isChecked();
    config.Connection.Protocol.tcpMode = ui->chkTCPMode->isChecked();

    config.Connection.Security.killSwitch = ui->chkKillSwitch->isChecked();
    config.Connection.Timeout.responseTimeout = ui->responseTimeoutSpinBox->value();
    config.Connection.Timeout.autoReconnect = ui->chkAutoReconnect->isChecked();

    SettingsManager::instance().setGeneralConfig(config);
}


void SettingsDialog::on_buttonBox_accepted()
{
    saveUItoSettings();
    this->accept();
}

