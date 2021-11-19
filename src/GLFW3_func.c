//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// LESSON 05: Image struct
// NOTE: Image data is stored in CPU memory (RAM)
typedef struct Image {
    unsigned int width;         // Image width
    unsigned int height;        // Image height
    Color* data;                // Image data (Color - 32 bpp - R8G8B8A8)
} Image;

// LESSON 06: Tile struct
typedef struct Tile {
    int value;                  // Tile index value (in tileset)
    bool collider;              // Tile collider (0 -> walkable)
    Color color;                // Tile color (could be useful)
} Tile;

// LESSON 06: Tilemap struct
typedef struct Tilemap {
    Tile* tiles;                // Tiles data
    int tileCountX;             // Tiles counter X
    int tileCountY;             // Tiles counter Y
    int tileSize;               // Tile size (XY)
    Vector2 position;           // Tilemap position in screen
} Tilemap;

#define LIGHTGRAY  (Color){ 200, 200, 200, 255 }        // Light Gray
#define GRAY       (Color){ 130, 130, 130, 255 }        // Gray
#define DARKGRAY   (Color){ 80, 80, 80, 255 }           // Dark Gray
#define YELLOW     (Color){ 253, 249, 0, 255 }          // Yellow
#define GOLD       (Color){ 255, 203, 0, 255 }          // Gold
#define ORANGE     (Color){ 255, 161, 0, 255 }          // Orange
#define PINK       (Color){ 255, 109, 194, 255 }        // Pink
#define RED        (Color){ 230, 41, 55, 255 }          // Red
#define MAROON     (Color){ 190, 33, 55, 255 }          // Maroon
#define GREEN      (Color){ 0, 228, 48, 255 }           // Green
#define LIME       (Color){ 0, 158, 47, 255 }           // Lime
#define DARKGREEN  (Color){ 0, 117, 44, 255 }           // Dark Green
#define SKYBLUE    (Color){ 102, 191, 255, 255 }        // Sky Blue
#define BLUE       (Color){ 0, 121, 241, 255 }          // Blue
#define DARKBLUE   (Color){ 0, 82, 172, 255 }           // Dark Blue
#define PURPLE     (Color){ 200, 122, 255, 255 }        // Purple
#define VIOLET     (Color){ 135, 60, 190, 255 }         // Violet
#define DARKPURPLE (Color){ 112, 31, 126, 255 }         // Dark Purple
#define BEIGE      (Color){ 211, 176, 131, 255 }        // Beige
#define BROWN      (Color){ 127, 106, 79, 255 }         // Brown
#define DARKBROWN  (Color){ 76, 63, 47, 255 }           // Dark Brown

#define WHITE      (Color){ 255, 255, 255, 255 }        // White
#define BLACK      (Color){ 0, 0, 0, 255 }              // Black
#define BLANK      (Color){ 0, 0, 0, 0 }                // Transparent
#define MAGENTA    (Color){ 255, 0, 255, 255 }          // Magenta
#define RAYWHITE   (Color){ 245, 245, 245, 255 }        // Ray White

//----------------------------------------------------------------------------------
// Global Variables Declaration
//----------------------------------------------------------------------------------

// LESSON 01: Window and graphic device initialization and management
GLFWwindow* window;

// Timming required variables
static double currentTime, previousTime;    // Used to track timmings
static double frameTime = 0.0;              // Time measure for one frame
static double targetTime = 0.0;             // Desired time for one frame, if 0 not applied

// LESSON 03: Keyboard input management
// Register keyboard states (current and previous)
static char previousKeyState[512] = { 0 };  // Registers previous frame key state
static char currentKeyState[512] = { 0 };   // Registers current frame key state

// LESSON 06: Tilemap data loading and drawing
#define TILESET_TILES  308

// NOTE: Tileset rectangles are directly provided in this array but
// they can also be loaded from a file... usually generated with
// a tilemap editor software
static Rectangle tilesetRecs[TILESET_TILES] = {
    { 0, 0, 16, 16 }, { 16, 0, 16, 16 }, { 32, 0, 16, 16 },
    { 48, 0, 16, 16 }, { 64, 0, 16, 16 }, { 80, 0, 16, 16 },
    { 96, 0, 16, 16 }, { 112, 0, 16, 16 }, { 128, 0, 16, 16 },
    { 144, 0, 16, 16 }, { 160, 0, 16, 16 }, { 176, 0, 16, 16 },
    { 192, 0, 16, 16 }, { 208, 0, 16, 16 }, { 224, 0, 16, 16 },
    { 240, 0, 16, 16 }, { 256, 0, 16, 16 }, { 272, 0, 16, 16 },
    { 288, 0, 16, 16 }, { 304, 0, 16, 16 }, { 320, 0, 16, 16 },
    { 336, 0, 16, 16 },
    { 0, 16, 16, 16 }, { 16, 16, 16, 16 }, { 32, 16, 16, 16 },
    { 48, 16, 16, 16 }, { 64, 16, 16, 16 }, { 80, 16, 16, 16 },
    { 96, 16, 16, 16 }, { 112, 16, 16, 16 }, { 128, 16, 16, 16 },
    { 144, 16, 16, 16 }, { 160, 16, 16, 16 }, { 176, 16, 16, 16 },
    { 192, 16, 16, 16 }, { 208, 16, 16, 16 }, { 224, 16, 16, 16 },
    { 240, 16, 16, 16 }, { 256, 16, 16, 16 }, { 272, 16, 16, 16 },
    { 288, 16, 16, 16 }, { 304, 16, 16, 16 }, { 320, 16, 16, 16 },
    { 336, 16, 16, 16 },
    { 0, 32, 16, 16 }, { 16, 32, 16, 16 }, { 32, 32, 16, 16 },
    { 48, 32, 16, 16 }, { 64, 32, 16, 16 }, { 80, 32, 16, 16 },
    { 96, 32, 16, 16 }, { 112, 32, 16, 16 }, { 128, 32, 16, 16 },
    { 144, 32, 16, 16 }, { 160, 32, 16, 16 }, { 176, 32, 16, 16 },
    { 192, 32, 16, 16 }, { 208, 32, 16, 16 }, { 224, 32, 16, 16 },
    { 240, 32, 16, 16 }, { 256, 32, 16, 16 }, { 272, 32, 16, 16 },
    { 288, 32, 16, 16 }, { 304, 32, 16, 16 }, { 320, 32, 16, 16 },
    { 336, 32, 16, 16 },
    { 0, 48, 16, 16 }, { 16, 48, 16, 16 }, { 32, 48, 16, 16 },
    { 48, 48, 16, 16 }, { 64, 48, 16, 16 }, { 80, 48, 16, 16 },
    { 96, 48, 16, 16 }, { 112, 48, 16, 16 }, { 128, 48, 16, 16 },
    { 144, 48, 16, 16 }, { 160, 48, 16, 16 }, { 176, 48, 16, 16 },
    { 192, 48, 16, 16 }, { 208, 48, 16, 16 }, { 224, 48, 16, 16 },
    { 240, 48, 16, 16 }, { 256, 48, 16, 16 }, { 272, 48, 16, 16 },
    { 288, 48, 16, 16 }, { 304, 48, 16, 16 }, { 320, 48, 16, 16 },
    { 336, 48, 16, 16 },
    { 0, 64, 16, 16 }, { 16, 64, 16, 16 }, { 32, 64, 16, 16 },
    { 48, 64, 16, 16 }, { 64, 64, 16, 16 }, { 80, 64, 16, 16 },
    { 96, 64, 16, 16 }, { 112, 64, 16, 16 }, { 128, 64, 16, 16 },
    { 144, 64, 16, 16 }, { 160, 64, 16, 16 }, { 176, 64, 16, 16 },
    { 192, 64, 16, 16 }, { 208, 64, 16, 16 }, { 224, 64, 16, 16 },
    { 240, 64, 16, 16 }, { 256, 64, 16, 16 }, { 272, 64, 16, 16 },
    { 288, 64, 16, 16 }, { 304, 64, 16, 16 }, { 320, 64, 16, 16 },
    { 336, 64, 16, 16 },
    { 0, 80, 16, 16 }, { 16, 80, 16, 16 }, { 32, 80, 16, 16 },
    { 48, 80, 16, 16 }, { 64, 80, 16, 16 }, { 80, 80, 16, 16 },
    { 96, 80, 16, 16 }, { 112, 80, 16, 16 }, { 128, 80, 16, 16 },
    { 144, 80, 16, 16 }, { 160, 80, 16, 16 }, { 176, 80, 16, 16 },
    { 192, 80, 16, 16 }, { 208, 80, 16, 16 }, { 224, 80, 16, 16 },
    { 240, 80, 16, 16 }, { 256, 80, 16, 16 }, { 272, 80, 16, 16 },
    { 288, 80, 16, 16 }, { 304, 80, 16, 16 }, { 320, 80, 16, 16 },
    { 336, 80, 16, 16 },
    { 0, 96, 16, 16 }, { 16, 96, 16, 16 }, { 32, 96, 16, 16 },
    { 48, 96, 16, 16 }, { 64, 96, 16, 16 }, { 80, 96, 16, 16 },
    { 96, 96, 16, 16 }, { 112, 96, 16, 16 }, { 128, 96, 16, 16 },
    { 144, 96, 16, 16 }, { 160, 96, 16, 16 }, { 176, 96, 16, 16 },
    { 192, 96, 16, 16 }, { 208, 96, 16, 16 }, { 224, 96, 16, 16 },
    { 240, 96, 16, 16 }, { 256, 96, 16, 16 }, { 272, 96, 16, 16 },
    { 288, 96, 16, 16 }, { 304, 96, 16, 16 }, { 320, 96, 16, 16 },
    { 336, 96, 16, 16 },
    { 0, 112, 16, 16 }, { 16, 112, 16, 16 }, { 32, 112, 16, 16 },
    { 48, 112, 16, 16 }, { 64, 112, 16, 16 }, { 80, 112, 16, 16 },
    { 96, 112, 16, 16 }, { 112, 112, 16, 16 }, { 128, 112, 16, 16 },
    { 144, 112, 16, 16 }, { 160, 112, 16, 16 }, { 176, 112, 16, 16 },
    { 192, 112, 16, 16 }, { 208, 112, 16, 16 }, { 224, 112, 16, 16 },
    { 240, 112, 16, 16 }, { 256, 112, 16, 16 }, { 272, 112, 16, 16 },
    { 288, 112, 16, 16 }, { 304, 112, 16, 16 }, { 320, 112, 16, 16 },
    { 336, 112, 16, 16 },
    { 0, 128, 16, 16 }, { 16, 128, 16, 16 }, { 32, 128, 16, 16 },
    { 48, 128, 16, 16 }, { 64, 128, 16, 16 }, { 80, 128, 16, 16 },
    { 96, 128, 16, 16 }, { 112, 128, 16, 16 }, { 128, 128, 16, 16 },
    { 144, 128, 16, 16 }, { 160, 128, 16, 16 }, { 176, 128, 16, 16 },
    { 192, 128, 16, 16 }, { 208, 128, 16, 16 }, { 224, 128, 16, 16 },
    { 240, 128, 16, 16 }, { 256, 128, 16, 16 }, { 272, 128, 16, 16 },
    { 288, 128, 16, 16 }, { 304, 128, 16, 16 }, { 320, 128, 16, 16 },
    { 336, 128, 16, 16 },
    { 0, 144, 16, 16 }, { 16, 144, 16, 16 }, { 32, 144, 16, 16 },
    { 48, 144, 16, 16 }, { 64, 144, 16, 16 }, { 80, 144, 16, 16 },
    { 96, 144, 16, 16 }, { 112, 144, 16, 16 }, { 128, 144, 16, 16 },
    { 144, 144, 16, 16 }, { 160, 144, 16, 16 }, { 176, 144, 16, 16 },
    { 192, 144, 16, 16 }, { 208, 144, 16, 16 }, { 224, 144, 16, 16 },
    { 240, 144, 16, 16 }, { 256, 144, 16, 16 }, { 272, 144, 16, 16 },
    { 288, 144, 16, 16 }, { 304, 144, 16, 16 }, { 320, 144, 16, 16 },
    { 336, 144, 16, 16 },
    { 0, 160, 16, 16 }, { 16, 160, 16, 16 }, { 32, 160, 16, 16 },
    { 48, 160, 16, 16 }, { 64, 160, 16, 16 }, { 80, 160, 16, 16 },
    { 96, 160, 16, 16 }, { 112, 160, 16, 16 }, { 128, 160, 16, 16 },
    { 144, 160, 16, 16 }, { 160, 160, 16, 16 }, { 176, 160, 16, 16 },
    { 192, 160, 16, 16 }, { 208, 160, 16, 16 }, { 224, 160, 16, 16 },
    { 240, 160, 16, 16 }, { 256, 160, 16, 16 }, { 272, 160, 16, 16 },
    { 288, 160, 16, 16 }, { 304, 160, 16, 16 }, { 320, 160, 16, 16 },
    { 336, 160, 16, 16 },
    { 0, 176, 16, 16 }, { 16, 176, 16, 16 }, { 32, 176, 16, 16 },
    { 48, 176, 16, 16 }, { 64, 176, 16, 16 }, { 80, 176, 16, 16 },
    { 96, 176, 16, 16 }, { 112, 176, 16, 16 }, { 128, 176, 16, 16 },
    { 144, 176, 16, 16 }, { 160, 176, 16, 16 }, { 176, 176, 16, 16 },
    { 192, 176, 16, 16 }, { 208, 176, 16, 16 }, { 224, 176, 16, 16 },
    { 240, 176, 16, 16 }, { 256, 176, 16, 16 }, { 272, 176, 16, 16 },
    { 288, 176, 16, 16 }, { 304, 176, 16, 16 }, { 320, 176, 16, 16 },
    { 336, 176, 16, 16 },
    { 0, 192, 16, 16 }, { 16, 192, 16, 16 }, { 32, 192, 16, 16 },
    { 48, 192, 16, 16 }, { 64, 192, 16, 16 }, { 80, 192, 16, 16 },
    { 96, 192, 16, 16 }, { 112, 192, 16, 16 }, { 128, 192, 16, 16 },
    { 144, 192, 16, 16 }, { 160, 192, 16, 16 }, { 176, 192, 16, 16 },
    { 192, 192, 16, 16 }, { 208, 192, 16, 16 }, { 224, 192, 16, 16 },
    { 240, 192, 16, 16 }, { 256, 192, 16, 16 }, { 272, 192, 16, 16 },
    { 288, 192, 16, 16 }, { 304, 192, 16, 16 }, { 320, 192, 16, 16 },
    { 336, 192, 16, 16 },
    { 0, 208, 16, 16 }, { 16, 208, 16, 16 }, { 32, 208, 16, 16 },
    { 48, 208, 16, 16 }, { 64, 208, 16, 16 }, { 80, 208, 16, 16 },
    { 96, 208, 16, 16 }, { 112, 208, 16, 16 }, { 128, 208, 16, 16 },
    { 144, 208, 16, 16 }, { 160, 208, 16, 16 }, { 176, 208, 16, 16 },
    { 192, 208, 16, 16 }, { 208, 208, 16, 16 }, { 224, 208, 16, 16 },
    { 240, 208, 16, 16 }, { 256, 208, 16, 16 }, { 272, 208, 16, 16 },
    { 288, 208, 16, 16 }, { 304, 208, 16, 16 }, { 320, 208, 16, 16 },
    { 336, 208, 16, 16 }
};

// LESSON 07: Collision detection
#define PLAYER_COLLISION_PADDING    12      // Player padding to detect collision with walls

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------

// LESSON 02: Window and graphic device initialization and management
//----------------------------------------------------------------------------------
static void ErrorCallback(int error, const char* description);                              // GLFW3: Error callback function
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);   // GLFW3: Keyboard callback function

static void InitWindow(int width, int height);          // Initialize window and context
static void InitGraphicsDevice(int width, int height);  // Initialize graphic device
static void CloseWindow(void);                          // Close window and free resources
static void SetTargetFPS(int fps);                      // Set target FPS (maximum)
static void SyncFrame(void);                            // Synchronize to desired framerate

// LESSON 03: Inputs management (keyboard and mouse)
//----------------------------------------------------------------------------------
static bool IsKeyDown(int key);                     // Detect if a key is being pressed (key held down)
static bool IsKeyPressed(int key);                  // Detect if a key has been pressed once
static void PollInputEvents(void);                  // Poll (store) all input events

// LESSON 04: Basic shapes drawing
//----------------------------------------------------------------------------------
static void DrawLine(Vector2 startPos, Vector2 endPos, Color color);                // Draw a line
static void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);          // Draw a triangle
static void DrawRectangle(int posX, int posY, int width, int height, Color color);  // Draw a rectangle
static void DrawRectangleRec(Rectangle rec, Color color);                           // Draw a rectangle

// LESSON 05: Image data loading, texture creation, texture drawing
//----------------------------------------------------------------------------------
static Image LoadImage(const char* fileName);       // Load image data to CPU memory (RAM)
static void UnloadImage(Image image);               // Unload image data from CPU memory (RAM)
static Texture2D LoadTextureFromImage(Image image); // Load texture from image data into GPU memory (VRAM)
static void UnloadTexture(Texture2D texture);       // Unload texture data from GPU memory (VRAM)
static Image LoadBMP(const char* fileName);         // Load BMP image file data

static void DrawTexture(Texture2D texture, int posX, int posY, Color tint);   // Draw texture in screen position coordinates
static void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);    // Draw a Texture2D with extended parameters
static void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);           // Draw a part of a texture (defined by a rectangle)
static void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint); // Draw a part of a texture (defined by a rectangle) with 'pro' parameters

// LESSON 06: Tilemap data loading and drawing
//----------------------------------------------------------------------------------
static Tilemap LoadTilemap(const char* valuesMap, const char* collidersMap);// Load tilemap data from file
static void UnloadTilemap(Tilemap map);                   // Unload tilemap data
static void DrawTilemap(Tilemap map, Texture2D tileset);  // Draw tilemap using tileset

// LESSON 07: Collision detection
//----------------------------------------------------------------------------------
static bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2); // Check collision between two rectangles



//----------------------------------------------------------------------------------
// Module specific Functions Definitions
//----------------------------------------------------------------------------------

// GLFW3: Error callback
static void ErrorCallback(int error, const char* description)
{
    TraceLog(LOG_ERROR, description);
}

// GLFW3: Keyboard callback
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    else currentKeyState[key] = action;
}

// LESSON 01: Window creation and management
//----------------------------------------------------------------------------------
// Initialize window and context (OpenGL 3.3)
static void InitWindow(int screenWidth, int screenHeight)
{
    // GLFW3 Initialization + OpenGL 3.3 Context + Extensions
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) TraceLog(LOG_WARNING, "GLFW3: Can not initialize GLFW");
    else TraceLog(LOG_INFO, "GLFW3: GLFW initialized successfully");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(screenWidth, screenHeight, "PEC2: 2D DUNGEON GAME", NULL, NULL);

    if (!window) glfwTerminate();
    else TraceLog(LOG_INFO, "GLFW3: Window created successfully");

    glfwSetWindowPos(window, 200, 200);

    glfwSetKeyCallback(window, KeyCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

// Close window and free resources
static void CloseWindow(void)
{
    glfwDestroyWindow(window);      // Close window
    glfwTerminate();                // Free GLFW3 resources
}

// Set target FPS (maximum)
static void SetTargetFPS(int fps)
{
    if (fps < 1) targetTime = 0.0;
    else targetTime = 1.0 / (double)fps;
}

// Synchronize to desired framerate
static void SyncFrame(void)
{
    // Frame time control system
    currentTime = glfwGetTime();
    frameTime = currentTime - previousTime;
    previousTime = currentTime;

    // Wait for some milliseconds...
    if (frameTime < targetTime)
    {
        double prevTime = glfwGetTime();
        double nextTime = 0.0;

        // Busy wait loop
        while ((nextTime - prevTime) < (targetTime - frameTime)) nextTime = glfwGetTime();

        currentTime = glfwGetTime();
        double extraTime = currentTime - previousTime;
        previousTime = currentTime;

        frameTime += extraTime;
    }
}

// LESSON 02: Graphic device initialization and management
//----------------------------------------------------------------------------------
// Initialize graphic device (OpenGL 3.3)
static void InitGraphicsDevice(int width, int height)
{
    // Load OpenGL 3.3 supported extensions
    rlLoadExtensions(glfwGetProcAddress);

    // Initialize OpenGL context (states and resources)
    rlglInit(width, height);

    // Initialize viewport and internal projection/modelview matrices
    rlViewport(0, 0, width, height);
    rlMatrixMode(RL_PROJECTION);                        // Switch to PROJECTION matrix
    rlLoadIdentity();                                   // Reset current matrix (PROJECTION)
    rlOrtho(0, width, height, 0, 0.0f, 1.0f);           // Orthographic projection with top-left corner at (0,0)
    rlMatrixMode(RL_MODELVIEW);                         // Switch back to MODELVIEW matrix
    rlLoadIdentity();                                   // Reset current matrix (MODELVIEW)

    rlClearColor(255, 255, 255, 255);                         // Define clear color (BLACK)
    rlEnableDepthTest();                                // Enable DEPTH_TEST for 3D
}

// LESSON 03: Inputs management (keyboard and mouse)
//----------------------------------------------------------------------------------
// Detect if a key is being pressed (key held down)
static bool IsKeyDown(int key)
{
    return glfwGetKey(window, key);
}

// Detect if a key has been pressed once
static bool IsKeyPressed(int key)
{
    if ((currentKeyState[key] != previousKeyState[key]) && (currentKeyState[key] == 1)) return true;
    else return false;
}

// Poll (store) all input events
static void PollInputEvents(void)
{
    // Register previous keys states (required to check variations)
    for (int i = 0; i < 512; i++) previousKeyState[i] = currentKeyState[i];

    // Input events polling (managed by GLFW3 through callback)
    glfwPollEvents();
}

// LESSON 04: Basic shapes drawing
//----------------------------------------------------------------------------------
// Draw a line
static void DrawLine(Vector2 startPos, Vector2 endPos, Color color)
{
    rlBegin(RL_LINES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex2f(startPos.x, startPos.y);
    rlVertex2f(endPos.x, endPos.y);
    rlEnd();
}

// Draw a triangle
static void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color)
{
    rlEnableTexture(GetTextureDefault().id); // Default white texture

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlVertex2f(v1.x, v1.y);
    rlVertex2f(v2.x, v2.y);
    rlVertex2f(v2.x, v2.y);
    rlVertex2f(v3.x, v3.y);
    rlEnd();

    rlDisableTexture();
}

// Draw color-filled rectangle
static void DrawRectangle(int posX, int posY, int width, int height, Color color)
{
#define TRIS_RECTANGLE
#if defined(TRIS_RECTANGLE)
    // NOTE: We use rlgl OpenGL 1.1 style vertex definition
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlVertex2i(posX, posY);
    rlVertex2i(posX, posY + height);
    rlVertex2i(posX + width, posY + height);

    rlVertex2i(posX, posY);
    rlVertex2i(posX + width, posY + height);
    rlVertex2i(posX + width, posY);
    rlEnd();
#else   // QUADS_RECTANGLE
    // NOTE: Alternative implementation using RL_QUADS
    rlEnableTexture(GetDefaultTexture().id);    // Default white texture
    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlNormal3f(0.0f, 0.0f, 1.0f);

    rlTexCoord2f(0.0f, 0.0f);
    rlVertex2f(position.x, position.y);

    rlTexCoord2f(0.0f, 1.0f);
    rlVertex2f(position.x, position.y + size.y);

    rlTexCoord2f(1.0f, 1.0f);
    rlVertex2f(position.x + size.x, position.y + size.y);

    rlTexCoord2f(1.0f, 0.0f);
    rlVertex2f(position.x + size.x, position.y);
    rlEnd();
    rlDisableTexture();
#endif
}

// Draw a color-filled rectangle
static void DrawRectangleRec(Rectangle rec, Color color)
{
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, color);
}

// LESSON 05: Image data loading, texture creation, texture drawing
//----------------------------------------------------------------------------------
// Load image data to CPU memory (RAM)
static Image LoadImage(const char* fileName)
{
    Image image = { 0 };
    const char* fileExt;

    if ((fileExt = strrchr(fileName, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".bmp") == 0) image = LoadBMP(fileName);
    }

    return image;
}

// Unload image data from CPU memory (RAM)
static void UnloadImage(Image image)
{
    if (image.data != NULL) free(image.data);
}

// Load texture from image data into GPU memory (VRAM)
static Texture2D LoadTextureFromImage(Image image)
{
#define UNCOMPRESSED_R8G8B8A8    7      // Texture format (must match image.data)

    Texture2D texture = { 0 };

    // NOTE: Texture2D struct is defined inside rlgl
    texture.width = image.width;
    texture.height = image.height;
    texture.format = UNCOMPRESSED_R8G8B8A8;
    texture.mipmaps = 1;

    texture.id = rlLoadTexture(image.data, image.width, image.height, UNCOMPRESSED_R8G8B8A8, 1);

    return texture;
}

// Unload texture data from GPU memory (VRAM)
static void UnloadTexture(Texture2D texture)
{
    if (texture.id > 0) rlDeleteTextures(texture.id);
}

// Load bmp fileformat data
// NOTE: Be careful with lines padding and v-flipped data 
static Image LoadBMP(const char* fileName)
{
    Image image = { 0 };

    int imgWidth;
    int imgHeight;
    short imgBpp;
    int imgDataOffset;

    FILE* bmpFile = fopen(fileName, "rb");

    fseek(bmpFile, 10, SEEK_SET);
    fread(&imgDataOffset, 4, 1, bmpFile);   // Read bmp data offset
    fseek(bmpFile, 18, SEEK_SET);
    fread(&imgWidth, 4, 1, bmpFile);        // Read bmp width
    fread(&imgHeight, 4, 1, bmpFile);       // Read bmp height
    fseek(bmpFile, 28, SEEK_SET);
    fread(&imgBpp, 2, 1, bmpFile);          // Read bmp bit-per-pixel (usually 24bpp - B8G8R8)

    Color* imgData = (Color*)malloc(imgWidth * imgHeight * sizeof(Color));

    fseek(bmpFile, imgDataOffset, SEEK_SET);

    // Calculate image padding per line
    int padding = (imgWidth * imgBpp) % 32;
    int unusedData = 0;
    int extraBytes = 0;

    if ((padding / 8) > 0) extraBytes = 4 - (padding / 8);

    // Read image data
    for (int j = 0; j < imgHeight; j++)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            fread(&imgData[j * imgWidth + i].b, 1, 1, bmpFile);
            fread(&imgData[j * imgWidth + i].g, 1, 1, bmpFile);
            fread(&imgData[j * imgWidth + i].r, 1, 1, bmpFile);
            imgData[j * imgWidth + i].a = 255;    // Set alpha to fully opaque by default

            // NOTE: We consider a color key: MAGENTA RGB{ 255, 0, 255 },
            // in that case, pixel will be transparent
            if ((imgData[j * imgWidth + i].r == 255) &&
                (imgData[j * imgWidth + i].g == 0) &&
                (imgData[j * imgWidth + i].b == 255)) imgData[j * imgWidth + i].a = 0;
        }

        fread(&unusedData, extraBytes, 1, bmpFile);
    }

    fclose(bmpFile);

    image.data = (Color*)malloc(imgWidth * imgHeight * sizeof(Color));

    // Flip image vertically
    for (int j = 0; j < imgHeight; j++)
    {
        for (int i = 0; i < imgWidth; i++)
        {
            image.data[j * imgWidth + i] = imgData[((imgHeight - 1) - j) * imgWidth + i];
        }
    }

    free(imgData);

    image.width = imgWidth;
    image.height = imgHeight;

    TraceLog(LOG_INFO, "[%s] BMP Image loaded successfully (%ix%i)", fileName, imgWidth, imgHeight);

    return image;
}

// NOTE: Multiple versions od DrawTexture() are provided with multiple options

// Draw texture in screen position coordinates
static void DrawTexture(Texture2D texture, int posX, int posY, Color tint)
{
    DrawTextureEx(texture, (Vector2) { (float)posX, (float)posY }, 0, 1.0f, tint);
}

// Draw a Texture2D with extended parameters
static void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
{
    Rectangle sourceRec = { 0, 0, texture.width, texture.height };
    Rectangle destRec = { (int)position.x, (int)position.y, texture.width * scale, texture.height * scale };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, tint);
}

// Draw a part of a texture (defined by a rectangle)
static void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint)
{
    Rectangle destRec = { (int)position.x, (int)position.y, abs(sourceRec.width), abs(sourceRec.height) };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, tint);
}

// Draw a part of a texture (defined by a rectangle) with 'pro' parameters
// NOTE: origin is relative to destination rectangle size
static void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint)
{
    // Check if texture is valid
    if (texture.id != 0)
    {
        if (sourceRec.width < 0) sourceRec.x -= sourceRec.width;
        if (sourceRec.height < 0) sourceRec.y -= sourceRec.height;

        rlEnableTexture(texture.id);

        rlPushMatrix();
        rlTranslatef((float)destRec.x, (float)destRec.y, 0);
        rlRotatef(rotation, 0, 0, 1);
        rlTranslatef(-origin.x, -origin.y, 0);

        rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        rlNormal3f(0.0f, 0.0f, 1.0f);                          // Normal vector pointing towards viewer

        // Bottom-left corner for texture and quad
        rlTexCoord2f((float)sourceRec.x / texture.width, (float)sourceRec.y / texture.height);
        rlVertex2f(0.0f, 0.0f);

        // Bottom-right corner for texture and quad
        rlTexCoord2f((float)sourceRec.x / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
        rlVertex2f(0.0f, (float)destRec.height);

        // Top-right corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)(sourceRec.y + sourceRec.height) / texture.height);
        rlVertex2f((float)destRec.width, (float)destRec.height);

        // Top-left corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width) / texture.width, (float)sourceRec.y / texture.height);
        rlVertex2f((float)destRec.width, 0.0f);
        rlEnd();
        rlPopMatrix();

        rlDisableTexture();
    }
}

// LESSON 06: Tilemap data loading and drawing
//----------------------------------------------------------------------------------
// Load tilemap data from file (text/image)
static Tilemap LoadTilemap(const char* valuesMap, const char* collidersMap)
{
    Tilemap map = { 0 };
    const char* fileExt;

    if ((fileExt = strrchr(valuesMap, '.')) != NULL)
    {
        // Check if file extension is supported
        if (strcmp(fileExt, ".txt") == 0)
        {
            int counter = 0;
            int temp = 0;

            // Read values from text file
            FILE* valuesFile = fopen(valuesMap, "rt");

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &temp);
                counter++;
            }

            rewind(valuesFile);        // Return to the beginning of the file, to read again

            map.tiles = (Tile*)malloc(counter * sizeof(Tile));

            map.tileCountX = 12;
            map.tileCountY = 8;
            counter = 0;

            while (!feof(valuesFile))
            {
                fscanf(valuesFile, "%i", &map.tiles[counter].value);
                counter++;
            }

            fclose(valuesFile);

            // Read values from text file
            // NOTE: Colliders map data MUST match values data, 
            // or we need to do a previous check like done with values data
            FILE* collidersFile = fopen(collidersMap, "rt");
            counter = 0;
            temp = 0;

            while (!feof(collidersFile))
            {
                fscanf(collidersFile, "%i", &temp);
                map.tiles[counter].collider = temp;

                counter++;
            }

            fclose(collidersFile);

            // print tilemap information loaded
            /*for (int j = 0; j < map.tileCountY; j++)
            {
                for (int i = 0; i < map.tileCountX; i++)
                {
                    printf("%i ", map.tiles[j * map.tileCountX + i].collider);
                }

                printf("\n");
            }*/

        }
        else if (strcmp(fileExt, ".bmp") == 0)
        {
            Image image = LoadImage(valuesMap);
            Image image_colliders = LoadImage(collidersMap);

            map.tileCountX = image.width;
            map.tileCountY = image.height;
            map.tileSize = image.width * image.height;
            map.tiles = (Tile*)malloc(map.tileSize * sizeof(Tile));

            // TODO: Load tile data from image pixel data

            // NOTE: When using images to codify map data, 
            // lot of extra information can be codified in each pixel!

            for (int i = 0; i < map.tileSize; i++)
            {
                map.tiles[i].color = image.data[i];

                if (image_colliders.data[i].r == 0 && image_colliders.data[i].g == 0 && image_colliders.data[i].b == 0) map.tiles[i].collider = 1;
                else map.tiles[i].collider = 0;

                map.tiles[i].value = image.data[i].r;
            }
        }
    }

    return map;
}

// Unload tilemap data from memory
static void UnloadTilemap(Tilemap map)
{
    if (map.tiles != NULL) free(map.tiles);
}

// Draw tilemap using tileset
static void DrawTilemap(Tilemap map, Texture2D tileset)
{
    for (int y = 0; y < map.tileCountY; y++)
    {
        for (int x = 0; x < map.tileCountX; x++)
        {
            // Draw each piece of the tileset in the right position to build map
            DrawTextureRec(tileset, tilesetRecs[map.tiles[y * map.tileCountX + x].value - 1],
                (Vector2) {
                map.position.x + x * map.tileSize, map.position.y + y * map.tileSize
            }, WHITE);
        }
    }
}

// LESSON 07: Collision detection
//----------------------------------------------------------------------------------
// Check collision between two rectangles
static bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2)
{
    bool collision = false;

    int dx = abs((rec1.x + rec1.width / 2) - (rec2.x + rec2.width / 2));
    int dy = abs((rec1.y + rec1.height / 2) - (rec2.y + rec2.height / 2));

    if ((dx <= (rec1.width / 2 + rec2.width / 2)) && ((dy <= (rec1.height / 2 + rec2.height / 2)))) collision = true;

    return collision;
}