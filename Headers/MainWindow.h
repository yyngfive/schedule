#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <qdebug.h>
#include <QEvent>
#include <QMouseEvent>
#include <QRect>
#include <QTime>
#include <QTimer>

#include <QDesktopServices>
#include <QDialog>
#include <QListWidgetItem>
#include <QString>
#include <QSettings>
#include <QDir>
#include <QDesktopWidget>

#define DIR QCoreApplication::applicationDirPath() +"/settings.ini"
//#define MAINDIR QCoreApplication::applicationDirPath() +"/mainwindow.qss"
//#define DIR "D://qt-program/qt-designer1/settings.ini"


static int weekToInt(QString week)
{
  int week_num=0;
  if(week=="Sunday")
    {
      week_num=0;
    }
  else if (week=="Monday") {
      week_num=1;
    }
  else if (week=="Tuesday") {
      week_num=2;
    }
  else if (week=="Wednesday") {
      week_num=3;
    }
  else if (week=="Thursday") {
      week_num=4;
    }
  else if (week=="Friday") {
      week_num=5;
    }
  else if (week=="Saturday") {
      week_num=6;
    }
  return week_num;
}

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
//  void paintEvent(QPaintEvent *event);

  QStringList start;
  QStringList end;
  QStringList list={
    "语文",
    "数学",
    "英语",
    "物理",
    "化学",
    "生物",
    "政治",
    "历史",
    "地理",
    "音乐",
    "美术",
    "体育",
    "信息",
    "实事",
    "班会",
    "活动",
    "阅读",
    " "
  };

  void updateSet(QListWidget *listWid,QString week)
  {
    settings=new QSettings( DIR,QSettings::IniFormat);
     QString nowday=QString::number(weekToInt(week),10);
     qDebug()<<nowday;
    settings->beginReadArray(nowday);
    for(int i=0;i<9;i++)
      {
        QFont minFont;
        minFont.setPointSize(25);
        minFont.setFamily("微软雅黑");
        QFont maxFont;
        maxFont.setPointSize(27);
        maxFont.setFamily("微软雅黑");
        for(int i=0;i<9;i++)
          {
            listWid->item(i)->setTextColor(QColor(255,255,255,255));
            listWid->item(i)->setFont(minFont);
          }
        settings->setArrayIndex(i);
        listWid->takeItem(i);
        QListWidgetItem *item = new QListWidgetItem;

        item->setText(list[settings->value("name").toInt()]);
        listWid->insertItem(i,item);

        start.insert(i,settings->value("start").toString());
        end.insert(i,settings->value("end").toString());

      }
    settings->endArray();
  }



private slots:


  void on_pushButton_clicked();

  void receiveData(QString);
  void receiveBool(bool);
  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

private:
  Ui::MainWindow *ui;
  QSettings *settings;
  QString week;

protected:

    void leaveEvent(QEvent *e);
    void enterEvent(QEvent *e);
};

#endif  //MAINWINDOW_H
