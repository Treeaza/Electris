#include "electris.hpp"

using namespace Electris;

void ElectrisGame::registerCallback(GameEvent trigger, void (*cb)()) {
	callbackMap[trigger].push_back(cb);
}

void ElectrisGame::triggerCallbacks(GameEvent trigger) {
	// iterate over all cbs with trigger, call callback func for each
	for (std::vector<void (*)()>::iterator it = callbackMap[trigger].begin();
		 it != callbackMap[trigger].end(); ++it) {
		(*it)();
	}

	// this is fucking gross
	// but the easiest place to put it sadly
	if (trigger == GameEvent::BLOCK_LANDING) {
		holdUsed = false;
	}
}

Mino* ElectrisGame::queueNextMino() {
	// only makes sense if we're out
	if (falling != &MINO_NONE) {
		return falling;
	}

	if (upcoming.size() < 2) {
		// add one of each mino to queue, in random order
		std::vector<Mino> toAdd = {MINO_I, MINO_O, MINO_L, MINO_J,
								   MINO_S, MINO_Z, MINO_T};

		// push random item onto upcoming queue until we run out
		while (!toAdd.empty()) {
			int r = rand() % toAdd.size();
			upcoming.push(&toAdd[r]);
			toAdd.erase(toAdd.begin() + r);
		}
	}

	// pop next mino out and into current position
	falling = upcoming.front();
	upcoming.pop();

	// attempt to spawn
	spawnNextMino();

	// return the new current mino for convenience
	return falling;
}

void ElectrisGame::hold() {
	// if we got here we're assuming hold is legal
	holdUsed = true;

	// cycle the falling/held minos
	Mino* temp = falling;
	falling = held;
	held = falling;

	// pop the next mino in
	spawnNextMino();
}

void ElectrisGame::slam() {
	slammed = true;

	// drop mino row by row until we find resting position
	// check to see if one row down is valid
	// if not, lock in here
	while (checkHypotheticalPosition(*falling, rotation, x, y - 1)) y--;

	// SRS dictates locking hard drop
	// so lock it I guess
	lock();
}

void ElectrisGame::descend() {
	// check to see if it's valid to move down, if not lock in place
	if (checkHypotheticalPosition(*falling, rotation, x, y - 1))
		y--;
	else
		lock();
}

void ElectrisGame::lock() {
	// add the tiles of the falling Mino
	// to the field

	// if this is being called we're gonna assume already that it's valid

	// same as our position check loop, just add to the field
	for (unsigned int r = 0; r < 4; r++) {
		for (unsigned int c = 0; c < 4; c++) {
			if (falling->rotationStates[rotation][r][c]) {
				field[y - r][x + c] = falling->landedValue;
			}
		}
	}

	falling = &MINO_NONE;

	triggerCallbacks(GameEvent::BLOCK_LANDING);

	// spawn next Mino in
	queueNextMino();
}

void ElectrisGame::rotate(bool direction) {
	// identify rotation, true is right
	unsigned int next = rotation + (direction ? 1 : -1);
	if (next > 3)
		next = 0;
	else if (next < 0)
		next = 3;

	// big ugly nasty but oh well, I can't be
	// bothered to make this nicer
	int wallKickRow = 0;

	if (rotation == 0 && next == 1) {
		wallKickRow = 0;
	} else if (rotation == 1 && next == 0) {
		wallKickRow = 1;
	} else if (rotation == 1 && next == 2) {
		wallKickRow = 2;
	} else if (rotation == 2 && next == 1) {
		wallKickRow = 3;
	} else if (rotation == 2 && next == 3) {
		wallKickRow = 4;
	} else if (rotation == 3 && next == 2) {
		wallKickRow = 5;
	} else if (rotation == 3 && next == 0) {
		wallKickRow = 6;
	} else if (rotation == 0 && next == 3) {
		wallKickRow = 7;
	}

	bool valid = false;
	WallKickPairList* wallKicks =
		(falling == &MINO_I) ? &I_WALLKICKS : &JLTSZ_WALLKICKS;

	int ind = 0;
	while (ind < 5) {
		WallKickPair w = *wallKicks[wallKickRow][ind];
		if (checkHypotheticalPosition(*falling, next, x + w.x, y + w.y)) {
			rotation = next;
			x += w.x;
			y += w.y;
			valid = true;

			// rotation is complete, return
			return;
		}
		ind++;
	}

	// if we got here rotation failed, return
}

void ElectrisGame::move(bool direction) {
	int dx = direction ? 1 : -1;
	if (checkHypotheticalPosition(*falling, rotation, x + dx, y)) x += dx;
}

void ElectrisGame::spawnNextMino() {
	if (falling == &MINO_NONE) {
		return;
	}

	// attempt to spawn in rows 20-21

	// this is the row the top of the mino array will be placed into
	unsigned int spawnRow = 21;
	bool valid = checkHypotheticalPosition(*falling, 0, 4, spawnRow);

	if (!valid) {
		// if we're still here attempt to spawn in rows 21-22
		spawnRow = 22;
		checkHypotheticalPosition(*falling, 0, 4, spawnRow);
	}

	if (valid) {
		// spawn the Mino... really just set some members
		x = 4;
		y = spawnRow;
		return;
	}

	// if we're STILL here, the player lost, the stupid dumb idiot
	// oof
	currentState = GameState::LOST;
	triggerCallbacks(GameEvent::GAME_OVER);
}

void ElectrisGame::minoLandedCallback() { holdUsed = false; }

ElectrisGame::ElectrisGame() {
	currentState = GameState::PRESTART;
	held = &MINO_NONE;
	falling = &MINO_NONE;

	fallTime = 0;
	rotateLeftHoldTime = 0;
	rotateRightHoldTime = 0;
	downHoldTime = 0;
	leftHoldTime = 0;
	rightHoldTime = 0;
}

ElectrisGame::~ElectrisGame() {}

GameState ElectrisGame::getGameState() { return currentState; }

Mino* ElectrisGame::getHeldMino() { return held; }

Mino* ElectrisGame::getFallingMino() { return falling; }

Mino* ElectrisGame::getNextMino() { return upcoming.front(); }

unsigned int ElectrisGame::getLevel() { return level; }

bool ElectrisGame::checkHypotheticalPosition(Mino mino, unsigned int rot,
											 int _x, int _y) {
	for (unsigned int r = 0; r < 4; r++) {
		for (unsigned int c = 0; c < 4; c++) {
			if (falling->rotationStates[rot][r][c] && field[_y - r][_x + c]) {
				return false;
			}
		}
	}

	return true;
}

int ElectrisGame::startGame() {
	// check we are in correct state
	if (currentState == GameState::PRESTART) {
		// update state, call cbs
		currentState == GameState::RUNNING;
		triggerCallbacks(GameEvent::GAME_START);

		// get minos into the queue
		queueNextMino();
		return 0;
	}

	// if we got here we were in wrong state
	// return error
	return 1;
}

GameState ElectrisGame::updateGame(float deltaTime, InputState inputs) {
	// this is gonna be spaghetti likely, might clean it up later

	// first thing's first, make sure there's a mino?
	if (falling == &MINO_NONE) {
		queueNextMino();
		spawnNextMino();
	}

	// hold takes priority I think
	if (inputs.hold && !holdUsed) {
		hold();
	}

	// next up, downslam - this should only trigger ONCE PER PRESS
	if (inputs.slam && !slammed) {
		slam();
	} else if (!inputs.slam) {
		// reset slam state when button not down
		slammed = false;
	}

	// remaining actions are timed: rotation, soft drop, timed drop etc.

	// these all operate in a similar way: when the button is pressed
	// we want the action to trigger immediately. If it's held we want to
	// repeat it after a set time, and if it's released and pressed again
	// we again want an immediate trigger

	// should probably generalize this code because don't repeat yourself but oh
	// well
	if (inputs.tnLeft) {
		if (rotateLeftHoldTime == 0 || rotateLeftHoldTime > ROTATE_THRESHOLD) {
			rotate(false);
			if (rotateLeftHoldTime > 0) {
				rotateLeftHoldTime -= ROTATE_THRESHOLD;
			}
		}
		rotateLeftHoldTime += deltaTime;
	} else {
		rotateLeftHoldTime = 0;
	}

	if (inputs.tnRight) {
		if (rotateRightHoldTime == 0 ||
			rotateRightHoldTime > ROTATE_THRESHOLD) {
			rotate(false);
			if (rotateRightHoldTime > 0) {
				rotateRightHoldTime -= ROTATE_THRESHOLD;
			}
		}
		rotateRightHoldTime += deltaTime;
	} else {
		rotateRightHoldTime = 0;
	}

	if (inputs.mvLeft) {
		if (leftHoldTime == 0 || leftHoldTime > MOVE_THRESHOLD) {
			move(false);
			if (leftHoldTime > 0) {
				leftHoldTime -= MOVE_THRESHOLD;
			}
		}
		leftHoldTime += deltaTime;
	} else {
		leftHoldTime = 0;
	}

	if (inputs.mvRight) {
		if (rightHoldTime == 0 || rightHoldTime > MOVE_THRESHOLD) {
			move(true);
			if (rightHoldTime > 0) {
				rightHoldTime -= MOVE_THRESHOLD;
			}
		}
		rightHoldTime += deltaTime;
	} else {
		rightHoldTime = 0;
	}

	// this one is a little different, because it also needs to
	// happen without a button press I guess
	if (inputs.mvDown) {
		if (downHoldTime == 0 || downHoldTime > MOVE_THRESHOLD) {
			descend();
			if (downHoldTime > 0) {
				downHoldTime -= MOVE_THRESHOLD;
			}
		}
		downHoldTime += deltaTime;
	} else {
		downHoldTime = 0;

		// if we aren't actively lowering the mino, do it passively
		fallTime += deltaTime;

		if (fallTime > BASE_FALL_TIME * FALL_LEVEL_MULTIPLIER * level) {
			descend();
			fallTime -= BASE_FALL_TIME * FALL_LEVEL_MULTIPLIER * level;
		}
	}

	return currentState;
}
