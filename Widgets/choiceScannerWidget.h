#ifndef CHOICESCANNERWIDGET_H
#define CHOICESCANNERWIDGET_H

#include <fstream>
#include <iostream>

#include <QWidget>
#include <QtWidgets>

class ChoiceScannerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceScannerWidget(QWidget *parent = nullptr);
    void test();

signals:

public slots:

private:
    std::string execute(const std::string& command);
};

#endif // CHOICESCANNERWIDGET_H
