#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H

#include <QImage>
#include "field.h"
#include <QPainter>

class ImagePainter
{
public:
  ImagePainter();
  static void drawNet(QImage *img, Field *f);
  static void drawAnimals(QImage *img, Field *f);
};

#endif // IMAGEPAINTER_H
