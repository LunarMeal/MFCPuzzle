#include "pch.h"
#include "PuzzleLock.h"
#include <iostream>
using namespace std;
string PuzzleLock::password = "";
//string wrongword = "";

template <typename T>
void swapElem(T& t1, T& t2) {
    T temp = t1;
    t1 = t2;
    t2 = temp;
}

vector<string> PuzzleLock::getQuestion()
{
    //数域
    vector<char> numField;
    //位域
    vector<Dight> posField;
    //正确项
    vector<Dight> right;
    //干扰项
    vector<Dight> wrong;
    //题序
    vector<string> question;

    password = "";

    numField.clear();
    for (int i = 0; i < 10; i++) {
        numField.push_back(i + '0');
    }
    //打乱数域
    random_shuffle(numField.begin(), numField.end());
    //生成密码与正确项
    for (int i = 0; i < 3; i++) {
        char d = numField[numField.size() - 1];
        //随机密码
        password += d;
        Dight dight = { d,i };
        right.push_back(dight);
        numField.pop_back();
    }

    //测试项
    //password = "618";

    //打乱正确项，A是right[0]，B是right[1]，C是right[2]
    random_shuffle(right.begin(), right.end());

    //生成干扰项，F1是wrong[0]，F2是wrong[1]，F3是wrong[2]，F4是wrong[3]，F5是wrong[4]，F6是wrong[5]
    for (int i = 0; i < 6; i++) {
        char d = numField[numField.size() - 1];
        //wrongword += d;
        Dight dight = { d,-1 };
        wrong.push_back(dight);
        numField.pop_back();
    }

    //生成题目
    string title = "存在一个三位数的密码锁，请根据5个已知条件，推断出正确密码是多少！\n输入格式：密码abc\nabc代表3个不同的数字，如123\n\n";

    //生成q1
    string q1 = "";
    {
        //q1临时作用域
        posField.clear();
        posField.push_back(right[0]);
        posField.push_back(wrong[0]);
        posField.push_back(wrong[1]);
        //先打乱顺序
        random_shuffle(posField.begin(), posField.end());
        //判断A是否在正确的位置上
        int Apos = right[0].pos;
        
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == right[0].dight) {
                //posField[i]为A
                if (i != Apos) {
                    //如果A不在正确的位置上
                    swapElem<Dight>(posField[i], posField[Apos]);
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]为F1
                wrong[0].pos = i;
            }
        }
        for (int i = 0; i < 3; i++) {
            q1 += posField[i].dight;
        }
        q1 += "一个号码正确，且位置正确";
    }

    //生成q2
    string q2 = "";
    bool posTab = false;
    {
        //q2临时作用域
        posField.clear();
        posField.push_back(right[1]);
        posField.push_back(wrong[0]);
        posField.push_back(wrong[2]);

        //先打乱顺序
        random_shuffle(posField.begin(), posField.end());
        //判断F3是否在B的位置上
        int F1pos,F3pos,Bpos;
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]为F1
                F1pos = i;
            }
            if (posField[i].dight == wrong[2].dight) {
                //posField[i]为F3
                F3pos = i;
            }
            if (posField[i].dight == right[1].dight) {
                //posField[i]为B
                Bpos = i;
            }
        }

        //判断B是否在正确的位置上

        if (F1pos == right[1].pos || F3pos == right[1].pos) {
            if (F1pos == right[1].pos) {
                //如果F1在正确的位置上，则与F3进行交换
                swapElem<Dight>(posField[F1pos], posField[F3pos]);
            }
        }
        else {
            //如果B在正确的位置上，则与F3进行交换
            swapElem<Dight>(posField[Bpos], posField[F3pos]);
        }

        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]为F1，如果q2中F1的位置与q1中F1的位置不相同，则q3中需要特别设置F1与q1的F1位置相同
                if (wrong[0].pos != i) {
                    posTab = true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            q2 += posField[i].dight;
        }
        q2 += "一个号码正确，但位置不正确";
    }

    //生成q3
    string q3 = "";
    int Crpos;
    {
        //q3临时作用域
        posField.clear();
        vector<Dight> vtemp;
        vtemp.push_back(right[0]);
        vtemp.push_back(right[1]);
        random_shuffle(vtemp.begin(), vtemp.end());

        posField.push_back(vtemp[0]);
        posField.push_back(right[2]);
        posField.push_back(wrong[0]);
        //先打乱顺序
        random_shuffle(posField.begin(), posField.end());

        if (posTab) {
            //需要把F1放到q1的F1位置上
            int F1pos = wrong[0].pos;

            for (int i = 0; i < 3; i++) {
                if (posField[i].dight == wrong[0].dight) {
                    //posField[i]为F1
                    if (i != F1pos) {
                        //如果F1不在q1的F1位置上
                        swapElem<Dight>(posField[i], posField[F1pos]);
                    }
                }
            }
        }
        int Tpos = vtemp[0].pos;
        int Cpos = right[2].pos;
        int t, c;

        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == vtemp[0].dight) {
                //posField[i]为T
                t = i;
            }
            if (posField[i].dight == right[2].dight) {
                //posField[i]为C
                c = i;
            }
        }
        //记录一下C在q3的位置
        Crpos = c;
        if (t == Tpos || c == Cpos) {
            //T和C之间有一个位置正确都要互换位置
            swapElem<Dight>(posField[t], posField[c]);
            Crpos = t;
        }

        for (int i = 0; i < 3; i++) {
            q3 += posField[i].dight;
        }
        q3 += "两个号码正确，但位置都不正确";
    }

    //生成q4
    string q4 = "";
    {
        //q4临时作用域
        posField.clear();
        posField.push_back(wrong[3]);
        posField.push_back(wrong[4]);
        posField.push_back(wrong[5]);

        //先打乱顺序
        random_shuffle(posField.begin(), posField.end());

        for (int i = 0; i < 3; i++) {
            q4 += posField[i].dight;
        }
        q4 += "没有一个号码正确";
    }

    //生成q5
    string q5 = "";
    {
        posField.clear();
        vector<Dight> vtemp;
        vtemp.push_back(wrong[3]);
        vtemp.push_back(wrong[4]);
        vtemp.push_back(wrong[5]);
        random_shuffle(vtemp.begin(), vtemp.end());

        posField.push_back(vtemp[0]);
        posField.push_back(vtemp[1]);
        posField.push_back(right[2]);

        //找C剩下的位置
        int Cpos;
        for (int i = 0; i < 3; i++) {
            if (i != right[2].pos && i != Crpos) {
                Cpos = i;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == right[2].dight) {
                //posField[i]为C
                if (i != Cpos) {
                    swapElem<Dight>(posField[i], posField[Cpos]);
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            q5 += posField[i].dight;
        }
        q5 += "一个号码正确，但位置不正确";

    }
    question.push_back(q1);
    question.push_back(q2);
    question.push_back(q3);
    question.push_back(q4);
    question.push_back(q5);

    random_shuffle(question.begin(), question.end());

    return question;
}

std::string PuzzleLock::getResult()
{
    return password;
}
