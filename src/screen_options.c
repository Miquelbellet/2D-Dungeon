static int finishScreen;

void InitOptionsScreen(void) {
    finishScreen = 0;
}

void UpdateOptionsScreen(void) {
    if (IsKeyPressed(GLFW_KEY_ENTER)) {
        finishScreen = 1;
    }
}

void DrawOptionsScreen(void) {

}

void UnloadOptionsScreen(void) {

}

int FinishOptionsScreen(void) {
    return finishScreen;
}