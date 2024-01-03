#include "Explain.h"
#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

bool explain::isNumber(string str) {
    try {
        size_t pos;
        stoi(str, &pos);
        return pos == str.size(); // ��������ַ����Ƿ񶼱�����Ϊ����
    } catch (...) {
        return false; // �����쳣���ַ����޷�������Ϊ����
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
    int index=0;//���ִ�е���Ԫʽ��
    int left;int right;int res;//����������Ҳ������������'
    while(index<quaternion.size())
    {
        //������Ԫʽ�ĵ�һԪ�жϲ���
        if(quaternion[index][0][0]=='l') //��label
        {
            //index++;
        }else if(quaternion[index][0]=="+")
        {
            if(isdigit(quaternion[index][1][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }

            v_table[quaternion[index][3]] = left+right;


        }else if(quaternion[index][0]=="-")
        {
            if(isdigit(quaternion[index][1][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left-right;

        }else if(quaternion[index][0]=="*")
        {
            if(isdigit(quaternion[index][1][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left*right;

        }else if(quaternion[index][0]=="/")
        {
            if(isdigit(quaternion[index][1][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                left = stoi(quaternion[index][1]);
            }else
            {
                left = v_table[quaternion[index][1]];
            }
            if(isdigit(quaternion[index][2][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
            {
                right = stoi(quaternion[index][2]);
            }else
            {
                right = v_table[quaternion[index][2]];
            }
            v_table[quaternion[index][3]] = left/right;
        }else if(quaternion[index][0]=="=")
        {
            if(isdigit(quaternion[index][1][0]))//ͨ����һ�����ǲ����������ж��Ǳ�ʶ����������
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
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="<")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left<right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]==">=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left>=right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="<=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left<=right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="==")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left==right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="!=")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left!=right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;
        }else if(quaternion[index][0]=="||")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left||right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }else if(quaternion[index][0]=="&&")
        {
            int temp;
            left = v_table[quaternion[index][1]];
            right = v_table[quaternion[index][2]];
            if(left&&right)
            {
                temp = 1; //ʹ��01���沼��ֵ
            }else temp=0;
            v_table[quaternion[index][3]] = temp;

        }
        else if(quaternion[index][0]=="JZ")
        {
            if(v_table[quaternion[index][1]]!=0) //����Ϊ��
            {
                //index++;
            }else
            {
                index = label_index[quaternion[index][3]];//��ת����labelִ��
                continue;
            }
        }else if(quaternion[index][0]=="JP")//��ת
         {
            index = label_index[quaternion[index][3]];
            continue;
        }else if(quaternion[index][0]=="@")
        {
            out.push_back(quaternion[index][3]+"��ֵΪ��"+to_string(v_table[quaternion[index][3]]));
        }
        index++;
        cout<<index;
    }
    for (const auto& pair : v_table) {
            std::cout << "��: " << pair.first << ", ֵ: " << pair.second << std::endl;
        }
}
