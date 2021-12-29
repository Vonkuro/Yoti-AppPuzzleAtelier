#ifndef VALIDATIONWIDGET_H
#define VALIDATIONWIDGET_H

#include <QWidget>
#include <QtWidgets>

class ValidationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ValidationWidget(QWidget *parent = nullptr);
    ~ValidationWidget();
    void validateImageWebcam(int idPuzzle, int idImage);

signals:

public slots:

private:
    QHBoxLayout* widgetLayout;
    QVBoxLayout* choiceLayout;

    QLabel* imageLabel;
    QPushButton* validButton;
    QPushButton* cancelButton;


    int puzzleId;
    int imageId;
    QPixmap image;
};

#endif // VALIDATIONWIDGET_H
