#define NUMBER_OF_ENEMIES       8
#define ENEMIES_ATTACK_SPEED    140
#define MAX_SHOOTS              20
#define SHOOTS_MAX_LIFETIME     70

typedef struct Enemy {
    int x;
    int y;
    int level;
} Enemy;

typedef struct Shoot {
    int x;
    int y;
    int direction;
    int lifeTime;
    bool active;
} Shoot;

static int finishScreen;
int mapNumber;
int frameCount;

Enemy enemies[NUMBER_OF_ENEMIES] = { 
    {240, 200, 1}, {290, 110, 1}, {400, 230, 1}, {590, 200, 1},
    {200, 200, 2}, {260, 120, 2}, {430, 230, 2}, {550, 220, 2}
};
Texture2D enemyTex;
Shoot shoots[MAX_SHOOTS] = { 0 };

Tilemap tilemap;
Tilemap tilemap_decoration;
Texture2D texTileset;
Texture2D texPlayer;
Texture2D shootTex;
Rectangle player;
Rectangle oldPlayer;

void LoadMapLevel(void);
void EnemiesShootsLogic(void);

void InitGameplayScreen(void) {
    finishScreen = 0;
    frameCount = ENEMIES_ATTACK_SPEED;

    // Load player texture
    Image imPlayer = LoadImage("resources/character.bmp");
    texPlayer = LoadTextureFromImage(imPlayer);
    UnloadImage(imPlayer);

    mapNumber = 1;
    LoadMapLevel();

    // Load tileset texture
    Image imTileset = LoadImage("resources/tileset_world.bmp");
    texTileset = LoadTextureFromImage(imTileset);
    UnloadImage(imTileset);
    
    Image enemyImg = LoadImage("resources/enemy.bmp");
    enemyTex = LoadTextureFromImage(enemyImg);
    UnloadImage(enemyImg);

    Image shootImg = LoadImage("resources/energy_ball.bmp");
    shootTex = LoadTextureFromImage(shootImg);
    UnloadImage(shootImg);

    // Init player position
    player = (Rectangle){ tilemap.position.x + 1 * tilemap.tileSize + 8, tilemap.position.y + 1 * tilemap.tileSize + 8, 8, 8 };
    oldPlayer = player;

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        shoots[i].x = 0;
        shoots[i].y = 0;
        shoots[i].direction = 0;
        shoots[i].lifeTime = 0;
        shoots[i].active = false;
    }
}

void UpdateGameplayScreen(void) {
    // Player movement logic
    oldPlayer = player;

    if (IsKeyDown(GLFW_KEY_DOWN)) player.y += 2;
    else if (IsKeyDown(GLFW_KEY_UP)) player.y -= 2;

    if (IsKeyDown(GLFW_KEY_RIGHT)) player.x += 2;
    else if (IsKeyDown(GLFW_KEY_LEFT)) player.x -= 2;

    // LESSON 7: Collision detection and resolution
    for (int y = 0; y < tilemap.tileCountY; y++)
    {
        for (int x = 0; x < tilemap.tileCountX; x++)
        {
            // TODO: Review player padding for a better collision with walls
            if ((tilemap.tiles[y * tilemap.tileCountX + x].collider == 0 &&
                CheckCollisionRecs(
                    (Rectangle) { player.x + PLAYER_COLLISION_PADDING, player.y + PLAYER_COLLISION_PADDING, player.width, player.height },
                    (Rectangle) {(int)tilemap.position.x + x * tilemap.tileSize + PLAYER_COLLISION_PADDING, (int)tilemap.position.y + y * tilemap.tileSize + PLAYER_COLLISION_PADDING, tilemap.tileSize, tilemap.tileSize}
                )) ||
                (tilemap_decoration.tiles[y * tilemap_decoration.tileCountX + x].collider == 0 &&
                CheckCollisionRecs(
                    (Rectangle) {player.x + PLAYER_COLLISION_PADDING, player.y + PLAYER_COLLISION_PADDING, player.width, player.height},
                    (Rectangle) {(int)tilemap_decoration.position.x + x * tilemap_decoration.tileSize + PLAYER_COLLISION_PADDING, (int)tilemap_decoration.position.y + y * tilemap_decoration.tileSize + PLAYER_COLLISION_PADDING, tilemap_decoration.tileSize, tilemap_decoration.tileSize}
                ))
            )
            {
                // Reset player position (undo player position update!)
                player = oldPlayer;
            }
        }
    }

    EnemiesShootsLogic();

    for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        if (enemies[i].level == mapNumber) {
            if (CheckCollisionRecs(
                (Rectangle) {
                player.x, player.y, player.width, player.height
            },
                (Rectangle) {
                enemies[i].x, enemies[i].y, 20, 20
            }
                )
                ) {
                winner = false;
                finishScreen = 1;
            }
        }
    }

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        if (shoots[i].active) {
            if (CheckCollisionRecs(
                (Rectangle) {
                player.x, player.y, player.width, player.height
            },
                (Rectangle) {
                shoots[i].x, shoots[i].y, 5, 5
            }
                )
                ) {
                winner = false;
                finishScreen = 1;
            }
        }
    }

    if (mapNumber == 1 && player.x >= 630) {
        mapNumber = 2;
        LoadMapLevel();
    }
    else if (mapNumber == 2 && player.x >= 630) {
        winner = true;
        finishScreen = 1;
    }
}

void DrawGameplayScreen(void) {
    DrawTilemap(tilemap, texTileset);   // Draw tilemap using provide tileset
    DrawTilemap(tilemap_decoration, texTileset);   // Draw tilemap using provide tileset
    DrawTexture(texPlayer, player.x, player.y, WHITE); // Draw player texture

    for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
    {
        if (enemies[i].level == mapNumber) {
            DrawTexture(enemyTex, enemies[i].x, enemies[i].y, WHITE);
        }
    }

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        if (shoots[i].active) DrawTexture(shootTex, shoots[i].x, shoots[i].y, WHITE);
    }
}

void UnloadGameplayScreen(void) {
    UnloadTexture(texPlayer);       // Unload player texture
    UnloadTexture(texTileset);      // Unload tileset texture
    UnloadTilemap(tilemap);         // Unload tilemap data
    UnloadTilemap(tilemap_decoration);         // Unload tilemap data
}

int FinishGameplayScreen(void) {
    return finishScreen;
}

void LoadMapLevel() {
    // LESSON 06: Load tilemap data: tile values (tileset index) and tile colliders
    switch (mapNumber)
    {
    case 1:
        tilemap = LoadTilemap("resources/tilemap_level1.bmp", "resources/tilemap_level1_colliders.bmp");
        tilemap_decoration = LoadTilemap("resources/tilemap_level1_decoration.bmp", "resources/tilemap_level1_decoration_colliders.bmp");
        break;
    case 2:
        tilemap = LoadTilemap("resources/tilemap_level2.bmp", "resources/tilemap_level2_colliders.bmp");
        tilemap_decoration = LoadTilemap("resources/tilemap_level2_decoration.bmp", "resources/tilemap_level2_decoration_colliders.bmp");
        break;
    default:
        break;
    }

    tilemap.tileSize = 16;
    tilemap.position = (Vector2){ screenWidth / 2.f - tilemap.tileCountX * tilemap.tileSize / 2,
                                  screenHeight / 2.f - tilemap.tileCountY * tilemap.tileSize / 2 };

    tilemap_decoration.tileSize = 16;
    tilemap_decoration.position = (Vector2){ screenWidth / 2.f - tilemap_decoration.tileCountX * tilemap_decoration.tileSize / 2,
                                  screenHeight / 2.f - tilemap_decoration.tileCountY * tilemap_decoration.tileSize / 2 };

    player = (Rectangle){ tilemap.position.x + 1 * tilemap.tileSize + 8, tilemap.position.y + 1 * tilemap.tileSize + 8, 8, 8 };
    oldPlayer = player;

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        shoots[i].active = false;
    }
}

void EnemiesShootsLogic() {
    frameCount++;
    if (frameCount >= ENEMIES_ATTACK_SPEED) {
        frameCount = 0;
        for (int n = 0; n < NUMBER_OF_ENEMIES; n++)
        {
            if (enemies[n].level == mapNumber) {
                for (int i = 0; i < MAX_SHOOTS; i++)
                {
                    if (!shoots[i].active && !shoots[i + 1].active && !shoots[i + 2].active && !shoots[i + 3].active) {
                        shoots[i].x = enemies[n].x + 4;
                        shoots[i].y = enemies[n].y + 10;
                        shoots[i].direction = 1;
                        shoots[i].lifeTime = 0;
                        shoots[i].active = true;

                        shoots[i + 1].x = enemies[n].x + 4;
                        shoots[i + 1].y = enemies[n].y + 10;
                        shoots[i + 1].direction = 2;
                        shoots[i + 1].lifeTime = 0;
                        shoots[i + 1].active = true;

                        shoots[i + 2].x = enemies[n].x + 4;
                        shoots[i + 2].y = enemies[n].y + 10;
                        shoots[i + 2].direction = 3;
                        shoots[i + 2].lifeTime = 0;
                        shoots[i + 2].active = true;

                        shoots[i + 3].x = enemies[n].x + 4;
                        shoots[i + 3].y = enemies[n].y + 10;
                        shoots[i + 3].direction = 4;
                        shoots[i + 3].lifeTime = 0;
                        shoots[i + 3].active = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_SHOOTS; i++)
    {
        if (shoots[i].active) {
            shoots[i].lifeTime++;
            if (shoots[i].lifeTime >= SHOOTS_MAX_LIFETIME) shoots[i].active = false;

            switch (shoots[i].direction)
            {
            case 1:
                shoots[i].y--;
                break;
            case 2:
                shoots[i].x++;
                break;
            case 3:
                shoots[i].y++;
                break;
            case 4:
                shoots[i].x--;
                break;
            default:
                break;
            }
        }
    }
}