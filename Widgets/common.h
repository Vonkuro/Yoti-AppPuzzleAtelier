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

inline QString greenButtonFontStyle = "font: bold \"Montserrat\"; font-size: 28px; color: #2C2E71;";
inline QString greenButtonBackgroundStyle = "background-color: #78C29B; border: 2px solid #6569C4;";
inline QString greenCheckedButtonBackgroundStyle = "background-color: #2f4f4f; border: 2px solid #6569C4;";
inline QString greenButtonSizeStyle = "height: 50px; max-width: 800px; min-width: 800px; ";

#endif // COMMON_H
