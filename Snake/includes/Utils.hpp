#pragma once

struct Utils {
    enum class GameState {
        PLAY,
        PAUSED,
        GAMEOVER
    };

	static constexpr int tileSize = 30;
	static constexpr int mapSizeInTilesX = 21;
    static constexpr int mapSizeInTilesY = 21;
};