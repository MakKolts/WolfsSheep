#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "field.h"
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QTimer>

namespace Ui {
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();
  void prepareField(int x,int y, int r);

protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);

private slots:
  void on_wolf_nums_valueChanged(int arg1);

  void on_sheep_nums_valueChanged(int arg1);

  void on_rndWolf_clicked();

  void on_rndSheep_clicked();

  void on_start_clicked();

  void on_stop_clicked();

  void on_step_clicked();

  void on_autoplay_clicked();

  void on_pause_clicked();

private:
  Ui::Widget *ui;
  Field *field;
  QImage *img;
  void autoplay();
  bool autostepping;
  int speed;
};

#endif // WIDGET_H
