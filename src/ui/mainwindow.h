#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QFutureWatcher>
#include <QMainWindow>
#include <QString>

#include "app_menu_bar.h"
#include "app_status_bar.h"
#include "scanning/scanner.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QContextMenuEvent* event) override;
#endif
    void closeEvent(QCloseEvent* event) override;

private:
    void closeApplication();
    void chooseFolder();
    void cancelScanning();
    void onScanFinished();

    AppMenuBar* appMenuBar{};
    AppStatusBar* appStatusBar{};
    QFutureWatcher<ScanResult>* scanWatcher{};
    QString selectedFolder;
};

#endif // MAINWINDOW_H
