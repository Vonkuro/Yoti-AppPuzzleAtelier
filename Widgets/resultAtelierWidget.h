#ifndef RESULTATELIERWIDGET_H
#define RESULTATELIERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "oneResultWidget.h"
#include "envLocal.h"

class resultAtelierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit resultAtelierWidget(QWidget *parent = nullptr);
    ~resultAtelierWidget();

signals:
    void noResult();

public slots:

private:
    QVBoxLayout* widgetLayout;
    QVBoxLayout* scrollLayout;

    QWidget* scrollContainer;

    QLabel* logoLabel;
    QScrollArea* scrollArea;
    QPushButton* finishButton;

    EnvLocal dataWrapper;
    QList<OneResultWidget*> resultList; // maybe with pointers

    void showResults();

    void deleteResults();

};

#endif // RESULTATELIERWIDGET_H
