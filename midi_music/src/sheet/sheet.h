#ifndef SHEET
#define SHEET

#include <string>
#include <vector>
#include <Windows.h>

#include "../visualizer/visualizer.h"

const std::string NoteName[] = {
	"A0", "A0s", "B0", "C1", "C1s", "D1", "D1s", "E1", "F1", "F1s", "G1", "G1s", 
	"A1", "A1s", "B1", "C2", "C2s", "D2", "D2s", "E2", "F2", "F2s", "G2", "G2s", 
	"A2", "A2s", "B2", "C3", "C3s", "D3", "D3s", "E3", "F3", "F3s", "G3", "G3s", 
	"A3", "A3s", "B3", "C4", "C4s", "D4", "D4s", "E4", "F4", "F4s", "G4", "G4s", 
	"A4", "A4s", "B4", "C5", "C5s", "D5", "D5s", "E5", "F5", "F5s", "G5", "G5s", 
	"A5", "A5s", "B5", "C6", "C6s", "D6", "D6s", "E6", "F6", "F6s", "G6", "G6s", 
	"A6", "A6s", "B6", "C7", "C7s", "D7", "D7s", "E7", "F7", "F7s", "G7", "G7s", 
	"A7", "A7s", "B7"};

const std::string VoiceName[] = {
	"H7", "H6", "H5", "H4", "H3", "H2", "H1",
	"M7", "M6", "M5", "M4", "M3", "M2", "M1",
	"L7", "L6", "L5", "L4", "L3", "L2", "L1"
};

std::vector<Note> ReadSheet(std::string path);
DWORD MidiOutMessage(HMIDIOUT hMidi, int status, int channel, int note, int velocity);
void PlaySheet(std::vector<Note> sheet, HMIDIOUT midiHandle, int channel, Visualizer* vis);

#endif