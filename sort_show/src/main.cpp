#include <iostream>
#include <string>
#include "sort/sort.h"
#include "util/util.h"
#include "visualizer/visualizer.h"

using namespace std;

typedef void (*p_sort)(visualizer*);

int main()
{
    const p_sort algorithms[] = { optimized_bubble_sort, optimized_insert_sort };
    const char algo_names[][20] = { "√∞≈›≈≈–Ú", "≤Â»Î≈≈–Ú" };
    const auto algo_count = sizeof(algorithms) / sizeof(*algorithms);

    string selection;
    visualizer* vis;
    while (true)
    {
        for (auto i = 0; i < algo_count; i++)
        {
            cout << i + 1 << ". " << algo_names[i] << endl;
        }

        cout << " ‰»Î∆‰À˚‘ÚÕÀ≥ˆ" << endl;
        cout << "«Î ‰»Î–Ú∫≈: ";
        getline(cin, selection);

        if (selection == "1" || selection == "2")
        {
            vis = new visualizer();
            algorithms[selection[0] - '0' - 1](vis);
            vis->dispose();
        }
        else
        {
            break;
        }
    }

    return 0;
}