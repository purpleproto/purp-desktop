#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include "settingsmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *settingsDialog = new SettingsDialog;
    settingsDialog->show();
}

void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/logo"));
    trayIcon->setToolTip("PurP");

    trayMenu = new QMenu(this);
    QAction *restoreAction = trayMenu->addAction(tr("Open"));
    QAction *settingsAction = trayMenu->addAction(tr("Settings"));
    trayMenu->addSeparator();
    QAction *quitAction = trayMenu->addAction(tr("Quit"));

    connect(restoreAction, &QAction::triggered, this, &MainWindow::showNormal);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::on_actionSettings_triggered);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();

    connect(trayIcon,
            &QSystemTrayIcon::activated,
            this, [this](QSystemTrayIcon::ActivationReason reason) {
                if (reason == QSystemTrayIcon::DoubleClick) {
                    this->showNormal();
                    this->activateWindow();
                }
    });
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    auto config = SettingsManager::instance().generalConfig();

    if (trayIcon->isVisible() && config.General.Window.closeToTray)
    {
        this->hide();
        event->ignore();

        trayIcon->showMessage("PurP",
                              tr("Application minimized to tray"),
                              QSystemTrayIcon::Information, 2000);
    }
    else
    {
        event->accept();
    }
}