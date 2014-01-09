#include "Screen.h"

int Screen::height = 0;
int Screen::width = 0;

int Screen::pxHeight = 0;
int Screen::pxWidth = 0;

double Screen::xVariation = 0;
double Screen::yVariation = 0;

void Screen::computeVariation() {
	Screen::yVariation = Screen::pxHeight / height;
	Screen::xVariation = Screen::pxWidth / width;
}