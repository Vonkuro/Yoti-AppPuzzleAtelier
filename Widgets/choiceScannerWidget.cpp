#include "choiceScannerWidget.h"

ChoiceScannerWidget::ChoiceScannerWidget(QWidget *parent) : QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;

// Linking view objects
    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(choiceButton, &QPushButton::clicked, this, &ChoiceScannerWidget::scannerChosen);
}

// The end of the line for the pointers
ChoiceScannerWidget::~ChoiceScannerWidget()
{
    delete choiceCombobox;
    delete choiceButton;
    delete widgetLayout;
}

// Look for the available scanners and store them in the choiceCombobox
void ChoiceScannerWidget::searchScanner(int id)
{
    Id = id;

    Devices deviceList = findScanners();
    for ( Devices::iterator i = deviceList.begin() ; i!=deviceList.end() ; ++i)
    {
        choiceCombobox->addItem( i.key(), QVariant(i.value()) );
    }

}

// Look for the available scanner for searchScanner
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

// Emit the signal scannerSetUp loaded with the name of the scanner and the id of the puzzle
void ChoiceScannerWidget::scannerChosen()
{
    QString scannerName = choiceCombobox->currentData().toString();
    emit scannerSetUp(Id,scannerName);
}
