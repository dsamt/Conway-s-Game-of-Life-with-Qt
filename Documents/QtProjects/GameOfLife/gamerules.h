#ifndef GAMERULES_H
#define GAMERULES_H


int neighbourSum(int** grid, const int& rowCount, const int& columnCount, const int& rowIdx, const int& columnIdx);
void evolveNextGeneration(int** grid, const int& rowCount, const int& columnCount);

#endif // GAMERULES_H
