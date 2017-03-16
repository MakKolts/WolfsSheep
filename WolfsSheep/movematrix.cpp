#include "movematrix.h"

MoveMatrix::MoveMatrix()
{
    int i,j;
    for(i = 0; i < 5; i++)
      for(j = 0; j < 5; j++){
          matrix[i][j] = 0;
        }
}

MoveMatrix::MoveMatrix(int r){
  int i,j;
  for(i = 0; i < 5; i++)
    for(j = 0; j < 5; j++){
        matrix[i][j] = 0;
      }
  setRadius(r);
}

int MoveMatrix::setRadius(int r){
  if(r > 2 || r < 1)
    return -1;
  else{
      switch(r){
        case 2:
          for(int j = 0; j < 3; j++){
            for(int i = 0; i < 3; i++){
                matrix[i+j][2-i+j] = -1;
            }
          }
        case 1:
          for(int j = 0; j < 2; j++){
            for(int i = 0; i < 2; i++){
                matrix[1+i+j][2-i+j] = 1;
            }
          }
        default:;
        }
      return 0;
    }
}

int MoveMatrix::getRadius(){
  return 0 - matrix[0][3] + 1;
}

int MoveMatrix::getXY(int x, int y){
  return matrix[x][y];
}
