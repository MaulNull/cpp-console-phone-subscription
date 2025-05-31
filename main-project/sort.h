#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phone_subscription.h"



// ��������� �������

// ������� ��� ���������� ����������������� � ��������.
int total_seconds(const period* p);

// ������� ���������.
// ��������� �� �������� ����������������� ��������� (������������ ���� tm).
int compare_duration_desc(const void* a, const void* b);

// ��������� �� ����������� ������ ��������,
// � ��� ���������� � �� �������� ��������� ��������� (���� pay).
int compare_phone_cost(const void* a, const void* b);

// ������� ����������:
// ��������������� ������� ��� ������������� ���������� (Heap sort)
void heapify(phone_subscription* arr[], int n, int i, int (*cmp)(const void*, const void*));

// ������������� ����������. ��������� ������ ���������� �� phone_subscription,
// ������ ������� � ��������� �� ������� ���������.
void heap_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*));

// ��������������� ������� ��� ����������� ���������� ������� ���������� (Quick sort)
void quick_sort_helper(phone_subscription* arr[], int left, int right, int (*cmp)(const void*, const void*));

// ������� ����������. ����� ��� �� ��������, ��� � heap_sort.
void quick_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*));

#endif 