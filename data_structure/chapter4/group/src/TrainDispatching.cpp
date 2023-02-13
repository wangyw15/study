// test data
// 5, 5 3 1 2 4

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool Train_Dispatching(vector<string> &process)
{
    int n_train;
    cout << "请输入调度的火车数量n：";
    cin >> n_train;
    cout << "请输入火车入站顺序：";
    vector<int> in;
    int nums;
    for (int i = 0; i < n_train; i++)
    {
        cin >> nums;
        in.push_back(nums);
    }
    stack<int> st;
    int i = 1, j = 0;
    while (i <= n_train && j != n_train)
    {
        if (in[j] == i) // 相同直接通过
        {
            i++;
            string str = to_string(in[j]) + "直接通过";
            process.push_back(str);
            j++;
        }
        else // 不相同判断栈
        {
            if (st.empty()) // 栈为空直接进栈
            {
                st.push(in[j]);
                string str = to_string(in[j]) + "进入中间轨道";
                process.push_back(str);
                j++;
            }
            else // 栈不为空
            {
                if (st.top() == i) // 栈顶相同，出栈
                {
                    st.pop();
                    string str = to_string(i) + "从中间轨道出去";
                    process.push_back(str);
                    i++;
                }
                else // 栈顶不同，进栈
                {
                    st.push(in[j]);
                    string str = to_string(in[j]) + "进入中间轨道";
                    process.push_back(str);
                    j++;
                }
            }
        }
    }
    if (!st.empty()) // 进完了栈不为空，全部出栈
    {
        while (!st.empty())
        {
            if (st.top() != i)
            {
                return false;
            }
            st.pop();
            string str = to_string(i) + "从中间轨道出去";
            process.push_back(str);
            i++;
        }
        if (st.empty() && i == n_train + 1)
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

int main()
{
    vector<string> process;
    if (Train_Dispatching(process))
    {
        cout << "可以进行调度，调度过程如下：" << endl;
        for (int i = 0; i <= process.size() - 1; i++)
        {
            cout << process[i] << endl;
        }
    }
    else
    {
        cout << "无法进行调度" << endl;
    }
    return 0;
}