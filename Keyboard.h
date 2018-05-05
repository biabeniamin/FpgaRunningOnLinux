#include <stdio.h>
#include "DataTypes.h"

#define KEYBOARD_ADDRESS 0x43C80000

void InitKeyboard();

DWORD GetKeyboardPin();

void CheckKeyboardNewKeyPressed();

void ResetKeyboard();

