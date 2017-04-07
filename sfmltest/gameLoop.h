#pragma once

#define MAX_PATH 260

enum direction { DOWN, UP, LEFT, RIGHT };

bool keyPressDebounce(bool &bulletShot);
void gameLoop();
