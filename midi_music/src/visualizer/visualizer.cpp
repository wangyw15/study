#include <future>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <string>
#include <Windows.h>

#include "visualizer.h"
#include "../sheet/sheet.h"

std::string NoteNumber2String(NoteNumber note)
{
	return NoteName[int(note) - 21];
}

short NoteNumber2Row(NoteNumber note)
{
	auto noteStr = NoteNumber2String(note);

	short ret = (noteStr[1] - '3') * 7;
	if ('A' <= noteStr[0] && noteStr[0] <= 'B')
	{
		ret += noteStr[0] - 'A' + 5;
	}
	else
	{
		ret += noteStr[0] - 'C';
	}

	return ret;
}

void Visualizer::_Update(int frameRate)
{
	for (auto& name : VoiceName)
	{
		std::cout << name << " |" << std::endl;
	}
	while (!_StopThread)
	{
		_MutexLocker.lock();
		for (auto& note : _Notes)
		{
			if (note.Position >= _MinWidth && note.Position <= _MaxWidth)
			{
				auto currentRow = NoteNumber2Row(note.Note);
				_DrawNote(note.Position, currentRow, true);
				if (note.Position != _MaxWidth)
				{
					note.Position++;
					_DrawNote(note.Position, currentRow);
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
	_StopThread = false;
	_TimerThread = std::thread(&Visualizer::_Update, this, FrameRate);
}

void Visualizer::Stop()
{
	_StopThread = true;
	_TimerThread.join();
}

void Visualizer::KeyDown(NoteNumber note)
{
	_MutexLocker.lock();
	VisualNote tmp{ note, _MinWidth };
	_Notes.push_back(tmp);
	_MutexLocker.unlock();
}

void Visualizer::_DrawNote(short x, short y, bool clear)
{
	_CursorPoint = COORD{ x, y };
	SetConsoleCursorPosition(_OutHandle, _CursorPoint);
	std::cout << (clear ? " " : "=");
}
