#pragma once
#include <stdlib.h>
#include <vector>
#include "Vector2.h"
// Extremely Fast Line Algorithm Var E (Addition Fixed Point PreCalc)
// Copyright 2001-2, By Po-Han Lin


// Freely useable in non-commercial applications as long as credits 
// to Po-Han Lin and link to http://www.edepot.com is provided in 
// source code and can been seen in compiled executable.  
// Commercial applications please inquire about licensing the algorithms.
//
// Lastest version at http://www.edepot.com/phl.html
// This version is for standard displays (up to 65536x65536)
// For small display version (256x256) visit http://www.edepot.com/lineex.html

class EFLAvE
{
public:
	// used by myLine
	static void myPixel(std::vector<Vector2>* vec, int x, int y) {
		// PLOT x,y point on surface
		vec->push_back(Vector2(x, y));
	}

	// THE EXTREMELY FAST LINE ALGORITHM Variation E (Addition Fixed Point PreCalc)
	static void myLine(std::vector<Vector2>* vec, int x, int y, int x2, int y2) {
		bool yLonger = false;
		int shortLen = y2 - y;
		int longLen = x2 - x;
		if (abs(shortLen) > abs(longLen)) {
			int swap = shortLen;
			shortLen = longLen;
			longLen = swap;
			yLonger = true;
		}
		int decInc;
		if (longLen == 0) decInc = 0;
		else decInc = (shortLen << 16) / longLen;

		if (yLonger) {
			if (longLen > 0) {
				longLen += y;
				for (int j = 0x8000 + (x << 16); y <= longLen; ++y) {
					myPixel(vec, j >> 16, y);
					j += decInc;
				}
				return;
			}
			longLen += y;
			for (int j = 0x8000 + (x << 16); y >= longLen; --y) {
				myPixel(vec, j >> 16, y);
				j -= decInc;
			}
			return;
		}

		if (longLen > 0) {
			longLen += x;
			for (int j = 0x8000 + (y << 16); x <= longLen; ++x) {
				myPixel(vec, x, j >> 16);
				j += decInc;
			}
			return;
		}
		longLen += x;
		for (int j = 0x8000 + (y << 16); x >= longLen; --x) {
			myPixel(vec, x, j >> 16);
			j -= decInc;
		}
	}
};

