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
    Devices listScanners(QString rawList);

// Object managers of view
    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* subTitleLabel;
// Attributs
    int Id;

    void viewStyle();
};

#endif // CHOICESCANNERWIDGET_H
