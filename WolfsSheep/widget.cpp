#include "widget.h"
#include "ui_widget.h"
#include "imagepainter.h"


Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  img = new QImage(1001,651,QImage::Format_RGB32);
  img->fill(QColor(20,20,20));
  autostepping = false;
}

Widget::~Widget()
{
  delete ui;
  delete img;
}

void Widget::paintEvent(QPaintEvent *event){
  Q_UNUSED(event);
  QPainter painter(this);
  painter.drawImage(10,10,*img);
}

void Widget::prepareField(int x, int y, int r){
  this->field = new Field(x,y,r);
  ImagePainter::drawNet(img,field);
  repaint();
}

void Widget::on_wolf_nums_valueChanged(int arg1)
{
    field->setWolfNum(arg1);
}

void Widget::on_sheep_nums_valueChanged(int arg1)
{
    field->setSheepNum(arg1);
}

void Widget::on_rndWolf_clicked()
{
    field->clearWolf();
    field->randomDistributionWolf();
    ImagePainter::drawAnimals(img,field);
    repaint();
}

void Widget::on_rndSheep_clicked()
{
    field->clearSheep();
    field->randomDistributionSheep();
    ImagePainter::drawAnimals(img,field);
    repaint();
}

void Widget::on_start_clicked()
{
    ui->flow->setEnabled(true);
    ui->preparation->setEnabled(false);
}

void Widget::on_stop_clicked()
{
  ui->flow->setEnabled(false);
  ui->preparation->setEnabled(true);
  autostepping = false;
}

void Widget::on_step_clicked()
{
    field->step();
    ImagePainter::drawAnimals(img,field);
    repaint();
}

void Widget::timerEvent(QTimerEvent *event){
  if(event->timerId() == speed){
    field->step();
    ImagePainter::drawAnimals(img,field);
    repaint();
    killTimer(speed);
    autoplay();
    }
}

void Widget::on_autoplay_clicked()
{
    autostepping = true;
    autoplay();
}

void Widget::autoplay(){
  if(autostepping){
      speed = startTimer(1000 - 9 * ui->speedSlider->value());
    }
  else{

    }
}

void Widget::on_pause_clicked()
{
    autostepping = false;
}
