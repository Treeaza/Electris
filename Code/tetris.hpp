#ifndef ELECTRIS_GAME  // include guard
#define ELECTRIS_GAME

#define ROWS 22
#define COLS 10

#define LEFT_SPAWN_COL 4

#include <map>
#include <queue>
#include <vector>

namespace Electris {

typedef BlockValue Field[ROWS][COLS];
typedef void (*EventCallback)();
typedef unsigned char MinoState[4][4];

enum GameState { PRESTART, RUNNING, LOST };

enum GameEvent {
    BLOCK_COLLISION,
    BLOCK_LANDING,
    LINE_CLEAR,
    GAME_OVER,
    GAME_START
};

enum BlockValue {
    EMPTY = 0,
    LANDED_A = 1,
    LANDED_B = 2,
    LANDED_C = 3,
    LANDED_D = 4,
    LANDED_E = 5,
    LANDED_F = 6,
    LANDED_G = 7,
};

struct Mino {
    MinoState rotationStates[4];
};

static const Mino L{{{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                     {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
                     {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
                     {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
    I{{{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
       {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}},
    S{{{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
       {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
       {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
    Z{{{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}}},
    O{{{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}}},
    T{{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
    J{{{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
       {{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
       {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
       {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}}};

struct InputState {
    bool mvLeft, mvRight, slam, mvDown, tnLeft, tnRight, hold;
};

class ElectrisGame {
   private:
    // callbacks
    std::map<GameEvent, std::vector<EventCallback>> callbackMap;

    // game state
    Field field[10][16];
    bool holdUsed, slammed;
    Mino held, falling;
    unsigned int x, y;
    unsigned int rotation;
    GameState currentState;

    std::queue<Mino> upcoming;

    void triggerCallbacks(GameEvent trigger);
    Mino queueNextMino();
    void hold();
    void slam();
    void spawnNextMino();

   public:
    ElectrisGame();
    ~ElectrisGame();
    GameState getGameState();
    Mino getHeldMino();
    Mino getFallingMino();
    Mino getNextMino();

    int startGame();
    GameState updateGame(float deltaTime, InputState inputs);

    void registerCallback(GameEvent trigger, EventCallback cb);
};

}  // namespace Electris

#endif  // include guard
