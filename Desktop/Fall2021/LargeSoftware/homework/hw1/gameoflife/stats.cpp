#include "stats.h"
#include "ui_stats.h"

/*
* Constructor for the stats class and just sets up the dialog window to display the statistics
*/
Stats::Stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);
}

/*
* Destrctor for the class and just deletes the ui from memory
*/
Stats::~Stats()
{
    delete ui;
}

/*
* Sets the textEdit widget for the cycle info based on the paramter passed from the grid
* class where the statsistic is calculated, also sets the color based on user input
*/
void Stats::setCycleInfo(const int& cyc)
{
    ui->textEdit->setTextColor(this->getColor());
    ui->textEdit->setText( QString::number(cyc));

}

/*
* Sets the textEdit widget for the dots count for a given cycle based on the paramter passed from the grid
* class where the statsistic is calculated, also sets the color based on user input
*/
void Stats::setDotsCount(const int& cnt)
{
    ui->textEdit_2->setTextColor(this->getColor());
    ui->textEdit_2->setText(QString::number(cnt));
}

/*
* Sets the textEdit widget for the percent filled for a given cycle based on the paramter passed from the grid
* class where the statsistic is calculated, also sets the color based on user input
*/
void Stats::setPctFill(const float& cnt)
{
    ui->textEdit_3->setTextColor(this->getColor());
    ui->textEdit_3->setText(QString::number(cnt) + "%");
}

/*
* Sets the textEdit widget for the new dots that were occupied based on the paramter passed from the grid
* class where the statsistic is calculated, also sets the color based on user input
*/
void Stats::setNewDotsCount(const int& cnt)
{
    ui->textEdit_4->setTextColor(this->getColor());
    ui->textEdit_4->setText(QString::number(cnt));
}

/*
* Sets the textEdit widget for the new blanks that were shown based on the paramter passed from the grid
* class where the statsistic is calculated, also sets the color based on user input
*/
void Stats::setBlanksCount(const int& cnt)
{
    ui->textEdit_5->setTextColor(this->getColor());
    ui->textEdit_5->setText(QString::number(cnt));
}

/*
* Sets the private variable color for the text color so it can be accessed later based on user input
*/
void Stats::setColor(const QColor& col)
{
    color = col;
}

/*
* Gives access to the private variable color so it can be read from
*/
QColor Stats::getColor()
{
    return color;
}
