#include "field.h"
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>

Field::Field(int x, int y,int r)
{
  this->width = x;
  this->height = y;
  this->space = new std::vector<std::vector<int>>(y, std::vector<int>(x,0));
  this->wolfNum = 0;
  this->sheepNum = 0;
  this->matrix = new MoveMatrix(r);
}

Field::~Field(){
  delete space;
  delete matrix;
}

int Field::getHeight(){
  return height;
}

int Field::getWidth(){
  return width;
}

void Field::setSheepNum(int x){
  sheepNum = x;
}

void Field::setWolfNum(int x){
  wolfNum = x;
}

int Field::getSheepNum(){
  return sheepNum;
}

int Field::getWolfNum(){
  return wolfNum;
}

void Field::randomDistributionSheep(){
  std::srand(time(NULL));
  int i;
  for(i = 0; i < sheepNum; i++){
      int x = std::rand() % width;
      int y = std::rand() % height;
      while((*space)[y][x] != 0){
          x = std::rand() % width;
          y = std::rand() % height;
        }
      (*space)[y][x] = 1;
    }
}

void Field::randomDistributionWolf(){
  std::srand(time(NULL));
  int i;
  for(i = 0; i < wolfNum; i++){
      int x = std::rand() % width;
      int y = std::rand() % height;
      while((*space)[y][x] != 0){
          x = std::rand() % width;
          y = std::rand() % height;
        }
      (*space)[y][x] = -1;
    }
}

void Field::clearSheep(){
  int i,j;
  for(i = 0; i < width; i++){
      for(j = 0; j < height; j++){
          (*space)[j][i] = ( (*space)[j][i] > 0)?0:(*space)[j][i];
        }
    }
}

void Field::clearWolf(){
  int i,j;
  for(i = 0; i < width; i++){
      for(j = 0; j < height; j++){
          (*space)[j][i] = ( (*space)[j][i] < 0)?0:(*space)[j][i];
        }
    }
}

std::vector<std::vector<int>>* Field::getSpace(){
  return space;
}

void Field::step(){
  std::vector<std::vector<int>> *newspace =
      new std::vector<std::vector<int>>(height, std::vector<int>(width,0));
  int i,j;
  for(i = 0; i < height; i++){
      for(j = 0; j < width; j++){
          if((*space)[i][j] != 0){
              makeMove(i,j,newspace);
            }
        }
    }
  delete space;
  space = newspace;
  evolve();
}

void Field::makeMove(int y, int x,std::vector<std::vector<int> > *newspace){
  float probabilities[] = {1.0, 1.0, 1.0, 1.0, 1.0};
  float step = (matrix->getRadius() == 2)?0.15:0.4;
  float bigStep = 0.8;
  int i,j,k;
  k = 0;
  for(i = -1; i < 2; i++){
      for(j = -1; j < 2; j++){
          if( i*j == 0){
              if( (*space)[(i + y + height) % height][(j + x + width) % width] * (*space)[y][x] > 0 )
                probabilities[k] = 0;
              else if((*space)[(i + y + height) % height][(j + x + width) % width] * (*space)[y][x] < 0)
                probabilities[k] = probabilities[k] - bigStep * (*space)[y][x]/std::abs((*space)[y][x]);
              else{
                  int s,t, stepnums = 0;
                  for(s = -1; s < 2; s++)
                    for(t = -1; t < 2; t++){
                        stepnums = stepnums +
                            ( ((*space)[(i + y + s + height) % height][(j + x + t + width) % width] *
                            std::abs(matrix->getXY(2 + i + s,2 + j + t)) * (*space)[y][x] < 0 )?1:0 );
                      }
                  probabilities[k] = probabilities[k] - step * stepnums *
                      (*space)[y][x]/std::abs((*space)[y][x]);
                }
              k++;
            }
        }
    }
  float sumprob = 0.0;
  for(k = 0; k < 5; k++){
      sumprob = sumprob + probabilities[k];
    }
  for(k = 0; k < 5; k++){
      probabilities[k] = probabilities[k] / sumprob;
    }
  for(k = 1; k < 5; k++){
      probabilities[k] = probabilities[k] + probabilities[k-1];
    }
  int random = std::rand() % 1000;
  for(k = 0; k < 4; k++){
      if(random < probabilities[k]*1000)
        break;
    }
  int xn = 0, yn = 0;
  switch(k){
    case 0:
      xn = x;
      yn = (y - 1 + height) % height;
     break;
    case 1:
      xn = (x - 1 + width) % width;
      yn = y;
      break;
    case 2:
      xn = x;
      yn = y;
      break;
    case 3:
      xn = (x + 1 + width) % width;
      yn = y;
      break;
    case 4:
      xn = x;
      yn = (y + 1 + height) % height;
      break;
    default:;
    }
  if((*newspace)[y][x] !=0 ){
      if((*newspace)[y][x] == (*space)[yn][xn] && (*newspace)[y][x] * (*space)[yn][xn] < 0){
          (*newspace)[yn][xn] = -1;
          (*newspace)[y][x] = -1;
        }
      else if((*newspace)[yn][xn] == 0){
          (*newspace)[yn][xn] = (*space)[y][x];
        }
      else if((*newspace)[yn][xn] * (*space)[y][x] < 0){
          (*newspace)[yn][xn] = -1; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
      else if((*newspace)[y][x] * (*space)[y][x] < 0){
          (*newspace)[y][x] = -1;
        }
    }
  else{
        if((*newspace)[yn][xn] == 0){
           (*newspace)[yn][xn] = (*space)[y][x];
        }
        else if((*newspace)[yn][xn] * (*space)[y][x] > 0){
           (*newspace)[y][x] = (*space)[y][x];
        }
        else{
           (*newspace)[yn][xn] = -1;
           (*newspace)[y][x] = -1;
        }
    }

}

std::pair<int,int> Field::nearestEmty(int y, int x, std::vector<std::vector<int> > *newspace){
  int i,j;
  for(i = -1; i < 2; i++)
    for(j = -1; j < 2; j++)
      if((*newspace)[(y + i + height) % height][(x + j + width) % width] == 0)
        return std::pair<int,int>((y + i + height) % height,(x + j + width) % width);
  return std::pair<int,int>(-1,-1);
}

void Field::evolve(){
  int i,j;
  for(i = 0; i < height; i++){
      for(j = 0; j < width; j++){
          if((*space)[i][j] > 0){
              (*space)[i][j]++;
              int breeding = 1 + rand() % width;
              if(breeding < (*space)[i][j]){
                  std::pair<int,int> place = nearestEmty(i,j,space);
                  if(place.first != -1){
                      (*space)[i][j] = 1;
                      (*space)[place.first][place.second] = 1;
                    }
                }
            }
          else if((*space)[i][j] < 0){
              (*space)[i][j]--;
              int dying = 0 - (1 + rand() % width);
              if(dying > (*space)[i][j]){
                  (*space)[i][j] = 0;
                }
            }
        }
    }
}
