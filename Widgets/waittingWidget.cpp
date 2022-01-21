#include "waittingWidget.h"

WaittingWidget::WaittingWidget(QWidget *parent) : QWidget(parent)
{
// QString for the running command
    commandStringHead = "./Yoti-PuzzleSolver ../Images/Puzzle-";

// Qstring for testing without new photos
    //commandStringHead = "./Yoti-PuzzleSolver ../../PuzzleSolverProject/Scans/puzzle";

// Init of view objects
    widgetLayout = new QVBoxLayout;
    logoLabel = new QLabel;
    titleLabel = new QLabel;
    gifMovie = new QMovie(":/viewRessource/waittingGif");
    gifLabel = new QLabel;

// Linking the view object
    widgetLayout->addWidget(logoLabel);
    widgetLayout->addWidget(titleLabel);
    gifLabel->setMovie(gifMovie);
    widgetLayout->addWidget(gifLabel);
    this->setLayout(widgetLayout);

// Connect the signals to the slots
    connect(&solverWatcher, &QFutureWatcher<QString>::finished, this, &WaittingWidget::solverProcessEnd);

    viewStyle();
}

// The end of the line for pointers
WaittingWidget::~WaittingWidget()
{
    delete logoLabel;
    delete titleLabel;
    delete gifLabel;
    delete gifMovie;
    delete widgetLayout;
}

// Start a thread in order to run the puzzle solver in it
void WaittingWidget::solverProcessStart(int id)
{
    // id fix to one during test without photos
    idPuzzle = id;

    QString commandString = commandStringHead + QString::number(idPuzzle) + "/";
    std::string command = commandString.toStdString();


    solverProcess = QtConcurrent::run(execute, command);
    solverWatcher.setFuture(solverProcess);

    gifMovie->start();
}

// Handle the result from the puzzle solver
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

// Extract the number of pieces from the splited output
int WaittingWidget::findPiecesNumber(QStringList solverSplited)
{
    QString piecesNumberString = solverSplited[1];

    int indexEnd = piecesNumberString.indexOf("Nombre");
    indexEnd -= 2;

    piecesNumberString = piecesNumberString.mid(1,indexEnd);

    int piecesNumber = piecesNumberString.toInt();

    return piecesNumber;
}

// Extract the information of if the puzzle is complet or not
bool WaittingWidget::findIfCompleted(QStringList solverSplited)
{
    QString completedString = solverSplited[2];
    gifMovie->stop();
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

// Save in database the completeness and number of pieces of the puzzle
void WaittingWidget::saveInDatabase(int numberPieces, bool completed)
{
    QSqlDatabase database = dataWrapper.getDatabase();
    if ( database.open() )
    {
        QSqlQuery resultSql(database);

        resultSql.prepare("UPDATE Puzzle SET pieces_number = ? , completed = ?  WHERE id = ?");
        resultSql.bindValue(0,numberPieces);
        resultSql.bindValue(1,completed);
        resultSql.bindValue(2,idPuzzle);

        resultSql.exec();

        database.close();
    }
}

// Manage details of the view
void WaittingWidget::viewStyle()
{
    QPixmap logo(":/viewRessource/logoYoti");
    logoLabel->setProperty("cssClass","logo");
    logoLabel->setScaledContents(true);
    logoLabel->setPixmap(logo);
    widgetLayout->setAlignment(logoLabel,Qt::AlignHCenter);

    titleLabel->setProperty("cssClass","title");
    titleLabel->setText("Veuillez patienter pendant que Yoti App Puzzle travaille");
    titleLabel->setStyleSheet("text-align: center");
    widgetLayout->setAlignment(titleLabel,Qt::AlignHCenter);

    gifLabel->setScaledContents(true);
    gifLabel->setStyleSheet("border: 2px solid #6569C4; min-width: 854; max-width: 854; min-height: 480; max-height:480");
    widgetLayout->setAlignment(gifLabel,Qt::AlignHCenter);

    widgetLayout->setAlignment(Qt::AlignTop);
    widgetLayout->setSpacing(100);

}
