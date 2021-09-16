#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFontDialog>
#include<QColorDialog>
//#include "grid_layout.h"
#include "grid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_StartPushButton_clicked();
    void setSliderInfo(const int& size);
    void setSpinBoxInfo(const int& size);

    void on_colorPushButton_clicked();

private:
    Ui::MainWindow *ui;
    void setSlider();
    void setSpinBox();
    Grid* grid = new Grid(this);
};
#endif // MAINWINDOW_H
