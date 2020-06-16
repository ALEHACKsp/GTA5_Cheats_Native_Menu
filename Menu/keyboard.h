#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#pragma once

#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000

// parameters are the same as with aru's ScriptHook for IV
void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
bool KeyDown(DWORD key);
bool KeyJustUp(DWORD key, bool exclusive = true);
bool KeyPressedOnce(bool& bIsPressed, DWORD vk);
void ResetKeyState(DWORD key);

enum navsound {
	NAV_OPEN,
	NAV_CLOSED,
	NAV_SELECT,
	NAV_CANCEL,
	NAV_UP_DOWN,
	NAV_LEFT_RIGHT,
};

void menu_beep(int snd);
void get_button_state(bool *a, bool *b, bool *up, bool *down, bool *l, bool *r);

bool trainer_switch_pressed();
void reset_trainer_switch();
void setGameInputToEnabled(bool enabled, bool force = false);

#endif // __KEYBOARD_H__