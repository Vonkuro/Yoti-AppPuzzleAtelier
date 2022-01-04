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
    prepareScanner();
    lastImageId = 0;
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);
}

void ScannerWidget::scanPuzzle()
{
    QString imagePathQString = "../" + pathImageDirectory + "/Image-" + lastImageId;

    std::string imagePathString = imagePathQString.toStdString();
    const char* imagePath = imagePathString.c_str();

    scanningStart(imagePath);
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
