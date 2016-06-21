#pragma once

u32 getCurrentColor();

void setScreen(int screen);

void setColor(int r, int g, int b);

void setColor(int r, int g, int b, int a);

int getCurrentScreen();

void screenShot();

void translateCoords(int * x, int * y);

void translate(int x, int y);

void push();

void pop();