#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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

private:
	void createActions();
	void createMenus();
	void createStatusBar();
	void closeApplication();
	void updateMemoryUsage();
	void chooseFolder();
	// menu bar
	QMenuBar* menuBar;
	// file menu
	QMenu* fileMenu;
	QAction* chooseFolderAct;
	QAction* chooseDiskAct;
	QAction* cancelScanningAct;
	QAction* importAct;
	QAction* exportAct;
	QAction* exitAct;
	// help menu
	QMenu* helpMenu;
	QAction* aboutAct;
	// status bar
	QLabel* ramLabel;
	QTimer* updateMemoryTimer;
	// selected folder
	QLabel* folderLabel;
	QString selectedFolder;
};
#endif // MAINWINDOW_H
