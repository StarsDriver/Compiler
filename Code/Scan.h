#ifndef CLASS_H
#define CLASS_H
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

class Scanner
{
public:
    string file;//Ҫɨ���Դ�����ļ�·��
    string token; //��ǰ�����ķ���
    string Source;
    vector<vector<string>> WORDS; //��¼�ʷ�������Ԫ����
    vector<string> log;//��¼������־
    bool result;//�ʷ�������������Ƿ���ȷ
    unordered_set<string> KeyWord=
    { "main","int","char","if","else"
      ,"while","return","void"
      ,"string","for"};
    //�ʷ���������
    Scanner(string file);
    void print();
    void scan();
};

#endif // CLASS_H
