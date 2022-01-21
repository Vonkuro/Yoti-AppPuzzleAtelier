#include "choiceScannerWidget.h"

ChoiceScannerWidget::ChoiceScannerWidget(QWidget *parent) : QWidget(parent)
{
// Init of view objects
    widgetLayout = new QVBoxLayout;
    choiceButton = new QPushButton;
    choiceCombobox = new QComboBox;
    logoLabel = new QLabel;
    titleLabel = new QLabel;
    subTitleLabel = new QLabel;

// Linking view objects
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    widgetLayout->addWidget(subTitleLabel);
    widgetLayout->addWidget(choiceCombobox);
    widgetLayout->addWidget(choiceButton);

    this->setLayout(widgetLayout);

// Connect the signals and the slots
    connect(choiceButton, &QPushButton::clicked, this, &ChoiceScannerWidget::scannerChosen);

    viewStyle();
}

// The end of the line for the pointers
ChoiceScannerWidget::~ChoiceScannerWidget()
{
    delete logoLabel;
    delete titleLabel;
    delete subTitleLabel;
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

// Manage details of the view
void ChoiceScannerWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    titleLabel->setProperty("cssClass","title");
    titleLabel->setText("Imprimantes Disponibles");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    subTitleLabel->setProperty("cssClass","subtitle");
    subTitleLabel->setText("Veuillez choisir une Imprimante dans la liste");
    widgetLayout->setAlignment(subTitleLabel,Qt::AlignHCenter);

    choiceCombobox->setProperty("cssClass","choice");
    widgetLayout->setAlignment(choiceCombobox,Qt::AlignHCenter);

    choiceButton->setProperty("cssClass","greenButton");
    choiceButton->setText("Choisir cette Imprimante");
    widgetLayout->setAlignment(choiceButton,Qt::AlignHCenter);

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(50);
}
