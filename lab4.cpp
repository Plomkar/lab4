#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// данные об избирателях
struct kGroup {
    int count;
    vector<string> preferences;
};

// Метод Борда
void mBorda(int n, const vector<kGroup>& groups, const vector<string>& allCandid) {
    map<string, int> scores;

    // Иницилизация баллов
    for (const auto& name : allCandid) {
        scores[name] = 0;
    }

    // Подсчет баллов Борда
    for (const auto& group : groups) {
        for (int i = 0; i < n; ++i) {
            int points = n - 1 - i;
            scores[group.preferences[i]] += points * group.count;
        }
    }

    string winner;
    int maxPoints = -1;

    cout << "Результаты метода Борда" << endl;
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << " очков" << endl;
        if (score > maxPoints) {
            maxPoints = score;
            winner = name;
        }
    }
    cout << "Победитель по Борда: " << winner << endl;
}

// Метод Кондорсе
void mCondorcet(const vector<string>& candidates, const vector<kGroup>& groups) {
    string winner = "не определен (парадокс Кондорсе)";

    for (const auto& candA : candidates) {
        bool isWin = true;

        for (const auto& candB : candidates) {
            if (candA == candB) continue;

            int votesA = 0;
            int votesB = 0;

            for (const auto& group : groups) {
                int posA = -1, posB = -1;

                // поиск позиций
                int index = 0;
                for (const auto& pref : group.preferences) {
                    if (pref == candA) posA = index;
                    if (pref == candB) posB = index;
                    ++index;
                }

                if (posA < posB) votesA += group.count;
                else votesB += group.count;
            }

            if (votesA <= votesB) {
                isWin = false;
                break;
            }
        }

        if (isWin) {
            winner = candA;
            break;
        }
    }

    cout << "Результаты метода Кондорсе" << endl;
    cout << "Победитель по Кондорсе: " << winner  << endl;
}

int main() {
    int n, k;
    cout << "Введите количество кандидатов (n): ";
    cin >> n;

    vector<string> candidates(n);
    cout << "Введите имена кандидатов через пробел: ";
    for (auto& name : candidates) {
        cin >> name;
    }

    cout << "Введите количество групп избирателей (k): ";
    cin >> k;

    vector<kGroup> groups(k);
    for (int i = 0; i < k; ++i) {
        cout << "Группа " << i + 1 << ". Количество избирателей: ";
        cin >> groups[i].count;
        
        cout << "Ранжирование (через пробел): ";
        groups[i].preferences.resize(n);
        for (auto& pref : groups[i].preferences) {
            cin >> pref;
        }
    }

    mBorda(n, groups, candidates);
    mCondorcet(candidates, groups);

    return 0;
}