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
// Tools for the master widget
    bool isThereResult();
signals:
    void resultHandled();
public slots:  
    void finished();

private:
    // View object
    QVBoxLayout* widgetLayout;
    QVBoxLayout* scrollLayout;

    QWidget* containerWidget;

    QLabel* logoLabel;
    QLabel* titleLabel;
    QScrollArea* scrollArea;
    QPushButton* finishButton;

    // Attributs
    EnvLocal dataWrapper;
    QList<OneResultWidget*> resultList;
    bool thereIsResult;

    // Methods
    void showResults();
    void deleteResults();
    void markShown(int idPuzzle);
    void viewStyle();
private slots:
    void removeResult(int idPuzzle);
};

#endif // RESULTATELIERWIDGET_H
