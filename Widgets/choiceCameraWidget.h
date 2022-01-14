#ifndef CHOIXCAMERAWIDGET_H
#define CHOIXCAMERAWIDGET_H

#include <QWidget>
#include <QtWidgets>
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
    void cameraSetUp(int id, QCameraInfo cameraInfo);

private:
// Object managers of view
    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

// Attributs
    QList<QCameraInfo> cameraList;
    int Id;
};

#endif // CHOIXCAMERAWIDGET_H
