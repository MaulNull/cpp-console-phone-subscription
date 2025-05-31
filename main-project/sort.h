#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phone_subscription.h"



// Прототипы функций

// Функция для вычисления продолжительности в секундах.
int total_seconds(const period* p);

// Функции сравнения.
// Сравнение по убыванию продолжительности разговора (используется поле tm).
int compare_duration_desc(const void* a, const void* b);

// Сравнение по возрастанию номера телефона,
// а при совпадении — по убыванию стоимости разговора (поле pay).
int compare_phone_cost(const void* a, const void* b);

// Функции сортировки:
// Вспомогательная функция для пирамидальной сортировки (Heap sort)
void heapify(phone_subscription* arr[], int n, int i, int (*cmp)(const void*, const void*));

// Пирамидальная сортировка. Принимает массив указателей на phone_subscription,
// размер массива и указатель на функцию сравнения.
void heap_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*));

// Вспомогательная функция для рекурсивной реализации быстрой сортировки (Quick sort)
void quick_sort_helper(phone_subscription* arr[], int left, int right, int (*cmp)(const void*, const void*));

// Быстрая сортировка. Имеет тот же прототип, что и heap_sort.
void quick_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*));

#endif 