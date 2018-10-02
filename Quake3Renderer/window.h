#pragma once

#define VSYNC_ON 1
#define VSYNC_OFF 0

int createwindow(int width, int height, const char* title);
void setvsync(int enable);