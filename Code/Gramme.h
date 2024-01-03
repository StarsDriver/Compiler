#ifndef GRAMME_H
#define GRAMME_H
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
using namespace std;
//递归下降语法分析类
class Grammer
{

public:
    bool is_false = false;//记录递归下降分析过程中是否出现错误
    int cur_point; //当前读取到的词
    vector<vector<string>> Words; //储存词法分析器的分析结果
    Grammer(vector<vector<string>>& Words); //输入词法分析器的结果进行语法分析
    unordered_set<string> Follow_Declare =  //使用哈希集合存放Declare的Follow集
    {"if","while","{","ID","for"}; //其中KEYWORD中的if和while才是Follow
    unordered_map<string,int> IDtable; //使用哈希表存放变量与值的映射
    vector<vector<string>> quaternion;//记录语法制导翻译输出的四元式
    int temp_index = 1;//记录当前使用到的临时变量名字
    int label_index = 1;//记录当前标号序号
    bool is_false_gram = false; //语法分析是否出错


    vector<string> sym;//当前分析字符,二元组
    vector<string>& getsym();//得到下一个待分析字符，二元组
    vector<string> LOG; //记录报错日志
    //递归下降语法分析方法
    void Program();
    void Declare();
    void Sentence();
    string Bool();
    string Expression();
    void Language();
    string Term_bool();
    string Factor_bool();
    string Term_exp();
    string Factor_exp(); //返回属性值
    void ELSE();
    string newtemp(); //获得一个临时变量tn
    void print_quaternion();
    string get_label(); //控制语句设置标号

};

#endif // GRAMME_H
