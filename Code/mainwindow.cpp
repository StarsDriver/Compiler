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
        return pos == str.size(); // ��������ַ����Ƿ񶼱�����Ϊ����
    } catch (...) {
        return false; // �����쳣���ַ����޷�������Ϊ����
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WORD_result = false;//�ʷ���������ô�
    Grammer_res = false;//�﷨��������ô�
    this->file  = "D:/1ADESKTOP/example.txt";



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    string WORDS_res; // Ҫ����չʾ�Ľ��
    string LOG_res; //�����־
    Scanner scanner = Scanner(file);
    scanner.scan(); //���ôʷ������������ɨ��
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
        if(grammer.is_false==false)//�﷨��������޴���
        {
            Grammer_res = true;
            quaternion_out = grammer.quaternion;

        }


    }else
    {
        string log = "�ʷ������б����δ���дʷ�����!\n���ڴʷ�������ȷ���ٽ����﷨���������";
        ui->label_2->setText(QString::fromLocal8Bit(log.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(Grammer_res==true)
    {
        string out = "�������:\n";
        explain explainer = explain(quaternion_out);
        explainer.execute();
        for (string mes:explainer.out)
        {
            out+=mes+"\n";
        }
        out += "ִ�к������ֵΪ��\n";
        for (const auto& pair : explainer.v_table)
        {
                if(pair.first[0]=='t')
                {
                    if(isNumber(pair.first.substr(1)))//����ʱ������չʾ
                        continue;

                }
                out+=pair.first +"="+to_string(pair.second)+"\n";
        }

        ui->label_2->setText(QString::fromLocal8Bit(out.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());

    }else
    {
        string log = "��Ԫʽδ��ȷ���ɣ���ȷ����һ��������ȷִ��";
        ui->label_2->setText(QString::fromLocal8Bit(log.c_str()));
        ui->label_2->adjustSize();
        ui->scrollAreaWidgetContents_3->setMinimumHeight(ui->label_2->height());
    }

}
