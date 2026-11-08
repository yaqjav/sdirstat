#include "mainwindow.h"
#include "utils/size_tools.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrentRun>

#include "dialogs/sourcedialog.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle("SDirStat");
    resize(1000, 650);

    appMenuBar = new AppMenuBar(this);
    setMenuBar(appMenuBar);
    appStatusBar = new AppStatusBar(this);
    setStatusBar(appStatusBar);

    connect(appMenuBar, &AppMenuBar::chooseDiskRequested,
                this, &MainWindow::chooseDisk);
    connect(appMenuBar, &AppMenuBar::chooseFolderRequested,
            this, &MainWindow::chooseFolder);
    connect(appMenuBar, &AppMenuBar::cancelScanRequested,
            this, &MainWindow::cancelScanning);
    connect(appMenuBar, &AppMenuBar::exitRequested,
            this, &MainWindow::closeApplication);

    scanWatcher = new QFutureWatcher<ScanResult>(this);
    connect(scanWatcher, &QFutureWatcher<ScanResult>::finished,
            this, &MainWindow::onScanFinished);
}

MainWindow::~MainWindow() = default;

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (scanWatcher->isRunning())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "SDirStat",
            "Skanowanie jest w toku, czy chcesz je przerwać?",
            QMessageBox::Yes | QMessageBox::No
        );
        if (reply == QMessageBox::Yes)
        {
            scanWatcher->cancel();
            QMainWindow::closeEvent(event);
        }
        else
            event->ignore();
    }
}

void MainWindow::closeApplication()
{
    close();
}

void MainWindow::chooseDisk()
{
    SourceDialog dialog(this);
    dialog.exec();
}

void MainWindow::chooseFolder()
{
    if (scanWatcher->isRunning()) return;

    selectedFolder = QFileDialog::getExistingDirectory(this, tr("Wybierz folder skanowania"),
                                                       QDir::homePath(),
                                                       QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);

    if (selectedFolder.isEmpty())
    {
        return;
    }
    else
    {
        appStatusBar->setFolderPath(selectedFolder);
        scanWatcher->setFuture(
            QtConcurrent::run(scanFolder, selectedFolder)
        );
    }
}

void MainWindow::cancelScanning()
{
    if (scanWatcher->isRunning())
    {
        scanWatcher->cancel();
        QMessageBox::warning(
            this,
            "SDirStat",
            "Zatrzymano skanowanie!"
        );
    }
    else
    {
        QMessageBox::information(
            this,
            "SDirStat",
            "Skanowanie nie jest w toku!"
        );
    }
}

void MainWindow::onScanFinished()
{
    if (scanWatcher->isCanceled()) return;
    const ScanResult result = scanWatcher->result();
    qDebug() << "path: " << selectedFolder << " :: size: " << getSizeWithUnit(result.totalBytes) << " :: amount: " <<
        result.fileCount << "\n";
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // Obsługa menu pod prawym przyciskiem myszy.
    // Na obecnym etapie zostawiamy ją pustą.
}
#endif
