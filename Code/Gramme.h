#ifndef GRAMME_H
#define GRAMME_H
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
using namespace std;
//�ݹ��½��﷨������
class Grammer
{

public:
    bool is_false = false;//��¼�ݹ��½������������Ƿ���ִ���
    int cur_point; //��ǰ��ȡ���Ĵ�
    vector<vector<string>> Words; //����ʷ��������ķ������
    Grammer(vector<vector<string>>& Words); //����ʷ��������Ľ�������﷨����
    unordered_set<string> Follow_Declare =  //ʹ�ù�ϣ���ϴ��Declare��Follow��
    {"if","while","{","ID","for"}; //����KEYWORD�е�if��while����Follow
    unordered_map<string,int> IDtable; //ʹ�ù�ϣ���ű�����ֵ��ӳ��
    vector<vector<string>> quaternion;//��¼�﷨�Ƶ������������Ԫʽ
    int temp_index = 1;//��¼��ǰʹ�õ�����ʱ��������
    int label_index = 1;//��¼��ǰ������
    bool is_false_gram = false; //�﷨�����Ƿ����


    vector<string> sym;//��ǰ�����ַ�,��Ԫ��
    vector<string>& getsym();//�õ���һ���������ַ�����Ԫ��
    vector<string> LOG; //��¼������־
    //�ݹ��½��﷨��������
    void Program();
    void Declare();
    void Sentence();
    string Bool();
    string Expression();
    void Language();
    string Term_bool();
    string Factor_bool();
    string Term_exp();
    string Factor_exp(); //��������ֵ
    void ELSE();
    string newtemp(); //���һ����ʱ����tn
    void print_quaternion();
    string get_label(); //����������ñ��

};

#endif // GRAMME_H
