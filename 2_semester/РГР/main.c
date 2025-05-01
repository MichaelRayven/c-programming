#include <stdio.h>
#include <stdlib.h>

#include "ui/ui.h"

// Элементы GUI
uiEntry *entry1, *entry2;
uiLabel *resultLabel;

// Обработчик кнопки
void onSuper(uiButton *b, void *data)
{
    const char *text1 = uiEntryText(entry1);
    const char *text2 = uiEntryText(entry2);
    char *endptr;
    long num1, num2;

    // Парсим первое число
    num1 = strtol(text1, &endptr, 10);

    // Парсим второе число
    num2 = strtol(text2, &endptr, 10);

    // Вычисляем и выводим результат
    long sum = num1 + num2;
    char result[50];
    snprintf(result, sizeof(result), "Сумма: %ld", sum);
    uiLabelSetText(resultLabel, result);
}

// Обработчик закрытия окна
int onClosing(uiWindow *w, void *data)
{
    uiQuit();
    return 1;
}

int main()
{
    uiInitOptions opts = {0};
    uiInit(&opts);

    // Создаем окно
    uiWindow *win = uiNewWindow("Сумматор целых чисел", 300, 200, 0);
    uiWindowOnClosing(win, onClosing, NULL);

    // Создаем элементы
    entry1 = uiNewEntry();
    entry2 = uiNewEntry();
    uiButton *calcBtn = uiNewButton("Сложить");
    resultLabel = uiNewLabel("Введите два целых числа");

    // Устанавливаем начальные значения
    uiEntrySetText(entry1, "10");
    uiEntrySetText(entry2, "20");

    // Компоновка
    uiBox *vbox = uiNewVerticalBox();
    uiBoxSetPadded(vbox, 1);
    uiBoxAppend(vbox, uiControl(entry1), 0);
    uiBoxAppend(vbox, uiControl(entry2), 0);
    uiBoxAppend(vbox, uiControl(calcBtn), 0);
    uiBoxAppend(vbox, uiControl(resultLabel), 0);
    uiWindowSetChild(win, uiControl(vbox));

    // Подключаем обработчики
    uiButtonOnClicked(calcBtn, onSuper, NULL);

    // Запуск
    uiControlShow(uiControl(win));
    uiMain();
    uiUninit();
    return 0;
}