#include <stdio.h>
#include <string.h>

void removeSpaces(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "H e l l o ,  W o r l d ! ";
    printf("Original string: '%s'\n", str);
    
    removeSpaces(str);
    printf("String after removing spaces: '%s'\n", str);
    
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // 定义单元格的最大宽度和高度
// #define MAX_CELL_WIDTH 20
// #define MAX_CELL_HEIGHT 3

// // 定义单元格结构
// typedef struct {
//     char content[MAX_CELL_HEIGHT][MAX_CELL_WIDTH];
// } Cell;

// // 打印水平分隔线
// void print_horizontal_line(int num_cols, int cell_width) {
//     for (int col = 0; col < num_cols; col++) {
//         printf("+");
//         for (int i = 0; i < cell_width; i++) {
//             printf("-");
//         }
//     }
//     printf("+\n");
// }

// // 打印单元格内容
// void print_cell_content(Cell **cells, int row, int col, int cell_width, int cell_height) {
//     for (int line = 0; line < cell_height; line++) {
//         printf("|");
//         for (int col_index = 0; col_index < col; col_index++) {
//             printf("%-*s", cell_width, ""); // 打印空单元格
//             printf("|");
//         }
//         printf("%-*s", cell_width, cells[row][col].content[line]);
//         for (int col_index = col + 1; col_index < col + 1; col_index++) {
//             printf("|");
//             printf("%-*s", cell_width, ""); // 打印空单元格
//         }
//         printf("|\n");
//     }
// }

// // 打印整个表格
// void print_table(Cell **cells, int num_rows, int num_cols, int cell_width, int cell_height) {
//     for (int row = 0; row < num_rows; row++) {
//         print_horizontal_line(num_cols, cell_width);
//         for (int col = 0; col < num_cols; col++) {
//             print_cell_content(cells, row, col, cell_width, cell_height);
//         }
//     }
//     print_horizontal_line(num_cols, cell_width);
// }

// int main() {
//     int num_rows, num_cols;

//     // 获取行数和列数
//     printf("Enter number of rows: ");
//     scanf("%d", &num_rows);
//     printf("Enter number of columns: ");
//     scanf("%d", &num_cols);

//     // 动态分配内存2
//     Cell **cells = (Cell **)malloc(num_rows * sizeof(Cell *));
//     for (int i = 0; i < num_rows; i++) {
//         cells[i] = (Cell *)malloc(num_cols * sizeof(Cell));
//     }
//     print_table(cells, num_rows, num_cols, 1, 1);
// }