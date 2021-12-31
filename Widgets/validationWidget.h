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
// Tool for the master widget to manage the validation widget
    void validateImageWebcam(int idPuzzle, int idImage);

// Handle the validation process
signals:
    void newPhoto();

public slots:
    void valid();
    void cancel();

private:
// Objects managers of View
    QHBoxLayout* widgetLayout;
    QVBoxLayout* choiceLayout;

    QLabel* imageLabel;
    QPushButton* validButton;
    QPushButton* cancelButton;

// Attributs
    int puzzleId;
    int imageId;
    QPixmap image;
    QString imagePath;
};

#endif // VALIDATIONWIDGET_H
