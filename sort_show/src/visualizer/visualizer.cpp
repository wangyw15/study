#include <iostream>
#include <Windows.h>
#include "visualizer.h"
#include "../util/util.h"

using namespace std;

visualizer::visualizer()
{
    data_size = 15;
    data = new int[data_size];
    init_data(data, data_size, 0);
    init_midi();
}

visualizer::visualizer(int size)
{
    data_size = size;
    data = new int[data_size];
    init_data(data, data_size, 0);
    init_midi();
}

DWORD visualizer::midi_send_msg(int status, int channel, int flip, int volume)
{
    // 音量 | 音符 | 状态字节(高4位) | 通道(低4位)
    DWORD dwMessage = (volume << 16) | (flip << 8) | status | channel;
    return midiOutShortMsg(h_midi_output, dwMessage);
}

void visualizer::init_midi()
{
    midiOutOpen(&h_midi_output, MIDIMAPPER, NULL, NULL, NULL);
    midi_send_msg(0xC0, 0, 0, 0);	// 设置通道0的音色为钢琴
}

void visualizer::play_sheet()
{
    const char notes[] = { 60, 62, 64, 65, 67, 69, 71 };

    if (current_sheet_index == sheet_length)
    {
        current_sheet_index = 0;
    }

    if (sheet[current_sheet_index] != ' ')
    {
        midi_send_msg(0x90, 0, notes[sheet[current_sheet_index] - '1'], 112);
        Sleep(500);
        midi_send_msg(0x80, 0, notes[sheet[current_sheet_index] - '1'], 127);
    }
    else
    {
        Sleep(500);
    }

    current_sheet_index++;
}

void visualizer::visualize_swap(int index1, int index2)
{
    swap(data[index1], data[index2]);
    // 重绘画面
    clear_console();
    for (auto i = 0; i < data_size; i++)
    {
        if (data[i] < 10)
        {
            cout << 0;
        }
        cout << data[i] << " ";

        for (auto j = 0; j < data[i]; j++)
        {
            cout << "=";
        }
        cout << endl;
    }
    // 放歌
    play_sheet();
    // play_sheet();
    //wait(1000); // 玄学
}

void visualizer::dispose()
{
    delete []data;
    delete this;
}