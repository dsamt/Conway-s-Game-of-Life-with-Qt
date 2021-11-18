#include "grid.h"
#include "ui_grid.h"
#include "gamerules.h"

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <iostream>

Grid::Grid(Stats * stats, int time, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grid),
    randNumber((std::random_device())()),
    randomDistribution(1, 10),
    stat(stats)
{
   ui->setupUi(this);

   setTimer(time);

   setTransparency();
   makeGrid();
   //timer->start();


   connect(timer, SIGNAL(timeout()), this, SLOT(evolve()));

 //  connect(timer, SIGNAL(timeout()), stats, SLOT(setCycleInfo(this->getCycle())));

}

Grid::~Grid()
{
    delete ui;
}


void Grid::makeGrid()
{

    grid = new int*[rowCount];

    for (int i = 0; i < rowCount; i++){
        grid[i] = new int[columnCount];
        for (int j = 0; j < columnCount; j++){
            grid[i][j] = initialCellState();

        }
    }
}

int Grid::initialCellState()
{
    int random = randomDistribution(randNumber);
    return (random <= 5) ? 0 : 1;
}

void Grid::deleteGrid()
{
    for (int i = 0; i < rowCount; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
}

void Grid::setGameSize(const int& size)
{
    //deleteGrid();
    rowCount = size;
    columnCount = size;
    //makeGrid();
    update();
}

void Grid::setCellSize(const int& size)
{
    //deleteGrid();
    scaleFactor = size;
    //makeGrid();
    update();
}

void Grid::setColor(const QColor& color)
{
    //deleteGrid();
    cellColor =  color;
    //makeGrid();
    update();
}

int Grid::getGameSize() const
{
    return rowCount;
}

void Grid::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintUniverseBorder(painter);
    paintCellGrid(painter);
}

void Grid::paintCellGrid(QPainter &painter)
{
    for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
       {
           for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
           {
               if (grid[rowIdx][columnIdx] == 1)
               {
                   qreal x = rowIdx * getCellWidth();
                   qreal y = columnIdx * getCellHeight();
                   QRect cellField(x, y,  getCellHeight() - 1, getCellHeight() - 1);
                   painter.setBrush(QBrush(cellColor));
                   painter.fillRect(cellField, painter.brush());
                  //ui->lineEdit->setText(QString::number(grid[rowIdx][columnIdx]));
               }
           }
       }
}

void Grid::paintUniverseBorder(QPainter& painter)
{
    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(universeFieldColour));
    painter.fillRect(universeBorder, painter.brush());
   // painter.setPen(QPen(universeBorderColour, universeBorderThickness));
    //painter.drawRect(universeBorder);
}

qreal Grid::getCellHeight()
{
    qreal cH;
    if (rowCount > 200 && scaleFactor == 1){
        cH = 1.8 * height() / rowCount;
    }
    else{
        cH = scaleFactor * height() / rowCount;
    }
    return cH;
}

qreal Grid::getCellWidth()
{
    qreal cW;
    if (columnCount > 200 && scaleFactor == 1){
        cW = 1.8 * width() / columnCount;
    }
    else{
        cW = scaleFactor * width() / columnCount;
    }
    return cW;
}

void Grid::setTransparency()
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellColor.setAlpha(255);
}

void Grid::evolve()
{
    cycle++;
    evolveNextGeneration(grid, rowCount, columnCount);
    update();
    stat->setCycleInfo(this->getCycle());
    stat->setDotsCount(this->calcDots());
    float fill = this->calcPctFill();
    stat->setPctFill(fill);
    stat->setNewDotsCount(this->calcNewDots());

}

void Grid::setCycle(int cyc)
{
    cycle = cyc;
}

int Grid::getCycle()
{
    return cycle;
}

void Grid::setTimer(int time)
{
    timer = new QTimer(this);
    timer->setInterval(time);
    //connect(timer, SIGNAL(timeout()), this, SLOT(evolve()));
}

void Grid::closeEvent(QCloseEvent *)
{
    resetGrid();
}

void Grid::resetGrid()
{
    timer->stop();
    deleteGrid();
    makeGrid();
    update();
}

void Grid::startTimer()
{
    timer->start();
}

QColor Grid::getColor()
{
    return cellColor;
}

int Grid::calcDots()
{
    dotsCount = 0;
    for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
           {
               for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
               {
                   if (grid[rowIdx][columnIdx] == 1)
                   {
                       dotsCount++;
                   }
               }
           }
    dotsHist.push_back(dotsCount);
    return dotsCount;
}

float Grid::calcPctFill()
{
    float dec = 100 * (static_cast<float> (dotsCount) / static_cast<float>(rowCount * columnCount));
    return dec;
}

int Grid::calcNewDots()
{
    if (dotsHist.size() == 1){
        newDot.push_back(false);
    }

        //return dotsHist[dotsHist.size() - 1] - dotsHist[dotsHist.size() - 2];
        for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
               {
                   for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
                   {
                       if (grid[rowIdx][columnIdx] == 1 && !newDot[rowCount * columnCount])
                       {
                           newDotsCount++;
                           newDot.push_back(true);
                       }
                   }
               }
    return newDotsCount;
}

int Grid::calcNewBlanks()
{

}
