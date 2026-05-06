#include <iostream>
#include <vector>

using namespace std;
int main() {
    int a, b, n, m;
    char op;

    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;
    cout << "Введите n: ";
    cin >> n;
    cout << "Введите модуль m: ";
    cin >> m;
    cout << "Введите операцию (+, -, *, ^): ";
    cin >> op;

    // n = max(a, b) определяет количество начальных значений
    int maxLag = (a > b) ? a : b;

    if (n < maxLag) {
        cout << "Ошибка: N должно быть не меньше " << maxLag << endl;
        return 1;
    }

    vector<int> s;
    s.reserve(n);

    cout << "Введите " << maxLag << " начальных целых числа: " << endl;
    for (int i = 0; i < maxLag; ++i) {
        int temp;
        cout << "S[" << i << "]: ";
        cin >> temp;
        s.push_back(temp);
    }

    // Генерация по формуле Sn = (Sn-a op Sn-b) mod m
    for (int i = s.size(); i < n; ++i) {
        int valA = s[i - a];
        int valB = s[i - b];
        int res = 0;

        if (op == '+') {
            res = valA + valB;
        } else if (op == '-') {
            res = valA - valB;
        } else if (op == '*') {
            res = valA * valB;
        } else if (op == '^') {
            res = valA ^ valB;
        } else {
            cout << "Ошибка: операция не поддерживается!" << endl;
            return 1;
        }

        // взятие модуля
        int nextVal = res % m;
        if (nextVal < 0) nextVal += m;

        s.push_back(nextVal);
    }

    cout << "Результат генерации: " << endl;
    for (const auto& value : s) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}