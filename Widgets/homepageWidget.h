#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QWidget>
#include <QtWidgets>

class HomepageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomepageWidget(QWidget *parent = nullptr);
    ~HomepageWidget();

// Starting the Application
signals:
    void startApp();

private slots:
    void startButtonClicked();

private:
// Objects managers of the View
    QVBoxLayout* widgetLayout;
    QPushButton* startButton;


};

#endif // HOMEPAGEWIDGET_H
