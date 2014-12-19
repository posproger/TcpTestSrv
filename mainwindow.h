#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mtestcore.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void checkStatisticsSlot(void);

signals:
    void checkStatistics(void);

private:
    Ui::MainWindow *ui;
    MTestCore * m_core;

};

#endif // MAINWINDOW_H
