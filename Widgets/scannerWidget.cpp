#include "scannerWidget.h"


ScannerWidget::ScannerWidget()
{
// Prepare the view
    // Init of View Objects
    widgetLayout = new QVBoxLayout;
    scanButton = new QPushButton;
// Linking View Objects
    widgetLayout->addWidget(scanButton);
    this->setLayout(widgetLayout);
// Connect to slots
    connect(scanButton, &QPushButton::clicked, this, &ScannerWidget::scanPuzzle);
}

// The end of the line for the pointers
ScannerWidget::~ScannerWidget()
{
    delete widgetLayout;
    delete scanButton;
}

// Prepare the attributs and directory before scanning
void ScannerWidget::prepare(int id)
{
    lastImageId = 0;
    puzzleId = id;
    pathImageDirectory = "Images/Puzzle-" + QString::number(puzzleId);
    newDir("../" + pathImageDirectory);

}

// Scan with the first detected scanner and emit the photoTaken signal
void ScannerWidget::scanPuzzle()
{
    lastImageId += 1;
    QString imagePathQString = "../" + pathImageDirectory + "/image-" + QString::number(lastImageId) + ".jpg";

    QString commandQString = "scanimage --mode Color --format=jpeg > " + imagePathQString;
    std::string commandString = commandQString.toStdString();
    const char* command = commandString.c_str();
    system(command);

    delay();

     emit photoTaken(puzzleId, lastImageId);
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

// Delay the widget loop for 3 second
void ScannerWidget::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(3000);

    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
