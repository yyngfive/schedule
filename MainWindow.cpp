#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "ui_dialog.h"
#include "dialog.h"
#include <QFont>
#include <QColor>




MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->centralWidget->setMouseTracking(true);
  ui->pushButton->setMouseTracking(true);
  ui->pushButton_2->setMouseTracking(true);
  this->setMouseTracking(true);

  //QString appName = QApplication::applicationName();//程序名称

      //QString appPath = QApplication::applicationFilePath();// 程序路径

    //  appPath = appPath.replace("/","\\");

    //  QSettings *reg=new QSettings(
    //              "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
     //             QSettings::NativeFormat);

    //  QString val = reg->value(appName).toString();// 如果此键不存在，则返回的是空字符串
    //  if(val != appPath)
   //       reg->setValue(appName,appPath);// 如果移除的话，reg->remove(applicationName);

     // reg->deleteLater();


  //QFile qssfile(MAINDIR);
  //qssfile.open(QFile::ReadOnly);
 // QString qss;
  //qss = qssfile.readAll();
  //this->setStyleSheet(qss);

  QLocale locale=QLocale::English;
  week=locale.toString(QDateTime::currentDateTime(),"dddd");
  //设置时间显示的字体
  QPalette palette; palette.setColor(QPalette::WindowText,Qt::black);
  ui->label_CurrentTime->setPalette(palette); //定时器
  QTimer *CurrentTime = new QTimer(this);
  CurrentTime->start(0); //使用定时器信号槽，尽快更新时间的显示
  connect(CurrentTime,&QTimer::timeout,[=](){
     QDateTime current_time = QDateTime::currentDateTime();
     //显示时间，格式为：年-月-日 时：分：秒 周几
     QString StrCurrentTime = current_time.toString("hh:mm");
     //时间显示格式可自由设定，如hh:mm ddd 显示 时：分 周几
     //具体格式见函数QString QDateTime::​toString(const QString & format) const
     ui->label_CurrentTime->setText(StrCurrentTime);
     //ui->label_CurrentTime->setStyleSheet("{color:#565656;}");
     });
  qDebug()<<week;
  updateSet(ui->listWidget,week);
  connect(CurrentTime,&QTimer::timeout,[=](){
      QTime tellTime=QTime::currentTime();
      QString strTime=tellTime.toString("hh:mm:ss");
      for(int i=0;i<9;i++)
        {
          if(strTime==start[i])
            {
              int r3=ui->centralWidget->rect().width();
              ui->listWidget->item(i)->setTextColor(QColor(0xDC,0x14,0x3C,0xFF));
              if(i!=0)
                {
                  ui->listWidget->item(i-1)->setTextColor(QColor(255,255,255,255));
                }
              if(ui->listWidget->isHidden()==false/*&&settings->value("/option/mousecheck").toBool()==true*/)
                {
                  ui->pushButton->setText("↓");
                  ui->listWidget->setVisible(false);
                  this->resize(r3,60);

                }
            }
          if(strTime==end[i])
            {
              int r3=ui->centralWidget->rect().width();
              ui->listWidget->item(i)->setTextColor(QColor(255,255,255,255));
              if(i!=8)
                {
                  ui->listWidget->item(i+1)->setTextColor(QColor(0xDC,0x14,0x3C,0xFF));
                }
               if(ui->listWidget->isHidden()==true/*&&settings->value("/option/mousecheck").toBool()==true*/)
                {
                  ui->pushButton->setText("↑");
                  ui->listWidget->setVisible(true);
                  this->resize(r3,800);

                }
            }
        }
    });
  ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//鼠标移入显示
void MainWindow::enterEvent(QEvent *)
{
  //this->hide();
  int r3=ui->centralWidget->rect().width();
   if(ui->listWidget->isHidden()==true&&settings->value("/option/mousecheck").toBool()==true)
    {
      ui->pushButton->setText("↑");
      ui->listWidget->setVisible(true);
      this->resize(r3,800);
    }


}
//鼠标移出隐藏
void MainWindow::leaveEvent(QEvent *)
{
  //this->show();
  int r3=ui->centralWidget->rect().width();
  if(ui->listWidget->isHidden()==false&&settings->value("/option/mousecheck").toBool()==true)
    {
      ui->pushButton->setText("↓");
      ui->listWidget->setVisible(false);
      this->resize(r3,60);
    }


}

MainWindow::~MainWindow()
{
  delete ui;
  delete settings;
}

//窗口折叠
void MainWindow::on_pushButton_clicked()
{

  int r3=ui->centralWidget->rect().width();
  if(ui->listWidget->isHidden()==true)
   {
      ui->pushButton->setText("↑");
      ui->listWidget->setVisible(true);
      this->resize(r3,800);

    }
  else
    {
      ui->pushButton->setText("↓");
      ui->listWidget->setVisible(false);
      this->resize(r3,60);

    }

}

//退出程序
void MainWindow::on_pushButton_2_clicked()
{

    this->close();
}
//设置界面
void MainWindow::on_pushButton_3_clicked()
{


  Dialog *option = new Dialog(this);
  connect(option,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
  connect(option,SIGNAL(sendBool(bool)),this,SLOT(receiveBool(bool)));
  option->exec();

}
void MainWindow::receiveData(QString data)
{
  if(data == "updatelist")
    {
      MainWindow::updateSet(ui->listWidget,week);
    }

}

void MainWindow::receiveBool(bool check)
{
  settings->setValue("option/mousecheck",QString::number(check));
}


