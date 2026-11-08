#ifndef SDIRSTAT_APP_MENU_BAR_H
#define SDIRSTAT_APP_MENU_BAR_H

#include <QMenuBar>

class AppMenuBar : public QMenuBar
{
    Q_OBJECT

public:
    explicit AppMenuBar(QWidget* parent = nullptr);

signals:
    void chooseDiskRequested();
    void chooseFolderRequested();
    void cancelScanRequested();
    void exitRequested();

private:
    void createMenus();
    void createActions();

    QMenu* fileMenu{};
    QMenu* helpMenu{};
    QAction* chooseDiskAct{};
    QAction* chooseFolderAct{};
    QAction* cancelScanningAct{};
    QAction* importAct{};
    QAction* exportAct{};
    QAction* exitAct{};
    QAction* aboutAct{};
};

#endif // SDIRSTAT_APP_MENU_BAR_H
