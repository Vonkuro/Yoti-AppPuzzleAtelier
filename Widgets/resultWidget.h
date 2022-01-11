#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <QWidget>
#include <QtWidgets>


class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultWidget(QWidget *parent = nullptr);
    ~ResultWidget();

signals:

public slots:
    void display(int piecesNumber, bool completed);

private:
    QVBoxLayout* widgetLayout;
    QLabel* piecesNumberLabel;
    QLabel* completedLabel;


};

#endif // RESULTWIDGET_H
