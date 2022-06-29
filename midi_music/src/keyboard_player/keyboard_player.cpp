#include <conio.h>
#include <iostream>
#include <Windows.h>

#include "../visualizer/visualizer.h"
#include "../sheet/sheet.h"
#include "../types.h"

NoteNumber KeyboardToNoteNumber(char c)
{
	switch (c)
	{
	case 'q': return NoteNumber(H7); break;
	case 'w': return NoteNumber(H6); break;
	case 'e': return NoteNumber(H5); break;
	case 'r': return NoteNumber(H4); break;
	case 't': return NoteNumber(H3); break;
	case 'y': return NoteNumber(H2); break;
	case 'u': return NoteNumber(H1); break;

	case 'a': return NoteNumber(M7); break;
	case 's': return NoteNumber(M6); break;
	case 'd': return NoteNumber(M5); break;
	case 'f': return NoteNumber(M4); break;
	case 'g': return NoteNumber(M3); break;
	case 'h': return NoteNumber(M2); break;
	case 'j': return NoteNumber(M1); break;

	case 'z': return NoteNumber(L7); break;
	case 'x': return NoteNumber(L6); break;
	case 'c': return NoteNumber(L5); break;
	case 'v': return NoteNumber(L4); break;
	case 'b': return NoteNumber(L3); break;
	case 'n': return NoteNumber(L2); break;
	case 'm': return NoteNumber(L1); break;
	default: return Rest;
	}
}

void KeyboardPlayer(HMIDIOUT midiHandle, Visualizer* vis)
{
	MidiOutMessage(midiHandle, PIANO, 0, 0, 0);

	auto handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD consoleMode = 0;
	GetConsoleMode(handle, &consoleMode);
	SetConsoleMode(handle, consoleMode & (~ENABLE_ECHO_INPUT));

	char input;
	while (input = getch())
	{
		if (input == 27)
		{
			break;
		}
		auto note = KeyboardToNoteNumber(input);
		if (note != Rest)
		{
			MidiOutMessage(midiHandle, KEY_DOWN, 0, note, 127);
			vis->KeyDown(note);
		}
	}

	SetConsoleMode(handle, consoleMode);
}