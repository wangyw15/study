#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <future>
#include <sstream>
#include <filesystem>

#include "sheet/sheet.h"
#include "visualizer/visualizer.h"
#include "sheet_player/sheet_player.h"
#include "keyboard_player/keyboard_player.h"
#include "util/util.h"

#pragma comment(lib,"winmm.lib")

namespace fs = std::filesystem;

int main()
{
	// open MIDI device
	HMIDIOUT midiHandle;
	midiOutOpen(&midiHandle, 0, 0, 0, 0);

	// visualizer
	Visualizer vis;
	vis.FrameRate = 60;

	std::string line;

	while (true)
	{
		std::cout << "1. ��������" << std::endl
			<< "2. ��������" << std::endl
			<< "�����������˳�" << std::endl
			<< "��ѡ����: ";
		std::getline(std::cin, line);

		if (line == "1")
		{
			vis.Prompt = "������...";
			vis.KeyboardPrompt = false;
			vis.Start();
			SheetPlayer(midiHandle, &vis);
			vis.Stop();
			std::cout << "���»س�������ҳ��";
			std::getline(std::cin, line);
		}
		else if (line == "2")
		{
			vis.Prompt = "����ESC������ҳ��";
			vis.KeyboardPrompt = true;
			vis.Start();
			KeyboardPlayer(midiHandle, &vis);
			vis.Stop();
		}
		else
		{
			break;
		}
		vis.Reset();
	}

	// close MIDI devices
	midiOutClose(midiHandle);
	return 0;
}
