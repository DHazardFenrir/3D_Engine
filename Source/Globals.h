#pragma once
#define NOMINMAX

//#include <windows.h>
#include <stdio.h>
#include <string>
#include <vector>

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Super Awesome Engine"