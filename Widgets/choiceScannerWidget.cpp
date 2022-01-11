#include "choiceScannerWidget.h"

ChoiceScannerWidget::ChoiceScannerWidget(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;

    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

    connect(choiceButton, &QPushButton::clicked, this, &ChoiceScannerWidget::scannerChosen);
}

ChoiceScannerWidget::~ChoiceScannerWidget()
{
    delete choiceCombobox;
    delete choiceButton;
    delete widgetLayout;
}

void ChoiceScannerWidget::searchScanner(int id)
{
    Id = id;

    Devices deviceList = findScanners();
    for ( Devices::iterator i = deviceList.begin() ; i!=deviceList.end() ; ++i)
    {
        choiceCombobox->addItem( i.key(), QVariant(i.value()) );
    }

}

Devices ChoiceScannerWidget::findScanners()
{
    QString scanimageOutput = QString::fromStdString(execute("scanimage -L"));
    scanimageOutput = scanimageOutput.simplified();
    QStringList deviceListOutput = scanimageOutput.split("`");

    Devices deviceList;

    for ( QString substring : deviceListOutput)
    {
        if (substring.contains("'"))
        {
            QString deviceName = substring.split("'")[0];

            QString deviceDescription = substring.split("'")[1];
            deviceDescription = deviceDescription.mid(5);
            deviceDescription = deviceDescription.remove(" device ");

            deviceList.insert(deviceDescription,deviceName);
        }
    }
    return deviceList;
}

void ChoiceScannerWidget::scannerChosen()
{
    QString scannerName = choiceCombobox->currentData().toString();
    emit scannerSetUp(Id,scannerName);
}
