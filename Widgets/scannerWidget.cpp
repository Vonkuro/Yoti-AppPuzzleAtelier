#include "scannerWidget.h"


ScannerWidget::ScannerWidget()
{
    widgetLayout = new QVBoxLayout;
    scanButton = new QPushButton;

    widgetLayout->addWidget(scanButton);

    this->setLayout(widgetLayout);

    connect(scanButton, &QPushButton::clicked, this, &ScannerWidget::scanPuzzle);
}

ScannerWidget::~ScannerWidget()
{
    delete widgetLayout;
    delete scanButton;
}

void ScannerWidget::prepare(int id)
{
    lastImageId = 0;
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);

}

void ScannerWidget::scanPuzzle()
{
    lastImageId += 1;
    QString imagePathQString = "../" + pathImageDirectory + "/Image-" + QString::number(lastImageId) + ".jpg";

    QString commandQString = "scanimage --mode Color --format=jpeg > " + imagePathQString;
    std::string commandString = commandQString.toStdString();
    const char* command = commandString.c_str();
    system(command);
}

// Create a directory if it doesn't exit
void ScannerWidget::newDir(QString dirPath)
{
    QDir dir(dirPath);
    QDir dir2;
    if(!dir.exists())
    {
        dir2.mkpath(dirPath);
    }
}
