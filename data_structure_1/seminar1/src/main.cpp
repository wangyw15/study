#include <iostream>
#include <string>

#include "headers/RabinKarp.hpp"
#include "headers/KMP.hpp"

using namespace std;

void test(const string &pat, const string &str)
{
    int compare = 0;
    cout << "  pattern: " << pat << endl;
    cout << "   source: " << str << endl;
    KMPFind(pat, str, compare);
    cout << "      KMP: " << compare << endl;
    RefinedRabinKarp(pat, str, compare);
    cout << "RabinKarp: " << compare << endl << endl;
}

int main()
{
    string T1 = "AKJKDJKASJDKK";
    string P1 = "JKA";
    test(P1, T1);

    string T2 = "asjdhjkahdjk";
    string P2 = "hjk";
    test(P2, T2);

    string T3 = "10829238740230";
    string P3 = "023";
    test(P3, T3);

    string T4 = "10829238740230";
    string P4 = "021";
    test(P4, T4);

    string T5 = "qw378hf6nADIOU45t";
    string P5 = "6nA";
    test(P5, T5);

    return 0;
}