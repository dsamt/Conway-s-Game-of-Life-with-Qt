#include "stats.h"
#include "ui_stats.h"

Stats::Stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stats)
{
    ui->setupUi(this);
}

Stats::~Stats()
{
    delete ui;
}

void Stats::setCycleInfo(const int& cyc)
{
    ui->textEdit->setTextColor(this->getColor());
    ui->textEdit->setText( QString::number(cyc));

}

void Stats::setDotsCount(const int& cnt)
{
    ui->textEdit_2->setTextColor(this->getColor());
    ui->textEdit_2->setText(QString::number(cnt));
}

void Stats::setPctFill(const float& cnt)
{
    ui->textEdit_3->setTextColor(this->getColor());
    ui->textEdit_3->setText(QString::number(cnt) + "%");
}

void Stats::setNewDotsCount(const int& cnt)
{
    ui->textEdit_4->setTextColor(this->getColor());
    ui->textEdit_4->setText(QString::number(cnt));
}

void Stats::setBlanksCount(const int& cnt)
{
    ui->textEdit_5->setTextColor(this->getColor());
    ui->textEdit_5->setText(QString::number(cnt));
}

void Stats::setColor(const QColor& col)
{
    color = col;
}

QColor Stats::getColor()
{
    return color;
}
