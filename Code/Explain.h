#ifndef EXPLAIN_H
#define EXPLAIN_H

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;


class explain //解释器类
{
public:
    vector<string> out; //记录@的输出
    vector<vector<string>> quaternion;//解释四元式
    unordered_map<string,int> v_table;//符号表
    unordered_map<string,int> label_index;//获取各个标签的四元式索引
    explain(vector<vector<string>> quaternion);
    void execute();
    void scan();//扫描一遍，获取各个标号的位置
    bool isNumber(string str);
};

#endif // EXPLAIN_H
