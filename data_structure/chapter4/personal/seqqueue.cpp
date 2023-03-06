#include <iostream>
#include "headers/SeqQueue.hpp"

using namespace std;

int main()
{
    SeqQueue<int> queue;
    for (auto i = 0; i < 100; i++)
    {
        queue.EnQueue(i);
    }
    cout << "length: " << queue.Length() << endl << queue << endl << endl;

    cout << "dequeued 0-49, enqueued 200-249" << endl;
    for (auto i = 0; i < 50; i++)
    {
        queue.DeQueue();
    }
    for (auto i = 0; i < 50; i++)
    {
        queue.EnQueue(i + 200);
    }

    cout << "traverse:" << endl;
    queue.Traverse([](int item) { cout << item << " "; });
    cout << endl << endl;

    queue.Clear();
    cout<< "cleared: " << queue
        << "; length: " << queue.Length()
        << "; is " << (queue.IsEmpty() ? "" : "not") << "empty" << endl << endl;

    for (auto i = 100; i < 150; i++)
    {
        queue.EnQueue(i);
    }
    cout << "length: " << queue.Length() << "; head: " << queue.Head() << endl << endl;
    cout << "dequeue: " << endl;
    for (auto i = 100; i < 150; i++)
    {
        cout << queue.DeQueue() << " ";
    }
    cout << endl << endl << "length: " << queue.Length() << endl;
    return 0;
}