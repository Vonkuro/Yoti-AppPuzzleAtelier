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
    void searchCamera(int id);
    void cameraChosen();

signals:
    void cameraSetUp(int id, QCameraInfo cameraInfo);

private:
    QVBoxLayout* widgetLayout;
    QPushButton* choiceButton;
    QComboBox* choiceCombobox;

    QList<QCameraInfo> cameraList;
    int Id;
};

#endif // CHOIXCAMERAWIDGET_H
