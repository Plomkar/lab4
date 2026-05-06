package main

import (
	"fmt"
)

// описывает группу избирателей с одинаковыми предпочтениями
type kGroup struct {
	Count       int
	Preferences []string
}

// метод Борда
func mBorda(n int, groups []kGroup, allCandid []string) {
	scores := make(map[string]int)

	// Инициализация баллов
	for _, name := range allCandid {
		scores[name] = 0
	}

	// Подсчет баллов Борда
	for _, group := range groups {
		for i := 0; i < n; i++ {
			points := n - 1 - i
			scores[group.Preferences[i]] += points * group.Count
		}
	}

	winner := ""
	maxPoints := -1

	fmt.Println("Результаты метода Борда")

	for name, score := range scores {
		fmt.Printf("%s: %d очков\n", name, score)
		if score > maxPoints {
			maxPoints = score
			winner = name
		}
	}
	fmt.Printf("Победитель по Борда: %s\n", winner)
}

// mCondorcet реализует метод Кондорсе
func mCondorcet(candidates []string, groups []kGroup) {
	winner := "не определен (парадокс Кондорсе)"

	for _, candA := range candidates {
		isWin := true

		for _, candB := range candidates {
			if candA == candB {
				continue
			}

			votesA := 0
			votesB := 0

			for _, group := range groups {
				posA, posB := -1, -1

				// поиск позиций
				for index, pref := range group.Preferences {
					if pref == candA {
						posA = index
					}
					if pref == candB {
						posB = index
					}
				}

				if posA < posB {
					votesA += group.Count
				} else {
					votesB += group.Count
				}
			}

			if votesA <= votesB {
				isWin = false
				break
			}
		}

		if isWin {
			winner = candA
			break
		}
	}

	fmt.Println("Результаты метода Кондорсе")
	fmt.Printf("Победитель по Кондорсе: %s\n", winner)
}

func main() {
	var n, k int

	fmt.Print("Введите количество кандидатов (n): ")
	fmt.Scan(&n)

	candidates := make([]string, n)
	fmt.Print("Введите имена кандидатов через пробел: ")
	for i := 0; i < n; i++ {
		fmt.Scan(&candidates[i])
	}

	fmt.Print("Введите количество групп избирателей (k): ")
	fmt.Scan(&k)

	groups := make([]kGroup, k)
	for i := 0; i < k; i++ {
		fmt.Printf("Группа %d. Количество избирателей: ", i+1)
		fmt.Scan(&groups[i].Count)

		fmt.Print("Ранжирование (через пробел): ")
		groups[i].Preferences = make([]string, n)
		for j := 0; j < n; j++ {
			fmt.Scan(&groups[i].Preferences[j])
		}
	}

	mBorda(n, groups, candidates)
	mCondorcet(candidates, groups)
}
