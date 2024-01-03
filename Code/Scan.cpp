#include "Scan.h"

#include<iostream>
#include<string>
#include<cctype>
#include<unordered_set>
#include<vector>
#include <fstream>
using namespace std;


Scanner::Scanner(string file)
{
    result = false;
    this->file = file;
    ifstream fileIn(file);

    Source = "";
    if (fileIn.is_open())
    {
        string line;
        while (getline(fileIn, line))
        {
            Source += line;
        }
        Source += '#';
        fileIn.close();
    }
    cout<<Source<<endl;
    string WordType[]=
    {
        "ID",  //标识符
        "NUM",  //十进制整数
        "OPERATOR",  //运算符
        "KEYWORD",  //保留字，关键字
        "STRING"  //字符串
        ";",
        ":","(",")","[","]","{","}"
    };
}
//打印词法分析得到的二元组列表
void Scanner::print()
{
    for(vector<string> two : WORDS)
    {
        cout<<"("<<two[0]<<","<<two[1]<<")"<<endl;
    }
}
//扫描源代码
void Scanner::scan()
{
    int i = 0; //当前扫描到的字符索引
    log.push_back("词法分析开始");
    while(Source[i]!='#')
    {
        //cout<<Source[i]<<endl;
        if (Source[i] == ' ')//遇到空格跳过
        {
            i++;
        }else if(Source[i]=='\t')  //跳过制表符或其他转义符号，\t表示一个字符而不是两个
        {

            i++;
        }
        else
        {
            //是否是数字
            if (isdigit(Source[i]))
            {
                token = ""; //清空当前字符串
                int sum = 0;  //记录当前数字总数
                string type = "int";
                while (isdigit(Source[i]))
                {
                    sum = sum * 10 + (Source[i] - '0');
                    i++;  //字符位置++
                }
                token += to_string(sum);     //数字转化字符串

                this->WORDS.push_back({"NUM",token});/////////////////加入
             }
             else if(isalpha(Source[i]))
             {
                token = "";
                while (isdigit(Source[i]) || isalpha(Source[i]))
                {
                    token += Source[i];   //加入token字符串
                    i++;
                }
                //判断为标识符还是关键字
                if(KeyWord.find(token) != KeyWord.end()) //在关键字集合中
                {
                    this->WORDS.push_back({"KEYWORD",token});/////////////////加入
                }else //是标识符
                {
                    this->WORDS.push_back({"ID",token});/////////////////加入
                }
            }else //是其他符号或运算符
            {
                bool isEnd = false; //用来标记是否走到结尾时双引号未封闭
                token = ""; //清空当前字符串
                string type = "OPERATOR";
                switch (Source[i])
                {
                    case'=':
                        i++;
                        token = "=";
                        if (Source[i] == '=')
                        {
                            i++;
                            token = "==";
                        }
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case'+':
                       i++;
                       token = "+";
                       this->WORDS.push_back({type,token});/////////////////加入
                       break;

                    case'-':
                        i++;
                        token = "-";
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case'*':
                        i++;
                        token = "*";
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case'/':
                        i++;
                        token = "/";
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case'(':
                        i++;
                        token = "(";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case')':
                        i++;
                        token = ")";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case'[':
                        i++;
                        token = "[";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case']':
                        i++;
                        token = "]";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case'{':
                        i++;
                        token = "{";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case'}':
                        i++;
                        token = "}";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case',':
                        i++;
                        token = ",";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case':':
                        i++;
                        token = ":";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case';':
                        i++;
                        token = ";";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;

                    case'>':
                        i++;
                        token = ">";
                        if (Source[i] == '=')
                        {
                            i++;
                            token = ">=";
                        }
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case '<':
                        i++;
                        token = "<";
                        if (Source[i] == '=')
                        {
                            i++;
                            token = "<=";
                        }
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;

                    case'!':
                        i++;
                        if (Source[i] == '=')
                        {
                            i++;
                            token = "!=";
                        }
                        this->WORDS.push_back({type,token});/////////////////加入
                        break;
                    case'|':
                        i++;
                        if (Source[i] == '|')
                        {
                            i++;
                            token = "||";
                            this->WORDS.push_back({type,token});/////////////////加入
                        }else
                        {
                            cout<<"不存在运算符\"|\""<<endl;

                            log.push_back("词法分析错误:不存在运算符|");
                        }

                        break;
                    case'&':
                        i++;
                        if (Source[i] == '&')
                        {
                            i++;
                            token = "&&";
                            this->WORDS.push_back({type,token});/////////////////加入
                        }else
                        {
                            cout<<"不存在运算符\"&\""<<endl;
                            log.push_back("词法分析错误:不存在运算符&");
                        }

                        break;


                    case '"':
                        {
                            token += Source[i];
                            i++;
                            while (Source[i] != '"')
                            {
                                if (Source[i] == '#')
                                {
                                    isEnd = true;  //到结尾时双引号没有封闭
                                    break;
                                }
                                else
                                {
                                    token += Source[i];
                                    i++;   //读完所有非双引号字符
                                }
                             }
                             if (!isEnd)
                             {
                                token += Source[i];
                                i++;
                                this->WORDS.push_back({"STRING",token});/////////////////加入
                                break;
                             }
                             else
                             { //读到结尾，只有一个双引号
                                cout << "双引号只存在一个，非法输入 " << endl;
                                log.push_back("词法分析错误:双引号只存在一个，非法输入");
                                break;
                             }
                        }
                    case '@': //打印
                        i++;
                        token = "@";
                        this->WORDS.push_back({token,"$"});/////////////////加入
                        break;


                    case '#':
                        cout << "\n#结束" << endl;
                        break;

                }
            }
        }
    }
    //最后加上结束符号
    log.push_back("词法分析结束");
    int count = log.size()-2;
    if(count ==0) result=true;
    log.push_back("共出现"+to_string(count)+"个错误");
    this->WORDS.push_back({"#","$"});

}
