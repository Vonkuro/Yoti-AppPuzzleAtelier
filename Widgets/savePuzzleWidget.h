#ifndef SAVEPUZZLEWIDGET_H
#define SAVEPUZZLEWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QRegExp>
#include "envLocal.h"

class SavePuzzleWidget : public QWidget
{
    Q_OBJECT
public:
    SavePuzzleWidget();

private:
    QVBoxLayout* widgetLayout;
    QFormLayout* formLayout;

    QLabel* barcodeLabel;
    QLineEdit* barcodeSpinBox;

    QLabel* descriptionLabel;
    QTextEdit* descriptionTextEdit;

    QPushButton* validationButton;

    void form();

    bool descriptionValid(QString description);
    bool barcodeValid(QString barcode);

};

#endif // SAVEPUZZLEWIDGET_H
