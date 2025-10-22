class Application;

class GameState {
public:
    virtual ~GameState() = default;

    virtual void update(Application& app) = 0;
    virtual void render(Application& app) = 0;
};
