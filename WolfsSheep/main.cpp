#include "widget.h"
#include <QApplication>

#define W 200
#define H 130
#define R 1

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();

  w.prepareField(W,H,R);

  return a.exec();
}
