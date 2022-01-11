#ifndef WAITTINGWIDGET_H
#define WAITTINGWIDGET_H

#include <QWidget>

class WaittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaittingWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    void solverProcess();
};

#endif // WAITTINGWIDGET_H
