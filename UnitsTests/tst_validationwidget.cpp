#include "tst_validationwidget.h"

tst_validationWidget::tst_validationWidget()
{
    path = "../Images/Puzzle--3";
}

void tst_validationWidget::initTestCase()
{
    validation = new ValidationWidget;
    QDir directory;
    directory.mkpath(path);
    QPicture picture;
    QPainter painter;
    painter.begin(&picture);
    painter.drawText(0, 0, "Test");
    painter.end();
    picture.save(path + "/test.jpg");

    QFile image(path + "/test.jpg");
    QVERIFY(image.exists());


}

void tst_validationWidget::cleanupTestCase()
{
    QDir directory(path);
    directory.removeRecursively();
}

void tst_validationWidget::validTest()
{

}

void tst_validationWidget::cancelTest()
{

}
