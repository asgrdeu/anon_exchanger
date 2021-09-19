#include <iostream>

using namespace std;

int interface() {

    int menu = 0;

    cout << "Выберете один из вариантов "<< endl<< endl;
    cout << "[1] Экспортировать файл " << endl;
    cout << "[2] Импортировать файл " << endl;
    cout << "[3] Выход "

    cin >> menu;

    switch (menu) {
        case 1:
        cout << "[1] Выбрать файл для экспорта " << endl;
        cout << "[2] Экспортировать " << endl;
        cout << "[3] Вернуться в главное меню ";
            break;

        case 2:
            cout << "[1] Выбрать файл для импорта " << endl;
            cout << "[2] Импортировать " << endl;
            cout << "[3] Вернуться в главное меню ";
            break;

        case 3:
            cout << "[1] Экспортировать файл " << endl;
            cout << "[2] Импортировать файл " << endl;
            cout << "[3] Выход ";
            break;

    }

    return 0;
}
