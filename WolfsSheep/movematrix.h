#ifndef MOVEMATRIX_H
#define MOVEMATRIX_H


class MoveMatrix
{
public:
  MoveMatrix();
  MoveMatrix(int r);
  int setRadius(int r);
  int getRadius();
  int getXY(int x, int y);

private:
  int matrix[5][5];

};

#endif // MOVEMATRIX_H
