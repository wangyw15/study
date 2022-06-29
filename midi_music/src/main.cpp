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
		std::cout << "1. 播放音乐" << std::endl
			<< "2. 键盘演奏" << std::endl
			<< "其他输入则退出" << std::endl
			<< "请选择功能: ";
		std::getline(std::cin, line);

		if (line == "1")
		{
			vis.Prompt = "播放中...";
			vis.KeyboardPrompt = false;
			vis.Start();
			SheetPlayer(midiHandle, &vis);
			vis.Stop();
			std::cout << "按下回车返回主页面";
			std::getline(std::cin, line);
		}
		else if (line == "2")
		{
			vis.Prompt = "按下ESC返回主页面";
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
