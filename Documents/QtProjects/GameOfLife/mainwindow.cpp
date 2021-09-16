#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    setSlider();
    setSpinBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_StartPushButton_clicked()
{
        //connect(ui->StartPushButton, SIGNAL(clicked()), grid, SLOT(exec()));

    //Grid* grid1 = new Grid(this);
    grid->setModal(true);
    grid->exec();
}

void MainWindow::setSlider()
{
    ui->GameSizeHorizontalSlider->setMinimum(5);
    ui->GameSizeHorizontalSlider->setMaximum(40);
    ui->GameSizeHorizontalSlider->setValue(5);
    ui->GameSizeHorizontalSlider->setTickPosition(QSlider::TicksBelow);

    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), grid, SLOT(setGameSize(const int&)));
    connect(ui->GameSizeHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSliderInfo(int)));
    //connect(ui->GameSizeHorizontalSlider, &QSlider::valueChanged, this, [this]{setGenerationCountInfo(0);});

    //connect(grid, SIGNAL(universeSizeAdjustable(bool)), ui->GameSizeHorizontalSlider, SLOT(setEnabled(bool)));

}


void MainWindow::setSliderInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Game Size (# of cells): %d", size * 10) + 1;

    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Game Size (# of cells): %d", size * 10);

    QString newStr = buffer;

    ui->sliderLabel->setText(newStr);

}

void MainWindow::setSpinBox()
{
    ui->cellSizeSpinBox->setMinimum(1);
    ui->cellSizeSpinBox->setMaximum(10);
    ui->cellSizeSpinBox->setValue(1);
    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), grid, SLOT(setCellSize(const int&)));
    connect(ui->cellSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setSpinBoxInfo(int)));
}


void MainWindow::setSpinBoxInfo(const int& size)
{
    int newStrLen = snprintf(NULL, 0, "Cell Size: %d", size) + 1;


    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "Cell Size: %d", size);

    QString newStr = buffer;

    ui->spinBoxLabel->setText(newStr);
}



void MainWindow::on_colorPushButton_clicked()
{

    bool ok = true;

    QColor color = QColorDialog::getColor(Qt::black, this);

        if(ok) {
            grid->setColor(color);
        }
}

