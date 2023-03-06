#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <future>
#include <filesystem>
#include <sstream>

#include "sheet/sheet.h"

#pragma comment(lib,"winmm.lib")

namespace fs = std::filesystem;

void PlayForThread(std::vector<Note> sheet, HMIDIOUT midiHandle, int channel, std::chrono::high_resolution_clock::time_point startTime)
{
	// thread info
	std::stringstream ss;
	ss << "sub id: " << std::this_thread::get_id() << " channel: " << channel << std::endl;
	std::cout << ss.str();

	// thread synchronize
	std::this_thread::sleep_until(startTime);

	PlaySheet(sheet, midiHandle, channel);
}

int main()
{
	// open MIDI device
	HMIDIOUT midiHandle;
	midiOutOpen(&midiHandle, 0, 0, 0, 0);

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
		threads.push_back(std::thread(PlayForThread, sheet, midiHandle, channelIndex++, start));
	}

	// play sheets
	for (auto& t : threads)
	{
		t.join();
	}

	// close MIDI devices
	midiOutClose(midiHandle);

	// wait to exit
	std::cout << "按回车键退出..." << std::endl;
	std::string line;
	std::getline(std::cin, line);
	return 0;
}
