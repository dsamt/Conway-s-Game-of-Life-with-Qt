#ifndef STATS_H
#define STATS_H

#include <QDialog>


namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

    void setCycleInfo(const int& cyc);
    void setDotsCount(const int& cnt);
    void setPctFill(const float& cnt);
    void setNewDotsCount(const int& cnt);
    void setBlanksCount(const int& cnt);
    QColor getColor();

public slots:
    void setColor(const QColor& color);

private:
    Ui::Stats *ui;
    QColor color = Qt::black;

};

#endif // STATS_H
