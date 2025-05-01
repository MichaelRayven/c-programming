#include <stdio.h>
#include <stdlib.h>

#include "ui/ui.h"

#define SIZE 4
static int field[SIZE][SIZE];
static uiButton *buttons[SIZE][SIZE];
static uiWindow *window;

void swapTile(int r1, int c1, int r2, int c2) {
    int tempValue = field[r1][c1];
    char *tempLabel = uiButtonText(buttons[r1][c1]);

    field[r1][c1] = field[r2][c2];
    field[r2][c2] = tempValue;

    uiButtonSetText(buttons[r1][c1], uiButtonText(buttons[r2][c2]));
    uiButtonSetText(buttons[r2][c2], tempLabel);
}

// r2, c2 - координаты свободной клетки
int isValidMove(int r1, int c1, int r2, int c2) {
    return r1 == r2 || c1 == c2;    
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
    int direction[2] = {
      row - emptyRow < 0 ? 1 : -1,
      col - emptyCol < 0 ? 1 : -1 
    };

    
  }
  printf("%d \n", number);
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