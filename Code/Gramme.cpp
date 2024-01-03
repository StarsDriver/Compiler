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
    is_false_gram = false; //语法分析是否出错
}

vector<string>& Grammer::getsym()
{
    if(cur_point>=Words.size()-1) //有一个结束符
    {
        cur_point = Words.size()-1;
    }
    return Words[cur_point++];
}
void Grammer::Program()
{

    LOG.push_back("语法与语义分析开始");
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
                    cout<<"语法分析成功，无语法错误"<<endl;
                }
                LOG.push_back("语法分析与语义分析结束.");
                int count = LOG.size()-2;
                LOG.push_back("共出现："+to_string(count)+"处错误");
            }
            else
            {
                //cout<<sym[1]<<endl;
                is_false = true;
                is_false_gram = true;
                LOG.push_back("语法分析错误：缺少右大括号，主函数未封闭");
                cout<<"缺少右大括号，主函数未封闭"<<endl;
                LOG.push_back("语法分析与语义分析结束.");
                int count = LOG.size()-2;
                LOG.push_back("共出现："+to_string(count)+"处错误");

            }

        }
        else
        {
            is_false = true;
            is_false_gram = true;

            LOG.push_back("语法分析错误：缺少左大括号进入主程序");
            cout<<"缺少左大括号进入主程序"<<endl;
        }
    }
    else
    {
        is_false = true;
        is_false_gram = true;
        LOG.push_back("缺少main");
        cout<<"缺少main"<<endl;

    }
}
void Grammer::Declare()
{

    if((Follow_Declare.find(sym[0]) != Follow_Declare.end() )||(Follow_Declare.find(sym[1]) != Follow_Declare.end())) //sym在Declare Follow集中
    {
        return ; //此时使用空规则
    }else //不在follow集中
    {
        if(sym[1]=="int")
        {
            sym = getsym();
            if(sym[0]=="ID")
            {
                /*语法制导翻译部分*/
                //插入变量表
                if (IDtable.find(sym[1]) != IDtable.end()) //表中已存在，即已定义
                {
                    is_false = true;

                    cout<<"变量"<<sym[1]<<"重复定义！"<<endl;
                    LOG.push_back("语义分析错误：变量"+sym[1]+"重复定义！");
                }
                IDtable.insert({sym[1],0});//初始值都为0
                /*语法制导翻译部分*/
                sym = getsym();
                if(sym[0]==";")
                {
                    sym = getsym();
                    Declare();

                }else
                {
                    is_false = true;

                    //Declare();
                    cout<<"声明语句缺少分号"<<endl;
                    LOG.push_back("语法分析错误：声明语句缺少分号");
                }
            }else
            {
                is_false = true;

                cout<<"类型名后应跟随标识符"<<endl;
                LOG.push_back("语法分析错误：类型名后应跟随标识符");
            }
        }else
        {
            is_false = true;

            cout<<"类型错误，不为int"<<endl;
            LOG.push_back("语法分析错误：类型错误，不为int");
        }
    }
}
void Grammer::Sentence()
{
    if(sym[1]=="if")
    {
        string false_label; //假的则跳到该label
        string out_label; //跳出label
        string BOOL;//分析得到的布尔表达式
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            BOOL = this->Bool();
            if(sym[0]==")")
            {
                false_label = get_label();
                sym = getsym();
                this->quaternion.push_back({"JZ",BOOL,"_",false_label});//加入跳转语句
                this->Sentence();
                out_label = get_label();
                this->quaternion.push_back({"JP","_","_",out_label});//加入跳转语句
                this->quaternion.push_back({false_label,"_","_","_"});//设置标签
                this->ELSE();
                this->quaternion.push_back({out_label,"_","_","_"});//设置标签
            }else
            {
                is_false = true;

                cout<<"if 后的括号未封闭"<<endl;
                LOG.push_back("语法分析错误：if 后的括号未封闭");
            }


        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"if 后应跟进()"<<endl;
        }
    }else if(sym[1]=="while")
    {
        string BOOL;
        string out_label;//标记跳出
        string repeat_label;//标记重新开始循环
        repeat_label = get_label();
        this->quaternion.push_back({repeat_label,"_","_","_"}); //设置标记
        sym = getsym();
        if(sym[0]=="(")
        {
            sym = getsym();
            BOOL = this->Bool();
            out_label = get_label();
            if(sym[0]==")")
            {
                sym = getsym();
                this->quaternion.push_back({"JZ",BOOL,"_",out_label});//加入跳转语句

                this->Sentence();
                this->quaternion.push_back({"JP","_","_",repeat_label});//加入跳转语句
                this->quaternion.push_back({out_label,"_","_","_"}); //设置标记

            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"while 后的括号未封闭"<<endl;
                LOG.push_back("语法分析错误：while 后的括号未封闭");
            }


        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"while 后应跟进()"<<endl;
            LOG.push_back("语法分析错误：while 后应跟进()");
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
            cout<<"语句块大括号未封闭，少\"}\""<<sym[0]<<sym[1]<<Words[cur_point+2][1]<<Words[cur_point+2][0]<<endl;
            LOG.push_back("语法分析错误：语句块大括号未封闭，少\"}\"");
        }

    }else if(sym[0]=="ID")
    {
        if(IDtable.find(sym[1])==IDtable.end())//未定义
        {
            is_false = true;
            cout<<"变量"<<sym[1]<<"未定义即使用！！"<<endl;
            LOG.push_back("语义分析错误：变量"+sym[1]+"未定义即使用！！");
        }
        string id = sym[1];
        sym = getsym();
        if(sym[1]=="=")
        {
            sym = getsym();
            string val = this->Expression();
            this->quaternion.push_back({"=",val,"_",id});           //添加赋值四元式
            if(sym[0] ==";")
            {
                sym = getsym();
            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"赋值语句最右缺少分号;"<<endl;
                LOG.push_back("语法分析错误：赋值语句最右缺少分号;");
            }

        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"错误符号：("<<sym[0]<<","<<sym[1]<<")"<<endl;
            cout<<"标识符后需跟随赋值符号\"=\""<<endl;
            LOG.push_back("语法分析错误：标识符后需跟随赋值符号\"=\"");
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
                    this->quaternion.push_back({"=",val,"_",id});           //添加赋值四元式
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
                                    this->quaternion.push_back({"=",val,"_",id});           //添加赋值四元式
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
                                        cout<<"for循环右侧括号未封闭"<<endl;
                                        LOG.push_back("语法分析错误：for循环右侧括号未封闭");
                                    }
                                }else
                                {
                                    is_false = true;
                                    is_false_gram = true;
                                    cout<<"for语句第三个表达式标识符右缺少="<<endl;
                                    LOG.push_back("语法分析错误：for语句第三个表达式标识符右缺少=");
                                }
                            }else
                            {
                                is_false = true;
                                is_false_gram = true;
                                cout<<"for后表达式错误"<<endl;
                                LOG.push_back("语法分析错误：for后表达式错误");
                            }


                        }else
                        {
                            is_false = true;
                            is_false_gram = true;
                            cout<<"for语句缺少分号;"<<endl;
                            LOG.push_back("语法分析错误：for语句缺少分号;");
                        }
                    }else
                    {
                        is_false = true;
                        is_false_gram = true;
                        cout<<"for语句缺少分号;"<<endl;
                        LOG.push_back("语法分析错误：for语句缺少分号");
                    }


                }else
                {
                    is_false = true;
                    is_false_gram = true;
                    cout<<"标识符后缺少赋值符号"<<endl;
                    LOG.push_back("语法分析错误：标识符后缺少赋值符号");
                }


            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"for后的表达式错误"<<endl;
                LOG.push_back("语法分析错误：for后的表达式错误");
            }
        }else
        {
            is_false = true;
            is_false_gram = true;
            cout<<"for后面缺少("<<endl;
            LOG.push_back("语法分析错误：for后面缺少");
        }

    }else if(sym[0]=="@")//打印语句
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
                        LOG.push_back("语法分析错误：@语句后缺少；");
                    }
                }else
                {
                    LOG.push_back("语法分析错误：@后括号未封闭，缺少）");
                }

            }else
            {
                cout<<"@应打印标识符"<<endl;
                LOG.push_back("语法分析错误：@应打印标识符,()中缺少标识符");
            }

        }else
        {
            cout<<"@后缺少(";
            LOG.push_back("语法分析错误：@后缺少(");
        }

    }else{
        is_false = true;
        is_false_gram = true;
        cout<<"语句不正确"<<endl;
        LOG.push_back("语法分析错误：语句不正确");
    }
}

void Grammer::ELSE()
{
    if(sym[1]=="else") //有else生成，无else用空
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
    if(sym[0]=="}") //在Language的Follow集中，使用空规则
    {
        return;

    }else
    {
        if(is_false_gram==true) //如果 语法 已出错则不再递归防止无限递归循环
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
        //空
        return pre_res;
    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"布尔表达式错误1"<<endl;
        LOG.push_back("语法分析错误：布尔表达式错误1");
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
    if(sym[0]==")"||sym[1]=="||"||sym[0]==";") //Follow集
    {
        //空
        return preres;
    }else
    {

        is_false = true;
        is_false_gram = true;
        cout<<"布尔表达式错误2"<<endl;
        LOG.push_back("语法分析错误：布尔表达式错误2");
        return preres;
    }

}

string Grammer::Factor_bool()
{
    //返回一个临时变量
    string left;//左因子
    string middle;
    string right;
    string temp = newtemp();
    if(sym[0]=="ID")  //这里可以改成分析表达式？？？
    {
        left = sym[1];
        sym = getsym();
        if(sym[1]==">"||sym[1]=="<"||sym[1]==">="||sym[1]=="<="||sym[1]=="!="||sym[1]=="==") //relop
        {
            middle = sym[1];
            sym = getsym();
            if(sym[0]=="ID")
            {
                if(IDtable.find(sym[1])==IDtable.end())//未定义
                {
                    is_false = true;
                    cout<<"变量"<<sym[1]<<"未定义即使用！！"<<endl;
                    LOG.push_back("语义分析错误：变量"+sym[1]+"未定义即使用！！");
                }
                right = sym[1];
                sym = getsym();
                this->quaternion.push_back({middle,left,right,temp});
                return temp;

            }else
            {
                is_false = true;
                is_false_gram = true;
                cout<<"关系表达式右侧出错"<<endl;
                LOG.push_back("语法分析错误：关系表达式右侧出错");
                return temp;
            }
        }


    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"关系表达式左侧出错"<<endl;
        LOG.push_back("语法分析错误：关系表达式左侧出错");
        return temp;
    }
}

string Grammer::Expression()
{

    string pre_val = this->Term_exp();
    string next_val; //两个量，用于生成四元式
    string temp; //临时变量

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
    if(sym[0]==";"||sym[0]==")")//Follow集  !!!!!!!!!之前少算上了“）”
    {
        return pre_val;

    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"赋值语句最右缺少分号"<<endl;
        LOG.push_back("语法分析错误：赋值语句最右缺少分号");
        return pre_val;
    }

}
string Grammer::Term_exp()
{
    string pre_val = this->Factor_exp();
    string next_val; //两个量，用于生成四元式
    string temp; //临时变量
    while(sym[1]=="*"||sym[1]=="/")
    {
        if(sym[1]=="*")
        {
            sym = getsym();
            next_val = this->Factor_exp();
            temp = newtemp();

            this->quaternion.push_back({"*",pre_val,next_val,temp});
            pre_val = temp;
            //return temp;  !!while还没进行完，不能在此处return

        }else if(sym[1]=="/")
        {
            sym = getsym();
            next_val = this->Factor_exp();
            temp = newtemp();

            this->quaternion.push_back({"/",pre_val,next_val,temp});
            pre_val = temp;
            //return temp;  !!while还没进行完，不能在此处return
        }

    }
    if(sym[1]=="+"||sym[1]=="-"||sym[0]==";"||sym[0]==")")//Follow集  !!!!!!!!!之前少算一个右括号
    {
        return pre_val;
    }else
    {
        is_false = true;
        is_false_gram = true;
        cout<<"赋值语句结尾无分号"<<sym[0]<<sym[1]<<endl;
        LOG.push_back("语法分析错误：赋值语句结尾无分号");
        return pre_val;
    }

}
//返回一个参量，变量名或常数
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
            cout<<"括号未封闭"<<endl;
            LOG.push_back("语法分析错误：括号未封闭");
            return val;
        }
    }else if(sym[0]=="NUM")
    {
        string val = sym[1];
        sym = getsym();
        return val;
    }else if(sym[0]=="ID")
    {
        //查表
        if(IDtable.find(sym[1])==IDtable.end())//未定义
        {
            is_false = true;
            cout<<"变量"<<sym[1]<<"未定义即使用！！"<<endl;
            LOG.push_back("语义分析错误：变量"+sym[1]+"未定义即使用！！");
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
void Grammer::print_quaternion()//打印四元式
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
