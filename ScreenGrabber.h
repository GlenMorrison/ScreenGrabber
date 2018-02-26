#pragma once

#include "stdafx.h"

#include "ScreenGrabber.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <iostream>

class ScreenGrabber
{
public:

	void StartScreenCapture();
	void StopScreenCapture();

private:

	void CaptureScreen(HWND hwnd);
	void GetMetrics(HWND hwnd);

	cv::Mat screenCapture;

	int desktopWidth, desktopHeight;
	int heightScaled, widthScaled;

	int scaleFactor;

};