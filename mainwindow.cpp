#include "mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("SDirStat");
    resize(1000, 650);

    createMenus();
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

void MainWindow::closeApplication()
{
    close();
}

void MainWindow::createActions()
{
    // fileMenu Actions
    chooseDiskAct = new QAction("Wybierz dysk");
    chooseFolderAct = new QAction("Wybierz folder");
    cancelScanningAct = new QAction("Anuluj skanowanie");
    exitAct = new QAction("Zamknij");
    importAct = new QAction("Importuj dane skanowania z CSV/JSON");
    exportAct = new QAction("Eskportuj dane skanowania do CSV/JSON");
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
}

void MainWindow::createStatusBar()
{

}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // Obs³uga menu pod prawym przyciskiem myszy.
    // Na obecnym etapie zostawiamy j¹ pust¹.
}
#endif