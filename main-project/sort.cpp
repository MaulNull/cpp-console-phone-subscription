#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
// ������� ��� ���������� ����������������� � ��������
int total_seconds(const period* p) {
    return p->hours * 3600 + p->minutes * 60 + p->seconds;
}

/*
 * ������� ��������� ��� ���������� �� �������� ����������������� ���������.
 * ���� ������ ������� ����� ������� ����������������� (� ��������), �� �� ��������� "������"
 * ��� ���������� ������� - �� �������� � ��������.
 */
int compare_duration_desc(const void* a, const void* b) {
    const phone_subscription* sub1 = (const phone_subscription*)a;
    const phone_subscription* sub2 = (const phone_subscription*)b;
    int dur1 = total_seconds(&sub1->tm);
    int dur2 = total_seconds(&sub2->tm);
    // ���������� �� ��������: ���� sub1 �������, ������� ���������� ������������� ��������
    return dur2 - dur1;
}

/*
 * ������� ��������� ��� ����������:
 *  - �� ����������� ������ �������� (���� number);
 *  - ��� ���������� ������ � �� �������� ��������� ��������� (���� pay).
 */
int compare_phone_cost(const void* a, const void* b) {
    const phone_subscription* sub1 = (const phone_subscription*)a;
    const phone_subscription* sub2 = (const phone_subscription*)b;

    int cmp = strcmp(sub1->number, sub2->number);
    if (cmp != 0)
        return cmp;

    // ���� ������ ����� � ��������� �� �������� ���������.
    if (sub1->pay < sub2->pay)
        return 1;
    else if (sub1->pay > sub2->pay)
        return -1;
    else
        return 0;
}

/* ============================
   ���������� ������� ����������
   ============================
*/

/*
 * ��������������� ������� ��� ������������� ����������:
 * �������� ��������� � ������ � i � ��������� ����.
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
 * ������������� ���������� (Heap sort).
 * ��������� ������ ���������� �� phone_subscription, ������ ������� � ������� ���������.
 */
void heap_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*)) {
    // ���������� ����
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, cmp);
    }
    // ���������� ��������� �� ���� � ������������� ����
    for (int i = n - 1; i > 0; i--) {
        phone_subscription* temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0, cmp);
    }
}

/*
 * ��������������� ������� ��� ������� ���������� (Quick sort).
 * ��������� ����������� ��������� �������.
 */
void quick_sort_helper(phone_subscription* arr[], int left, int right, int (*cmp)(const void*, const void*)) {
    if (left < right) {
        // �������� ��������� ������� � �������� �������� (pivot)
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
        // �������� ������� ������� �� ��� ������������� �����
        phone_subscription* temp = arr[i + 1];
        arr[i + 1] = arr[right];
        arr[right] = temp;
        int p = i + 1;
        quick_sort_helper(arr, left, p - 1, cmp);
        quick_sort_helper(arr, p + 1, right, cmp);
    }
}

/*
 * ������� ���������� (Quick sort).
 * ����� ��� �� ��������, ��� � heap_sort.
 */
void quick_sort(phone_subscription* arr[], int n, int (*cmp)(const void*, const void*)) {
    quick_sort_helper(arr, 0, n - 1, cmp);
}

/* ============================
   �������� �������
   ============================
*/
/*int main(void) {
    const int COUNT = 5;

    // ������ ���������� �������
    phone_subscription sub1 = { "123456", {1, 1, 2022}, {10, 0, 0}, {0, 10, 0}, "TariffA", 10.50 };
    phone_subscription sub2 = { "654321", {2, 2, 2022}, {11, 0, 0}, {0, 20, 0}, "TariffB", 15.00 };
    phone_subscription sub3 = { "123456", {3, 3, 2022}, {12, 0, 0}, {0, 5, 0},  "TariffA", 8.80 };
    phone_subscription sub4 = { "345678", {4, 4, 2022}, {9, 0, 0},  {0, 30, 0}, "TariffC", 20.00 };
    phone_subscription sub5 = { "654321", {5, 5, 2022}, {8, 0, 0},  {0, 25, 0}, "TariffB", 12.75 };

    // ������ ���������� �� ���������� ��������
    phone_subscription* records[COUNT] = { &sub1, &sub2, &sub3, &sub4, &sub5 };

    // ����� ��������� �������
    printf("�������� ������ �������:\n");
    for (int i = 0; i < COUNT; i++) {
        phone_subscription* ps = records[i];
        printf("�����: %s, ����: %02d.%02d.%04d, ����� ������: %02d:%02d:%02d, �����������������: %02d:%02d:%02d, �����: %s, ������: %.2f\n",
            ps->number,
            ps->dt.day, ps->dt.month, ps->dt.year,
            ps->start.hours, ps->start.minutes, ps->start.seconds,
            ps->tm.hours, ps->tm.minutes, ps->tm.seconds,
            ps->tariff,
            ps->pay);
    }

    // ���� ������
    int method_choice, criteria_choice;
    printf("\n�������� ����� ����������:\n");
    printf("1. ������������� ���������� (Heap sort)\n");
    printf("2. ������� ���������� (Quick sort)\n");
    scanf("%d", &method_choice);

    printf("\n�������� �������� ����������:\n");
    printf("1. �� �������� ����������������� ���������\n");
    printf("2. �� ����������� ������ ��������, � ��� ���������� ������ �� �������� ��������� ���������\n");
    scanf("%d", &criteria_choice);

    // ������ ���������� �� ������� ����������
    void (*sort_functions[])(phone_subscription * [], int, int (*)(const void*, const void*)) = {
        heap_sort,
        quick_sort
    };

    // ������ ���������� �� ������� ���������
    int (*compare_functions[])(const void*, const void*) = {
        compare_duration_desc,
        compare_phone_cost
    };

    // ���������� ���������� �� ��������� ������������� ���������: ������� ���������� �����, ����� ������� ���������.
    sort_functions[method_choice - 1](records, COUNT, compare_functions[criteria_choice - 1]);

    // ����� ���������������� �������
    printf("\n��������������� ������ �������:\n");
    for (int i = 0; i < COUNT; i++) {
        phone_subscription* ps = records[i];
        printf("�����: %s, ����: %02d.%02d.%04d, ����� ������: %02d:%02d:%02d, �����������������: %02d:%02d:%02d, �����: %s, ������: %.2f\n",
            ps->number,
            ps->dt.day, ps->dt.month, ps->dt.year,
            ps->start.hours, ps->start.minutes, ps->start.seconds,
            ps->tm.hours, ps->tm.minutes, ps->tm.seconds,
            ps->tariff,
            ps->pay);
    }

    return 0;
}*/





