static int finishScreen;

static int selectedTitleOption = 0;
static int maxTitleOptions = 0;

Image option1_image;
Texture2D option1_texture;
Vector2 option1_position = { 0, 0 };

Image option2_image;
Texture2D option2_texture;
Vector2 option2_position = { 0, 0 };

void InitTitleScreen(void) {
    finishScreen = 0;
    winner = false;

    selectedTitleOption = 1;
    maxTitleOptions = 2;

    option1_image = LoadImage("resources/option1.bmp");
    option1_texture = LoadTextureFromImage(option1_image);
    UnloadImage(option1_image);
    option1_position.x = (float)(screenWidth / 2 - option1_texture.width / 2);
    option1_position.y = (float)(screenHeight / 2 - option1_texture.height / 2);

    option2_image = LoadImage("resources/option2.bmp");
    option2_texture = LoadTextureFromImage(option2_image);
    UnloadImage(option2_image);
    option2_position.x = (float)(screenWidth / 2 - option2_texture.width / 2);
    option2_position.y = (float)(screenHeight / 2 - option2_texture.height / 2);
}

void UpdateTitleScreen(void) {
    if (IsKeyPressed(GLFW_KEY_ENTER)) {
        finishScreen = selectedTitleOption;
    }
    if (IsKeyPressed(GLFW_KEY_DOWN)) {
        selectedTitleOption++;
        if (selectedTitleOption > maxTitleOptions) selectedTitleOption = 1;
    }
    else if (IsKeyPressed(GLFW_KEY_UP)) {
        selectedTitleOption--;
        if (selectedTitleOption == 0) selectedTitleOption = maxTitleOptions;
    }
}

void DrawTitleScreen(void) {
    switch (selectedTitleOption){
        case 1: {
            DrawTexture(option1_texture, option1_position.x, option1_position.y, WHITE);
        } break;
        case 2: {
            DrawTexture(option2_texture, option2_position.x, option2_position.y, WHITE);
        } break;
        default: break;
    }
}

void UnloadTitleScreen(void) {
    UnloadTexture(option1_texture);
    UnloadTexture(option2_texture);
}

int FinishTitleScreen(void) {
    return finishScreen;
}