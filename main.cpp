#include "MainWindow.h"
#include <QApplication>
#include <qpainter.h>
#include <QDesktopWidget>
#include <QRect>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  //w.setAttribute(Qt::WA_TranslucentBackground, true);
  //w.setWindowOpacity(0.5);

  QDesktopWidget *pdesk=QApplication::desktop();
  QRect deskRect = pdesk->screenGeometry();
  int width,height;
  width = deskRect.width();
  height = deskRect.height();

  w.move(static_cast<int>(width-0.05*width),static_cast<int>(height-0.95*height));
  w.resize(static_cast<int>(0.05*width),800);
  w.setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
  w.setAttribute(Qt::WA_TranslucentBackground);
  w.setWindowOpacity(1.0);
  w.show();

  return a.exec();
}

/*void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 255, 100));  //QColor最后一个参数80代表背景的透明度
}
*/
