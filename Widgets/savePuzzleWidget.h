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

signals:
    void puzzleSaved(int id);

private:
    // View
    QVBoxLayout* widgetLayout;
    QFormLayout* formLayout;

    QLabel* barcodeLabel;
    QLineEdit*  barcodeLineEdit;
    QLabel* barcodeErrorLabel;

    QLabel* descriptionLabel;
    QTextEdit* descriptionTextEdit;
    QLabel* descriptionErrorLabel;

    QPushButton* validationButton;

    void form();
    void viewStyle();

    // Validation
    bool descriptionValid(QString description);
    bool barcodeValid(QString barcodeText);

    // database
    EnvLocal dataWrapper;

    // methods

private slots:
    void save();

};

#endif // SAVEPUZZLEWIDGET_H
