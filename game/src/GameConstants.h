#ifndef __GAMECONSTANTS_H_
#define __GAMECONSTANTS_H_

//
// Global constants used in the game
//

const float GAME_FIELD_WIDTH = 7.0f;
const float GAME_FIELD_FAR_EDGE = -150.0f;
const float GAME_FIELD_NEAR_EDGE = 6.0f;
const int   MAX_LIVES = 5;
const int   ASTEROID_SPAWN_TIMER_START = 120;

const float ASTEROID_SIZE = 0.9f;
const float ASTEROID_START_SPEED = 0.2f;
const int   ASTEROID_KILL_SCORE = 5;
const int	ASTEROID_HEALTH = 4;
const int   ASTEROID_COLOR = 0xFFFFFFFF;
const float ASTEROID_FADE_IN_AT = -140.0f;
const float ASTEROID_FADE_OUT_AT = 0.0f;
const float ASTEROID_ROTATION_SPEED = 0.1f;

const float SPACESHIP_RESPONSIVENESS = 0.1f;
const float SPACESHIP_MOVE_SPEED = 0.15f;
const float SPACESHIP_SIZE = 0.8f;
const int   SPACESHIP_SHOOTING_COOLDOWN_TIME_MAX = 15;
const int   SPACESHIP_INVINCIBILITY_TIME_MAX = 90;

const float LAZER_SHOT_SIZE = 0.2f;
const float LAZER_SHOT_SPEED = -0.4f;
const int   LAZER_SHOT_COLOR = 0xFF0000FF;

const float PARTICLE_SYSTEM_SPEED = 0.08;
const int   PARTICLE_SYSTEM_FADE_OUT_START_TIME = 60;
const int   PARTICLE_SYSTEM_LIFE_LENGHT = 120;

#endif // __GAMECONSTANTS_H_
