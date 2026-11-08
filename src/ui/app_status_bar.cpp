#include "app_status_bar.h"
#include "utils/size_tools.h"

#include <Windows.h>
#include <Psapi.h>

AppStatusBar::AppStatusBar(QWidget* parent)
    : QStatusBar(parent)
{
    createStatusBar();

    updateMemoryTimer = new QTimer(this);
    connect(updateMemoryTimer, &QTimer::timeout,
            this, &AppStatusBar::updateMemoryUsage);
    updateMemoryUsage();
    updateMemoryTimer->start(1000);
}

void AppStatusBar::createStatusBar()
{
    folderLabel = new QLabel("Nie wybrano folderu", this);
    ramLabel = new QLabel("Użycie RAM: Oczekiwanie...", this);
    addPermanentWidget(folderLabel, 1);
    addPermanentWidget(ramLabel);
}

void AppStatusBar::setFolderPath(const QString& path)
{
    folderLabel->setText(path);
}

void AppStatusBar::updateMemoryUsage() const
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
    ramLabel->setText(memSize);
}
