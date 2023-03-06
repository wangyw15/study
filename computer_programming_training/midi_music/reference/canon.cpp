#include <iostream>
#include <windows.h>
#include <map>
#pragma comment(lib,"winmm.lib")

using namespace std;

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iNote, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iNote << 8) | iStatus | iChannel;
	return midiOutShortMsg(hMidi, dwMessage);
}

enum Scale
{
	Rest = 0, C8 = 108, B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100,
	D7s = 99, D7 = 98, C7s = 97, C7 = 96, B6 = 95, A6s = 94, A6 = 93, G6s = 92, G6 = 91, F6s = 90, F6 = 89,
	E6 = 88, D6s = 87, D6 = 86, C6s = 85, C6 = 84, B5 = 83, A5s = 82, A5 = 81, G5s = 80, G5 = 79, F5s = 78,
	F5 = 77, E5 = 76, D5s = 75, D5 = 74, C5s = 73, C5 = 72, B4 = 71, A4s = 70, A4 = 69, G4s = 68, G4 = 67,
	F4s = 66, F4 = 65, E4 = 64, D4s = 63, D4 = 62, C4s = 61, C4 = 60, B3 = 59, A3s = 58, A3 = 57, G3s = 56,
	G3 = 55, F3s = 54, F3 = 53, E3 = 52, D3s = 51, D3 = 50, C3s = 49, C3 = 48, B2 = 47, A2s = 46, A2 = 45,
	G2s = 44, G2 = 43, F2s = 42, F2 = 41, E2 = 40, D2s = 39, D2 = 38, C2s = 37, C2 = 36, B1 = 35, A1s = 34,
	A1 = 33, G1s = 32, G1 = 31, F1s = 30, F1 = 29, E1 = 28, D1s = 27, D1 = 26, C1s = 25, C1 = 24, B0 = 23,
	A0s = 22, A0 = 21
};
enum Voice
{
	L1 = C3, L2 = D3, L3 = E3, L4 = F3, L5 = G3, L6 = A3, L7 = B3,
	M1 = C4, M2 = D4, M3 = E4, M4 = F4, M5 = G4, M6 = A4, M7 = B4,
	H1 = C5, H2 = D5, H3 = E5, H4 = F5, H5 = G5, H6 = A5, H7 = B5,
	LOW_SPEED = 500, MIDDLE_SPEED = 400, HIGH_SPEED = 300,
	_ = 0XFF
};

void Music()
{
	HMIDIOUT handle;
	midiOutOpen(&handle, 0, 0, 0, 0);

	int volume = 0x7f;
	int voice = 0x0;
	int sleep = 150;
	int music[] = 
	{
		M5,_,_,_,_,_,M3,_,M4,_,M5,_,_,_,_,_,M3,_,M4,_,M5,_,L5,_,L6,_,L7,_,M1,_,M2,_,M3,_,M4,_,
		M3,_,_,_,_,_,M1,_,M2,_,M3,_,_,_,_,_,L3,_,L4,_,L5,_,L6,_,L5,_,L4,_,L5,_,
		M1,_,L7,_,M1,_,L6,_,_,_,_,_,M1,_,L7,_,L6,_,_,_,_,_,L5,_,L4,_,L5,_,L4,_,L3,_,L4,_,L5,_,L6,_,
		L7,_,M1,_,L6,_,_,_,_,_,M1,_,L7,_,M1,_,_,_,_,_,L7,_,M1,_,L7,_,L6,_,L7,_,M1,_,M2,_,M3,_,M4,_,M5,_,
		M5,_,_,_,_,_,M3,_,M4,_,M5,_,_,_,_,_,M3,_,M4,_,M5,_,L5,_,L6,_,L7,_,M1,_,M2,_,M3,_,M4,_,
		M3,_,_,_,_,_,M1,_,M2,_,M3,_,_,_,_,_,L3,_,L4,_,L5,_,L6,_,L5,_,L4,_,L5,_,
		M1,_,L7,_,M1,_,L6,_,_,_,_,_,M1,_,L7,_,L6,_,_,_,_,_,L5,_,L4,_,L5,_,L4,_,L3,_,L4,_,L5,_,L6,_,
		L7,_,M1,_,L6,_,_,_,_,_,M1,_,L7,_,M1,_,_,_,_,_,L7,_,L6,_,L7,_,M1,_,M2,_,M1,_,L7,_,M1,_,L6,_,L7,_,M1,_,_,_,_,_,_,_,_,_,_,_,_
		
	};

	for (int i=0 ; i<=sizeof(music)/sizeof(*music); i++)
	{
		if (music[i] == LOW_SPEED || music[i] == HIGH_SPEED || music[i] == MIDDLE_SPEED)
		{
			sleep = music[i];
			continue;
		}
		if (music[i] == _)
		{
			Sleep(40);
			continue;
		}
		MidiOutMessage(handle, 0x90, 0x0, music[i], 0x7f);
		midiOutShortMsg(handle, voice);
		Sleep(sleep);
	}
	midiOutClose(handle);
}

int main()
{
	Music();
	return 0;
}



