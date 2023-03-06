#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <future>
#include <sstream>
#include <filesystem>

#include "../sheet/sheet.h"
#include "../visualizer/visualizer.h"

#pragma comment(lib,"winmm.lib")

namespace fs = std::filesystem;

void PlayForThread(std::vector<Note> sheet, HMIDIOUT midiHandle, int channel, std::chrono::high_resolution_clock::time_point startTime, Visualizer* vis)
{
	// thread info
	/*std::stringstream ss;
	ss << "sub id: " << std::this_thread::get_id() << " channel: " << channel << std::endl;
	std::cout << ss.str();*/

	// thread synchronize
	std::this_thread::sleep_until(startTime);

	PlaySheet(sheet, midiHandle, channel, vis);
}

void SheetPlayer(HMIDIOUT midiHandle, Visualizer *vis)
{
	// multiple threads
	std::vector<std::thread> threads{};

	// thread synchronize
	auto start = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(500);

	// get sheets
	int channelIndex = 0;
	fs::path sheetDir("./sheets");
	for (auto& f : fs::directory_iterator(sheetDir))
	{
		auto sheet = ReadSheet(f.path().generic_string());

		// only visualize notes in main.txt
		if (f.path().filename() == "main.txt")
		{
			threads.push_back(std::thread(PlayForThread, sheet, midiHandle, channelIndex++, start, vis));
		}
		else
		{
			threads.push_back(std::thread(PlayForThread, sheet, midiHandle, channelIndex++, start, nullptr));
		}
	}

	// play sheets
	for (auto& t : threads)
	{
		t.join();
	}
}
