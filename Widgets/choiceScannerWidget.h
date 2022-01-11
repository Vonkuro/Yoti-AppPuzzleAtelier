#ifndef CHOICESCANNERWIDGET_H
#define CHOICESCANNERWIDGET_H

#include "common.h"

#include <QWidget>
#include <QtWidgets>

typedef QMap<QString, QString> Devices;

class ChoiceScannerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceScannerWidget(QWidget *parent = nullptr);
    ~ChoiceScannerWidget();

signals:
    void scannerSetUp(int id, QString scannerName);

public slots:
    void searchScanner(int id);
    void scannerChosen();

private:
    Devices findScanners();

    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

    int Id;

};

#endif // CHOICESCANNERWIDGET_H
