#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ui/ui.h"

#define SIZE 4
#define SHUFFLE_COUNT 100

static int field[SIZE][SIZE];
static uiButton *buttons[SIZE][SIZE];
static uiButton *shuffleBtn;
static uiWindow *window;
static uiEntry *movesLabel;

int emptyCol = SIZE - 1;
int emptyRow = SIZE - 1;
int movesCounter = 0;
int playing = 0;

void swapTile(int c1, int r1, int c2, int r2) {
  int tempValue = field[c1][r1];
  char *tempLabel = uiButtonText(buttons[c1][r1]);

  field[c1][r1] = field[c2][r2];
  field[c2][r2] = tempValue;

  uiButtonSetText(buttons[c1][r1], uiButtonText(buttons[c2][r2]));
  uiButtonSetText(buttons[c2][r2], tempLabel);
}

int isValidMove(int c1, int r1) { return r1 == emptyRow || c1 == emptyCol; }

int isSolved() {
  int count = 1;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Проверка что правая нижная клетка - пустая
      if (i == SIZE - 1 && j == SIZE - 1) {
        return field[i][j] == 0;
      }

      if (field[i][j] != count++) {
        return 0;
      }
    }
  }
  return 1;
}

void shuffleField() {
  srand(time(NULL));

  for (int n = 0; n < SHUFFLE_COUNT; n++) {
    // Случайное значение от 1 до n - 1,
    // где n - размер поля
    int shift = rand() % (SIZE - 1) + 1;
    if (rand() % 2) {
      // Горизонтальное смещение
      int row = (emptyRow + shift) % SIZE;
      int direction = row - emptyRow < 0 ? -1 : 1;
      for (int i = emptyRow; i != row; i += direction) {
        swapTile(emptyCol, i, emptyCol, i + direction);
      }
      emptyRow = row;
    } else {
      // Вертикальное смещение
      int col = (emptyCol + shift) % SIZE;
      int direction = col - emptyCol < 0 ? -1 : 1;
      for (int i = emptyCol; i != col; i += direction) {
        swapTile(i, emptyRow, i + direction, emptyRow);
      }
      emptyCol = col;
    }
  }
}

void increaseMovesCounter() {
  movesCounter++;
  char label[64];
  snprintf(label, sizeof(label), "Количество шагов: %d", movesCounter);
  uiEntrySetText(movesLabel, label);
}

void resetMovesCounter() {
  movesCounter = 0;
  char label[64];
  snprintf(label, sizeof(label), "Количество шагов: %d", movesCounter);
  uiEntrySetText(movesLabel, label);
}

// Обработчик кнопки
void shuffleBtnHandler(uiButton *b, void *data) {
  uiControlDisable(uiControl(shuffleBtn));
  uiControlHide(uiControl(shuffleBtn));

  uiControlShow(uiControl(movesLabel));
  resetMovesCounter();

  shuffleField();
  playing = 1;
}

void clickHandler(uiButton *b, void *data) {
  if (!playing) {
    uiMsgBox(
        window, "Как играть",
        "Нажимайте на клетки, чтобы \nпередвинуть их в пустое пространство. "
        "\n\nНажмите кнопку \"Перемешать\", \nчтобы начать игру.");
    return;
  }

  int number = *((int *)data), col = 0, row = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (field[i][j] == number) {
        col = i;
        row = j;
      }
    }
  }

  if (isValidMove(col, row)) {
    // Обновить счетчик шагов
    increaseMovesCounter();

    if (col == emptyCol) {
      int direction = row - emptyRow < 0 ? -1 : 1;
      for (int i = emptyRow; i != row; i += direction) {
        swapTile(emptyCol, i, emptyCol, i + direction);
      }
      emptyRow = row;
    }

    if (row == emptyRow) {
      int direction = col - emptyCol < 0 ? -1 : 1;
      for (int i = emptyCol; i != col; i += direction) {
        swapTile(i, emptyRow, i + direction, emptyRow);
      }
      emptyCol = col;
    }
  }

  if (isSolved()) {
    uiControlEnable(uiControl(shuffleBtn));
    uiControlShow(uiControl(shuffleBtn));

    uiControlHide(uiControl(movesLabel));

    char label[100];
    snprintf(label, sizeof(label),
             "Вы собрали Пятнашки!\n"
             "Вам потребовалось %d шагов.",
             movesCounter);
    uiMsgBox(window, "Поздравляем!", label);

    playing = 0;
  }
}

// Обработчик закрытия окна
int onClosing(uiWindow *w, void *data) {
  uiQuit();
  return 1;
}

void initField() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      field[i][j] = i * SIZE + j + 1;
    }
  }
  field[SIZE - 1][SIZE - 1] = 0;
}

int main() {
  uiInitOptions opts = {0};
  uiInit(&opts);

  // Создаем окно
  window = uiNewWindow("Пятнашки", 300, 300, 0);
  uiWindowSetMargined(window, 1);
  uiWindowOnClosing(window, onClosing, NULL);

  // Компоновка интерфейса
  uiBox *vbox = uiNewVerticalBox();
  uiBoxSetPadded(vbox, 1);
  uiWindowSetChild(window, uiControl(vbox));

  initField();

  char label[4];
  for (int i = 0; i < SIZE; i++) {
    // Создаем строки поля
    uiBox *hbox = uiNewHorizontalBox();
    uiBoxSetPadded(hbox, 1);
    uiBoxAppend(vbox, uiControl(hbox), 1);

    for (int j = 0; j < SIZE; j++) {
      // Создаем кнопку
      buttons[i][j] = uiNewButton("");
      if (field[i][j] != 0) {
        snprintf(label, sizeof(label), "%d", field[i][j]);
        uiButtonSetText(buttons[i][j], label);
      }

      // Добавляем кнопку в интерфейс
      uiBoxAppend(hbox, uiControl(buttons[i][j]), 1);

      // Добавляем обработчик нажатия
      uiButtonOnClicked(buttons[i][j], clickHandler, &field[i][j]);
    }
  }

  shuffleBtn = uiNewButton("Перемешать");
  uiButtonOnClicked(shuffleBtn, shuffleBtnHandler, NULL);
  uiBoxAppend(vbox, uiControl(shuffleBtn), 1);

  movesLabel = uiNewEntry();
  uiEntrySetReadOnly(movesLabel, 1);
  uiControlHide(uiControl(movesLabel));
  uiBoxAppend(vbox, uiControl(movesLabel), 1);

  // Запуск
  uiControlShow(uiControl(window));
  uiMain();
  uiUninit();
  return 0;
}

// TODO:
// - Saves
// - Better visuals