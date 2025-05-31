#include <iostream>
#include <iomanip>

using namespace std;

#include "phone_subscription.h"
#include "file_reader.h"
#include "constants.h"
#include "filter.h"
#include "sort.h"
void output(phone_subscription* subscriptions) {
    
    
    

        cout << "�����........: ";

        cout << subscriptions->number << " ";

        cout << '\n';

        cout << "����...........: ";

        cout << setw(2) << setfill('0') << subscriptions->dt.day << ".";

        cout << setw(2) << setfill('0') << subscriptions->dt.month << ".";

        cout << setw(4) << setfill('0') << subscriptions->dt.year << " ";
        cout << "\n";

        cout << "����� ������.....: ";
        cout << setw(2) << setfill('0') << subscriptions->start.hours << ':';

        cout << setw(2) << setfill('0') << subscriptions->start.minutes << ':';

        cout << setw(2) << setfill('0') << subscriptions->start.seconds;
        cout << '\n';

        cout << "�����������������...: ";
        cout << setw(2) << setfill('0') << subscriptions->tm.hours << ':';

        cout << setw(2) << setfill('0') << subscriptions->tm.minutes << ':';

        cout << setw(2) << setfill('0') << subscriptions->tm.seconds << ' ';
        cout << '\n';
        cout << "�����...: ";
        cout << subscriptions->tariff << " ";
        cout << '\n';
        cout << "���������...: ";
        cout << subscriptions->pay << " ";
        cout << '\n';
        cout << '\n';
    
}
int main()
{

    setlocale(LC_ALL, "Russian");
    cout << "������������ ������ �4. GIT\n";
    cout << "������� �9. �������\n";
    cout << "�����: �������� ������\n\n";
    phone_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", subscriptions, size);
        int option = 1;
        int methodChoice = 2;
        int criterionChoice = 2;
        int filterChoice = 2;
        bool (*check_function)(phone_subscription*) = NULL;
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
        while (option != 2) {
            cout << "�������� �����\n"
                << "0 - ����������\n"
                << "1 - ����������\n"
                << "2 - �����\n";
            cin >> option;
            switch (option) {
            case 0:
                cout << "�������� �������� ����������\n"
                    << "0 - ��������� �����\n"
                    << "1 - ������ 2021\n";
                cin >> filterChoice;
                break;
            case 1:
                cout << "�������� ����� ����������\n"
                    << "0 - ���������� �������������\n"
                    << "1 - ���������� �������\n";
                cin >> methodChoice;
                cout << "�������� �������� ����������\n"
                    << "0 - �� �������� ����������������� ���������\n"
                    << "1 - �� ����������� ������ ��������\n";
                cin >> criterionChoice;
                break;
            case 2:

                break;
            default:
                option = 2;

            }
            switch (filterChoice) {
            case 0:
                check_function = check_phone_subscription_by_mobile;
                break;
            case 1:
                check_function = check_phone_subscription_by_date;
                break;
            default:
                check_function = NULL;
            }
            if (check_function)
            {
                int new_size;
                phone_subscription** filtered = filter(subscriptions, size, check_function, new_size);
                for (int i = 0; i < new_size; i++)
                {
                    output(filtered[i]);
                }
                delete[] filtered;
            }
            if ((methodChoice == 0 || methodChoice == 1) && (criterionChoice == 0 || criterionChoice == 1)) {
                
                // ���������� ���������� �� ��������� ������������� ���������: ������� ���������� �����, ����� ������� ���������.
                
                sort_functions[methodChoice](subscriptions, size, compare_functions[criterionChoice]);

                for (int i = 0; i < size; i++) {

                    output(subscriptions[i]);
                }
                
                

            }
            for (int i = 0; i < size; i++)
            {
                delete subscriptions[i];
            }
        }
    }
        catch (const char* error)
        {
            cout << error << '\n';
        }


        return 0;
    }