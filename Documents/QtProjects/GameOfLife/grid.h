#ifndef GRID_H
#define GRID_H

#include <QDialog>
#include "grid_layout.h"

namespace Ui {
class Grid;
}

class Grid : public QDialog
{
    Q_OBJECT

public:
    explicit Grid(QWidget *parent = nullptr);
    ~Grid();    
    void setColor(QColor color);


protected:
    void paintEvent(QPaintEvent* event) override;


public slots:
    void setGameSize(const int& size);
    void setCellSize(const int& size);
    void makeGrid();
    void deleteGrid();

private:
    Ui::Grid *ui;

    int getGameSize() const;
    int getCellSize() const;

    int** grid;
    std::mt19937 randNumber;
    std::uniform_int_distribution<int> randomDistribution;

    int initialCellState();
    int rowCount = 40;
    int columnCount = 10;
    int cellHeight = 10;
    int cellWidth = 10;
    QColor cellColor = Qt::black;
    QColor universeFieldColour = Qt::white;
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 8.0;

    qreal getCellHeight();
    qreal getCellWidth();

    void paintCellGrid(QPainter& painter);
    void paintUniverseBorder(QPainter& painter);

    void setTransparency();


    void setTimer();
    QTimer* timer;

private slots:
     void evolve();
};

#endif // GRID_H
