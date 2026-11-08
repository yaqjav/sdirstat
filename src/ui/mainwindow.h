#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFutureWatcher>
#include "../scanning/scanner.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow() override;

protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent* event) override;
#endif // QT_NO_CONTEXTMENU
    void closeEvent(QCloseEvent* event) override;

private:

	void closeApplication();
	void chooseFolder();
    void cancelScanning();
    QFutureWatcher<ScanResult>* scanWatcher = nullptr;
    void onScanFinished();






};
#endif // MAINWINDOW_H
