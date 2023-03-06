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
    MidiOutMessage(hMidiOut, 0xC0, 0, 0, 0);	// ����ͨ��0����ɫΪ����

    MidiOutMessage(hMidiOut, 0x90, 0, 60, 112);	// ��������C(С��1��c1)������112(ff)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// ��������C(С��1��c1)���ٶ�127��������

    MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);	// ����e1������80(mf)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);	// ����e1

    MidiOutMessage(hMidiOut, 0x90, 0, 67, 96);	// ����g1������96(f)
    Sleep(500);
    MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);	// ����g1

    MidiOutMessage(hMidiOut, 0x90, 0, 60, 80);	// ���ң�����80(mf)
    MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);
    MidiOutMessage(hMidiOut, 0x90, 0, 67, 80);
    MidiOutMessage(hMidiOut, 0x90, 0, 72, 80);
    Sleep(2500);
    MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// ����
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
