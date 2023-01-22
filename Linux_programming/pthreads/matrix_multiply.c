#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 100

typedef int matrix_t[MATRIX_SIZE][MATRIX_SIZE];

typedef struct matrix_info
{
	int id;
	int size;
	int row;
	int col;
	matrix_t *MA;
	matrix_t *MB;
	matrix_t *MC;

} matrix_info_t;

void print_matrix(matrix_t MAT, int size)
{
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			printf("%d ", MAT[r][c]);
		}
		printf("\n");
	}
}
void mulitply_matrix(int size, int row, int col, matrix_t MA, matrix_t MB, matrix_t MC)
{
	MC[row][col] = 0;
	for (int pos = 0; pos < size; pos++) {
		MC[row][col] += (MA[row][pos] * MB[pos][col]);
	}
	//printf("M[r][c] = %d\n", MC[row][col]);
}

void* peer_mul(void *argc)
{
	matrix_info_t *minfo = (matrix_info_t *) argc;
	mulitply_matrix(minfo-> size, minfo->row, minfo->col,
					*(minfo->MA), *(minfo->MB), *(minfo->MC));
	
	free(argc);
}

int main()
{
	int size = MATRIX_SIZE;
	int row, col;
	//int MA[MATRIX_SIZE][MATRIX_SIZE];
	matrix_t MA, MB, MC;

	matrix_info_t *minfo;
	pthread_t peer_threads[size * size];

	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			MA[r][c] = 3;
			MB[r][c] = 3;
		}
	}

	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			minfo = malloc(sizeof(matrix_info_t));
			minfo->id = r + c;
			minfo->size = size;
			minfo->row = r;
			minfo->col = c;
			minfo->MA = &MA;
			minfo->MB = &MB;
			minfo->MC = &MC;

			pthread_create(&peer_threads[r+c], NULL, (void*)peer_mul, (void*)minfo);
		}
	}

	for (int i = 0; i < (size * size); i++) {
		pthread_join(peer_threads[i], NULL);
	}

	//print_matrix(MA, size);
	//print_matrix(MB, size);
	//print_matrix(MC, size);
	return 0;
}
