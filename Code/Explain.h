#ifndef EXPLAIN_H
#define EXPLAIN_H

#include<vector>
#include<string>
#include<unordered_map>
using namespace std;


class explain //��������
{
public:
    vector<string> out; //��¼@�����
    vector<vector<string>> quaternion;//������Ԫʽ
    unordered_map<string,int> v_table;//���ű�
    unordered_map<string,int> label_index;//��ȡ������ǩ����Ԫʽ����
    explain(vector<vector<string>> quaternion);
    void execute();
    void scan();//ɨ��һ�飬��ȡ������ŵ�λ��
    bool isNumber(string str);
};

#endif // EXPLAIN_H
