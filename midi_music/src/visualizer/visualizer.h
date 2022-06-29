#ifndef VISUALIZER
#define VISUALIZER

#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <Windows.h>

#include "../types.h"

const std::string KeyboardPromptString[] = {
	"Q", "W", "E", "R", "T", "Y", "U",
	"A", "S", "D", "F", "G", "H", "J",
	"Z", "X", "C", "V", "B", "N", "M"
};

typedef struct VisualNote
{
	NoteNumber Note;
	int Position;
} VisualNote;

class Visualizer
{
public:
	int FrameRate = 30;
	int MaxWidth = 100;
	std::string Prompt = "";
	bool KeyboardPrompt = false;
	void Start();
	void Stop();
	void Reset();
	void KeyDown(NoteNumber note);
private:
	const int _MillisecondsPerSpace = 100;
	int _MinWidth = 4;
	HANDLE _OutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::mutex _MutexLocker;
	std::vector<VisualNote> _Notes;
	std::thread _TimerThread;
	std::atomic_bool _StopThread = true;
	void _Update(int frameRate);
	void _DrawNote(short x, short y, bool clear = false);
};

#endif