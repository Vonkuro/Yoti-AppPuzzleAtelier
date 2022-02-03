#include "solver.h"

Solver::Solver(QObject *parent) : QObject(parent)
{
    commandHead = "Yoti-PuzzleSolver ";
}

void Solver::solvePuzzle(QMap<int, QString> puzzle)
{
    QString command = commandHead + puzzle.;
}

std::string Solver::execute(const std::string& command) {
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}
