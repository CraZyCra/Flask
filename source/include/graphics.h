#pragma once

u32 getCurrentColor();

void setScreen(int screen);

void setColor(int r, int g, int b);

void setColor(int r, int g, int b, int a);

int getCurrentScreen();

void screenShot();

void translateCoords(float * x, float * y);

void translate(float x, float y);

void push();

void pop();

void setScissor(u32 x, u32 y, u32 width, u32 height);

void setScissor();