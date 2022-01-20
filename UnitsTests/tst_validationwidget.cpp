#include "tst_validationwidget.h"
/*
// Don't change anything in the constructor or QTest will crash
// QString are safe (so far)
tst_validationWidget::tst_validationWidget()
{
    path = "../Images/Puzzle--3";
}

// Set up the common arrange
// Prepare a puzzle directory with a jpg image
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
    picture.save(path + "/image-1.jpg");

    QFile image(path + "/image-1.jpg");
    QVERIFY(image.exists());

    validation->validateImageWebcam(-3,1);


}

// Clean up the common arrange
// Remove the puzzle directory and it's content
void tst_validationWidget::cleanupTestCase()
{
    QDir directory(path);
    directory.removeRecursively();
}


// Test if the method button cancel remove the test image and emit the signal newPhoto
void tst_validationWidget::cancelTest()
{
    QSignalSpy spy(validation, SIGNAL(newPhoto()));
    QTest::mouseClick(validation->cancelButton, Qt::LeftButton);

    QCOMPARE(spy.count(), 1);

    QFile image(path + "/test.jpg");
    QVERIFY(! image.exists());
}
*/
