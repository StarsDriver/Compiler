#ifndef CLASS_H
#define CLASS_H
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

class Scanner
{
public:
    string file;//要扫描的源语言文件路径
    string token; //当前读到的符号
    string Source;
    vector<vector<string>> WORDS; //记录词法分析二元组结果
    vector<string> log;//记录错误日志
    bool result;//词法分析结果或者是否正确
    unordered_set<string> KeyWord=
    { "main","int","char","if","else"
      ,"while","return","void"
      ,"string","for"};
    //词法符号种类
    Scanner(string file);
    void print();
    void scan();
};

#endif // CLASS_H
