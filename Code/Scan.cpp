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
        "ID",  //��ʶ��
        "NUM",  //ʮ��������
        "OPERATOR",  //�����
        "KEYWORD",  //�����֣��ؼ���
        "STRING"  //�ַ���
        ";",
        ":","(",")","[","]","{","}"
    };
}
//��ӡ�ʷ������õ��Ķ�Ԫ���б�
void Scanner::print()
{
    for(vector<string> two : WORDS)
    {
        cout<<"("<<two[0]<<","<<two[1]<<")"<<endl;
    }
}
//ɨ��Դ����
void Scanner::scan()
{
    int i = 0; //��ǰɨ�赽���ַ�����
    log.push_back("�ʷ�������ʼ");
    while(Source[i]!='#')
    {
        //cout<<Source[i]<<endl;
        if (Source[i] == ' ')//�����ո�����
        {
            i++;
        }else if(Source[i]=='\t')  //�����Ʊ��������ת����ţ�\t��ʾһ���ַ�����������
        {

            i++;
        }
        else
        {
            //�Ƿ�������
            if (isdigit(Source[i]))
            {
                token = ""; //��յ�ǰ�ַ���
                int sum = 0;  //��¼��ǰ��������
                string type = "int";
                while (isdigit(Source[i]))
                {
                    sum = sum * 10 + (Source[i] - '0');
                    i++;  //�ַ�λ��++
                }
                token += to_string(sum);     //����ת���ַ���

                this->WORDS.push_back({"NUM",token});/////////////////����
             }
             else if(isalpha(Source[i]))
             {
                token = "";
                while (isdigit(Source[i]) || isalpha(Source[i]))
                {
                    token += Source[i];   //����token�ַ���
                    i++;
                }
                //�ж�Ϊ��ʶ�����ǹؼ���
                if(KeyWord.find(token) != KeyWord.end()) //�ڹؼ��ּ�����
                {
                    this->WORDS.push_back({"KEYWORD",token});/////////////////����
                }else //�Ǳ�ʶ��
                {
                    this->WORDS.push_back({"ID",token});/////////////////����
                }
            }else //���������Ż������
            {
                bool isEnd = false; //��������Ƿ��ߵ���βʱ˫����δ���
                token = ""; //��յ�ǰ�ַ���
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
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case'+':
                       i++;
                       token = "+";
                       this->WORDS.push_back({type,token});/////////////////����
                       break;

                    case'-':
                        i++;
                        token = "-";
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case'*':
                        i++;
                        token = "*";
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case'/':
                        i++;
                        token = "/";
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case'(':
                        i++;
                        token = "(";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case')':
                        i++;
                        token = ")";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case'[':
                        i++;
                        token = "[";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case']':
                        i++;
                        token = "]";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case'{':
                        i++;
                        token = "{";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case'}':
                        i++;
                        token = "}";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case',':
                        i++;
                        token = ",";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case':':
                        i++;
                        token = ":";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case';':
                        i++;
                        token = ";";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;

                    case'>':
                        i++;
                        token = ">";
                        if (Source[i] == '=')
                        {
                            i++;
                            token = ">=";
                        }
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case '<':
                        i++;
                        token = "<";
                        if (Source[i] == '=')
                        {
                            i++;
                            token = "<=";
                        }
                        this->WORDS.push_back({type,token});/////////////////����
                        break;

                    case'!':
                        i++;
                        if (Source[i] == '=')
                        {
                            i++;
                            token = "!=";
                        }
                        this->WORDS.push_back({type,token});/////////////////����
                        break;
                    case'|':
                        i++;
                        if (Source[i] == '|')
                        {
                            i++;
                            token = "||";
                            this->WORDS.push_back({type,token});/////////////////����
                        }else
                        {
                            cout<<"�����������\"|\""<<endl;

                            log.push_back("�ʷ���������:�����������|");
                        }

                        break;
                    case'&':
                        i++;
                        if (Source[i] == '&')
                        {
                            i++;
                            token = "&&";
                            this->WORDS.push_back({type,token});/////////////////����
                        }else
                        {
                            cout<<"�����������\"&\""<<endl;
                            log.push_back("�ʷ���������:�����������&");
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
                                    isEnd = true;  //����βʱ˫����û�з��
                                    break;
                                }
                                else
                                {
                                    token += Source[i];
                                    i++;   //�������з�˫�����ַ�
                                }
                             }
                             if (!isEnd)
                             {
                                token += Source[i];
                                i++;
                                this->WORDS.push_back({"STRING",token});/////////////////����
                                break;
                             }
                             else
                             { //������β��ֻ��һ��˫����
                                cout << "˫����ֻ����һ�����Ƿ����� " << endl;
                                log.push_back("�ʷ���������:˫����ֻ����һ�����Ƿ�����");
                                break;
                             }
                        }
                    case '@': //��ӡ
                        i++;
                        token = "@";
                        this->WORDS.push_back({token,"$"});/////////////////����
                        break;


                    case '#':
                        cout << "\n#����" << endl;
                        break;

                }
            }
        }
    }
    //�����Ͻ�������
    log.push_back("�ʷ���������");
    int count = log.size()-2;
    if(count ==0) result=true;
    log.push_back("������"+to_string(count)+"������");
    this->WORDS.push_back({"#","$"});

}
