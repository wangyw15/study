#ifndef VISUALIZER
#define VISUALIZER

class visualizer
{
public:
    int *data;
    int data_size;

    visualizer();
    visualizer(int size);
    void visualize_swap(int index1, int index2);
    void dispose();
};

#endif