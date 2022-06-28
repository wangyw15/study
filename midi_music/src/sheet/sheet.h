#ifndef SHEET
#define SHEET

#include <string>
#include <vector>
#include <Windows.h>

enum NoteNumber
{
	Rest = 0, C8 = 108, B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100,
	D7s = 99, D7 = 98, C7s = 97, C7 = 96, B6 = 95, A6s = 94, A6 = 93, G6s = 92, G6 = 91, F6s = 90, F6 = 89,
	E6 = 88, D6s = 87, D6 = 86, C6s = 85, C6 = 84, B5 = 83, A5s = 82, A5 = 81, G5s = 80, G5 = 79, F5s = 78,
	F5 = 77, E5 = 76, D5s = 75, D5 = 74, C5s = 73, C5 = 72, B4 = 71, A4s = 70, A4 = 69, G4s = 68, G4 = 67,
	F4s = 66, F4 = 65, E4 = 64, D4s = 63, D4 = 62, C4s = 61, C4 = 60, B3 = 59, A3s = 58, A3 = 57, G3s = 56,
	G3 = 55, F3s = 54, F3 = 53, E3 = 52, D3s = 51, D3 = 50, C3s = 49, C3 = 48, B2 = 47, A2s = 46, A2 = 45,
	G2s = 44, G2 = 43, F2s = 42, F2 = 41, E2 = 40, D2s = 39, D2 = 38, C2s = 37, C2 = 36, B1 = 35, A1s = 34,
	A1 = 33, G1s = 32, G1 = 31, F1s = 30, F1 = 29, E1 = 28, D1s = 27, D1 = 26, C1s = 25, C1 = 24, B0 = 23,
	A0s = 22, A0 = 21
};

const char NoteName[][7] = {
	"A0", "A0s", "B0", "C1", "C1s", "D1", "D1s", "E1", "F1", "F1s", "G1", "G1s", 
	"A1", "A1s", "B1", "C2", "C2s", "D2", "D2s", "E2", "F2", "F2s", "G2", "G2s", 
	"A2", "A2s", "B2", "C3", "C3s", "D3", "D3s", "E3", "F3", "F3s", "G3", "G3s", 
	"A3", "A3s", "B3", "C4", "C4s", "D4", "D4s", "E4", "F4", "F4s", "G4", "G4s", 
	"A4", "A4s", "B4", "C5", "C5s", "D5", "D5s", "E5", "F5", "F5s", "G5", "G5s", 
	"A5", "A5s", "B5", "C6", "C6s", "D6", "D6s", "E6", "F6", "F6s", "G6", "G6s", 
	"A6", "A6s", "B6", "C7", "C7s", "D7", "D7s", "E7", "F7", "F7s", "G7", "G7s", 
	"A7", "A7s", "B7"};

typedef struct Note
{
	int Note;
	int Velocity;
	int Duration;
} Note;

std::vector<Note> ReadSheet(std::string path);

#endif