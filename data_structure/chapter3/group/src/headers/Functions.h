#ifndef FUNCTIONS
#define FUNCTIONS

#include "SeqList.h"
#include <iostream>
using namespace std;

class Functions
{
  private:
    SeqList<double> ce; // ϵ��
    SeqList<int> id;    // ָ��
    int nums;           // ����
  public:
    Functions() : nums(0){};
    Functions(SeqList<int> id, SeqList<double> ce);
    Functions(SeqList<int> id, SeqList<double> ce, int num);
    ~Functions(){};

    friend istream &operator>>(istream &in, Functions &f);
    friend ostream &operator<<(ostream &out, Functions &f);

    void Derivation();
    void Evaluation();
    friend void Subtraction(Functions &f1, Functions &f2);
};

#endif
