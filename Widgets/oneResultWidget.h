#ifndef ONERESULTWIDGET_H
#define ONERESULTWIDGET_H

#include <QWidget>
#include <QtWidgets>

class OneResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OneResultWidget(QWidget *parent = nullptr, int idPuzzle, int barcode, int pieces, bool completed);
    explicit OneResultWidget(QWidget *parent = nullptr, int idPuzzle, int barcode);
    ~OneResultWidget();

signals:

public slots:

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

    void init(int idPuzzle);

};

#endif // ONERESULTWIDGET_H
