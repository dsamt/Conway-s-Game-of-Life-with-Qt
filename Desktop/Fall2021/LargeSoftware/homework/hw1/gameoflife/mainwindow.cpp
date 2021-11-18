#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    setSlider();
    setSpinBox();
    setTimerSlider();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{

}


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

void MainWindow::setSlider()
{
    ui->GameSizeHorizontalSlider->setMinimum(50);
    ui->GameSizeHorizontalSlider->setMaximum(400);
    ui->GameSizeHorizontalSlider->setValue(50);
    ui->GameSizeHorizontalSlider->setTickPosition(QSlider::TicksBelow);


    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderInfo(int)));
    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setGameSize(const int&)));


}

void MainWindow::setTimerSlider()
{
    ui->timeDelaySlider->setMinimum(0);
    ui->timeDelaySlider->setMaximum(1000);
    ui->timeDelaySlider->setValue(300);
    ui->timeDelaySlider->setTickPosition(QSlider::TicksBelow);


    connect(ui->timeDelaySlider, SIGNAL(valueChanged(int)), this, SLOT(setTimerInfo(int)));
    connect(ui->timeDelaySlider, SIGNAL(valueChanged(int)), this, SLOT(setTimer(const int&)));


}

void MainWindow::setTimerInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Time Delay: %d", size) + 1;

    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Time Delay: %d", size);

    QString newStr = buffer;

    ui->timeDelayLabel->setText(newStr);

}


void MainWindow::setSliderInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Game Size (# of cells): %d", size) + 1;

    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Game Size (# of cells): %d", size);

    QString newStr = buffer;

    ui->sliderLabel->setText(newStr);

}

void MainWindow::setSpinBox()
{
    ui->cellSizeSpinBox->setMinimum(1);
    ui->cellSizeSpinBox->setMaximum(10);
    ui->cellSizeSpinBox->setValue(1);


    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxInfo(int)));
    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setCellSize(const int&)));
}


void MainWindow::setSpinBoxInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Scale factor: %d", size) + 1;


    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Scale factor: %d", size);

    QString newStr = buffer;

    ui->spinBoxLabel->setText(newStr);
}


void MainWindow::on_colorPushButton_clicked()
{
    bool ok = true;
    QColor color = QColorDialog::getColor(Qt::black, this);
        if(ok) {
            this->setColor(color);
        }
}

void MainWindow::setColor(const QColor& color)
{
    cellColor =  color;
}

QColor MainWindow::getColor()
{
    return cellColor;
}

void MainWindow::setGameSize(const int & size)
{
    gameSize = size;
}

void MainWindow::setCellSize(const int & size)
{
    scaleFactor = size;
}

int MainWindow::getCellSize()
{
    return scaleFactor;
}

int MainWindow::getGameSize()
{
    return gameSize;
}

void MainWindow::setTimer(const int& size)
{
    timer = size;
}

int MainWindow::getTimer()
{
    return timer;
}




void MainWindow::on_StartPushButton_2_clicked()
{
    for(size_t i = 0; i < dialogs.size(); i++){
        dialogs[i]->close();
    }
    gameCount = 0;
}

