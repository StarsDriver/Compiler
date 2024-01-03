#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Scan.h"
#include "Gramme.h"
#include "Explain.h"
#include<string>
#include<iostream>
#include<fstream>
#include<cctype>
#include<QString>
using namespace std;

bool isNumber(string str) {
    try {
        size_t pos;
        stoi(str, &pos);
        return pos == str.size(); // 检查整个字符串是否都被解析为数字
    } catch (...) {
        return false; // 捕获到异常，字符串无法被解析为数字
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WORD_result = false;//词法分析结果置错
    Grammer_res = false;//语法分析结果置错
    this->file  = "D:/1ADESKTOP/example.txt";



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    string WORDS_res; // 要进行展示的结果
    string LOG_res; //输出日志
    Scanner scanner = Scanner(file);
    scanner.scan(); //调用词法分析程序进行扫描
    for(vector<string> two : scanner.WORDS)
    {
        WORDS_res+="(  "+two[0]+" , "+two[1]+"  )\n";
    }
    ui->label_4->setText(QString::fromStdString(WORDS_res));
    ui->label_4->adjustSize();
    ui->scrollAreaWidgetContents_2->setMinimumHeight(ui->label_4->height());
    for(string log :scanner.log)
    {
        LOG_res += log+"\n";
    }
    cout<<LOG_res;

    ui->label_2->setText(QString::fromLocal8Bit(LOG_res.c_str()));
    ui->label_2->adjustSize();
    ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
    if(scanner.result==true)
    {
        WORD_result = true;
        WORDS_OUT= scanner.WORDS;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    WORD_result = false;
    Grammer_res = false;
    file = this->ui->lineEdit->text().toStdString();
    string Source = "";

    ifstream fileIn(file);

    if (fileIn.is_open())
    {
        string line;
        while (getline(fileIn, line))
        {
            Source += line;
            Source +="\n";
        }
        Source += '#';
        fileIn.close();
    }
    ui->label_3->setText(QString::fromStdString(Source));
    ui->label_3->adjustSize();
    ui->scrollAreaWidgetContents->setMinimumHeight(ui->label_3->height());


}

void MainWindow::on_pushButton_2_clicked()
{
    if(WORD_result==true)
    {
        string LOG_res;
        string res;
        Grammer grammer = Grammer(this->WORDS_OUT);
        grammer.Program();

        for(vector<string> four : grammer.quaternion)
        {
            res+="(  "+four[0]+" , "+four[1]+","+four[2]+","+four[3]+ "  )\n";
        }
        ui->label_4->setText(QString::fromStdString(res));
        ui->label_4->adjustSize();
        ui->scrollAreaWidgetContents_2->setMinimumHeight(ui->label_4->height());


        for(string log :grammer.LOG)
        {
            LOG_res += log+"\n";
        }
        ui->label_2->setText(QString::fromLocal8Bit(LOG_res.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
        if(grammer.is_false==false)//语法语义分析无错误
        {
            Grammer_res = true;
            quaternion_out = grammer.quaternion;

        }


    }else
    {
        string log = "词法分析有报错或未进行词法分析!\n请在词法分析正确后再进行语法和语义分析";
        ui->label_2->setText(QString::fromLocal8Bit(log.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(Grammer_res==true)
    {
        string out = "程序输出:\n";
        explain explainer = explain(quaternion_out);
        explainer.execute();
        for (string mes:explainer.out)
        {
            out+=mes+"\n";
        }
        out += "执行后各变量值为：\n";
        for (const auto& pair : explainer.v_table)
        {
                if(pair.first[0]=='t')
                {
                    if(isNumber(pair.first.substr(1)))//是临时变量则不展示
                        continue;

                }
                out+=pair.first +"="+to_string(pair.second)+"\n";
        }

        ui->label_2->setText(QString::fromLocal8Bit(out.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());

    }else
    {
        string log = "四元式未正确生成，请确保上一步骤已正确执行";
        ui->label_2->setText(QString::fromLocal8Bit(log.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
    }

}
