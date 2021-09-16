#include "grid.h"
#include "ui_grid.h"
#include "gamerules.h"

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

Grid::Grid(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grid),
    randNumber((std::random_device())()),
    randomDistribution(1, 10)
{
   ui->setupUi(this);

   setTransparency();
   setTimer();
   makeGrid();
   //connect(timer, SIGNAL(timeout), this, SLOT(evolve()));


   //evolve();

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
    deleteGrid();
    rowCount = size;
    makeGrid();
    update();
}

void Grid::setCellSize(const int& size)
{
    deleteGrid();
    cellHeight = 5 * size;
    cellWidth = 5 * size;
    makeGrid();
    update();
}

void Grid::setColor(QColor color)
{
    deleteGrid();
    universeFieldColour =  color;
    makeGrid();
    update();
}

int Grid::getGameSize() const
{
    return rowCount;
}

void Grid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    paintCellGrid(painter);
    //paintUniverseBorder(painter);
}

void Grid::paintCellGrid(QPainter &painter)
{
    for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
       {
           for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
           {
               if (grid[rowIdx][columnIdx] == 1)
               {
                   qreal cellLeftIdx = rowIdx * rowCount + columnCount + cellHeight;
                   qreal cellTopIdx = columnIdx * columnCount + rowCount + cellWidth;
                   QRect cellField(cellLeftIdx, cellTopIdx, getCellWidth() - 1.0, getCellHeight() - 1.0);
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
    painter.setPen(QPen(universeBorderColour, universeBorderThickness));
    painter.drawRect(universeBorder);
}

qreal Grid::getCellHeight()
{
    return cellHeight;
}

qreal Grid::getCellWidth()
{
    return cellWidth;
}

void Grid::setTransparency()
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellColor.setAlpha(255);
}

void Grid::evolve()
{

    evolveNextGeneration(grid, rowCount, columnCount);
    update();
}

void Grid::setTimer()
{
    timer = new QTimer(this);
    timer->setInterval(300);
    //connect(timer, SIGNAL(timeout()), this, SLOT(evolve()));
}

void Grid::on_startPushButton_clicked()
{
    timer->start();
    connect(ui->startPushButton, SIGNAL(clicked()), this, SLOT(evolve()));
    connect(timer, SIGNAL(timeout()), this, SLOT(evolve()));
}

