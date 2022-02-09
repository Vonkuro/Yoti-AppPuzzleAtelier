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

public slots:

private:
    QVBoxLayout* widgetLayout;
    QVBoxLayout* scrollLayout;

    QWidget* scrollContainer;

    QLabel* logoLabel;
    QScrollArea* scrollArea;

    EnvLocal dataWrapper;
    QList<OneResultWidget> resultList; // maybe with pointers

    void showResults();

};

#endif // RESULTATELIERWIDGET_H
