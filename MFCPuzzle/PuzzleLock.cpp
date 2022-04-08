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
    //����
    vector<char> numField;
    //λ��
    vector<Dight> posField;
    //��ȷ��
    vector<Dight> right;
    //������
    vector<Dight> wrong;
    //����
    vector<string> question;

    password = "";

    numField.clear();
    for (int i = 0; i < 10; i++) {
        numField.push_back(i + '0');
    }
    //��������
    random_shuffle(numField.begin(), numField.end());
    //������������ȷ��
    for (int i = 0; i < 3; i++) {
        char d = numField[numField.size() - 1];
        //�������
        password += d;
        Dight dight = { d,i };
        right.push_back(dight);
        numField.pop_back();
    }

    //������
    //password = "618";

    //������ȷ�A��right[0]��B��right[1]��C��right[2]
    random_shuffle(right.begin(), right.end());

    //���ɸ����F1��wrong[0]��F2��wrong[1]��F3��wrong[2]��F4��wrong[3]��F5��wrong[4]��F6��wrong[5]
    for (int i = 0; i < 6; i++) {
        char d = numField[numField.size() - 1];
        //wrongword += d;
        Dight dight = { d,-1 };
        wrong.push_back(dight);
        numField.pop_back();
    }

    //������Ŀ
    string title = "����һ����λ�����������������5����֪�������ƶϳ���ȷ�����Ƕ��٣�\n�����ʽ������abc\nabc����3����ͬ�����֣���123\n\n";

    //����q1
    string q1 = "";
    {
        //q1��ʱ������
        posField.clear();
        posField.push_back(right[0]);
        posField.push_back(wrong[0]);
        posField.push_back(wrong[1]);
        //�ȴ���˳��
        random_shuffle(posField.begin(), posField.end());
        //�ж�A�Ƿ�����ȷ��λ����
        int Apos = right[0].pos;
        
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == right[0].dight) {
                //posField[i]ΪA
                if (i != Apos) {
                    //���A������ȷ��λ����
                    swapElem<Dight>(posField[i], posField[Apos]);
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]ΪF1
                wrong[0].pos = i;
            }
        }
        for (int i = 0; i < 3; i++) {
            q1 += posField[i].dight;
        }
        q1 += "һ��������ȷ����λ����ȷ";
    }

    //����q2
    string q2 = "";
    bool posTab = false;
    {
        //q2��ʱ������
        posField.clear();
        posField.push_back(right[1]);
        posField.push_back(wrong[0]);
        posField.push_back(wrong[2]);

        //�ȴ���˳��
        random_shuffle(posField.begin(), posField.end());
        //�ж�F3�Ƿ���B��λ����
        int F1pos,F3pos,Bpos;
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]ΪF1
                F1pos = i;
            }
            if (posField[i].dight == wrong[2].dight) {
                //posField[i]ΪF3
                F3pos = i;
            }
            if (posField[i].dight == right[1].dight) {
                //posField[i]ΪB
                Bpos = i;
            }
        }

        //�ж�B�Ƿ�����ȷ��λ����

        if (F1pos == right[1].pos || F3pos == right[1].pos) {
            if (F1pos == right[1].pos) {
                //���F1����ȷ��λ���ϣ�����F3���н���
                swapElem<Dight>(posField[F1pos], posField[F3pos]);
            }
        }
        else {
            //���B����ȷ��λ���ϣ�����F3���н���
            swapElem<Dight>(posField[Bpos], posField[F3pos]);
        }

        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == wrong[0].dight) {
                //posField[i]ΪF1�����q2��F1��λ����q1��F1��λ�ò���ͬ����q3����Ҫ�ر�����F1��q1��F1λ����ͬ
                if (wrong[0].pos != i) {
                    posTab = true;
                }
            }
        }
        for (int i = 0; i < 3; i++) {
            q2 += posField[i].dight;
        }
        q2 += "һ��������ȷ����λ�ò���ȷ";
    }

    //����q3
    string q3 = "";
    int Crpos;
    {
        //q3��ʱ������
        posField.clear();
        vector<Dight> vtemp;
        vtemp.push_back(right[0]);
        vtemp.push_back(right[1]);
        random_shuffle(vtemp.begin(), vtemp.end());

        posField.push_back(vtemp[0]);
        posField.push_back(right[2]);
        posField.push_back(wrong[0]);
        //�ȴ���˳��
        random_shuffle(posField.begin(), posField.end());

        if (posTab) {
            //��Ҫ��F1�ŵ�q1��F1λ����
            int F1pos = wrong[0].pos;

            for (int i = 0; i < 3; i++) {
                if (posField[i].dight == wrong[0].dight) {
                    //posField[i]ΪF1
                    if (i != F1pos) {
                        //���F1����q1��F1λ����
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
                //posField[i]ΪT
                t = i;
            }
            if (posField[i].dight == right[2].dight) {
                //posField[i]ΪC
                c = i;
            }
        }
        //��¼һ��C��q3��λ��
        Crpos = c;
        if (t == Tpos || c == Cpos) {
            //T��C֮����һ��λ����ȷ��Ҫ����λ��
            swapElem<Dight>(posField[t], posField[c]);
            Crpos = t;
        }

        for (int i = 0; i < 3; i++) {
            q3 += posField[i].dight;
        }
        q3 += "����������ȷ����λ�ö�����ȷ";
    }

    //����q4
    string q4 = "";
    {
        //q4��ʱ������
        posField.clear();
        posField.push_back(wrong[3]);
        posField.push_back(wrong[4]);
        posField.push_back(wrong[5]);

        //�ȴ���˳��
        random_shuffle(posField.begin(), posField.end());

        for (int i = 0; i < 3; i++) {
            q4 += posField[i].dight;
        }
        q4 += "û��һ��������ȷ";
    }

    //����q5
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

        //��Cʣ�µ�λ��
        int Cpos;
        for (int i = 0; i < 3; i++) {
            if (i != right[2].pos && i != Crpos) {
                Cpos = i;
            }
        }
        for (int i = 0; i < 3; i++) {
            if (posField[i].dight == right[2].dight) {
                //posField[i]ΪC
                if (i != Cpos) {
                    swapElem<Dight>(posField[i], posField[Cpos]);
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            q5 += posField[i].dight;
        }
        q5 += "һ��������ȷ����λ�ò���ȷ";

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
