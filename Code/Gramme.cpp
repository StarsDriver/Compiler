#include "Gramme.h"
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

Grammer::Grammer(vector<vector<string>>& Words)
{
    this->Words = Words;
    this->cur_point = 0;
    is_false_gram = false; //�﷨�����Ƿ����
}

vector<string>& Grammer::getsym()
{
    if(cur_point>=Words.size()-1) //��һ��������
    {
        cur_point = Words.size()-1;
    }
    return Words[cur_point++];
}
void Grammer::Program()
{

    LOG.push_back("�﷨�����������ʼ");
    sym = getsym();

    if(sym[1]=="main")
    {
        sym = getsym();
        if(sym[0]=="{")
        {
            sym = getsym();
            //cout<<sym[0]<<sym[1];
            this->Declare();
            this->Sentence();
            if(sym[0]=="}")
            {
                if(is_false==false)
                {
                    cout<<"�﷨�����ɹ������﷨����"<<endl;
                }
                LOG.push_back("�﷨�����������������.");
                int count = LOG.size()-2;
                LOG.push_back("�����֣�"+to_string(count)+"������");
            }
            else
            {
                //cout<<sym[1]<<endl;
                is_false = true;
                is_false_gram = true;
                LOG.push_back("�﷨��������ȱ���Ҵ����ţ�������δ���");
                cout<<"ȱ���Ҵ����ţ�������δ���"<<endl;
                LOG.push_back("�﷨�����������������.");
                int count = LOG.size()-2;
                LOG.push_back("�����֣�"+to_string(count)+"������");

            }

        }
        else
        {
            is_false = true;
            is_false_gram = true;

            LOG.push_back("�﷨��������ȱ��������Ž���������");
            cout<<"ȱ��������Ž���������"<<endl;
        }
    }
    else
    {
        is_false = true;
        is_false_gram = true;
        LOG.push_back("ȱ��main");
        cout<<"ȱ��main"<<endl;

    }
}
void Grammer::Declare()
{

    if((Follow_Declare.find(sym[0]) != Follow_Declare.end() )||(Follow_Declare.find(sym[1]) != Follow_Declare.end())) //sym��Declare Follow����
    {
        return ; //��ʱʹ�ÿչ���
    }else //����follow����
    {
        if(sym[1]=="int")
        {
            sym = getsym();
            if(sym[0]=="ID")
            {
                /*�﷨�Ƶ����벿��*/
                //���������
                if (IDtable.find(sym[1]) != IDtable.end()) //�����Ѵ��ڣ����Ѷ���
                {
                    is_false = true;

                    cout<<"����"<<sym[1]<<"�ظ����壡"<<endl;
                    LOG.push_back("����������󣺱���"+sym[1]+"�ظ����壡");
                }
                IDtable.insert({sym[1],0});//��ʼֵ��Ϊ0
                /*�﷨�Ƶ����벿��*/
                sym = getsym();
                if(sym[0]==";")
                {
                    sym = getsym();
                    Declare();

                }else
                {
                    is_false = true;

                    //Declare();
                    cout<<"�������ȱ�ٷֺ�"<<endl;
                    LOG.push_back("�﷨���������������ȱ�ٷֺ�");
                }
            }else
            {
                is_false = true;

                cout<<"��������Ӧ�����ʶ��"<<endl;
                LOG.push_back("�﷨����������������Ӧ�����ʶ��");
            }
        }else
        {
            is_false = true;

            cout<<"���ʹ��󣬲�Ϊint"<<endl;
            LOG.push_back("�﷨�����������ʹ��󣬲�Ϊint");
        }
    }
}
void Grammer::Sentence()
{
    if(sym[1]=="if")
    {
        string false_label; //�ٵ���������label
        string out_label; //����label
        string BOOL;//�����õ��Ĳ������ʽ
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            BOOL = this->Bool();
            if(sym[0]==")")
            {
                false_label = get_label();
                sym = getsym();
                this->quaternion.push_back({"JZ",BOOL,"_",false_label});//������ת���
                this->Sentence();
                out_label = get_label();
                this->quaternion.push_back({"JP","_","_",out_label});//������ת���
                this->quaternion.push_back({false_label,"_","_","_"});//���ñ�ǩ
                this->ELSE();
                this->quaternion.push_back({out_label,"_","_","_"});//���ñ�ǩ
            }else
            {
                is_false = true;

                cout<<"if �������δ���"<<endl;
                LOG.push_back("�﷨��������if �������δ���");
            }


        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"if ��Ӧ����()"<<endl;
        }
    }else if(sym[1]=="while")
    {
        string BOOL;
        string out_label;//�������
        string repeat_label;//������¿�ʼѭ��
        repeat_label = get_label();
        this->quaternion.push_back({repeat_label,"_","_","_"}); //���ñ��
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            BOOL = this->Bool();
            out_label = get_label();
            if(sym[0]==")")
            {
                sym = getsym();
                this->quaternion.push_back({"JZ",BOOL,"_",out_label});//������ת���

                this->Sentence();
                this->quaternion.push_back({"JP","_","_",repeat_label});//������ת���
                this->quaternion.push_back({out_label,"_","_","_"}); //���ñ��

            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"while �������δ���"<<endl;
                LOG.push_back("�﷨��������while �������δ���");
            }


        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"while ��Ӧ����()"<<endl;
            LOG.push_back("�﷨��������while ��Ӧ����()");
        }

    }else if(sym[0]=="{")
    {
        sym = getsym();
        cout<<sym[0]<<sym[1];
        this->Language();
        cout<<sym[0]<<sym[1];
        if(sym[0]=="}")
        {
            sym = getsym();
        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"���������δ��գ���\"}\""<<sym[0]<<sym[1]<<Words[cur_point+2][1]<<Words[cur_point+2][0]<<endl;
            LOG.push_back("�﷨�����������������δ��գ���\"}\"");
        }

    }else if(sym[0]=="ID")
    {
        if(IDtable.find(sym[1])==IDtable.end())//δ����
        {
            is_false = true;
            cout<<"����"<<sym[1]<<"δ���弴ʹ�ã���"<<endl;
            LOG.push_back("����������󣺱���"+sym[1]+"δ���弴ʹ�ã���");
        }
        string id = sym[1];
        sym = getsym();
        if(sym[1]=="=")
        {
            sym = getsym();
            string val = this->Expression();
            this->quaternion.push_back({"=",val,"_",id});           //��Ӹ�ֵ��Ԫʽ
            if(sym[0] ==";")
            {
                sym = getsym();
            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"��ֵ�������ȱ�ٷֺ�;"<<endl;
                LOG.push_back("�﷨�������󣺸�ֵ�������ȱ�ٷֺ�;");
            }

        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"������ţ�("<<sym[0]<<","<<sym[1]<<")"<<endl;
            cout<<"��ʶ��������渳ֵ����\"=\""<<endl;
            LOG.push_back("�﷨�������󣺱�ʶ��������渳ֵ����\"=\"");
        }
    }else if(sym[1]=="for")
    {
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            if(sym[0]=="ID")
            {
                string id = sym[1];
                sym = getsym();
                if(sym[1]=="=")
                {
                    sym = getsym();
                    string val = this->Expression();
                    this->quaternion.push_back({"=",val,"_",id});           //��Ӹ�ֵ��Ԫʽ
                    if(sym[0] ==";")
                    {
                        string repeat_label = get_label();
                        this->quaternion.push_back({repeat_label,"_","_","_"});
                        sym = getsym();
                        string BOOL = this->Bool();
                        string out_label = get_label();
                        string start_label = get_label();
                        this->quaternion.push_back({"JZ",BOOL,"_",out_label});
                        this->quaternion.push_back({"JP","_","_",start_label});
                        if(sym[0]==";")
                        {
                            string repeat_exe_label = get_label();
                            this->quaternion.push_back({repeat_exe_label,"_","_","_"});

                            sym = getsym();
                            if(sym[0]=="ID")
                            {
                                string id = sym[1];
                                sym = getsym();
                                if(sym[1]=="=")
                                {
                                    sym = getsym();
                                    string val = this->Expression();
                                    this->quaternion.push_back({"=",val,"_",id});           //��Ӹ�ֵ��Ԫʽ
                                    this->quaternion.push_back({"JP","_","_",repeat_label});
                                    if(sym[0] == ")")
                                    {
                                        sym = getsym();
                                        this->quaternion.push_back({start_label,"_","_","_"});
                                        this->Sentence();
                                        this->quaternion.push_back({"JP","_","_",repeat_exe_label});
                                        this->quaternion.push_back({out_label,"_","_","_"});


                                    }else
                                    {
                                        is_false = true;
                                        is_false_gram = true;
                                        cout<<"forѭ���Ҳ�����δ���"<<endl;
                                        LOG.push_back("�﷨��������forѭ���Ҳ�����δ���");
                                    }
                                }else
                                {
                                    is_false = true;
                                    is_false_gram = true;
                                    cout<<"for�����������ʽ��ʶ����ȱ��="<<endl;
                                    LOG.push_back("�﷨��������for�����������ʽ��ʶ����ȱ��=");
                                }
                            }else
                            {
                                is_false = true;
                                is_false_gram = true;
                                cout<<"for����ʽ����"<<endl;
                                LOG.push_back("�﷨��������for����ʽ����");
                            }


                        }else
                        {
                            is_false = true;
                            is_false_gram = true;
                            cout<<"for���ȱ�ٷֺ�;"<<endl;
                            LOG.push_back("�﷨��������for���ȱ�ٷֺ�;");
                        }
                    }else
                    {
                        is_false = true;
                        is_false_gram = true;
                        cout<<"for���ȱ�ٷֺ�;"<<endl;
                        LOG.push_back("�﷨��������for���ȱ�ٷֺ�");
                    }


                }else
                {
                    is_false = true;
                    is_false_gram = true;
                    cout<<"��ʶ����ȱ�ٸ�ֵ����"<<endl;
                    LOG.push_back("�﷨�������󣺱�ʶ����ȱ�ٸ�ֵ����");
                }


            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"for��ı��ʽ����"<<endl;
                LOG.push_back("�﷨��������for��ı��ʽ����");
            }
        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"for����ȱ��("<<endl;
            LOG.push_back("�﷨��������for����ȱ��");
        }

    }else if(sym[0]=="@")//��ӡ���
    {
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            if(sym[0]=="ID")
            {
                this->quaternion.push_back({"@","_","_",sym[1]});
                sym = getsym();
                if(sym[0]==")")
                {
                    sym = getsym();
                    if(sym[0]==";")
                    {
                        sym = getsym();
                        return;

                    }else
                    {
                        LOG.push_back("�﷨��������@����ȱ�٣�");
                    }
                }else
                {
                    LOG.push_back("�﷨��������@������δ��գ�ȱ�٣�");
                }

            }else
            {
                cout<<"@Ӧ��ӡ��ʶ��"<<endl;
                LOG.push_back("�﷨��������@Ӧ��ӡ��ʶ��,()��ȱ�ٱ�ʶ��");
            }

        }else
        {
            cout<<"@��ȱ��(";
            LOG.push_back("�﷨��������@��ȱ��(");
        }

    }else{
        is_false = true;
        is_false_gram = true;
        cout<<"��䲻��ȷ"<<endl;
        LOG.push_back("�﷨����������䲻��ȷ");
    }
}

void Grammer::ELSE()
{
    if(sym[1]=="else") //��else���ɣ���else�ÿ�
    {
        sym = getsym();
        this->Sentence();

    }else
    {
        return;
    }
}
void Grammer::Language()
{
    if(sym[0]=="}") //��Language��Follow���У�ʹ�ÿչ���
    {
        return;

    }else
    {
        if(is_false_gram==true) //��� �﷨ �ѳ������ٵݹ��ֹ���޵ݹ�ѭ��
            return;
        //cout<<sym[0]<<sym[1]<<endl;
        this->Sentence();
        this->Language();
    }

}
string Grammer::Bool()
{
    string pre_res;
    string next_res;
    string middle;
    string temp = newtemp();
    pre_res = this->Term_bool();
    while(sym[1]=="||")
    {
        sym = getsym();
        next_res = this->Term_bool();

        middle = "||";
        this->quaternion.push_back({"||",pre_res,next_res,temp});
        pre_res = temp;

    }
    if(sym[0]==")"||sym[0]==";")
    {
        //��
        return pre_res;
    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"�������ʽ����1"<<endl;
        LOG.push_back("�﷨�������󣺲������ʽ����1");
        return pre_res;
    }
}
string Grammer::Term_bool()
{
    string preres = this->Factor_bool();
    string nextres;
    string middle;
    string temp = newtemp();
    while(sym[1]=="&&")
    {
        middle = "&&";
        sym = getsym();
        nextres = this->Factor_bool();
        this->quaternion.push_back({"&&",preres,nextres,temp});
        preres = temp;

    }
    if(sym[0]==")"||sym[1]=="||"||sym[0]==";") //Follow��
    {
        //��
        return preres;
    }else
    {

        is_false = true;
        is_false_gram = true;
        cout<<"�������ʽ����2"<<endl;
        LOG.push_back("�﷨�������󣺲������ʽ����2");
        return preres;
    }

}

string Grammer::Factor_bool()
{
    //����һ����ʱ����
    string left;//������
    string middle;
    string right;
    string temp = newtemp();
    if(sym[0]=="ID")  //������Ըĳɷ������ʽ������
    {
        left = sym[1];
        sym = getsym();
        if(sym[1]==">"||sym[1]=="<"||sym[1]==">="||sym[1]=="<="||sym[1]=="!="||sym[1]=="==") //relop
        {
            middle = sym[1];
            sym = getsym();
            if(sym[0]=="ID")
            {
                if(IDtable.find(sym[1])==IDtable.end())//δ����
                {
                    is_false = true;
                    cout<<"����"<<sym[1]<<"δ���弴ʹ�ã���"<<endl;
                    LOG.push_back("����������󣺱���"+sym[1]+"δ���弴ʹ�ã���");
                }
                right = sym[1];
                sym = getsym();
                this->quaternion.push_back({middle,left,right,temp});
                return temp;

            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"��ϵ���ʽ�Ҳ����"<<endl;
                LOG.push_back("�﷨�������󣺹�ϵ���ʽ�Ҳ����");
                return temp;
            }
        }


    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"��ϵ���ʽ������"<<endl;
        LOG.push_back("�﷨�������󣺹�ϵ���ʽ������");
        return temp;
    }
}

string Grammer::Expression()
{

    string pre_val = this->Term_exp();
    string next_val; //������������������Ԫʽ
    string temp; //��ʱ����

    while(sym[1]=="+"||sym[1]=="-")
    {
        if(sym[1]=="+")
        {
            sym = getsym();
            next_val = this->Term_exp();
            temp = newtemp();
            this->quaternion.push_back({"+",pre_val,next_val,temp});
            pre_val = temp;

        }else if(sym[1]=="-")
        {
            sym = getsym();
            next_val = this->Term_exp();
            temp = newtemp();
            this->quaternion.push_back({"-",pre_val,next_val,temp});
            pre_val = temp;
        }

    }
    if(sym[0]==";"||sym[0]==")")//Follow��  !!!!!!!!!֮ǰ�������ˡ�����
    {
        return pre_val;

    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"��ֵ�������ȱ�ٷֺ�"<<endl;
        LOG.push_back("�﷨�������󣺸�ֵ�������ȱ�ٷֺ�");
        return pre_val;
    }

}
string Grammer::Term_exp()
{
    string pre_val = this->Factor_exp();
    string next_val; //������������������Ԫʽ
    string temp; //��ʱ����
    while(sym[1]=="*"||sym[1]=="/")
    {
        if(sym[1]=="*")
        {
            sym = getsym();
            next_val = this->Factor_exp();
            temp = newtemp();

            this->quaternion.push_back({"*",pre_val,next_val,temp});
            pre_val = temp;
            //return temp;  !!while��û�����꣬�����ڴ˴�return

        }else if(sym[1]=="/")
        {
            sym = getsym();
            next_val = this->Factor_exp();
            temp = newtemp();

            this->quaternion.push_back({"/",pre_val,next_val,temp});
            pre_val = temp;
            //return temp;  !!while��û�����꣬�����ڴ˴�return
        }

    }
    if(sym[1]=="+"||sym[1]=="-"||sym[0]==";"||sym[0]==")")//Follow��  !!!!!!!!!֮ǰ����һ��������
    {
        return pre_val;
    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"��ֵ����β�޷ֺ�"<<sym[0]<<sym[1]<<endl;
        LOG.push_back("�﷨�������󣺸�ֵ����β�޷ֺ�");
        return pre_val;
    }

}
//����һ������������������
string Grammer::Factor_exp()
{
    if(sym[0]=="(")
    {
        sym = getsym();
        string val = this->Expression();
        if(sym[0]==")")
        {
            sym = getsym();
            return val;
        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"����δ���"<<endl;
            LOG.push_back("�﷨������������δ���");
            return val;
        }
    }else if(sym[0]=="NUM")
    {
        string val = sym[1];
        sym = getsym();
        return val;
    }else if(sym[0]=="ID")
    {
        //���
        if(IDtable.find(sym[1])==IDtable.end())//δ����
        {
            is_false = true;
            cout<<"����"<<sym[1]<<"δ���弴ʹ�ã���"<<endl;
            LOG.push_back("����������󣺱���"+sym[1]+"δ���弴ʹ�ã���");
        }
        string val = sym[1];
        sym = getsym();
        //cout<<"here"<<sym[1]<<endl;
        return val;
    }
}
string Grammer::newtemp()
{
    return "t"+to_string(this->temp_index++);
}
void Grammer::print_quaternion()//��ӡ��Ԫʽ
{
    for(vector<string> four : quaternion)
    {
        cout<<"("<< four[0]<<","<< four[1]<<","<< four[2]<<","<<four[3]<<")"<<endl;
    }
}
string Grammer::get_label()
{
    return "label"+to_string(this->label_index++);
}
