#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>

#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <QTextStream>
//#include "form.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    class Item{
    public:
        Item(int when,int what,QString tag,QString comment){ set(when,what,tag,comment);}
        void set(int when,int what,QString tag,QString comment){ when_=when;what_=what,tag_=tag,comment_=comment;}

        int when_,what_;
        QString tag_,comment_;
    };

    void set_pq(int a,int b){
        if(a==0){p="幼稚園";}
        if(a==1){p="小学校";}
        if(a==2){p="中学校";}
        if(a==3){p="高校";}
        if(a==4){p="大学";}

        if(b==0){q="学んだこと";}
        if(b==1){q="続けたいこと";}
        if(b==2){q="好きだったこと";}
        if(b==3){q="嫌だったこと";}
        if(b==4){q="その他";}
    }

    void set_str(string p,string q,QString c, QString d){
        ostringstream oss;
        string cc=c.toStdString();  //QStringをstringに変換
        string dd = d.toStdString();

        oss <<p<<"|"<<q<<"|"<<cc<<"||"<<dd;
        str = oss.str();  //steingに流し込む
    }



    vector<Item> list;
    vector<string>read;

    int when,what,when2,what2;
    QString tag,comment;

    string str,p,q,word2;//p,qは時期・ジャンルを数字から文字化したもの
    QString qstr;

    explicit MainWindow(QWidget *parent = 0);


    ~MainWindow();

private slots:

    void on_pushButton_save_released();

    void on_pushButton_show_released();

    void on_lineEdit_tag_textChanged(const QString &arg1);

    void on_plainTextEdit_textChanged();

    void on_comboBox_activated(int index);

    void on_comboBox_when_activated(int index);

    void on_comboBox_what_activated(int index);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_comboBox_2_activated(int index);

    void on_comboBox_3_activated(int index);

    void on_action_Open_triggered();

    void on_action_Set_triggered();

private:
    Ui::MainWindow *ui;
//    Form form;

};

#endif // MAINWINDOW_H

