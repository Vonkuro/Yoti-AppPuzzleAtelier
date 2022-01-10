#include "choiceScannerWidget.h"

ChoiceScannerWidget::ChoiceScannerWidget(QWidget *parent) : QWidget(parent)
{

}

std::string ChoiceScannerWidget::execute(const std::string& command) {
    system((command + " > temp.txt").c_str());

    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    return ret;
}

void ChoiceScannerWidget::test()
{
    QString output = QString::fromStdString(execute("scanimage -L"));
    qDebug() << output;
}
