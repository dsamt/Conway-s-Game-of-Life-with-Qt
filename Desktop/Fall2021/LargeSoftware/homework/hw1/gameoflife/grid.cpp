#include "grid.h"
#include "ui_grid.h"
#include "gamerules.h"

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <iostream>
#include <algorithm>


/*
 * Constructor for the Grid class and sets up multiple things for the Grid UI to run
 * and sets up the basics for the environment to be intilaized for the game
 * Takes an object from the Stats class in order to send data to that dialog window
 * Sets the UI up for the game windows and sets up random distribution for the random intial
 * game state, sets the timer to whatever time is passed to the constructor and is chosen by the user
 * in the main window, this defines the delay between udpdates in the game,
 * connects the timer to the evolve function that updates the game when th timer expires
 * also makeGrid() is called to setup the intial game
*/
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

/*
 * Destructor for the class that deletes the ui for the game
*/
Grid::~Grid()
{
    delete ui;
}

/*
 * Sets up the initial game environment and is called everytime something is updated like game size, cell
 * size, and delay, sets the intial state of the game to a random state for each cell, calculated
 * using the intialCellState() function call
*/
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

/*
 * Used to set the random state for each cell and just takes a random number between 1 and 10 and
 * if that number is less than or equal to 5 the cell is blank, else the cell is occupied
*/
int Grid::initialCellState()
{
    int random = randomDistribution(randNumber);
    return (random <= 5) ? 0 : 1;
}

/*
 * Function that allows for an game grid to be deleted whenever an update is made to the game size,
 * cell size, and time delay. Just goes through the grid array and deletes the elements from memory
*/
void Grid::deleteGrid()
{
    for (int i = 0; i < rowCount; i++)
        {
            delete[] grid[i];
        }
        delete[] grid;
}

/*
 * Defines the game size based on the paramter passed and sets the appropriate fields, rowCount and
 * columnCount, game is a square so these values are equal to the paramter passed
 * Deletes the old game environment and makes a new one updating the ui
*/
void Grid::setGameSize(const int& size)
{
    deleteGrid();
    rowCount = size;
    columnCount = size;
    makeGrid();
    update();
}

/*
 * Defines the game cell's size based on the paramter passed and sets the appropriate fields,
 * scaleFactor, this value is just equal to the paramter passed and just adjusts the scale of the cells displayed
 * Deletes the old game environment and makes a new one updating the ui
*/
void Grid::setCellSize(const int& size)
{
    deleteGrid();
    scaleFactor = size;
    makeGrid();
    update();
}

/*
 * Defines the game cell's color based on the paramter passed and sets the appropriate fields,
 * cellColor, this value is just equal to the paramter passed and just adjusts the color of the cells displayed
 * Deletes the old game environment and makes a new one updating the ui
*/
void Grid::setColor(const QColor& color)
{
    deleteGrid();
    cellColor =  color;
    makeGrid();
    update();
}

/*
* Gives acces to the private variable rowCount, which is equal to columnCount, which is equal to the game size
* so just defines the game size
*/
int Grid::getGameSize() const
{
    return rowCount;
}

/*
* Overrides the method paintevent for a qdialog and sets up the drawing of the environment
*/
void Grid::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintUniverseBorder(painter);
    paintCellGrid(painter);
}

/*
* Method called by paintEvent that sets the cells for the environment based on the value of the
* two dimensional integer array that defines the grid for the game
*/
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

/*
* Paints the border white so that cells are not running into the walls
*/
void Grid::paintUniverseBorder(QPainter& painter)
{
    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(universeFieldColour));
    painter.fillRect(universeBorder, painter.brush());
   // painter.setPen(QPen(universeBorderColour, universeBorderThickness));
    //painter.drawRect(universeBorder);
}

/*
* Method used by paintCellGrid to define what the cell height should be in order to fit
* in the defined space for the ui
*/
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

/*
* Method used by paintCellGrid to define what the cell width should be in order to fit
* in the defined space for the ui
*/
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

/*
* Sets transparency for the environemnt so that the cells actualy pop up and do not blend in with the background
*/
void Grid::setTransparency()
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellColor.setAlpha(255);
}

/*
* Copies the existing grid before it updates so that we know what the last grid looked like so
* we can update the statistics for new dots and blanks by comparing the old board to the new board
*/
void Grid::copyGrid()
{
    past_grid = new int*[rowCount];

    for (int i = 0; i < rowCount; i++){
        past_grid[i] = new int[columnCount];
        for (int j = 0; j < columnCount; j++){
            past_grid[i][j] = grid[i][j];
        }
    }
}

/*
* Updates the grid based on the rules defined by evolveNextGeneration() and also updates the statistics
* for each cycle of the game and sends them to the stats object defined earlier, so that those windows update
* every new cycle as well, called everytime the timer expires
*/
void Grid::evolve()
{
    cycle++;
    copyGrid();
    evolveNextGeneration(grid, rowCount, columnCount);
    update();
    stat->setCycleInfo(this->getCycle());
    stat->setDotsCount(this->calcDots());
    float fill = this->calcPctFill();
    stat->setPctFill(fill);
    stat->setNewDotsCount(this->calcNewDots());
    stat->setBlanksCount(this->calcNewBlanks());
}

/*
* Sets the private variable cycle so that it can be accesed later
*/
void Grid::setCycle(int cyc)
{
    cycle = cyc;
}

/*
* Gives access to the private variable cycle, that defines what cycle the game is running in
*/
int Grid::getCycle()
{
    return cycle;
}

/*
* Sets the timer for the game
*/
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

/*
* Resets the game so that if you close the game using the x in the corner using closeEvent()
* the game is deleted and a new one is created
*/
void Grid::resetGrid()
{
    timer->stop();
    deleteGrid();
    makeGrid();
    update();
}

/*
* Starts the timer so that the game will update
*/
void Grid::startTimer()
{
    timer->start();
}

/*
* Gives access to the private variable cellColor so that the color of the game's cells can be accessed
*/
QColor Grid::getColor()
{
    return cellColor;
}

/*
* Calculates the number of cells occupied ina given cycle of a game
*/
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

/*
* Calculates the ratio of cells occupied to unoccupied in a given game
*/
float Grid::calcPctFill()
{
    float dec = 100 * (static_cast<float> (dotsCount) / static_cast<float>(rowCount * columnCount));
    return dec;
}

/*
* Calculates the number of occupied cells in the current game that were unoccupied in the previous game
*/
int Grid::calcNewDots()
{
    newDotsCount = 0;
    if (dotsHist.size() == 1){
        return this->calcDots();
    }

        for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
               {
                   for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
                   {
                       if (grid[rowIdx][columnIdx] == 1 &&
                               past_grid[rowIdx][columnIdx] == 0)
                       {
                           newDotsCount++;
                       }
                   }
               }
    return newDotsCount;
}

/*
* Calculates the number of unoccupied cells in the current game that were occupied in the previous game
*/
int Grid::calcNewBlanks()
{
    newBlanksCount = 0;
    if (dotsHist.size() == 1){
        return (rowCount * columnCount) - this->calcDots();
    }

        for (int rowIdx = 0; rowIdx < rowCount; rowIdx++)
               {
                   for (int columnIdx = 0; columnIdx < columnCount; columnIdx++)
                   {
                       if (grid[rowIdx][columnIdx] == 0 &&
                               past_grid[rowIdx][columnIdx] == 1)
                       {
                           newBlanksCount++;
                       }
                   }
               }
    return newBlanksCount;
}
