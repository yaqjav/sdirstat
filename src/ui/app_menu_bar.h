//
// Created by Kuba on 5.11.2026.
//

#ifndef SDIRSTAT_APP_MENU_BAR_H
#define SDIRSTAT_APP_MENU_BAR_H

#include <QMenuBar>

class app_menu_bar : public QMenuBar
{
public:
    void createMenus();
    void createActions();

private:
    // menu bar
    QMenuBar* menuBar{};
    // file menu
    QMenu* fileMenu{};
    QAction* chooseDiskAct{};
    QAction* chooseFolderAct{};
    QAction* cancelScanningAct{};
    QAction* importAct{};
    QAction* exportAct{};
    QAction* exitAct{};
    // help menu
    QMenu* helpMenu{};
    QAction* aboutAct{};
};


#endif //SDIRSTAT_APP_MENU_BAR_H
