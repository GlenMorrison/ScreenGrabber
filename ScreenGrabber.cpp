// ScreenGrabber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ScreenGrabber.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace cv;

void ScreenGrabber::CaptureScreen(HWND hwnd)
{
	screenCapture.release();

	HDC hwindowDC;
	HDC hwindowCompatibleDC;

	HBITMAP hbwindow;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);

	screenCapture.create(heightScaled, widthScaled, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, widthScaled, heightScaled);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = widthScaled;
	bi.biHeight = -heightScaled;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	if (!SelectObject(hwindowCompatibleDC, hbwindow))
	{
		// failed!
		return;
	}

	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
	if (!StretchBlt(hwindowCompatibleDC, 0, 0, widthScaled, heightScaled, hwindowDC, 0, 0, desktopWidth, desktopHeight, SRCCOPY))
	{
		// failed!
		return;
	}

	if (!GetDIBits(hwindowCompatibleDC, hbwindow, 0, heightScaled, screenCapture.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS))
	{
		// failed!
		return;
	}

	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);
}

void ScreenGrabber::GetMetrics(HWND hwnd)
{
	scaleFactor = 2;

	HWND hwndDesktop = GetDesktopWindow();

	RECT windowsize;
	GetClientRect(hwndDesktop, &windowsize);

	desktopHeight = windowsize.bottom;
	desktopWidth = windowsize.right;

	heightScaled = windowsize.bottom / scaleFactor;
	widthScaled = windowsize.right / scaleFactor;
}

void ScreenGrabber::StartScreenCapture()
{

	HWND hwndDesktop = GetDesktopWindow();

	GetMetrics(hwndDesktop);

	namedWindow("screen-grab", WINDOW_NORMAL);
	int key = 0;

	while (key != 27)
	{
		CaptureScreen(hwndDesktop);
		imshow("screen-grab", screenCapture);
		key = waitKey(10);
	}
}

void ScreenGrabber::StopScreenCapture()
{
	screenCapture.release();
}

int main(int argc, char **argv)
{
	ScreenGrabber main;
	main.StartScreenCapture();
}