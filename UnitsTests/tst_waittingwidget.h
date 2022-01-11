#ifndef TST_WAITTINGWIDGET_H
#define TST_WAITTINGWIDGET_H

#include <QObject>

class tst_waittingWidget : public QObject
{
    Q_OBJECT
public:
    explicit tst_waittingWidget(QObject *parent = nullptr);

signals:

private slots:
    // Specials QT Tests at the launch at the start and the end of the Test Case
    void initTestCase(); // start
    void cleanupTestCase(); //end
    // Unit-Tests of Methods
    void completeTest();
    void IncompleteTest();
};

#endif // TST_WAITTINGWIDGET_H
