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
    string file; //要进行编译的源文件
    bool WORD_result;//词法分析结果是否正确
    bool Grammer_res; //语法语义分析是否正确
    vector<vector<string>> WORDS_OUT;//记录词法分析输出
    vector<vector<string>> quaternion_out;//记录语法语义分析输出
    vector<string> output;//运行输出
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
