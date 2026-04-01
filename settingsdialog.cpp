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

    ui->chkLaunchStartup->setChecked(config.autostart);
    ui->chkAutoCheckUpdates->setChecked(config.autoCheckUpdates);
    ui->chkCloseSysTray->setChecked(config.closeToTray);
    ui->chkNotifyStatusChng->setChecked(config.notifyStatus);
    ui->chkSoundAlerts->setChecked(config.soundEnabled);
}

void SettingsDialog::saveUItoSettings()
{
    SettingsManager::GeneralConfig config;

    config.autostart = ui->chkLaunchStartup->isChecked();
    config.closeToTray = ui->chkCloseSysTray->isChecked();
    config.notifyStatus = ui->chkNotifyStatusChng->isChecked();
    config.soundEnabled = ui->chkSoundAlerts->isChecked();
    config.autoCheckUpdates = ui->chkAutoCheckUpdates->isChecked();

    SettingsManager::instance().setGeneralConfig(config);
}


void SettingsDialog::on_buttonBox_accepted()
{
    saveUItoSettings();
    this->accept();
}

