#include <stdio.h>
#include <stdlib.h>

#include "ui/ui.h"

#define SIZE 4
static int field[SIZE][SIZE];
static uiButton *buttons[SIZE][SIZE];
static uiWindow *window;

void swapTile(int r1, int c1, int r2, int c2) {
    int tempValue = field[c1][r1];
    char *tempLabel = uiButtonText(buttons[c1][r1]);

    field[c1][r1] = field[c2][r2];
    field[c2][r2] = tempValue;

    uiButtonSetText(buttons[c1][r1], uiButtonText(buttons[c2][r2]));
    uiButtonSetText(buttons[c2][r2], tempLabel);
}

// r2, c2 - координаты свободной клетки
int isValidMove(int r1, int c1, int r2, int c2) {
    return r1 == r2 || c1 == c2;    
}

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

// Обработчик кнопки
void clickHandler(uiButton *b, void *data) {
  int number = *((int *) data), col = 0, row = 0, emptyRow = 0, emptyCol = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
        if (field[i][j] == number) {
            col = i;
            row = j;
        }
        if (field[i][j] == 0) {
            emptyCol = i;
            emptyRow = j;
        }
    }
  }

  if (isValidMove(col, row, emptyCol, emptyRow)) {
    printf("%d \n", number);

    if (col == emptyCol) {
      int direction = row - emptyRow < 0 ? -1 : 1;
      for (int i = emptyRow; i != row; i += direction) {
        swapTile(i, col, i + direction, col);
      }
    }

    if (row == emptyRow) {
      int direction = col - emptyCol < 0 ? -1 : 1;
      for (int i = emptyCol; i != col; i += direction) {
        swapTile(row, i, row, i + direction);
      }
    }
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

  // Запуск
  uiControlShow(uiControl(window));
  uiMain();
  uiUninit();
  return 0;
}