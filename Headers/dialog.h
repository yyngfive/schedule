#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSettings>
#include <QLayout>
#include <QComboBox>
#include <QDir>
#include <QTimeEdit>
#include <math.h>
#include <QString>
#include <QFile>

#define DIR QCoreApplication::applicationDirPath() +"/settings.ini"
//#define DIALOGDIR QCoreApplication::applicationDirPath() +"/dialog.qss"
//#define DIR "D://qt-program/qt-designer1/settings.ini"

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
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
  QStringList startTime;
  QStringList endTime;
  QTimeEdit *StartTimes[7][9];
  QTimeEdit *EndTimes[7][9];

  double getHour(double time)
  {
    double hour=0;
    hour = floor(time);
    return hour;
  }
  double getMinute(double time)
  {
    double minute=0;

    minute = time-getHour(time);
    minute = minute*100;
    return minute;
  }


signals:
  void sendData(QString);
  void sendBool(bool);
private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_checkBox_stateChanged(int arg1);

  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

private:
  Ui::Dialog *ui;
  QSettings *settings;
  QGridLayout *allLayout[7];
  QComboBox *allBox[7][9];


};

#endif // DIALOG_H
