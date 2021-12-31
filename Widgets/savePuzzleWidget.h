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

// Saving the Puzzle
signals:
    void puzzleSaved(int id);

private slots:
    void save();

private:
// Objects managers of the View
    QVBoxLayout* widgetLayout;
    QFormLayout* formLayout;

    QLabel* barcodeLabel;
    QLineEdit*  barcodeLineEdit;
    QLabel* barcodeErrorLabel;

    QLabel* descriptionLabel;
    QTextEdit* descriptionTextEdit;
    QLabel* descriptionErrorLabel;

    QPushButton* validationButton;

// Methods managers of the View
    void form();
    void viewStyle();

// Validation
    bool descriptionValid(QString description);
    bool barcodeValid(QString barcodeText);

// Database
    EnvLocal dataWrapper;

// Methods back


};

#endif // SAVEPUZZLEWIDGET_H
