#ifndef WAITTINGWIDGET_H
#define WAITTINGWIDGET_H

#include "common.h"
#include "envLocal.h"

#include <QWidget>
#include <QtWidgets>
#include <QtConcurrent/QtConcurrent>

class WaittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaittingWidget(QWidget *parent = nullptr);
    ~WaittingWidget();

signals:
    void puzzleSolved(int numberPieces, bool completed);
public slots:
    void solverProcessStart(int id);
    void solverProcessEnd();

private:
    int findPiecesNumber(QStringList solverSplited);
    bool findIfCompleted(QStringList solverSplited);
    void saveInDatabase(int numberPieces, bool completed);

    EnvLocal dataWrapper;
    QFutureWatcher<std::string> solverWatcher;
    QFuture<std::string> solverProcess;

    int idPuzzle;
    QString commandStringHead;

    QVBoxLayout* widgetLayout;

};

#endif // WAITTINGWIDGET_H
