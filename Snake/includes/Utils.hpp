#pragma once

struct Utils {
    enum class GameState {
        PLAY,
        PAUSED,
        GAMEOVER
    };

    static constexpr int tileSize = 1;
    static constexpr int mapSizeInTilesX = 5;
    static constexpr int mapSizeInTilesY = 5;
    static constexpr int scale = 50;
};