#ifndef ELECTRIS_GAME  // include guard
#define ELECTRIS_GAME

#define ROWS 22
#define COLS 10

#define LEFT_SPAWN_COL 4

#define ROTATE_THRESHOLD 0.4
#define MOVE_THRESHOLD 0.4
#define SLOW_FALL_THRESHOLD 0.4

#include <map>
#include <queue>
#include <vector>

namespace Electris {
	typedef BlockValue Field[ROWS][COLS];
	typedef unsigned char MinoState[4][4];
	typedef WallKickPair WallKickPairList[8][5];

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

	struct WallKickPair {
		int x, y;
	};

	static Mino MINO_L{
		{{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		 {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
		 {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
		 {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
		MINO_I{{{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
				{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}}},
		MINO_S{{{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
				{{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
		MINO_Z{{{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}}},
		MINO_O{{{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}}},
		MINO_T{{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}}},
		MINO_J{{{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}}},
		MINO_NONE{{{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				   {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				   {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				   {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}}};

	static WallKickPairList JLTSZ_WALLKICKS = {
		{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},	// 0 >> 1
		{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},		// 1 >> 0
		{{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},		// 1 >> 2
		{{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},	// 2 >> 1
		{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},		// 2 >> 3
		{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},	// 3 >> 2
		{{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},	// 3 >> 0
		{{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}};	// 0 >> 3

	static WallKickPairList I_WALLKICKS = {
		{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},   // 0 >> 1
		{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},   // 1 >> 0
		{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},   // 1 >> 2
		{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},   // 2 >> 1
		{{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},   // 2 >> 3
		{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},   // 3 >> 2
		{{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},   // 3 >> 0
		{{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}};  // 0 >> 3

	struct InputState {
		bool mvLeft, mvRight, slam, mvDown, tnLeft, tnRight, hold;
	};

	class ElectrisGame {
	   private:
		// callbacks
		std::map<GameEvent, std::vector<void (*)()>> callbackMap;

		// game state
		Field field;
		bool holdUsed, slammed;
		Mino* held;
		Mino* falling;
		int x, y;
		unsigned int rotation;
		GameState currentState;
		float fallTime, rotateLeftHoldTime, rotateRightHoldTime, downHoldTime, leftHoldTime, rightHoldTime;

		std::queue<Mino*> upcoming;

		void triggerCallbacks(GameEvent trigger);
		Mino* queueNextMino();
		void hold();
		void slam();
		void descend();
		void lock();
		void rotate(bool direction);
		void move(bool direction);
		void spawnNextMino();

		void minoLandedCallback();

	   public:
		ElectrisGame();
		~ElectrisGame();
		GameState getGameState();
		Mino* getHeldMino();
		Mino* getFallingMino();
		Mino* getNextMino();

		bool checkHypotheticalPosition(Mino mino, unsigned int rot, int x, int y);

		int startGame();
		GameState updateGame(float deltaTime, InputState inputs);

		void registerCallback(GameEvent trigger, void (*cb)());
	};

}  // namespace Electris

#endif	// include guard
