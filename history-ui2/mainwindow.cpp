#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <QTextStream>

using namespace std;

#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//入力用・・2つのcomboBoxとTextEditから数値とデータをヘッダーの変数に割り当て
void MainWindow::on_comboBox_when_activated(int index)
{
     when=index;
}

void MainWindow::on_comboBox_what_activated(int index)
{
     what=index;
}

void MainWindow::on_lineEdit_tag_textChanged(const QString &arg1)
{
    tag=arg1;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    comment=ui->plainTextEdit->toPlainText();

}


//Saveボタンが押されたら、ベクトルに入れる。同時にファイル出力する
void MainWindow::on_pushButton_save_released()
{
    list.push_back(Item(when,what,tag,comment));

    string x = tag.toStdString();
    string y = comment.toStdString();

    /*  string filename = "test.txt";

    ofstream writing_file;
    writing_file.open(filename,ios::out);*/

    ofstream fOut("test.txt",ios::app);
    fOut<<when<<endl<<what<<endl<<x<<endl<<y<<endl;

}

//以下、個別検索
//新旧で並べ替え
void MainWindow::on_comboBox_activated(int index)
{
    if(index==0)
    {
        class LessAn {
        public:
            bool operator()(const Item& a, const Item& b)
             {return a.when_ < b.when_;}
        };

        sort(list.begin(), list.end(), LessAn());
        for(int j=0 ; j<list.size() ; ++j){

            Item n=list[j];
            int a=n.when_;
            int b=n.what_;
            QString c=n.tag_;
            QString d=n.comment_;

            set_pq(a,b);
            set_str(p,q,c,d);
            cout<<str<<endl;
        }

    }


    if(index==1)
    {
        class LessAn {
        public:
            bool operator()(const Item& a, const Item& b)
            {return a.when_ > b.when_;}
        };

        sort(list.begin(), list.end(), LessAn());
        for(int j=0 ; j<list.size() ; ++j){

            Item n=list[j];
            int a=n.when_;
            int b=n.what_;
            QString c=n.tag_;
            QString d=n.comment_;

            set_pq(a,b);
            set_str(p,q,c,d);
            cout<<str<<endl;
        }
    }
}

//時期で検索
void MainWindow::on_comboBox_2_activated(int index)
{
    when2=index;
    for(int j=0 ; j<list.size() ; ++j){

        Item n=list[j];
        int a=n.when_;
        int b=n.what_;
        QString c=n.tag_;
        QString d=n.comment_;

        set_pq(a,b);
        set_str(p,q,c,d);

        if(index==0){ if (a==0) {cout<<str<<endl;}}
        if(index==1){ if (a==1) {cout<<str<<endl;}}
        if(index==2){ if (a==2) {cout<<str<<endl;}}
        if(index==3){ if (a==3) {cout<<str<<endl;}}
        if(index==4){ if (a==4) {cout<<str<<endl;}}

    }
}
//ジャンルで検索
void MainWindow::on_comboBox_3_activated(int index)
{
    what2=index;

    for(int j=0 ; j<list.size() ; ++j){

        Item n=list[j];
        int a=n.when_;
        int b=n.what_;
        QString c=n.tag_;
        QString d=n.comment_;

        set_pq(a,b);
        set_str(p,q,c,d);

        if(index==0){ if (b==0) {cout<<str<<endl;}}
        if(index==1){ if (b==1) {cout<<str<<endl;}}
        if(index==2){ if (b==2) {cout<<str<<endl;}}
        if(index==3){ if (b==3) {cout<<str<<endl;}}
        if(index==4){ if (b==4) {cout<<str<<endl;}}

    }
}

//単語で検索
void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    string word = arg1.toStdString();
    word2=arg1.toStdString();

    for(int j=0 ; j<list.size() ; ++j){

        Item n=list[j];
        int a=n.when_;
        int b=n.what_;
        QString c=n.tag_;
        QString d=n.comment_;

        set_pq(a,b);

        set_str(p,q,c,d);


        if (str.find(word) != string::npos) {
            cout<<str<<endl;
        }//wordが一部一致したらcoutする
    }

}

//and検索を実行
void MainWindow::on_pushButton_show_released()
{
    for(int j=0 ; j<list.size() ; ++j){
        Item n=list[j];
        int a=n.when_;
        int b=n.what_;
        QString c=n.tag_;
        QString d=n.comment_;

        set_pq(a,b);
        set_str(p,q,c,d);

        if (a==when2&&b==what2) {
            if(str.find(word2)!= string::npos)
            {cout<<str<<endl;}
        }//時期とジャンルとwordが一致したらcoutする
    }
}









//メニューからOpenが押されたら、テキストデータからstringで読み込み、一度ベクトルに入れる
void MainWindow::on_action_Open_triggered()
{
    ifstream ifs("test.txt");
    string str;
    while (getline(ifs, str))
    {
        read.push_back(str);
    }

}

//メニューからSetが押されたら、先ほどのベクトルからitemのベクトルに入れ直す
void MainWindow::on_action_Set_triggered()
{
    string a,b,c,d;
    int aa,bb;

    for(int j=0 ; j<read.size() ; ++j){

        if(j%4==0){a=read[j];}
        if(j%4==1){b=read[j];}
        if(j%4==2){c=read[j];}
        if(j%4==3){d=read[j];
            aa=stoi(a);
            bb=stoi(b);
            QString cc = QString::fromStdString(c);
            QString dd = QString::fromStdString(d);
            list.push_back(Item(aa,bb,cc,dd));  }

    }


}
