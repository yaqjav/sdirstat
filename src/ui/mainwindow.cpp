#include "../../mainwindow.h"
#include "../utils/size_tools.h"
#include "../scanning/scanner.h"
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QDirListing>
#include <QCloseEvent>
#include <QtConcurrentRun>
#include <QDir>
#include <QFlags>
#include <QDebug>
#include <Windows.h>
#include <Psapi.h>
#include <string>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("SDirStat");
    resize(1000, 650);

    createMenus();
    createStatusBar();

    // RAM Usage Timer
    updateMemoryTimer = new QTimer(this);
    connect(updateMemoryTimer, &QTimer::timeout,
            this, &MainWindow::updateMemoryUsage);
    updateMemoryUsage();
    updateMemoryTimer->start(1000);

    scanWatcher = new QFutureWatcher<ScanResult>(this);
    connect(scanWatcher, &QFutureWatcher<ScanResult>::finished,
            this, &MainWindow::onScanFinished);
}

MainWindow::~MainWindow() = default;

void MainWindow::createMenus()
{
    menuBar = new QMenuBar(this);
    menuBar->setStyleSheet(
        "QMenuBar { padding: 0px; }"
        "QMenuBar::item { padding: 1px 6px; }"
    );
    fileMenu = new QMenu("Plik");
    helpMenu = new QMenu("Pomoc");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);

    setMenuBar(menuBar);
    createActions();
}

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
        } else
            event->ignore();
    }
}

void MainWindow::closeApplication()
{
    close();
}

void MainWindow::updateMemoryUsage() const
{
    PROCESS_MEMORY_COUNTERS memory{};
    memory.cb = sizeof(memory);
    BOOL success = GetProcessMemoryInfo(
        GetCurrentProcess(),
        &memory,
        sizeof(memory)
    );

    if (!success)
    {
        ramLabel->setText("Użycie RAM: Błąd pobierania danych");
        return;
    }

    QString memSize = "Użycie RAM: " + getSizeWithUnit(static_cast<qint64>(memory.WorkingSetSize));
    ramLabel->setText(memSize); // Memory size in MiB
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
        folderLabel->setText(selectedFolder);
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
    } else
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

void MainWindow::createActions()
{
    // fileMenu Actions
    chooseDiskAct = new QAction("Wybierz dysk");
    chooseFolderAct = new QAction("Wybierz folder");
    cancelScanningAct = new QAction("Anuluj skanowanie");
    exitAct = new QAction("Zamknij");
    importAct = new QAction("Importuj dane skanowania z CSV/JSON");
    exportAct = new QAction("Eksportuj dane skanowania do CSV/JSON");
    fileMenu->addAction(chooseDiskAct);
    fileMenu->addAction(chooseFolderAct);
    fileMenu->addAction(cancelScanningAct);
    fileMenu->addSeparator();
    fileMenu->addAction(importAct);
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    // helpMenu Actions
    aboutAct = new QAction("O programie");
    helpMenu->addAction(aboutAct);

    connect(exitAct, &QAction::triggered, this, &MainWindow::closeApplication);
    connect(chooseFolderAct, &QAction::triggered, this, &MainWindow::chooseFolder);
    connect(cancelScanningAct, &QAction::triggered, this, &MainWindow::cancelScanning);
}

void MainWindow::createStatusBar()
{
    folderLabel = new QLabel("Nie wybrano folderu");
    ramLabel = new QLabel("Użycie RAM: Oczekiwanie...");
    statusBar()->addPermanentWidget(folderLabel, 1);
    statusBar()->addPermanentWidget(ramLabel);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // Obsługa menu pod prawym przyciskiem myszy.
    // Na obecnym etapie zostawiamy ją pustą.
}
#endif
