#include "imagepainter.h"

ImagePainter::ImagePainter()
{

}

void ImagePainter::drawNet(QImage *img, Field *f){
  QPainter painter(img);
  painter.setPen(QColor(50,50,50));
  int imageWidth = img->width();
  int imageHeight = img->height();
  int w = f->getWidth();
  int h = f->getHeight();
  int i;
  for(i = 0; i < w + 1; i++){
      painter.drawLine(i*(imageWidth-1)/w,0,i*(imageWidth-1)/w,imageHeight-1);
    }
  for(i = 0; i < h + 1; i++){
      painter.drawLine(0,i*(imageHeight-1)/h,imageWidth-1,i*(imageHeight-1)/h);
    }
}

void ImagePainter::drawAnimals(QImage *img, Field *f){
  QPainter painter(img);
  painter.setBrush(QBrush(QColor(50,50,50)));
  int imageWidth = img->width();
  int imageHeight = img->height();
  int w = f->getWidth();
  int h = f->getHeight();
  int i,j;
  for(i = 0; i < w; i++){
      for(j = 0; j < h; j++){
          painter.fillRect(i*(imageWidth-1)/w+1,j*(imageHeight-1)/h+1,
                           (imageWidth-1)/w-1,(imageHeight-1)/h-1,
                           QColor(20+150*(((*(f->getSpace()))[j][i] < 0)?1:0),
                                  20+100*(((*(f->getSpace()))[j][i] > 0)?1:0), 20));
      }
  }
}
