#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include "common.h"

class HomepageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HomepageWidget(QWidget *parent = nullptr);
    ~HomepageWidget();
// Objects managers of the View
    QVBoxLayout* widgetLayout;
    QPushButton* startButton;
    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* subtitleLabel;

// Starting the Application
signals:
    void startApp();
private slots:
    void startButtonClicked();

// Manage the view
private:
    void viewStyle();


};

#endif // HOMEPAGEWIDGET_H
