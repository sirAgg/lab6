#ifndef __INPUTACTIONS_H_
#define __INPUTACTIONS_H_

//
// Store state of keyboard inputs in a bitmap InputActions
//
typedef unsigned char InputActions;
const InputActions ACTION_SHOOT = 1;
const InputActions ACTION_LEFT = 1 << 1;
const InputActions ACTION_RIGHT = 1 << 2;

#endif // __INPUTACTIONS_H_
