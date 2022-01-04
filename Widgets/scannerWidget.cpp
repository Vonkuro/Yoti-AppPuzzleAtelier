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

void ScannerWidget::prepare()
{
    prepareScanner();
}

void ScannerWidget::scanPuzzle()
{
    scanningStart("../Images/ScanTest/test");
}
