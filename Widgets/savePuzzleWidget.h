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
    ~SavePuzzleWidget();

private:
    // View
    QVBoxLayout* widgetLayout;
    QFormLayout* formLayout;

    QLabel* barcodeLabel;
    QLineEdit*  barcodeLineEdit;

    QLabel* descriptionLabel;
    QTextEdit* descriptionTextEdit;

    QPushButton* validationButton;

    void form();

    // Validation
    bool descriptionValid(QString description);
    bool barcodeValid(QString barcode);

    // database
    EnvLocal dataWrapper;

    // methods
    long long int manageBarcode();

private slots:
    void save();

};

#endif // SAVEPUZZLEWIDGET_H
