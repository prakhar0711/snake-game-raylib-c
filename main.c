// Tasks
// handle self collision
// handle border collision
// display scores
// play restart and exit prompts
#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SCREEN_TITLE "Snake Game"
#define TARGET_FPS 10
#define GRID_SIZE 20
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)

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

void InitGame();
void UpdateGame();
void DrawGame();

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
  SetTargetFPS(TARGET_FPS);
  InitGame();

  while (!WindowShouldClose()) {
    UpdateGame();
    BeginDrawing();
    DrawGame();
    EndDrawing();
  }
  return 0;
}

// handle snake initialization
void InitGame() {
  snake.length = 3;
  snake.direction = (Position){1, 0};
  for (int i = 0; i < snake.length; i++) {
    snake.body[i] = (Position){GRID_WIDTH / 2 - i, GRID_HEIGHT / 2};
  }
  srand(time(NULL));
  snake.food.x = rand() % GRID_WIDTH;
  snake.food.y = rand() % GRID_HEIGHT;
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

  for (int i = snake.length - 1; i > 0; i--) {
    snake.body[i] = snake.body[i - 1];
  }
  snake.body[0].x += snake.direction.x;
  snake.body[0].y += snake.direction.y;

  if (snake.body[0].x == snake.food.x && snake.body[0].y == snake.food.y) {
    snake.length++;
    snake.food.x = rand() % GRID_WIDTH;
    snake.food.y = rand() % GRID_HEIGHT;
  }
  if (snake.body[0].x < 0 || snake.body[0].x >= GRID_WIDTH ||
      snake.body[0].y < 0 || snake.body[0].y >= GRID_HEIGHT) {
    InitGame();
  }
}

// Draw the snake window and snake and food
void DrawGame() {
  ClearBackground(BLACK);
  for (int i = 0; i < snake.length; i++)
    DrawRectangle(snake.body[i].x * GRID_SIZE, snake.body[i].y * GRID_SIZE,
                  GRID_SIZE, GRID_SIZE, GREEN);
  DrawRectangle(snake.food.x * GRID_SIZE, snake.food.y * GRID_SIZE, GRID_SIZE,
                GRID_SIZE, RED);
}
