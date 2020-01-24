package main

import (
	"fmt"
	"math/rand"
	"time"
)

func printMatrix(cellMatrix [][]bool, sizeMatrix int) {
	for i:=0; i<sizeMatrix; i++ {
		for j:=0; j<sizeMatrix; j++ {
			if (cellMatrix[i][j])	{		
				fmt.Printf("X")
			} else {
				fmt.Printf(".")
			}
		}
		fmt.Println("")
	}
}

/*
func printMatrix2(cellMatrix [][]int, sizeMatrix int) {
	for i:=0; i<sizeMatrix; i++ {
		for j:=0; j<sizeMatrix; j++ {	
				fmt.Printf("%d",cellMatrix[i][j])
		}
		fmt.Println("")
	}
}
*/

func countNeighbors(cellMatrix [][]bool, x int, y int, sizeMatrix int) (int) {
	live_count := 0

	if x - 1 >= 0 && y - 1 >= 0 && x - 1 < sizeMatrix && y - 1 < sizeMatrix && cellMatrix[x - 1][y - 1] == true {
		live_count++
	}
	if x - 1 >= 0 && y >= 0 && x - 1 < sizeMatrix && y < sizeMatrix && cellMatrix[x - 1][y] == true {
		live_count++
	}
	if x - 1 >= 0 && y + 1 >= 0 && x - 1 < sizeMatrix && y + 1 < sizeMatrix && cellMatrix[x - 1][y + 1] == true {
		live_count++
	}
	if x >= 0 && y - 1 >= 0 && 1 < sizeMatrix && y-1 < sizeMatrix && cellMatrix[x][y-1] == true {
		live_count++
	}
	if x >= 0 && y + 1 >= 0 && x < sizeMatrix && y + 1 < sizeMatrix && cellMatrix[x][y + 1] == true {
		live_count++
	}
	if x + 1 >= 0 && y - 1 >= 0 && x + 1 < sizeMatrix && y - 1 < sizeMatrix && cellMatrix[x + 1][y - 1] == true {
		live_count++
	}
	if x + 1 >= 0 && y >= 0 && x + 1 < sizeMatrix && y < sizeMatrix && cellMatrix[x + 1][y] == true {
		live_count++
	}
	if x + 1 >= 0 && y + 1 >= 0 && x + 1 < sizeMatrix && y + 1 < sizeMatrix && cellMatrix[x + 1][y + 1] == true {
		live_count++
	}
	return live_count
}


func nextGeneration (cellMatrix [][]bool, sizeMatrix int) ([][]bool, int) {
	/*tmp matrix*/
	evaluateMatrix := make([][]int, sizeMatrix)
	/*create evaluate matrix */
	for i:=0; i<sizeMatrix; i++ {
		evaluateMatrix[i] = make([]int, sizeMatrix)
		for j:=0; j<sizeMatrix; j++ {		
			evaluateMatrix[i][j] = countNeighbors(cellMatrix, i, j, sizeMatrix)
		}
	}
	changeMatrix := 0
	//printMatrix2(evaluateMatrix, sizeMatrix)
	for i:=0; i<sizeMatrix; i++ {
		for j:=0; j<sizeMatrix; j++ {	
			if evaluateMatrix[i][j] < 2 && cellMatrix[i][j]	== true {
				cellMatrix[i][j] = false
				changeMatrix = 1
			} else if (evaluateMatrix[i][j] == 2 || evaluateMatrix[i][j] == 3) && cellMatrix[i][j] ==true {
				cellMatrix[i][j] = true
			} else if evaluateMatrix[i][j] >= 3 && cellMatrix[i][j] == true {
				cellMatrix[i][j] = false
				changeMatrix = 1
			} else if evaluateMatrix[i][j] == 3 && cellMatrix[i][j] == false {
				cellMatrix[i][j] = true
				changeMatrix = 1
			}
		}
	}

	return cellMatrix, changeMatrix

}

func main(){
	rand.Seed(time.Now().UnixNano())
	changeMatrix := 0
	sizeMatrix := 10
	cellMatrix := make([][]bool, sizeMatrix)
	/*create radnom matrix */
	for i:=0; i<sizeMatrix; i++ {
		cellMatrix[i] = make([]bool, sizeMatrix)
		for j:=0; j<sizeMatrix; j++ {
			x := rand.Intn(100)
			if (x < 30)	{		
				cellMatrix[i][j] = true
			} else {
				cellMatrix[i][j] = false
			}
		}
	}
	printMatrix(cellMatrix,sizeMatrix)
	for i:=0; i < 100; i++ {
		cellMatrix, changeMatrix = nextGeneration(cellMatrix, sizeMatrix)
		fmt.Println("")
		printMatrix(cellMatrix,sizeMatrix)
		if changeMatrix == 0 {
			break
		}
	}
}

