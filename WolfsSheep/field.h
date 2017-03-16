#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "movematrix.h"

class Field
{
public:
  Field(int x, int y, int r);
  ~Field();
  int getWidth();
  int getHeight();
  void setWolfNum(int x);
  void setSheepNum(int x);
  int getWolfNum();
  int getSheepNum();
  void randomDistributionSheep();
  void randomDistributionWolf();
  void clearWolf();
  void clearSheep();
  std::vector<std::vector<int>>* getSpace();
  void step();

private:
  int width;
  int height;
  std::vector<std::vector<int>> *space;
  int wolfNum;
  int sheepNum;
  MoveMatrix *matrix;
  void makeMove(int x, int y, std::vector<std::vector<int>>* newspace);
  std::pair<int,int> nearestEmty(int x, int y, std::vector<std::vector<int>>* newspace);
  void evolve();
};

#endif // FIELD_H
