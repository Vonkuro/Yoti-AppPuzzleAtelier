#ifndef SAVEPUZZLEWIDGET_H
#define SAVEPUZZLEWIDGET_H

#include "common.h"
#include <QRegExp>
#include "envLocal.h"

class SavePuzzleWidget : public QWidget
{
    Q_OBJECT
public:
    SavePuzzleWidget();
    ~SavePuzzleWidget();
    void prepare();

// Saving the Puzzle
signals:
    void puzzleSaved(int id);
    void puzzleContinue(int id, int restartNumber);

private slots:
    void save();

private:
// Objects managers of the View
    QVBoxLayout* widgetLayout;
    QWidget* backgroundWidget;
    QVBoxLayout* backgroundLayout;
    QFormLayout* formLayout;

    QLabel* logoLabel;
    QLabel* titleLabel;

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
    QMessageBox* messageBoxWithStyle();

};

#endif // SAVEPUZZLEWIDGET_H
