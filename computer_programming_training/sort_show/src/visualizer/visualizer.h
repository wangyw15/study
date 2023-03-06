#ifndef VISUALIZER
#define VISUALIZER

#include <Windows.h>
#include <cstring>

class visualizer
{
public:
    int *data;
    int data_size;

    visualizer();
    visualizer(int size);
    void visualize_swap(int index1, int index2);
    void dispose();

private:
    HMIDIOUT h_midi_output;
    const char *sheet = "1155665 4433221 5544332 5544332 1155665 4433221 ";
    const int sheet_length = strlen(sheet);
    int current_sheet_index = 0;

    void init_midi();
    DWORD midi_send_msg(int status, int channel, int flip, int volume);
    void play_sheet();
};

#endif
