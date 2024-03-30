#ifndef ELECTRIS_GAME  // include guard
#define ELECTRIS_GAME

#include <map>
#include <queue>
#include <vector>

namespace Electris {

#define ROWS 22
#define COLS 10

#define LEFT_SPAWN_COL 4

#define ROTATE_THRESHOLD 0.4
#define MOVE_THRESHOLD 0.4
#define SLOW_FALL_THRESHOLD 0.4

#define BASE_FALL_TIME 0.75
#define FALL_LEVEL_MULTIPLIER 0.9

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

	typedef BlockValue Field[ROWS][COLS];
	
	struct Mino {
		MinoState rotationStates[4];
		BlockValue landedValue;
	};

	struct WallKickPair {
		int x, y;
	};

	typedef WallKickPair WallKickPairList[8][5];

	static Mino MINO_L{
		{{{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
		 {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
		 {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
		 {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
		BlockValue::LANDED_G},
		MINO_I{{{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
				{{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},
			   BlockValue::LANDED_A},
		MINO_S{{{{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
				{{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
			   BlockValue::LANDED_B},
		MINO_Z{{{{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}},
			   BlockValue::LANDED_C},
		MINO_O{{{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
			   BlockValue::LANDED_D},
		MINO_T{{{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
			   BlockValue::LANDED_E},
		MINO_J{{{{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
				{{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
				{{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
				{{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}}},
			   BlockValue::LANDED_F},
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
		float fallTime, rotateLeftHoldTime, rotateRightHoldTime, downHoldTime,
			leftHoldTime, rightHoldTime;

		unsigned int level;

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
		unsigned int getLevel();

		bool checkHypotheticalPosition(Mino mino, unsigned int rot, int x,
									   int y);

		int startGame();
		GameState updateGame(float deltaTime, InputState inputs);

		void registerCallback(GameEvent trigger, void (*cb)());
	};

}  // namespace Electris

#endif	// include guard
