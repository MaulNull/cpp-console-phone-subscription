#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
// Функция для вычисления продолжительности в секундах
int total_seconds(const period* p) {
    return p->hours * 3600 + p->minutes * 60 + p->seconds;
}

/*
 * Функция сравнения для сортировки по убыванию продолжительности разговора.
 * Если первый элемент имеет большую продолжительность (в секундах), то он считается "меньше"
 * для достижения порядка - от большего к меньшему.
 */
int compare_duration_desc(const void* a, const void* b) {
    const phone_subscription* sub1 = (const phone_subscription*)a;
    const phone_subscription* sub2 = (const phone_subscription*)b;
    int dur1 = total_seconds(&sub1->tm);
    int dur2 = total_seconds(&sub2->tm);
    // Сортировка по убыванию: если sub1 длиннее, функция возвращает отрицательное значение
    return dur2 - dur1;
}

/*
 * Функция сравнения для сортировки:
 *  - По возрастанию номера телефона (поле number);
 *  - При совпадении номера — по убыванию стоимости разговора (поле pay).
 */
int compare_phone_cost(const void* a, const void* b) {
    const phone_subscription* sub1 = (const phone_subscription*)a;
    const phone_subscription* sub2 = (const phone_subscription*)b;

    int cmp = strcmp(sub1->number, sub2->number);
    if (cmp != 0)
        return cmp;

    // Если номера равны — сортируем по убыванию стоимости.
    if (sub1->pay < sub2->pay)
        return 1;
    else if (sub1->pay > sub2->pay)
        return -1;
    else
        return 0;
}

/* ============================
   Реализация методов сортировки
   ============================
*/

/*
 * Вспомогательная функция для пирамидальной сортировки:
 * приводит поддерево с корнем в i к свойствам кучи.
 */
void heapify(phone_subscription* arr[], int n, int i, int (*cmp)(const void*, const void*)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && cmp(arr[left], arr[largest]) > 0)
        largest = left;
    if (right < n && cmp(arr[right], arr[largest]) > 0)
        largest = right;
    if (largest != i) {
        phone_subscription* temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, cmp);
    }
}

/*
 * Пирамидальная сортировка (Heap sort).
 * Принимает массив указателей на phone_subscription, размер массива и функцию сравнения.
 */
void heap_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*)) {
    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, cmp);
    }
    // Извлечение элементов из кучи и корректировка кучи
    for (int i = n - 1; i > 0; i--) {
        phone_subscription* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, cmp);
    }
}

/*
 * Вспомогательная функция для быстрой сортировки (Quick sort).
 * Реализует рекурсивное разбиение массива.
 */
void quick_sort_helper(phone_subscription* arr[], int left, int right, int (*cmp)(const void*, const void*)) {
    if (left < right) {
        // Выбираем последний элемент в качестве опорного (pivot)
        phone_subscription* pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (cmp(arr[j], pivot) < 0) {
                i++;
                phone_subscription* temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // Помещаем опорный элемент на его окончательное место
        phone_subscription* temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;
        int p = i + 1;
        quick_sort_helper(arr, left, p - 1, cmp);
        quick_sort_helper(arr, p + 1, right, cmp);
    }
}

/*
 * Быстрая сортировка (Quick sort).
 * Имеет тот же прототип, что и heap_sort.
 */
void quick_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*)) {
    quick_sort_helper(arr, 0, n - 1, cmp);
}

/* ============================
   Основная функция
   ============================
*/
/*int main(void) {
    const int COUNT = 5;

    // Пример заполнения записей
    phone_subscription sub1 = { "123456", {1, 1, 2022}, {10, 0, 0}, {0, 10, 0}, "TariffA", 10.50 };
    phone_subscription sub2 = { "654321", {2, 2, 2022}, {11, 0, 0}, {0, 20, 0}, "TariffB", 15.00 };
    phone_subscription sub3 = { "123456", {3, 3, 2022}, {12, 0, 0}, {0, 5, 0},  "TariffA", 8.80 };
    phone_subscription sub4 = { "345678", {4, 4, 2022}, {9, 0, 0},  {0, 30, 0}, "TariffC", 20.00 };
    phone_subscription sub5 = { "654321", {5, 5, 2022}, {8, 0, 0},  {0, 25, 0}, "TariffB", 12.75 };

    // Массив указателей на телефонные подписки
    phone_subscription* records[COUNT] = { &sub1, &sub2, &sub3, &sub4, &sub5 };

    // Вывод исходного массива
    printf("Исходный массив записей:\n");
    for (int i = 0; i < COUNT; i++) {
        phone_subscription* ps = records[i];
        printf("Номер: %s, Дата: %02d.%02d.%04d, Время начала: %02d:%02d:%02d, Продолжительность: %02d:%02d:%02d, Тариф: %s, Оплата: %.2f\n",
            ps->number,
            ps->dt.day, ps->dt.month, ps->dt.year,
            ps->start.hours, ps->start.minutes, ps->start.seconds,
            ps->tm.hours, ps->tm.minutes, ps->tm.seconds,
            ps->tariff,
            ps->pay);
    }

    // Меню выбора
    int method_choice, criteria_choice;
    printf("\nВыберите метод сортировки:\n");
    printf("1. Пирамидальная сортировка (Heap sort)\n");
    printf("2. Быстрая сортировка (Quick sort)\n");
    scanf("%d", &method_choice);

    printf("\nВыберите критерий сортировки:\n");
    printf("1. По убыванию продолжительности разговора\n");
    printf("2. По возрастанию номера телефона, а при совпадении номера по убыванию стоимости разговора\n");
    scanf("%d", &criteria_choice);

    // Массив указателей на функции сортировки
    void (*sort_functions[])(phone_subscription * [], int, int (*)(const void*, const void*)) = {
        heap_sort,
        quick_sort
    };

    // Массив указателей на функции сравнения
    int (*compare_functions[])(const void*, const void*) = {
        compare_duration_desc,
        compare_phone_cost
    };

    // Выполнение сортировки по выбранным пользователем критериям: сначала выбирается метод, потом функция сравнения.
    sort_functions[method_choice - 1](records, COUNT, compare_functions[criteria_choice - 1]);

    // Вывод отсортированного массива
    printf("\nОтсортированный массив записей:\n");
    for (int i = 0; i < COUNT; i++) {
        phone_subscription* ps = records[i];
        printf("Номер: %s, Дата: %02d.%02d.%04d, Время начала: %02d:%02d:%02d, Продолжительность: %02d:%02d:%02d, Тариф: %s, Оплата: %.2f\n",
            ps->number,
            ps->dt.day, ps->dt.month, ps->dt.year,
            ps->start.hours, ps->start.minutes, ps->start.seconds,
            ps->tm.hours, ps->tm.minutes, ps->tm.seconds,
            ps->tariff,
            ps->pay);
    }

    return 0;
}*/





