#ifndef __INPUTACTIONS_H_
#define __INPUTACTIONS_H_

typedef unsigned char InputActions;
const InputActions ACTION_UP = 1;
const InputActions ACTION_DOWN = 1 << 1;
const InputActions ACTION_LEFT = 1 << 2;
const InputActions ACTION_RIGHT = 1 << 3;

#endif // __INPUTACTIONS_H_
