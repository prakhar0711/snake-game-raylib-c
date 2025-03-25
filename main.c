#include <assert.h>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 460
#define SCREEN_TITLE "Snake Game"
#define TARGET_FPS 10
#define GRID_SIZE 20
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)

typedef enum { PLAYING, GAME_OVER } GameState;
typedef struct {
  int x;
  int y;
} Position;
typedef struct {
  Position body[100];
  int length;
  Position direction;
  Position food;
} Snake;

Snake snake;
int score = 0;
GameState gameState;

void InitGame();
void UpdateGame();
void DrawGame();
void CheckCollisions();
void DrawGridLines();
void GenerateFood();

int main() {

  assert(SCREEN_WIDTH % 20 == 0);
  assert(SCREEN_HEIGHT % 20 == 0);

  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

  SetTargetFPS(TARGET_FPS);

  InitGame();
  while (!WindowShouldClose()) {
    if (gameState == PLAYING) {
      UpdateGame();
    } else if (gameState == GAME_OVER && IsKeyPressed(KEY_ENTER)) {
      InitGame();
    }
    BeginDrawing();
    DrawGame();
    EndDrawing();
  }
  return 0;
}

// handle snake game initialization
void InitGame() {
  snake.length = 3;
  snake.direction = (Position){1, 0};
  for (int i = 0; i < snake.length; i++) {
    snake.body[i] = (Position){GRID_WIDTH / 2 - i, GRID_HEIGHT / 2};
  }
  GenerateFood();
  gameState = PLAYING;

  score = 0;
}

// handle snake movement logic
void UpdateGame() {

  if (IsKeyPressed(KEY_UP) && snake.direction.y == 0) {
    snake.direction = (Position){0, -1};
  }
  if (IsKeyPressed(KEY_DOWN) && snake.direction.y == 0) {
    snake.direction = (Position){0, 1};
  }
  if (IsKeyPressed(KEY_LEFT) && snake.direction.x == 0) {
    snake.direction = (Position){-1, 0};
  }
  if (IsKeyPressed(KEY_RIGHT) && snake.direction.x == 0) {
    snake.direction = (Position){1, 0};
  }

  // optimizing snake movement
  Position prev = snake.body[0];
  Position temp;

  for (int i = 1; i < snake.length; i++) {
    temp = snake.body[i];
    snake.body[i] = prev;
    prev = temp;
  }
  snake.body[0].x += snake.direction.x;
  snake.body[0].y += snake.direction.y;

  // checking for self and border collisions
  CheckCollisions();
}

// Draw the snake window and snake and food
void DrawGame() {
  ClearBackground(BLACK);
  DrawGridLines();
  // displaying game over text and score at game over
  if (gameState == GAME_OVER) {

    DrawText("Game Over! Pres Enter to Continue", 0, 0, 30, RAYWHITE);
    DrawText(TextFormat("Final Score : %d", score), 0, 30, 40, RAYWHITE);
  }

  // drawing the snake and food
  for (int i = 0; i < snake.length; i++) {
    /*DrawRectangle(snake.body[i].x * GRID_SIZE, snake.body[i].y * GRID_SIZE,*/
    /*GRID_SIZE, GRID_SIZE, GREEN);*/
    Rectangle snakeSegment = {snake.body[i].x * GRID_SIZE,
                              snake.body[i].y * GRID_SIZE, GRID_SIZE,
                              GRID_SIZE};
    DrawRectangleRounded(snakeSegment, 2.5, 6, GREEN);
    Rectangle foodSegment = {snake.food.x * GRID_SIZE, snake.food.y * GRID_SIZE,
                             GRID_SIZE, GRID_SIZE};
    DrawRectangleRounded(foodSegment, 2.5, 6, RED);
  }
}

void CheckCollisions() {
  Position *head = &snake.body[0];
  // checking for collision with food and updating the score
  if (head->x < 0) {
    snake.body[0].x = GRID_WIDTH;
  } else if (head->x >= GRID_WIDTH) {
    snake.body[0].x = 0;
  }
  if (head->y < 0) {
    snake.body[0].y = GRID_HEIGHT;
  } else if (head->y >= GRID_HEIGHT) {
    snake.body[0].y = 0;
  }
  if (head->x == snake.food.x && head->y == snake.food.y) {
    snake.body[snake.length] = snake.body[snake.length - 1];
    snake.length++;

    score += 5;
    GenerateFood();
  }
  for (int i = 1; i < snake.length; i++) {
    if (head->x == snake.body[i].x && head->y == snake.body[i].y) {
      gameState = GAME_OVER;
      return;
    }
  }

  // border collisions
  /*if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 ||*/
  /*    head.y >= GRID_HEIGHT) {*/
  /*  gameState = GAME_OVER;*/
  /*  return;*/
  /*}*/
}

void DrawGridLines() {
  // Drawing vertical grid lines
  for (int x = 0; x < SCREEN_WIDTH; x += GRID_SIZE) {
    DrawLine(x, 0, x, SCREEN_HEIGHT, DARKGRAY);
  }

  // Drawing horizontal grid lines
  for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE) {
    DrawLine(0, y, SCREEN_WIDTH, y, DARKGRAY);
  }
}

void GenerateFood() {
  int FoodX = rand() % GRID_WIDTH;
  int FoodY = rand() % GRID_HEIGHT;
  for (int i = 0; i < snake.length; i++) {
    if (snake.body[i].x == FoodX && snake.body[i].y == FoodY) {
      GenerateFood();
      return;
    }
  }
  snake.food.x = FoodX;
  snake.food.y = FoodY;
}
