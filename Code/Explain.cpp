#include "Explain.h"
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

bool explain::isNumber(string str) {
    try {
        size_t pos;
        stoi(str, &pos);
        return pos == str.size(); // 检查整个字符串是否都被解析为数字
    } catch (...) {
        return false; // 捕获到异常，字符串无法被解析为数字
    }
}
explain::explain(vector<vector<string>> quaternion)
{
    this->quaternion = quaternion;
}
void explain::scan()
{
    int i=0;
    for(vector<string> four:quaternion)
    {
        if(four[0][0]=='l')
        {
            label_index[four[0]] = i;
        }
        i++;
    }
}
void explain::execute()
{
    this->scan();
    int index=0;//标记执行的四元式行
    int left;int right;int res;//左操作数，右操作数，运算符'
    while(index<quaternion.size())
    {
        //根据四元式的第一元判断操作
        if(quaternion[index][0][0]=='l') //是label
        {
            //index++;
        }else if(quaternion[index][0]=="+")
        {
            if(isdigit(quaternion[index][1][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }

            v_table[quaternion[index][3]] = left+right;


        }else if(quaternion[index][0]=="-")
        {
            if(isdigit(quaternion[index][1][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left-right;

        }else if(quaternion[index][0]=="*")
        {
            if(isdigit(quaternion[index][1][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left*right;

        }else if(quaternion[index][0]=="/")
        {
            if(isdigit(quaternion[index][1][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left/right;
        }else if(quaternion[index][0]=="=")
        {
            if(isdigit(quaternion[index][1][0]))//通过第一个字是不是数字来判断是标识符还是整形
            {
                v_table[quaternion[index][3]] = stoi(quaternion[index][1]);
            }
            else
            {
                v_table[quaternion[index][3]] =  v_table[quaternion[index][1]];
            }
        }else if(quaternion[index][0]==">")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left>right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="<")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left<right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]==">=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left>=right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="<=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left<=right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="==")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left==right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="!=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left!=right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="||")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left||right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="&&")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left&&right)
            {
                temp = 1; //使用01代替布尔值
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }
        else if(quaternion[index][0]=="JZ")
        {
            if(v_table[quaternion[index][1]]!=0) //条件为真
            {
                //index++;
            }else
            {
                index = label_index[quaternion[index][3]];//跳转到该label执行
                continue;
            }
        }else if(quaternion[index][0]=="JP")//跳转
         {
            index = label_index[quaternion[index][3]];
            continue;
        }else if(quaternion[index][0]=="@")
        {
            out.push_back(quaternion[index][3]+"的值为："+to_string(v_table[quaternion[index][3]]));
        }
        index++;
        cout<<index;
    }
    for (const auto& pair : v_table) {
            std::cout << "键: " << pair.first << ", 值: " << pair.second << std::endl;
        }
}
