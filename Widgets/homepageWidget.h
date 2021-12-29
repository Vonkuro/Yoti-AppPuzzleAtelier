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
signals:
    void startApp();
public slots:

private:
    QVBoxLayout* widgetLayout;
    QPushButton* startButton;

private slots:
    void startButtonClicked();
};

#endif // HOMEPAGEWIDGET_H
