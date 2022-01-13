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
    void restart();
public slots:
    void display(int piecesNumber, bool completed);
    void emitRestart();

private:
    QVBoxLayout* widgetLayout;
    QLabel* piecesNumberLabel;
    QLabel* completedLabel;
    QPushButton* restartButton;

};

#endif // RESULTWIDGET_H
