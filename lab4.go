package main

import (
	"fmt"
	"math"
	"strings"
)

// Структура для хранения шага итерации
type IterationStep struct {
	N    int
	A    float64
	B    float64
	X    float64
	Diff float64
}

// новое уравнение 2x^2 + cos(x) = 6 -> 2x^2 + cos(x) - 6 = 0
func f(x float64) float64 {
	return 2*x*x + math.Cos(x) - 6
}

// производная нового уравнения
func df(x float64) float64 {
	return 4*x - math.Sin(x)
}

// phi(x) для нового уравнения (взята положительная ветка sqrt)
func phi(x float64) float64 {
	return math.Sqrt((6 - math.Cos(x)) / 2)
}

// Метод половинного деления
func solveBisection(a, b, eps float64) []IterationStep {
	history := []IterationStep{}
	currA, currB := a, b
	k := 0

	for math.Abs(currB-currA) > eps {
		mid := (currA + currB) / 2.0
		k++
		history = append(history, IterationStep{
			N:    k,
			A:    currA,
			B:    currB,
			X:    mid,
			Diff: math.Abs(currB - currA),
		})
		if f(currA)*f(mid) < 0 {
			currB = mid
		} else {
			currA = mid
		}
	}
	return history
}

// Метод Ньютона
func solveNewton(x0, eps float64) []IterationStep {
	history := []IterationStep{}
	xPrev := x0
	k := 0

	for {
		xNext := xPrev - f(xPrev)/df(xPrev)
		diff := math.Abs(xNext - xPrev)
		k++
		history = append(history, IterationStep{
			N:    k,
			A:    xPrev,
			B:    xNext,
			X:    xNext,
			Diff: diff,
		})
		if diff < eps {
			break
		}
		xPrev = xNext
	}
	return history
}

// Метод простых итераций
func solveFixedPoint(x0, eps float64) []IterationStep {
	history := []IterationStep{}
	xPrev := x0
	k := 0

	for {
		xNext := phi(xPrev)
		diff := math.Abs(xNext - xPrev)
		k++
		history = append(history, IterationStep{
			N:    k,
			A:    xPrev,
			B:    xNext,
			X:    xNext,
			Diff: diff,
		})
		if diff < eps {
			break
		}
		xPrev = xNext
	}
	return history
}

func printBorder(width int) {
	fmt.Print("+" + strings.Repeat("-", width-1) + "+\n")
}

func printTable(title string, history []IterationStep) {
	const tableWidth = 55
	fmt.Printf("\n=== %s ===\n", title)
	printBorder(tableWidth)
	fmt.Printf("| %-6s %-16s %-16s %-16s |\n", "N", "a_n (x_n)", "b_n (x_n+1)", "diff")
	fmt.Print("| " + strings.Repeat("-", tableWidth-3) + " |\n")

	for _, step := range history {
		fmt.Printf("| %-6d %-16.6f %-16.6f %-16.6f |\n",
			step.N, step.A, step.B, step.Diff)
	}
	printBorder(tableWidth)
}

func main() {
	a := 1.7
	b := 1.8
	x0 := 1.6
	eps := 1e-4

	printTable("Метод половинного деления", solveBisection(a, b, eps))
	printTable("Метод Ньютона", solveNewton(x0, eps))
	printTable("Метод простых итераций", solveFixedPoint(x0, eps))
}
