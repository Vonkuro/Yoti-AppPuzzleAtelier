#ifndef RESULTATELIERWIDGET_H
#define RESULTATELIERWIDGET_H

#include <QWidget>
#include <QScrollArea>

class resultAtelierWidget : public QWidget
{
    Q_OBJECT
public:
    explicit resultAtelierWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    QScrollArea* scrollArea;

    void ;
};

#endif // RESULTATELIERWIDGET_H
