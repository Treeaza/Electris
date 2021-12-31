#include "tetris.hpp"

using namespace Electris;

void ElectrisGame::triggerCallbacks(GameEvent trigger) {
    // iterate over all cbs with trigger, call callback func for each
    for (std::vector<EventCallback>::iterator it = callbackMap[trigger].begin();
         it != callbackMap[trigger].end(); ++it) {
        (*it)();
    }
}

Mino ElectrisGame::queueNextMino() {
    // only makes sense if we're out
    if (falling != nullptr) {
        return falling;
    }

    if (upcoming.size() < 2) {
        // add one of each mino to queue, in random order
        std::vector<Mino> toAdd = {Mino::I, Mino::O, Mino::L, Mino::J,
                                   Mino::S, Mino::Z, Mino::T};

        // push random item onto upcoming queue until we run out
        while (!toAdd.empty()) {
            int r = rand() % toAdd.size();
            upcoming.push(toAdd[r]);
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

    Mino temp = falling;
    falling = held;
    held = falling;

    // spun this into a new method, it's awkward
    spawnNextMino();
}

void ElectrisGame::slam() {
    slammed = true;

    // drop mino row by row until we find resting position

    // spawn next Mino in
    queueNextMino();
}

void spawnNextMino() {
    if (falling == nullptr) {
        return;
    }

    // attempt to spawn in rows 20-21

    // if we're still here attempt to spawn in rows 21-22

    // if we're STILL here, the player lost, the stupid dumb idiot
}

ElectrisGame::ElectrisGame() {
    currentState = GameState::PRESTART;
    held = NULL;
}

ElectrisGame::~ElectrisGame() {}

GameState ElectrisGame::getGameState() { return currentState; }

Mino ElectrisGame::getHeldMino() { return held; }

Mino ElectrisGame::getFallingMino() { return falling; }

Mino ElectrisGame::getNextMino() { return upcoming.front(); }

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

    return currentState;
}

void ElectrisGame::registerCallback(GameEvent trigger, EventCallback cb) {
    callbackMap[trigger].push_back(cb);
}