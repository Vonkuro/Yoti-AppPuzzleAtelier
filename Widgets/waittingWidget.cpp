#include "waittingWidget.h"

WaittingWidget::WaittingWidget(QWidget *parent) : QWidget(parent)
{
    // QString for the running command
    commandStringHead = "./Yoti-PuzzleSolver ../Images/Puzzle-";

    // Qstring for testing without photos
    //commandStringHead = "./Yoti-PuzzleSolver ../../PuzzleSolverProject/Scans/puzzle";

    widgetLayout = new QVBoxLayout;

    this->setLayout(widgetLayout);

    connect(&solverWatcher, &QFutureWatcher<QString>::finished, this, &WaittingWidget::solverProcessEnd);
}

WaittingWidget::~WaittingWidget()
{
    delete widgetLayout;
}

void WaittingWidget::solverProcessStart(int id)
{
    // id fix to one for test until creating correct images
    idPuzzle = id;

    QString commandString = commandStringHead + QString::number(idPuzzle) + "/";
    std::string command = commandString.toStdString();


    solverProcess = QtConcurrent::run(execute, command);
    solverWatcher.setFuture(solverProcess);

}

void WaittingWidget::solverProcessEnd()
{
    QString solverOutput = QString::fromStdString( solverProcess.result() );

    qDebug() << solverOutput;

    solverOutput = solverOutput.simplified();

    if (solverOutput.contains("Nombre")){
        QStringList solverSplited = solverOutput.split(":");

        int piecesNumber = findPiecesNumber(solverSplited);
        bool completed = findIfCompleted(solverSplited);
        saveInDatabase(piecesNumber, completed);
        emit puzzleSolved(piecesNumber, completed);
    } else
    {
        emit puzzleNotSolved();
    }


}

int WaittingWidget::findPiecesNumber(QStringList solverSplited)
{
    QString piecesNumberString = solverSplited[1];

    int indexEnd = piecesNumberString.indexOf("Nombre");
    indexEnd -= 2;

    piecesNumberString = piecesNumberString.mid(1,indexEnd);

    int piecesNumber = piecesNumberString.toInt();

    return piecesNumber;
}

bool WaittingWidget::findIfCompleted(QStringList solverSplited)
{
    QString completedString = solverSplited[3];

    if (completedString.contains("incomplet"))
    {
        return false;
    }
    else if (completedString.contains("complet"))
    {
        return true;
    } else
    {
        return false;
    }
}

void WaittingWidget::saveInDatabase(int numberPieces, bool completed)
{
    QSqlDatabase database = dataWrapper.getDatabase();
    if ( database.open() )
    {
        QSqlQuery resultSql;

        resultSql.prepare("UPDATE Puzzle SET pieces_number = ? , completed = ?  WHERE id = ?");
        resultSql.bindValue(0,numberPieces);
        resultSql.bindValue(1,completed);
        resultSql.bindValue(2,idPuzzle);

        resultSql.exec();

        database.close();
    }
}
