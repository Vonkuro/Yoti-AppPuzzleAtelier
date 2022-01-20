#ifndef VALIDATIONWIDGET_H
#define VALIDATIONWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QFile>

enum photoDevice {Webcam, Scanner};

class ValidationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ValidationWidget(QWidget *parent = nullptr);
    ~ValidationWidget();
// Tool for the master widget to manage the validation widget
    void validateImageWebcam(int idPuzzle, int idImage, photoDevice device);

// Objects managers of View
    QVBoxLayout* logoLayout;
    QHBoxLayout* widgetLayout;
    QVBoxLayout* choiceLayout;

    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* imageLabel;
    QPushButton* validButton;
    QPushButton* cancelButton;

// Attributs
    int puzzleId;
    int imageId;
    QPixmap image;
    QString imagePath;
    void viewStyle();

// Handle the validation process
signals:
    void newPhoto();
    void allIsValidated(int idPuzzle);

public slots:
    void valid();
    void cancel();


};

#endif // VALIDATIONWIDGET_H
