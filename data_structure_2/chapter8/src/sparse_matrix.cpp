/*
����һ��1000x1000��ϡ���������1%��Ԫ��Ϊ����Ԫ�أ�����ʹ��ɢ�б���Ϊ�洢�ṹ��ɢ�б���һ���Լ�-ֵ��(key-value)��ʽ�洢���ݵ����ݽṹ����ͨ����ϣ��������ӳ�䵽���е�һ��λ�������ʼ�¼���Լӿ�����ٶȡ�
���ڸ�������ֵ����ֵ�����Խ�������ϳ�һ���ַ���������"row,column"��Ȼ��ʹ�ù�ϣ��������ӳ�䵽ɢ�б��е�һ��λ�á��������Ϳ��Կ���ȷ������Ԫ����ɢ�б��ϵ�λ�á�
����ϡ��������Ԫ���洢�ṹ�ϴ�ȡԪ�ص��㷨��ȣ�ʹ��ɢ�б�洢�ṹ��ʱ�临�Ӷ�ͨ�����͡�����Ԫ���洢�ṹ�У�����һ��Ԫ����Ҫ����������ʱ�临�Ӷ�ΪO(n)������nΪ����Ԫ�ظ���������ɢ�б��У�����һ��Ԫ��ֻ��Ҫ�������ϣֵ��������Ӧλ�ã�ʱ�临�ӶȽӽ�O(1)��
��Ȼ����ֻ�������ϵ�ʱ�临�ӶȱȽϡ�ʵ��Ӧ���У�ɢ�б�����ܻ��ܵ��������Ӱ�죬���ϣ������ѡ�񡢳�ͻ��������ȡ�
*/

#include <iostream>
#include <random>
#include "headers/HashMatrix.hpp"

using namespace std;

int main()
{
    const int CAPACITY = 1000 * 1000 / 100;
    
    // generate numbers
    random_device device;
    mt19937 engine(device());
    uniform_int_distribution<> dis(0, 10000);
    int nums[CAPACITY];
    HashMatrix hashMatrix(CAPACITY);
    for (int i = 0; i < CAPACITY; i++)
    {
        nums[i] = dis(engine);
        hashMatrix.Insert(i / 100, i % 100, nums[i]);
    }
    hashMatrix.Traverse([](MatrixNode node) -> void
        { 
            cout << node.X << ", " << node.Y << ": " << node.Data << endl;
        });
    return 0;
}