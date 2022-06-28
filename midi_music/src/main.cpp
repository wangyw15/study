#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>

#include "sheet/sheet.h"

#define KEY_DOWN 0x90
#define KEY_UP 0x80
#define PIANO 0xC0

#pragma comment(lib,"winmm.lib")

enum Voice
{
	L1 = C3, L2 = D3, L3 = E3, L4 = F3, L5 = G3, L6 = A3, L7 = B3,
	M1 = C4, M2 = D4, M3 = E4, M4 = F4, M5 = G4, M6 = A4, M7 = B4,
	H1 = C5, H2 = D5, H3 = E5, H4 = F5, H5 = G5, H6 = A5, H7 = B5,
	LOW_SPEED = 500, MIDDLE_SPEED = 400, HIGH_SPEED = 300,
	_ = 0XFF
};

// https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes

union MidiShortMsg {
	DWORD dwData;
	/// <summary>
	/// 0: MIDI status byte;
	/// 1: first MIDI data byte;
	/// 2: second MIDI data byte;
	/// 3: 0;
	/// </summary>
	BYTE bData[4];
};

DWORD MidiOutMessage(HMIDIOUT hMidi, int status, int channel, int note, int velocity)
{
	MidiShortMsg msg;
	msg.bData[0] = status | channel;
	msg.bData[1] = note;
	msg.bData[2] = velocity;
	msg.bData[3] = 0;
	// DWORD dwMessage = (velocity << 16) | (note << 8) | status | channel;
	//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
	return midiOutShortMsg(hMidi, msg.dwData);
}

int main()
{
	HMIDIOUT midiHandle;
	midiOutOpen(&midiHandle, 0, 0, 0, 0);
	MidiOutMessage(midiHandle, 0xC0, 0, 0, 0);

	auto sheet = ReadSheet("sheet.txt");
	if (sheet.size() == 0)
	{
		std::cout << "sheet.txt不存在或为空" << std::endl;
	}
	else
	{
		std::cout << "播放中..." << std::endl;

		auto expectedTime = 0;
		auto startTime = std::chrono::high_resolution_clock::now();

		auto calibration = 0;
		auto innerStart = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds truePlayTime;
		for (auto i = sheet.begin(); i != sheet.end(); i++)
		{
			innerStart = std::chrono::high_resolution_clock::now();

			// std::cout << ((*i).Note == 0 ? "Rest" : NoteName[(*i).Note - 21]) << " ";
			std::cout << NoteName[(*i).Note - 21] << " ";
			expectedTime += (*i).Duration + 150;

			MidiOutMessage(midiHandle, KEY_DOWN, 0, (*i).Note, (*i).Velocity);

			std::chrono::microseconds sleepTime(((*i).Duration + 150) * 1000 + calibration);
			std::this_thread::sleep_for(sleepTime);

			MidiOutMessage(midiHandle, KEY_UP, 0, (*i).Note, (*i).Velocity);

			truePlayTime = std::chrono::duration_cast<std::chrono::microseconds>
				(std::chrono::high_resolution_clock::now() - innerStart);
			calibration = ((*i).Duration + 150) * 1000 - truePlayTime.count();
		}
		auto endTime = std::chrono::high_resolution_clock::now();
		std::cout << std::endl;

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		std::cout << "理论播放时间：" << expectedTime << ".000ms" << std::endl;
		std::cout << "实际播放时间：" << duration.count() / 1000.000 << "ms" << std::endl;
	}

	midiOutClose(midiHandle);
	std::string line;
	std::getline(std::cin, line);
	return 0;
}



