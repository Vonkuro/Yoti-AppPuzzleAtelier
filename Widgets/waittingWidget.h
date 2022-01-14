#ifndef WAITTINGWIDGET_H
#define WAITTINGWIDGET_H

#include "common.h"
#include "envLocal.h"

#include <QtConcurrent/QtConcurrent>

class WaittingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaittingWidget(QWidget *parent = nullptr);
    ~WaittingWidget();

// Signal to transfert the results
signals:
    void puzzleSolved(int numberPieces, bool completed);
    void puzzleNotSolved();

// Manage the work of the Puzzle Solver (propriary software of Yoti)
public slots:
    void solverProcessStart(int id);
    void solverProcessEnd();

private:
// Methods
    int findPiecesNumber(QStringList solverSplited);
    bool findIfCompleted(QStringList solverSplited);
    void saveInDatabase(int numberPieces, bool completed);

// Database
    EnvLocal dataWrapper;
// Objects managers of thread
    QFutureWatcher<std::string> solverWatcher;
    QFuture<std::string> solverProcess;
// Attributs
    int idPuzzle;
    QString commandStringHead;

// Objects mmanagers of View
    QVBoxLayout* widgetLayout;

};

#endif // WAITTINGWIDGET_H
