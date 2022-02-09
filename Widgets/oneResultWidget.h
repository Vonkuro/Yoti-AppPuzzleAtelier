#ifndef ONERESULTWIDGET_H
#define ONERESULTWIDGET_H

#include <QWidget>
#include <QtWidgets>

class OneResultWidget : public QWidget
{
    Q_OBJECT
public:
     OneResultWidget(int idPuzzle, int barcode, QString description, int pieces, bool completed, QWidget *parent = nullptr);
     OneResultWidget(int idPuzzle, int barcode, QString description, QWidget *parent = nullptr);
    ~OneResultWidget();
     int puzzleId;

signals:
     void checked(int idPuzzle);
public slots:
     void check();
     void displayDescription();

private :
    QHBoxLayout* widgetLayout;
    QVBoxLayout* informationLayout;
    QHBoxLayout* buttonsLayout;

    QLabel* coverLabel;
    QLabel* barcodeLabel;
    QLabel* completedLabel;
    QLabel* piecesLabel;
    QPushButton* shortDescriptionButton;
    QPushButton* checkedButton;

    QString pathCover;
    QString shortDescription;

    void init(int idPuzzle, QString description);
    void viewStyleCommon(int barcode);
    void viewStyleSolved(int pieces, bool completed);
    void viewStyleUnsolved();
};

#endif // ONERESULTWIDGET_H
