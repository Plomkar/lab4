#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

int main() {
    // Настройка генератора (ranlux24_base)
    ranlux24_base gen(random_device{}());
    uniform_int_distribution<> dist(150, 300);

    // 1. Иницилизация массива
    int n;
    cout << "1 задание" << endl;
    cout << "Введите размер для первого массива (n >= 10): ";
    cin >> n;
    if (n < 10) {
        cout << "Размер слишком мал. Выберем n = 10" << endl;
        n = 10;
    }

    vector<int> arr(n);
    for (int& x : arr) {
        x = dist(gen);
    }

    cout << "Иницилизированный массив: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << endl;

    // 2. Самая длинная убывающая последовательность
    vector<int> longestSub;
    vector<int> currentSub;

    if (!arr.empty()) {
        currentSub.push_back(arr[0]);
        for (size_t i = 1; i < arr.size(); ++i) {
            if (arr[i] < arr[i - 1]) {
                currentSub.push_back(arr[i]);
            } else {
            if (currentSub.size() > longestSub.size()) {
                longestSub = currentSub;
            }
            currentSub.clear();
            currentSub.push_back(arr[i]);
            }
        }
        if (currentSub.size() > longestSub.size()) {
            longestSub = currentSub;
        }
    }

    cout << "2 задание" << endl;
    cout << "Самая длинная убывающая последовательность (размер: "<< longestSub.size() << "): ";
    for (int x : longestSub) cout << x << " ";
    cout << endl;
    cout << endl;

    // 3. Среднее арифметическое
    double sum = 0;
    for (int x : arr) {
        sum += x;
    }
    double average = (arr.empty()) ? 0 : sum / arr.size();

    vector<int> lessAvg;
    for (int x : arr) {
        if (x < average) {
            lessAvg.push_back(x);
        }
    }

    cout << "3 задание" << endl;
    cout << "Среднее арифметическое значение: " << average << endl;
    cout << "Массив, содержащий числа, меньшие average (размер: " << lessAvg.size() << "): ";
    for (int x : lessAvg) cout << x << " ";
    cout << endl;
    cout << endl;

    // 4. Сдвиг влево на две позиции
    if (arr.size() >= 2) {
        // сохранение первых двух элементов
        int first = arr[0];
        int second = arr[1];

        // сдвиг всех элементов влево на два. копируем в i = 0 элемент из i + 2
        for (size_t i = 0; i < arr.size() - 2; ++i) {
            arr[i] = arr[i+2];
        }

        // сохраненные элементы в конец
        arr[arr.size() - 2] = first;
        arr[arr.size() - 1] = second;
    }

    cout << "4 задание" << endl;
    cout << "После сдвига влево на 2 позиции: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    cout << endl;

    // 5. Массив, отсортированный по убыванию + число, встречающееся наибольшее количетсво раз
    int n2;
    cout << "5 задание" << endl;
    cout << "Введите размер для второго массива (n >= 20): ";
    cin >> n2;

    if (n2 < 20) {
        cout << "Размер слишком мал. Выберем n = 20" << endl;
        n2 = 20;
    }

    vector<int> arr2(n2);
    uniform_int_distribution<> dist2(100, 120);

    // заполнение массива
    for (int& x : arr2) {
        x = dist2(gen);
    }

    // сортировка по убыванию
    sort(arr2.begin(), arr2.end(), greater<int>());

    cout << "Отсортированный по убыванию массив: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // наиболее встречающееся число
    int maxCount = 0;
    int mostFreq = arr2[0];
    int currCount = 0;

    for (size_t i = 0; i < arr2.size(); ++i) {
        ++currCount;

        // если последний элемент или следующий отличается от текущего
        if (i == arr2.size() - 1 || arr2[i] != arr2[i + 1]) {
            if (currCount > maxCount) {
                maxCount = currCount;
                mostFreq = arr2[i];
            }
            currCount = 0;
        }
    }
    
    cout << "Число, встречающееся наибольшее количество раз (" << maxCount << " раз): " << mostFreq << endl;
    
    return 0;
}