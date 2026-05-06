#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Структура для хранения шага итерации
struct iterationStep {
    int n;
    double a;
    double b;
    double x;
    double diff;
};

// новое уравнение 2x^2 + cos(x) = 6 -> 2x^2 + cos(x) - 6 = 0
double f(double x) {
    return 2 * x * x + cos(x) - 6;
}

// производная нового уравнения
double df(double x) {
    return 4 * x - sin(x);
}

// phi(x) для нового уравнения (взята положительная ветка sqrt)
double phi(double x) {
    return sqrt((6 - cos(x)) / 2);
}

// Метод половинного деления
vector<iterationStep> solveBisection(double a, double b, double eps) {
    vector<iterationStep> history;
    double currA = a, currB = b;
    int k = 0;
    while (abs(currB - currA) > eps) {
        double mid = (currA + currB) / 2.0;
        history.push_back({++k, currA, currB, mid, abs(currB - currA)});
        if (f(currA) * f(mid) < 0) currB = mid;
        else currA = mid;
    }
    return history;
}

// Метод Ньютона
vector<iterationStep> solveNewton(double x0, double eps) {
    vector<iterationStep> history;
    double xPrev = x0;
    double xNext;
    int k = 0;
    do {
        xNext = xPrev - f(xPrev) / df(xPrev);
        double diff = abs(xNext - xPrev);
        history.push_back({++k, xPrev, xNext, xNext, diff});
        if (diff < eps) break;
        xPrev = xNext;
    } while (true);
    return history;
}

// Метод простых итераций
vector<iterationStep> solveFixedPoint(double x0, double eps) {
    vector<iterationStep> history;
    double xPrev = x0;
    double xNext;
    int k = 0;
    do {
        xNext = phi(xPrev);
        double diff = abs(xNext - xPrev);
        history.push_back({++k, xPrev, xNext, xNext, diff});
        if (diff < eps) break;
        xPrev = xNext;
    } while (true);
    return history;
}

void printBorder(int width) {
    cout << "+" << setfill('-') << setw(width) << "" << "+" << setfill(' ') << endl;
}

void printTable(const string& title, const vector<iterationStep>& history) {
    const int tableWidth = 55;
    cout << "\n=== " << title << " ===\n";
    printBorder(tableWidth);
    cout << "| " << left << setw(6) << "N" 
         << setw(16) << "a_n (x_n)" 
         << setw(16) << "b_n (x_n+1)" 
         << setw(16) << "diff" << "|" << endl;
    cout << "| " << setfill('-') << setw(tableWidth - 2) << "" << setfill(' ') << " |" << endl;

    cout << fixed << setprecision(6);
    for (const auto& step : history) {
        cout << "| " << left << setw(6) << step.n 
             << setw(16) << step.a 
             << setw(16) << step.b 
             << setw(16) << step.diff << "|" << endl;
    }
    printBorder(tableWidth);
}

// начальные параметры под новое уравнение
int main() {
    double a = 1.7, b = 1.8;
    double x0 = 1.6;            // начальное приближение (было 0.5)
    double eps = 1e-4;

    printTable("Метод половинного деления", solveBisection(a, b, eps));
    printTable("Метод Ньютона", solveNewton(x0, eps));
    printTable("Метод простых итераций", solveFixedPoint(x0, eps));

    return 0;
}