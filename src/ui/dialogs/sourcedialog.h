#ifndef SDIRSTAT_SOURCEDIALOG_H
#define SDIRSTAT_SOURCEDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QTreeWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>

class SourceDialog : public QDialog
{
public:
    explicit SourceDialog(QWidget* parent = nullptr);
    ~SourceDialog() override;
private:
    QRadioButton* choiceRadio{};
    QTreeWidget* diskTree = nullptr;
    QLineEdit* pathBox = nullptr;
    QPushButton* exploreButton = nullptr;
    QDialogButtonBox* confirmButtons{};
};


#endif //SDIRSTAT_SOURCEDIALOG_H
