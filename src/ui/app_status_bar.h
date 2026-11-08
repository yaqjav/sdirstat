#ifndef SDIRSTAT_APP_STATUS_BAR_H
#define SDIRSTAT_APP_STATUS_BAR_H

#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <QTimer>

class AppStatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit AppStatusBar(QWidget* parent = nullptr);
    void setFolderPath(const QString& path);

private:
    void createStatusBar();
    void updateMemoryUsage() const;

    QLabel* ramLabel{};
    QLabel* folderLabel{};
    QTimer* updateMemoryTimer{};
};

#endif // SDIRSTAT_APP_STATUS_BAR_H
