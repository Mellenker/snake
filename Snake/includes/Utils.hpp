#pragma once

struct Utils {
    enum class GameState {
        PLAY,
        PAUSED,
        GAMEOVER
    };

    static constexpr int tileSize = 45;
    static constexpr int mapSizeInTilesX = 3;
    static constexpr int mapSizeInTilesY = 3;
};