#ifndef CHOIXCAMERAWIDGET_H
#define CHOIXCAMERAWIDGET_H


#include "common.h"
#include <QCameraInfo>

class ChoiceCameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChoiceCameraWidget(QWidget *parent = 0);
    ~ChoiceCameraWidget();

public slots:
// Tools for master widget
    void searchCamera(int id);
// Methods
    void cameraChosen();

signals:
// Signal loaded with the return for master widget
    void cameraSetUp(int id, QCameraInfo cameraInfo);

private:
// Object managers of view
    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* subTitleLabel;

// Attributs
    QList<QCameraInfo> cameraList;
    int Id;

    void viewStyle();
};

#endif // CHOIXCAMERAWIDGET_H
