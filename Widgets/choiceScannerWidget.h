#ifndef CHOICESCANNERWIDGET_H
#define CHOICESCANNERWIDGET_H

#include "common.h"



typedef QMap<QString, QString> Devices;

class ChoiceScannerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceScannerWidget(QWidget *parent = nullptr);
    ~ChoiceScannerWidget();

signals:
// Transfert the name of the scanner
    void scannerSetUp(int id, QString scannerName);

public slots:
// Tools for master widget
    void searchScanner(int id);
// Methods
    void scannerChosen();

private:
    Devices findScanners();

// Object managers of view
    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

// Attributs
    int Id;

};

#endif // CHOICESCANNERWIDGET_H
