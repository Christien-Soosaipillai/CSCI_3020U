#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int valid[3][9];
int** sud_board;
pthread_t* threads;


int ROW_LEN = 9;
int COL_LEN = 9;
int NUM_ROW = 9;
int NUM_COL = 9;
int NUM_CELL = 9;
int NUM_THREADS = 11;

void check_row(int row_num) {
    int row_n = row_num;
	  int vals[9] = { 0 };
   	for(int i = 0; i < NUM_ROW; i++) {
        int index = sud_board[row_n][i] - 1;
        if (index != -1) {
            vals[index] += 1;
        }
   	}

    int check_valid = 1;
    for (int i = 0; i < 9; i++) {
        if (vals[i] != 1) {
            check_valid = 0;
        }
    }
    valid[0][row_n] = check_valid;
    return;
}

void* check_rows(void* n) {
    for (int i = 0; i < NUM_COL; i++) {
        check_row(i);
    }
    pthread_exit(NULL);
}

void check_column(int col_num) {
    int col_n = col_num;
	  int vals[9] = { 0 };
   	for(int i = 0; i < NUM_COL; i++) {
        int index = sud_board[i][col_n] - 1;
        if (index != -1) {
            vals[index] += 1;
        }
   	}
    int check_valid = 1;
    for (int i = 0; i < 9; i++) {
        if (vals[i] != 1) {
            check_valid = 0;
        }
    }
    valid[1][col_n] = check_valid;
    return;
}

void* check_columns(void* n) {
    for (int i = 0; i < NUM_COL; i++) {
        check_column(i);
    }
    
    pthread_exit(NULL);
}

void* check_cell(void* cell_num) {
    int cell_n = *((int*) cell_num);

    int vals[9] = { 0 };

    int row_n = (cell_n / 3) * 3;
    int col_n = (cell_n % 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sud_board[row_n+i][col_n+j] != 0) {
                int index = sud_board[row_n+i][col_n+j] - 1;
                if (index != -1) {
                    vals[index] += 1;
                }
            }
        }
    }
    pthread_exit(NULL);
}

int** init_sud_board() {
    sud_board = (int**) malloc(NUM_ROW*sizeof(int*));
    for (int i = 0; i < NUM_ROW; i++) {
        *(sud_board+i) = (int*) malloc(NUM_COL*sizeof(int));
    }


    return sud_board;
}



int main(int argc, char *argv[]) {
  sud_board = init_sud_board();
  FILE* f = fopen("puzzle.txt", "r");
  int d = 0;
  int i = 0;
  while (fscanf(f, "%d", &d) != EOF) {
      sud_board[i / 9][i % 9] = d;
      i++;
  }

  threads = (pthread_t*)calloc(NUM_THREADS, sizeof(pthread_t));
  pthread_create(threads, NULL, check_rows, 0);
  pthread_create(threads+1, NULL, check_columns, 0);
  int* cells = (int*) malloc(NUM_CELL*sizeof(int));


  for (int i = 0; i < NUM_THREADS-2; i++){
      cells[i] = i;
      pthread_create(threads+i+2, NULL, check_cell, (void*) &cells[i]);
  }

  int s;
  
  for (int i = 2; i < NUM_THREADS; i++) {
      s = pthread_join(threads[i], NULL);
  }
  
  for (int i = 0; i < NUM_ROW; i++) {
      free(sud_board[i]);
  }
  free(sud_board);
  free(threads);
  free(cells);

  return 0;
}
