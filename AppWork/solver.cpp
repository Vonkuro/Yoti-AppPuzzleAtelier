#include "solver.h"

Solver::Solver(QObject *parent) : QObject(parent)
{
    commandHead = "Yoti-PuzzleSolver ";
}

void Solver::solvePuzzle(std::tuple<int, QString> puzzle)
{
    QString command = commandHead + std::get<1>(puzzle);

}

std::string Solver::execute(QString commandString) {
    std::string command = commandString.toStdString();
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}
