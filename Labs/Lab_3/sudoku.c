#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **board;
pthread_t* threads;

int row_valid = 0;
int col_valid = 0;
int cell_valid = 0;

void create_board(){
  board = (int**) malloc(9*sizeof(int*));
  for(int i = 0; i < 9; i++) {
    *(board + i) = (int *)malloc(9*sizeof(int));
  }
}

void validate_row(int row) {
	int vals[9] = { 0 };
  for(int i = 0; i < 9; i++) {
        int index = board[row][i] - 1;
        if (index != -1) {
            vals[index] += 1;
        }
   	}

    for (int i = 0; i < 9; i++) {
        if (vals[i] == 1) {
          row_valid = 1;
          return;
        }
    }
}

void* check_rows(void* n) {
    for (int i = 0; i < 9; i++) {
        validate_row(i);
    }
    if(row_valid == 1){
      printf("%s\n", "INVALID ROW, THIS PUZZLE IS INVALID");
    }
    else {
      printf("%s\n", "ROW VALID");
    }
    pthread_exit(NULL);
}

void validate_col(int col) {
	  int vals[9] = { 0 };
   	for(int i = 0; i < 9; i++) {
        int index = board[i][col] - 1;
        if (index != -1) {
            vals[index] += 1;
        }
   	}
    int is_valid = 1;
    for (int i = 0; i < 9; i++) {
        if (vals[i] == 1) {
            col_valid = 1;
            return;
        }
    }
}

void* check_cols(void* n) {
    for (int i = 0; i < 9; i++) {
        validate_col(i);
    }

    if(row_valid == 1){
      printf("%s\n", "INVALID COLUMN, THIS PUZZLE IS INVALID");
    }
    else {
      printf("%s\n", "COLUMN VALID");
    }
    pthread_exit(NULL);
}

void* check_cell(int cell) {
  int vals[9] = { 0 };

    int row_n = (cell / 3) * 3;
    int col_n = (cell % 3) * 3;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[row_n+i][col_n+j] != 0) {
          int index = board[row_n+i][col_n+j] - 1;
          vals[index] += 1;
        }
      }
    }

    int is_valid = 1;
    for (int i = 0; i < 9; i++) {
        if (vals[i] == 1) {
          cell_valid = 1;
          break;
        }
    }

    if(row_valid == 1){
      printf("%s\n", "INVALID CELL, THIS PUZZLE IS INVALID");
    }
    else {
      printf("%s\n", "CELL VALID");
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  create_board();

  FILE* f = fopen("puzzle.txt", "r");
  int d = 0;
  int i = 0;
  while (fscanf(f, "%d", &d) != EOF) {
      board[i / 9][i % 9] = d;
      i++;
  }

  threads = calloc(11, sizeof(pthread_t));

  //Thread to check rows
  pthread_create(threads, NULL, check_rows, 0);

  //Thread to check columns
  pthread_create(threads+1, NULL, check_cols, 0);

  //Thread to chck cells
  int* cells = (int*) malloc(9*sizeof(int));
  pthread_create(threads+2, NULL, check_cell,(void *) &cells[i]);
  pthread_create(threads+3, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+4, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+5, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+6, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+7, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+8, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+9, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+10, NULL, check_cell, (void *) &cells[i]);
  pthread_create(threads+11, NULL, check_cell, (void *) &cells[i]);

  for (int i = 0; i < 11; i++) {
    pthread_join(threads[i],NULL);
  }

  return 0;
}
