#include <iostream>
#include <windows.h>
#include <ctime>
#pragma comment(lib, "winmm.lib")
using namespace std;

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume) {
    DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus | iChannel;
    return midiOutShortMsg(hMidi, dwMessage);
}

void HelloWorld(HMIDIOUT hMidiOut)
{
    MidiOutMessage(hMidiOut, 0xC0, 0, 0, 0);	// 设置通道0的音色为钢琴

    MidiOutMessage(hMidiOut, 0x90, 0, 60, 112);	// 开音中央C(小字1组c1)，力度112(ff)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// 关音中央C(小字1组c1)，速度127（立即）

    MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);	// 开音e1，力度80(mf)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);	// 关音e1

    MidiOutMessage(hMidiOut, 0x90, 0, 67, 96);	// 开音g1，力度96(f)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);	// 关音g1

    MidiOutMessage(hMidiOut, 0x90, 0, 60, 80);	// 和弦，力度80(mf)
    MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);
    MidiOutMessage(hMidiOut, 0x90, 0, 67, 80);
    MidiOutMessage(hMidiOut, 0x90, 0, 72, 80);
    Sleep(2500);
    MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// 关音
    MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);
    MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);
    MidiOutMessage(hMidiOut, 0x80, 0, 72, 127);
}

int main()
{
    HMIDIOUT hMidiOut;
    midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);
    HelloWorld(hMidiOut);
    midiOutClose(hMidiOut);
    return 0;
}
