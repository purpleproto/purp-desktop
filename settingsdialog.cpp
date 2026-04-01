#include "settingsdialog.h"
#include "settingsmanager.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->listSettings->setCurrentRow(0);
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

