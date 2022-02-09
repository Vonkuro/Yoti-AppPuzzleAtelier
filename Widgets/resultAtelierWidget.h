#ifndef RESULTATELIERWIDGET_H
#define RESULTATELIERWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "oneResultWidget.h"
#include "envLocal.h"

class ResultAtelierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultAtelierWidget(QWidget *parent = nullptr);
    ~ResultAtelierWidget();
    bool isThereResult();

signals:
    void resultHandled();

public slots:  
    void finished();
    void removeResult(int idPuzzle);

private:
    QVBoxLayout* widgetLayout;
    QVBoxLayout* scrollLayout;

    QWidget* containerWidget;

    QLabel* logoLabel;
    QScrollArea* scrollArea;
    QPushButton* finishButton;

    EnvLocal dataWrapper;
    QList<OneResultWidget*> resultList;
    bool thereIsResult;

    void showResults();
    void deleteResults();
    void markShown(int idPuzzle);
    void viewStyle();
};

#endif // RESULTATELIERWIDGET_H
