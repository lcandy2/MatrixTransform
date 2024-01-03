#include <stdio.h>
#include <stdlib.h>

/**
 * 动态初始化二维数组
 * @param rows
 * @param cols
 * @return
 */
int **initTwoArray(int rows, int cols) {
    int **array;
    // 声明二维指针
    array = (int **) malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        array[i] = (int *) malloc(sizeof(int) * cols);
    }
    // 使用0进行初始化
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            array[row][col] = 0;
    }
    return array;
}

/**
 * 打印二维数组
 * @param array
 * @param rows
 * @param cols
 */
void printArray(int **array, int rows, int cols) {
    int number = rows * cols;
    int count = 0;
    while (number != 0) {
        number /= 10;  // 这将会删除数字的最后一位
        count++;
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            // 使用动态宽度打印，保证任意位数的数字都能对齐
            printf("%*d", count + 1, array[row][col]);
        printf("\n");
    }
}

/**
 * 释放二维数组的内存
 * @param array
 * @param rows
 */
void destoryTwoArray(int **array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

/**
 * 顺序填充二维数组
 * @param array
 * @param rows
 * @param cols
 */
void fillDirectPrint(int **array, int rows, int cols) {
    int num = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = num++;
        }
    }
}

/**
 * 蛇形填充二维数组
 * @param array
 * @param rows
 * @param cols
 */
void fillSnakePattern(int **array, int rows, int cols) {
    int num = 1;
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;

    while (top <= bottom && left <= right) {
        // 从左到右填充最上面一行
        for (int i = left; i <= right; i++) {
            array[top][i] = num++;
        }
        top++;

        // 从上到下填充最右边一列
        for (int i = top; i <= bottom; i++) {
            array[i][right] = num++;
        }
        right--;

        // 从右到左填充最下面一行
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                array[bottom][i] = num++;
            }
            bottom--;
        }

        // 从下到上填充最左边一列
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                array[i][left] = num++;
            }
            left++;
        }
    }
}

/**
 * 比较函数
 * @param a
 * @param b
 * @return
 */
int compare(const void *a, const void *b) {
    int *arrA = *(int **)a;
    int *arrB = *(int **)b;
//    if (sortType == 0) {
        return arrA[2] - arrB[2]; // 按值字段升序排序
//    } else if (sortType == 1) {
//        return arrB[2] - arrA[2]; // 按值字段降序排序
//    }
}

/**
 * 逆向输出二维数组
 * @param array
 * @param rows
 * @param cols
 */
void reverseMatrix(int **array, int rows, int cols) {
    int totalElements = rows * cols;
//    int tempArray1D[totalElements];
//    int tempArrayToBeSorted[totalElements][3];
//    int tempArrayReserved[totalElements][cols];

    int **tempArrayToBeSorted = initTwoArray(totalElements, 3);

    // 动态分配内存以存储新数组
//    int (*tempArrayToBeSorted)[3] = malloc(totalElements * sizeof(*tempArrayToBeSorted));
    int index = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            tempArrayToBeSorted[index][0] = r;    // 行
            tempArrayToBeSorted[index][1] = c;    // 列
            tempArrayToBeSorted[index][2] = array[r][c]; // 值
            index++;
        }
    }

    // 使用 qsort 进行排序
    qsort(tempArrayToBeSorted, totalElements, sizeof(*tempArrayToBeSorted), compare);

    // 根据排序结果更新原数组
    for (int i = 0; i < totalElements; i++) {
        int r = tempArrayToBeSorted[i][0];
        int c = tempArrayToBeSorted[i][1];
        array[r][c] = tempArrayToBeSorted[i][2];
    }

//    printf("排序后的数组：\n");
//    printArray(tempArrayToBeSorted, totalElements, 3);

    int **tempArrayReserved = initTwoArray(totalElements, 3);

    for (int i = totalElements - 1; i >= 0; i--) {
        int index = totalElements - 1 - i;
        tempArrayReserved[index][0] = tempArrayToBeSorted[index][0];
        tempArrayReserved[index][1] = tempArrayToBeSorted[index][1];
        tempArrayReserved[index][2] = tempArrayToBeSorted[i][2];
    }

    // 释放临时数组的内存
    free(tempArrayToBeSorted);

    // 将临时数组的元素存入原数组
    for (int i = 0; i < totalElements; i++) {
        int row = tempArrayReserved[i][0];
        int col = tempArrayReserved[i][1];
        int value = tempArrayReserved[i][2];
        array[row][col] = value;
    }

    // 释放临时数组的内存
    free(tempArrayReserved);

//    index = 0;

//    // 将原数组的元素按逆序存入临时数组
//    for (int i = rows - 1; i >= 0; i--) {
//        for (int j = cols - 1; j >= 0; j--) {
//            tempArray1D[index++] = array[i][j];
//        }
//    }
//
//    int max = tempArray1D[0];
//    int min = tempArray1D[0];
//
//    for (int i = 1; i < totalElements; i++) {
//        if (tempArray1D[i] > max) {
//            max = tempArray1D[i];
//        }
//        if (tempArray1D[i] < min) {
//            min = tempArray1D[i];
//        }
//    }
//
//    // 遍历二维数组
//    index = 0;
//    for (int r = 0; r < rows; r++) {
//        for (int c = 0; c < cols; c++) {
//            int currentNum = array[r][c];
//            int currentRow = r + 1;
//            int currentCol = c + 1;
//            int currentNumIndex = currentCol * currentRow - 1;
//            // tempArrayIndex[0] 存储列号
//            // tempArrayIndex[1] 存储行号
//            // tempArrayIndex[2] 存储元素值
//            if (currentNum == max - currentNumIndex) {
//                tempArrayIndex[currentNumIndex][0] = r;
//                tempArrayIndex[currentNumIndex][1] = c;
//                tempArrayIndex[currentNumIndex][2] = currentNum;
//            } else if (currentNum == min - currentNumIndex) {
//                tempArrayIndex[currentNumIndex][0] = r;
//                tempArrayIndex[currentNumIndex][1] = c;
//                tempArrayIndex[currentNumIndex][2] = currentNum;
//            }
//        }
//    }
//
//    // 将临时数组的元素按逆序存入新数组
//    for (int i = totalElements - 1; i >= 0; i--) {
//        tempArrayReserved[tempArrayIndex[i][0]][tempArrayIndex[i][1]] = tempArrayIndex[i][2];
//    }
//
//    // 将临时数组的元素存入原数组
//    for (int i = 0; i < totalElements; i++) {
//        for (int j = 0; j < 3; j++)
//            array[i][j] = tempArrayReserved[i][j];
//    }
}

/**
 * 行列互换
 * @param array
 * @param rows
 * @param cols
 * @return
 */
int **transposeAndReverseMatrix(int **array, int rows, int cols) {
    int **transposedArray = initTwoArray(cols, rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposedArray[cols - 1 - j][rows - 1 - i] = array[i][j];
        }
    }

    return transposedArray;
}

/**
 * 水平翻转
 * @param array
 * @param rows
 * @param cols
 */
void horizontalFlip(int **array, int rows, int cols) {
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows / 2; row++) {
            int temp = array[row][col];
            array[row][col] = array[rows - 1 - row][col];
            array[rows - 1 - row][col] = temp;
        }
    }
}

/**
 * 垂直翻转
 * @param array
 * @param rows
 * @param cols
 */
void verticalFlip(int **array, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols / 2; col++) {
            int temp = array[row][col];
            array[row][col] = array[row][cols - 1 - col];
            array[row][cols - 1 - col] = temp;
        }
    }
}

int main() {
    int rows, cols;
    puts("|    行数 Row    |    列数 Col    |");
    puts("| 使用空格分隔 Seperate with space |");
    puts("- 请输入行数与列数 Rows and Cols:");
    scanf("%d %d", &rows, &cols);
    // 动态初始化二维数组
    int **array = initTwoArray(rows, cols);
    printf("- 你创建了一个 %d 行 %d 列的矩阵 You created a %d rows %d cols matrix\n", rows, cols, rows, cols);
    puts("| 1: 直接打印 Direct Print     | 2: 蛇形矩阵 Snake Pattern  |");
    puts("| 3: 逆向输出 Reverse Output   | 4: 行列互换 Transpose      |");
    puts("| 5: 水平翻转 Horizontal Flip  | 6: 垂直翻转 Vertical Flip  |");
    puts("| 0: 退出 Exit                                            |");
    puts("- 如何处理矩阵？ Input command");
    while (1) {
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                fillDirectPrint(array, rows, cols);
                puts("| 1: 直接打印 Print Matrix                                 |");
                printArray(array, rows, cols);
                break;
            case 2:
                fillSnakePattern(array, rows, cols);
                puts("| 2: 蛇形矩阵 Snake Pattern                                |");
                printArray(array, rows, cols);
                break;
            case 3:
                reverseMatrix(array, rows, cols);
                puts("| 3: 逆向输出 Reverse Output                               |");
                printArray(array, rows, cols);
                break;
            case 4:
                puts("| 4: 行列互换 Transpose                                    |");
                int **transposedMatrix = transposeAndReverseMatrix(array, rows, cols);
                printArray(transposedMatrix, cols, rows);
                destoryTwoArray(transposedMatrix, cols); // 释放新矩阵的内存
                break;
            case 5:
                puts("| 5: 水平翻转 Horizontal Flip                              |");
                horizontalFlip(array, rows, cols);
                printArray(array, rows, cols);
                break;
            case 6:
                puts("| 6: 垂直翻转 Vertical Flip                                |");
                verticalFlip(array, rows, cols);
                printArray(array, rows, cols);
                break;
            case 0:
                puts("| 0: 退出 Exit                                            |");
                destoryTwoArray(array, rows);
                return 0;
            default:
                puts("- 输入错误，请重新输入！ Command Error!");
                break;
        }
    }
}
