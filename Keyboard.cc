#include "Keyboard.h"
#include "Memory.h"

PDWORD _keyboardAddress;
DWORD _pin = 0xFFFFFFFF;
BYTE _lastKey = 0x1F;

void InitKeyboard()
{
	_keyboardAddress = MapPhysicalMemory(KEYBOARD_ADDRESS);
}

DWORD GetKeyboardPin()
{
	return _pin;
}

void CheckKeyboardNewKeyPressed()
{
	BYTE currentKey;
	
	currentKey = 0x1F;
	
	currentKey = _keyboardAddress[1];
	if (_lastKey != currentKey)
	{
		_lastKey = currentKey;
		_pin = (_pin << 4) | currentKey;
	}
}

