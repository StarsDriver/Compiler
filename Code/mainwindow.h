#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
#include<vector>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    string file; //Ҫ���б����Դ�ļ�
    bool WORD_result;//�ʷ���������Ƿ���ȷ
    bool Grammer_res; //�﷨��������Ƿ���ȷ
    vector<vector<string>> WORDS_OUT;//��¼�ʷ��������
    vector<vector<string>> quaternion_out;//��¼�﷨����������
    vector<string> output;//�������
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
