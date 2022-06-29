#ifndef VISUALIZER
#define VISUALIZER

#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <Windows.h>

#include "../types.h"

typedef struct VisualNote
{
	NoteNumber Note;
	int Position;
} VisualNote;

class Visualizer
{
public:
	void Start();
	void Stop();
	void KeyDown(NoteNumber note);
	int FrameRate = 30;
private:
	const int _MillisecondsPerSpace = 100;
	const int _MinWidth = 4;
	const int _MaxWidth = 60;
	HANDLE _OutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::mutex _MutexLocker;
	std::vector<VisualNote> _Notes;
	std::thread _TimerThread;
	std::atomic_bool _StopThread;
	COORD _CursorPoint;
	void _Update(int frameRate);
	void _DrawNote(short x, short y, bool clear = false);
};

#endif