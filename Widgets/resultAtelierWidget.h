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
    void resultHandled();

public slots:  
    void finished();
    void removeResult(int idPuzzle);

private:
    QVBoxLayout* widgetLayout;
    QVBoxLayout* scrollLayout;


    QLabel* logoLabel;
    QScrollArea* scrollArea;
    QPushButton* finishButton;

    EnvLocal dataWrapper;
    QList<OneResultWidget*> resultList;

    void showResults();
    void deleteResults();
    void markShown(int idPuzzle);
};

#endif // RESULTATELIERWIDGET_H
