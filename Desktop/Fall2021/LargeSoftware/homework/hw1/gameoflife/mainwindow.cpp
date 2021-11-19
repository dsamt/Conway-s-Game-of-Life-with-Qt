#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
* Constructor for the main window for the game that defines the user interface for the user to interact with
* and define parameters for the games
* Intializes all the various widgets in the main window for the user to play with
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    setSlider();
    setSpinBox();
    setTimerSlider();
}

/*
* Destructor for the class so delete the ui from memory
*/
MainWindow::~MainWindow()
{
    delete ui;
}

/*
* Defines what happens when the user clicks the start button
* Instantaiates a new stats window and grid window to show the game and its corresponding statistics
* sets the varibales up that are neeeded to run a game and the stats windows
* retrives user input and sends it to these classes to set them up and run them accordingly
*/
void MainWindow::on_StartPushButton_clicked()
{
    int time = this->getTimer();
    Stats * stats = new Stats();
    Grid* grid = new Grid(stats, time);
    grid->startTimer();
    grid->setColor(this->getColor());
    stats->setColor(this->getColor());
    grid->getColor();
    grid->setGameSize(this->getGameSize());
    grid->setCellSize(this->getCellSize());
    grid->setWindowTitle("Game #" + QString::number(gameCount));
    stats->setWindowTitle("Game #" + QString::number(gameCount));
    grid->setModal(false);
    stats->setModal(false);
    grid->show();
    stats->show();
    gameCount++;
    dialogs.push_back(grid);
    dialogs.push_back(stats);
}

/*
* Sets up the slider for the game size for the user to choose from a min value of 50 and max value of 400
* sends a signal to the functions to set the info for the main window and to set the game size for the game
* to access
*/
void MainWindow::setSlider()
{
    ui->GameSizeHorizontalSlider->setMinimum(50);
    ui->GameSizeHorizontalSlider->setMaximum(400);
    ui->GameSizeHorizontalSlider->setValue(50);
    ui->GameSizeHorizontalSlider->setTickPosition(QSlider::TicksBelow);


    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderInfo(int)));
    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setGameSize(const int&)));


}

/*
* Sets up the slider for the time delay for the user to choose from a min value of 0 and max value of 1000
* sends a signal to the functions to set the info for the main window and to set the time delay for the game
* to access
*/
void MainWindow::setTimerSlider()
{
    ui->timeDelaySlider->setMinimum(0);
    ui->timeDelaySlider->setMaximum(1000);
    ui->timeDelaySlider->setValue(300);
    ui->timeDelaySlider->setTickPosition(QSlider::TicksBelow);


    connect(ui->timeDelaySlider, SIGNAL(valueChanged(int)), this, SLOT(setTimerInfo(int)));
    connect(ui->timeDelaySlider, SIGNAL(valueChanged(int)), this, SLOT(setTimer(const int&)));


}

/*
* Sets the info for the time delay to be displayed on the main window
*/
void MainWindow::setTimerInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Time Delay: %d", size) + 1;

    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Time Delay: %d", size);

    QString newStr = buffer;

    ui->timeDelayLabel->setText(newStr);

}

/*
* Sets the info for the game size to be displayed on the main window
*/
void MainWindow::setSliderInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Game Size (# of cells): %d", size) + 1;

    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Game Size (# of cells): %d", size);

    QString newStr = buffer;

    ui->sliderLabel->setText(newStr);

}

/*
* Sets up the slider for the cell size for the user to choose from a min value of 50 and max value of 400
* sends a signal to the functions to set the info for the main window and to set the cell size for the game
* to access
*/
void MainWindow::setSpinBox()
{
    ui->cellSizeSpinBox->setMinimum(1);
    ui->cellSizeSpinBox->setMaximum(10);
    ui->cellSizeSpinBox->setValue(1);


    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxInfo(int)));
    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setCellSize(const int&)));
}

/*
* Sets the info for the cell size to be displayed on the main window
*/
void MainWindow::setSpinBoxInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Scale factor: %d", size) + 1;


    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Scale factor: %d", size);

    QString newStr = buffer;

    ui->spinBoxLabel->setText(newStr);
}

/*
* OPens a prompt for the user to select the color and from the user input allows
* for the game to set the color for the cell color and text color for statistics
*/
void MainWindow::on_colorPushButton_clicked()
{
    bool ok = true;
    QColor color = QColorDialog::getColor(Qt::black, this);
        if(ok) {
            this->setColor(color);
        }
}

/*
* Sets the private variable cellColor so that the color can be accessed later based on user input
*/
void MainWindow::setColor(const QColor& color)
{
    cellColor =  color;
}

/*
* Gives access to the private variable cellColor so that is can be read later and set the game up
*/
QColor MainWindow::getColor()
{
    return cellColor;
}

/*
* Sets the private variable gameSize so that the game size can be accessed later based on user input
*/
void MainWindow::setGameSize(const int & size)
{
    gameSize = size;
}

/*
* Sets the pruvate variable scaleFactor so that the cell size can be accessed later based on user input
*/
void MainWindow::setCellSize(const int & size)
{
    scaleFactor = size;
}

/*
* Gives access to the private variable scaleFactor so that is can be read later and set the game up
*/
int MainWindow::getCellSize()
{
    return scaleFactor;
}

/*
* Gives access to the private variable gameSize so that is can be read later and set the game up
*/
int MainWindow::getGameSize()
{
    return gameSize;
}

/*
* Sets the private variable timer so that the time delay can be accessed later based on user input
*/
void MainWindow::setTimer(const int& size)
{
    timer = size;
}

/*
* Gives access to the private variable timer so that is can be read later and set the game up
*/
int MainWindow::getTimer()
{
    return timer;
}

/*
* Defines what happens when the stop button is pressed
* When it is pressed it closes all the active game windows simultaneously
*/
void MainWindow::on_StartPushButton_2_clicked()
{
    for(size_t i = 0; i < dialogs.size(); i++){
        dialogs[i]->close();
    }
    gameCount = 0;
}

