#pragma once

#include <linux/input.h>

// перед закрытием игры
void BeforeCloseProgram();


// одновременное нажатие клавиш

// Методы для начала работы с библиотекой и завершением работы
void OpenKeysMode();

void CloseKeysMode();

// Получаем состояние клавиатуры
void RefreshKeyboardStatus();

int GetKeyState(int Key);
int GetKeyPressed(int Key);
