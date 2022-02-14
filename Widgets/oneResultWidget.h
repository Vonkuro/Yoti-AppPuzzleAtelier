#ifndef ONERESULTWIDGET_H
#define ONERESULTWIDGET_H

#include "common.h"

class OneResultWidget : public QWidget
{
    Q_OBJECT
public:
     OneResultWidget(int idPuzzle, qlonglong barcode, QString description, int pieces, bool completed, QWidget *parent = nullptr);
     OneResultWidget(int idPuzzle, qlonglong barcode, QString description, QWidget *parent = nullptr);
    ~OneResultWidget();
// Propriety
     int puzzleId;

// Checking the result
signals:
     void checked(int idPuzzle);
public slots:
     void check();
     void displayDescription();

private :
// Object managers of view
    QHBoxLayout* widgetLayout;
    QVBoxLayout* informationLayout;
    QHBoxLayout* buttonsLayout;

    QLabel* coverLabel;
    QLabel* barcodeLabel;
    QLabel* completedLabel;
    QLabel* piecesLabel;
    QPushButton* shortDescriptionButton;
    QPushButton* checkedButton;

// Attributs
    QString pathCover;
    QString shortDescription;

// Methods
    void init(int idPuzzle, QString description);
    void viewStyleCommon(qlonglong barcode);
    void viewStyleSolved(int pieces, bool completed);
    void viewStyleUnsolved();
};

#endif // ONERESULTWIDGET_H
