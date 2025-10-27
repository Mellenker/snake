#pragma once

namespace Utils {
    enum class GameState {
        PLAYING,
        PAUSED,
        GAMEOVER
    };

    inline const int g_tileSize = 45;
    inline const int g_mapSizeInTilesX = 15;
    inline const int g_mapSizeInTilesY = 15;
};