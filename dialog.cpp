#include "dialog.h"
#include "ui_dialog.h"
#include "privatedialog.h"



Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  //QFile qssfile(DIALOGDIR);
  //qssfile.open(QFile::ReadOnly);
  //QString qss;
  //qss = qssfile.readAll();
  //this->setStyleSheet(qss);
  this->setWindowTitle("设置");
  settings=new QSettings(DIR,QSettings::IniFormat);
  //设置鼠标监测
  if(settings->value("option/mousecheck").toBool()==true)
    {
      ui->checkBox->setCheckState(Qt::Checked);
    }
  else
    {
      ui->checkBox->setCheckState(Qt::Unchecked);
    }

  allLayout[0]=ui->gridLayout_0;
  allLayout[1]=ui->gridLayout_1;
  allLayout[2]=ui->gridLayout_2;
  allLayout[3]=ui->gridLayout_3;
  allLayout[4]=ui->gridLayout_4;
  allLayout[5]=ui->gridLayout_5;
  allLayout[6]=ui->gridLayout_6;

  //Read Data
 for(int j=0;j<7;j++)
   {
     settings->beginReadArray(QString::number(j,10));
     for(int i=0;i<9;i++)
       {
         allBox[j][i]=new QComboBox();
         allBox[j][i]->setObjectName(QString::asprintf("comboBox_%d_%d",j,i));
         allBox[j][i]->addItems(list);
         allLayout[j]->addWidget(allBox[j][i],i,1);
         StartTimes[j][i]=new QTimeEdit();
         StartTimes[j][i]->setObjectName(QString::asprintf("starttime_%d_%d",j,i));
         allLayout[j]->addWidget(StartTimes[j][i],i,2);
         EndTimes[j][i]=new QTimeEdit();
         EndTimes[j][i]->setObjectName(QString::asprintf("endtime_%d_%d",j,i));
         allLayout[j]->addWidget(EndTimes[j][i],i,3);
         settings->setArrayIndex(i);
         allBox[j][i]->setCurrentIndex(settings->value("name").toInt());
         //StartTimes[j][i]->setDisplayFormat("HH:mm");

         StartTimes[j][i]->setTime(QTime::fromString(settings->value("start").toString()));
         EndTimes[j][i]->setTime(QTime::fromString(settings->value("end").toString()));
         //StartTimes[j][i]->setTime(QTime(start_h,start_m));

         qDebug()<<settings->value("start").toDouble();
         qDebug()<<getMinute(settings->value("start").toDouble());
       }
     settings->endArray();
   }

}

Dialog::~Dialog()
{
  delete ui;
  delete settings;
}

//应用按钮
void Dialog::on_pushButton_clicked()
{
  //save data
  for(int j=0;j<7;j++)
    {
      settings->beginWriteArray(QString::number(j,10));
      for(int i=0;i<9;i++)
        {
          settings->setArrayIndex(i);
          settings->setValue("name",allBox[j][i]->currentIndex());
          settings->setValue("start",StartTimes[j][i]->time().toString());
          startTime.insert(j+i,StartTimes[j][i]->time().toString());
          settings->setValue("end",EndTimes[j][i]->time().toString());
          endTime.insert(j+i,EndTimes[j][i]->time().toString());
        }
      settings->endArray();
    }

  emit sendData("updatelist");

}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
}

void Dialog::on_checkBox_stateChanged(int arg1)
{
  if(arg1==Qt::Checked)
    {
      settings->setValue("option/mousecheck","true");
      //emit sendBool(true);
    }
  else
    {
      settings->setValue("option/mousecheck","false");
     //emit sendBool(false);
    }

}

//未实现功能
void Dialog::on_pushButton_3_clicked()
{
    QMessageBox::information(this,tr("提示"),tr("此功能没有实现"),QMessageBox::Cancel);
}

void Dialog::on_pushButton_4_clicked()
{
    QMessageBox::information(this,tr("提示"),tr("此功能没有实现"),QMessageBox::Cancel);

}

void Dialog::on_pushButton_5_clicked()
{
  const QUrl regUrl(QLatin1String("https://github.com/yyngfive/schedule"));
  QDesktopServices::openUrl(regUrl);
}
