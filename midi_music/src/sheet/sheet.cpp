#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <sstream>

#include "../types.h"
#include "../visualizer/visualizer.h"

#pragma comment(lib,"winmm.lib")

std::vector<Note> ReadSheet(std::string path)
{
	std::vector<Note> ret;

	std::ifstream file;
	file.open(path, std::ios::in);
	
	int input;
	int index = 0;
	Note current{};
	while (file >> input)
	{
		if (index == 0)
		{
			current.Note = (NoteNumber)input;
			index++;
		}
		else if (index == 1)
		{
			current.Velocity = input;
			index++;
		}
		else
		{
			current.Duration = input;
			ret.push_back(current);
			current = Note{};
			index = 0;
		}
	}
	file.close();

	return ret;
}

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

void PlaySheet(std::vector<Note> sheet, HMIDIOUT midiHandle, int channel, Visualizer* vis)
{
	MidiOutMessage(midiHandle, PIANO, channel, 0, 0);

	if (sheet.size() != 0)
	{
		auto calibration = 0;
		auto innerStart = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds truePlayTime;
		for (auto i = sheet.begin(); i != sheet.end(); i++)
		{
			innerStart = std::chrono::high_resolution_clock::now();

			//std::cout << NoteName[(*i).Note - 21] << " ";
			if (vis != nullptr)
			{
				vis->KeyDown(i->Note);
			}

			if (i != sheet.begin())
			{
				MidiOutMessage(midiHandle, KEY_UP, 0, (i - 1)->Note, (i - 1)->Velocity);
			}

			MidiOutMessage(midiHandle, KEY_DOWN, 0, i->Note, i->Velocity);
			std::chrono::microseconds sleepTime((i->Duration) * 1000 + calibration);
			std::this_thread::sleep_for(sleepTime);

			truePlayTime = std::chrono::duration_cast<std::chrono::microseconds>
				(std::chrono::high_resolution_clock::now() - innerStart);
			calibration = (i->Duration) * 1000 - (truePlayTime.count() - calibration);
		}
		MidiOutMessage(midiHandle, KEY_UP, 0, (sheet.end() - 1)->Note, (sheet.end() - 1)->Velocity);
	}
}