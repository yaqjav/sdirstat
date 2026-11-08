#include "app_menu_bar.h"

#include <QAction>
#include <QMenu>

AppMenuBar::AppMenuBar(QWidget* parent)
    : QMenuBar(parent)
{
    setStyleSheet(
        "QMenuBar { padding: 0px; }"
        "QMenuBar::item { padding: 1px 6px; }"
    );
    createMenus();
    createActions();
}

void AppMenuBar::createMenus()
{
    fileMenu = addMenu("Plik");
    helpMenu = addMenu("Pomoc");
}

void AppMenuBar::createActions()
{
    chooseDiskAct = new QAction("Wybierz dysk", this);
    chooseFolderAct = new QAction("Wybierz folder", this);
    cancelScanningAct = new QAction("Anuluj skanowanie", this);
    exitAct = new QAction("Zamknij", this);
    importAct = new QAction("Importuj dane skanowania z CSV/JSON", this);
    exportAct = new QAction("Eksportuj dane skanowania do CSV/JSON", this);

    fileMenu->addAction(chooseDiskAct);
    fileMenu->addAction(chooseFolderAct);
    fileMenu->addAction(cancelScanningAct);
    fileMenu->addSeparator();
    fileMenu->addAction(importAct);
    fileMenu->addAction(exportAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    aboutAct = new QAction("O programie", this);
    helpMenu->addAction(aboutAct);

    connect(chooseDiskAct, &QAction::triggered,
            this, &AppMenuBar::chooseDiskRequested);
    connect(chooseFolderAct, &QAction::triggered,
            this, &AppMenuBar::chooseFolderRequested);
    connect(cancelScanningAct, &QAction::triggered,
            this, &AppMenuBar::cancelScanRequested);
    connect(exitAct, &QAction::triggered,
            this, &AppMenuBar::exitRequested);
}
