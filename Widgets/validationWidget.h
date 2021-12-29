#ifndef VALIDATIONWIDGET_H
#define VALIDATIONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QFile>

class ValidationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ValidationWidget(QWidget *parent = nullptr);
    ~ValidationWidget();
    void validateImageWebcam(int idPuzzle, int idImage);

signals:
    void newPhoto();

private slots:
    void valid();
    void cancel();

private:
    QHBoxLayout* widgetLayout;
    QVBoxLayout* choiceLayout;

    QLabel* imageLabel;
    QPushButton* validButton;
    QPushButton* cancelButton;


    int puzzleId;
    int imageId;
    QPixmap image;
    QString imagePath;
};

#endif // VALIDATIONWIDGET_H
