#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFontDialog>
#include<QColorDialog>
//#include "grid_layout.h"
#include "grid.h"
#include <QThread>
#include <thread>
#include <stats.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QColor getColor();
    void newGame();
    int getGameSize();
    int getCellSize();
    int getTimer();


public slots:
    void setColor(const QColor& color);
    void setGameSize(const int& size);
    void setCellSize(const int& size);
    void setTimer(const int& size);



private slots:
    void on_StartPushButton_clicked();
    void setSliderInfo(const int& size);
    void setSpinBoxInfo(const int& size);
    void setTimerInfo(const int& size);

    //void on_colorPushButton_clicked();

    void on_colorPushButton_clicked();
    void on_StartPushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    void setSlider();
    QColor cellColor = Qt::black;
    int gameCount = 0;
    void setSpinBox();
    void setTimerSlider();

    int gameSize = 50;
    int scaleFactor = 1;
    int timer = 300;

    std::vector<QDialog*> dialogs;

};
#endif // MAINWINDOW_H
