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

std::string ChoiceScannerWidget::execute(const std::string& command) {
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
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
