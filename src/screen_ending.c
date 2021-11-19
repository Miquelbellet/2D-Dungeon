static int finishScreen;

static int endingSelectedTitleOption = 0;
static int endingMaxTitleOptions = 0;

Image exit_option1_image;
Texture2D exit_option1_texture;
Vector2 exit_option1_position = { 0, 0 };

Image exit_option2_image;
Texture2D exit_option2_texture;
Vector2 exit_option2_position = { 0, 0 };

Image exit_option3_image;
Texture2D exit_option3_texture;
Vector2 exit_option3_position = { 0, 0 };

Image winner_image;
Texture2D winner_texture;
Vector2 winner_position = { 0, 0 };

void InitEndingScreen(void) {
    finishScreen = 0;

    endingSelectedTitleOption = 1;
    endingMaxTitleOptions = 3;

    exit_option1_image = LoadImage("resources/exit_option1.bmp");
    exit_option1_texture = LoadTextureFromImage(exit_option1_image);
    UnloadImage(exit_option1_image);
    exit_option1_position.x = (float)(screenWidth / 2 - exit_option1_texture.width / 2);
    exit_option1_position.y = (float)(screenHeight / 2 - exit_option1_texture.height / 2);

    exit_option2_image = LoadImage("resources/exit_option2.bmp");
    exit_option2_texture = LoadTextureFromImage(exit_option2_image);
    UnloadImage(exit_option2_image);
    exit_option2_position.x = (float)(screenWidth / 2 - exit_option2_texture.width / 2);
    exit_option2_position.y = (float)(screenHeight / 2 - exit_option2_texture.height / 2);

    exit_option3_image = LoadImage("resources/exit_option3.bmp");
    exit_option3_texture = LoadTextureFromImage(exit_option3_image);
    UnloadImage(exit_option3_image);
    exit_option3_position.x = (float)(screenWidth / 2 - exit_option3_texture.width / 2);
    exit_option3_position.y = (float)(screenHeight / 2 - exit_option3_texture.height / 2);

    if (winner) winner_image = LoadImage("resources/win_game.bmp");
    else winner_image = LoadImage("resources/loose_game.bmp");
    winner_texture = LoadTextureFromImage(winner_image);
    UnloadImage(winner_image);
    winner_position.x = (float)(screenWidth / 2 - winner_texture.width / 2);
    winner_position.y = (float)(screenHeight / 6 - winner_texture.height / 2);
}

void UpdateEndingScreen(void) {
    if (IsKeyPressed(GLFW_KEY_ENTER)) {
        finishScreen = endingSelectedTitleOption;
    }
    if (IsKeyPressed(GLFW_KEY_DOWN)) {
        endingSelectedTitleOption++;
        if (endingSelectedTitleOption > endingMaxTitleOptions) endingSelectedTitleOption = 1;
    }
    else if (IsKeyPressed(GLFW_KEY_UP)) {
        endingSelectedTitleOption--;
        if (endingSelectedTitleOption == 0) endingSelectedTitleOption = endingMaxTitleOptions;
    }
}

void DrawEndingScreen(void) {
    DrawTexture(winner_texture, winner_position.x, winner_position.y, WHITE);

    switch (endingSelectedTitleOption) {
    case 1: {
        DrawTexture(exit_option1_texture, exit_option1_position.x, exit_option1_position.y, WHITE);
    } break;
    case 2: {
        DrawTexture(exit_option2_texture, exit_option2_position.x, exit_option2_position.y, WHITE);
    } break;
    case 3: {
        DrawTexture(exit_option3_texture, exit_option3_position.x, exit_option3_position.y, WHITE);
    } break;
    default: break;
    }
}

void UnloadEndingScreen(void) {
    UnloadTexture(exit_option1_texture);
    UnloadTexture(exit_option2_texture);
    UnloadTexture(exit_option3_texture);
}

int FinishEndingScreen(void) {
    return finishScreen;
}