#ifndef GRID_H
#define GRID_H

#include <QDialog>
#include <random>
#include "stats.h"

namespace Ui {
class Grid;
}

class Grid : public QDialog
{
    Q_OBJECT

public:
    Grid(Stats* stats, int time, QWidget *parent = nullptr);
    ~Grid();
   // void setColor(QColor color);
    void startTimer();
    QColor getColor();
    int getCycle();
    void setCycle(int cyc);


protected:
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent *event) override;


public slots:
    void setGameSize(const int& size);
    void setCellSize(const int& size);
    void setColor(const QColor& color);
    void makeGrid();
    void deleteGrid();
    void setTimer(int time);

private:
    Ui::Grid *ui;

    int getGameSize() const;
    int getCellSize() const;

    int** grid; //defines the game environment
    int** past_grid; //defines the previous game
    std::mt19937 randNumber;
    std::uniform_int_distribution<int> randomDistribution;
    int initialCellState();
    int rowCount = 50;
    int columnCount = 50;
    double cellHeight = 15;
    double cellWidth = 15;
    QColor cellColor = Qt::black;
    QColor universeFieldColour = Qt::white;
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 8.0;

    qreal getCellHeight();
    qreal getCellWidth();

    void paintCellGrid(QPainter& painter);
    void paintUniverseBorder(QPainter& painter);

    void setTransparency();



    QTimer* timer;

    void resetGrid();

    int scaleFactor = 1;

    int cycle = 0;
    int dotsCount = 0;
    int newDotsCount = 0;
    int newBlanksCount = 0;

    Stats * stat;

    int calcDots();
    float calcPctFill();
    int calcNewDots();
    int calcNewBlanks();
    void copyGrid();

    std::vector<int> dotsHist;

private slots:
     void evolve();
   //  void on_startPushButton_clicked();
};

#endif // GRID_H
