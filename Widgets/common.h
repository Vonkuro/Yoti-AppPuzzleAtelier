#ifndef COMMON_H
#define COMMON_H

#include <fstream>
#include <iostream>

#include <QtCore>
#include <QWidget>
#include <QtWidgets>

// Comonly used functions

void newDir(QString dirPath);

void delay(int milliSeconds);

std::string execute(const std::string& command);

#endif // COMMON_H
