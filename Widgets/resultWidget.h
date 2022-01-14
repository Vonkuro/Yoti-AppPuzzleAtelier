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

// Tools for the master Widget
signals:
    void restart();
public slots:
    void display(int piecesNumber, bool completed);
    void display();
    void emitRestart();

private:
// Object managers of the view
    QVBoxLayout* widgetLayout;
    QLabel* piecesNumberLabel;
    QLabel* completedLabel;
    QPushButton* restartButton;

};

#endif // RESULTWIDGET_H
