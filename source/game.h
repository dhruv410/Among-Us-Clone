#ifndef GAME_H
#define GAME_H
#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN, 
    GAME_LOST
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
// Defines a Collision typedef that represents collision data
typedef std::tuple<bool, Direction, glm::vec2> Collision; 
// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(30.0f, 25.0f); //40,30
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(140.0f);

const float PLAYER_RADIUS(10.0f);

const int MAZE_SIZE(10); // 8

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;  
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;
    std::vector<GameLevel>  Levels;
    // std::vector<PowerUp>    PowerUps;
    unsigned int            Level;
    unsigned int            Lives;
    glm::vec3               translate;
    // constructor/destructor
    
    glm::vec3 lightPos;
    float lightCutOff = 50.f;
    int light = 1;
    bool light_pressed = true;
    
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions();
    // reset
    void ResetLevel();
    void ResetPlayer();

    // void SpawnPowerUps(GameObject &block);
    // void UpdatePowerUps(float dt);
};

#endif