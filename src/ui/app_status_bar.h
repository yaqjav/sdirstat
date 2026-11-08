//
// Created by Kuba on 5.11.2026.
//

#ifndef SDIRSTAT_APP_STATUS_BAR_H
#define SDIRSTAT_APP_STATUS_BAR_H

#include <QString>
#include <QTimer>
#include <QLabel>
#include <QStatusBar>

class app_status_bar : public QStatusBar
{
public:
    void createStatusBar();
	void updateMemoryUsage() const;

private:
    // status bar
    QLabel* ramLabel{};
    QTimer* updateMemoryTimer;
    // selected folder
    QLabel* folderLabel{};
    QString selectedFolder;
};


#endif //SDIRSTAT_APP_STATUS_BAR_H
