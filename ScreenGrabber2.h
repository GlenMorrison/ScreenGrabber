#pragma once
#include "stdafx.h"
#include "windows.h"

#include "ScreenGrabber2.h"

#include <iostream>
#include <algorithm>
#include <vector>

class ScreenGrabber2 {

public:

	void ScreenCapture();
	void BlitScreen();
	void GetPixelData();

private:

	int screenHeight, screenWidth;
	HDC hdc;
	HDC hCaptureDC;
	HBITMAP hBitmap;
	HGDIOBJ hOld;

	BYTE* lpPixels;
	std::vector<char> bmpData, buffer;

	int headerSize;
	int imageSize;
};