#include "visualizer.h"
#include <future>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <string>
#include <Windows.h>

#include "visualizer.h"
#include "../sheet/sheet.h"
#include "../util/util.h"

std::string NoteNumber2String(NoteNumber note)
{
	return NoteName[int(note) - 21];
}

short NoteNumber2Row(NoteNumber note)
{
	auto noteStr = NoteNumber2String(note);

	short ret = ('5' - noteStr[1]) * 7;
	if ('A' <= noteStr[0] && noteStr[0] <= 'B')
	{
		ret += 'B' - noteStr[0];
	}
	else
	{
		ret += 'G' - noteStr[0] + 2;
	}

	return ret;
}

void Visualizer::_Update(int frameRate)
{
	int index = 0;
	for (auto& name : VoiceName)
	{
		std::cout << name << " " << (KeyboardPrompt ? "(" + KeyboardPromptString[index++] + ")" : "") << "|" << std::endl;
	}

	if (Prompt != "")
	{
		std::cout << Prompt << std::endl;
	}
	while (!_StopThread)
	{
		_MutexLocker.lock();
		for (auto& note : _Notes)
		{
			if (note.Position >= ((KeyboardPrompt ? 3 : 0) + _MinWidth) && note.Position <= MaxWidth)
			{
				auto currentRow = NoteNumber2Row(note.Note);
				_DrawNote(note.Position, currentRow, true);
				if (note.Position < MaxWidth)
				{
					_DrawNote(++note.Position, currentRow);
				}
				else
				{
					note.Position = -1;
				}
			}
		}
		_MutexLocker.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / frameRate));
	}
}

void Visualizer::Start()
{
	ClearConsole();

	// reset cursor position
	SetConsoleCursorPosition(_OutHandle, COORD{ 0, 0 });

	// start timer
	_StopThread = false;
	_TimerThread = std::thread(&Visualizer::_Update, this, FrameRate);
}

void Visualizer::Stop()
{
	_StopThread = true;
	_TimerThread.join();
	for (auto i = _Notes.begin(); i != _Notes.end(); )
	{
		i = _Notes.erase(i);
	}
	// reset cursor position
	SetConsoleCursorPosition(_OutHandle, COORD{ 0, short((Prompt == "") ? 21 : 22) });
}

void Visualizer::Reset()
{
	if (!_StopThread)
	{
		Stop();
	}
	ClearConsole();

	// reset cursor position
	SetConsoleCursorPosition(_OutHandle, COORD{ 0, 0 });
}

void Visualizer::KeyDown(NoteNumber note)
{
	VisualNote tmp{ note, ((KeyboardPrompt ? 3 : 0) + _MinWidth) };
	_MutexLocker.lock();
	_Notes.push_back(tmp);
	_MutexLocker.unlock();
}

void Visualizer::_DrawNote(short x, short y, bool clear)
{
	SetConsoleCursorPosition(_OutHandle, COORD{ x, y });
	if (!clear)
	{
		SetConsoleTextAttribute(_OutHandle, BACKGROUND_INTENSITY | BACKGROUND_BLUE);
	}
	std::cout << ' ';
	SetConsoleTextAttribute(_OutHandle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
