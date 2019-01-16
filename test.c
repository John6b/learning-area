#include<stdio.h>
#include<malloc.h>
void test(int n, int m);
int** newMatrix(int n, int m);
int pour(int **matrix, int n, int m);
int min(int a, int b);
void freeMatrix(int** matrix, int n, int m);

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  test(n, m);
  
 return 0; 
}
void test(int n, int m){
	int **matrix = newMatrix(n, m);
	int waternum = pour(matrix, n, m);
	printf("%d\n", waternum);
	freeMatrix(matrix, n, m);
}
int** newMatrix(int n, int m){
	int **matrix = (int**)malloc(sizeof(int*)*n);
	int i, j;
	for(i = 0; i < n; i++){
		matrix[i] = (int*)malloc(sizeof(int)*m);
		for(j = 0; j < m; j++){
			scanf("%d",&matrix[i][j]);
		}
	}
	return matrix;
}
int pour(int **matrix, int n, int m){
	int i, row_index = 0, col_index = 1, circle = 1, minheight, waternum = 0;
	char direction='r';
	for(int i=1;i<=n*m;i++){
		switch (direction){
			case 'r':
				if(++row_index < m-circle){
					minheight = min(matrix[col_index][row_index-1], matrix[col_index-1][row_index]);
					if(minheight > matrix[col_index][row_index]){
						waternum += minheight - matrix[col_index][row_index];
						matrix[col_index][row_index] = minheight;
					}
					break;
				}else{
					row_index--;
					direction='d';
				}
			case 'd':
				if(++col_index < n-circle){
					minheight = min(matrix[col_index][row_index+1], matrix[col_index-1][row_index]);
					if(minheight > matrix[col_index][row_index]){
						waternum += minheight - matrix[col_index][row_index];
						matrix[col_index][row_index] = minheight;
					}
					break;
				}
				else{
					col_index--;
					direction='l';
				}
				
			case 'l':
				if(--row_index>=circle){
					minheight = min(matrix[col_index][row_index+1], matrix[col_index+1][row_index]);
					if(minheight > matrix[col_index][row_index]){
						waternum += minheight - matrix[col_index][row_index];
						matrix[col_index][row_index] = minheight;
					}
					break;
				}
				else{
					row_index++;
					direction='u';
					circle++;
				}
			case 'u':
				if(--col_index>=circle){
					minheight = min(matrix[col_index][row_index+1], matrix[col_index+1][row_index]);
					if(minheight > matrix[col_index][row_index]){
						waternum += minheight - matrix[col_index][row_index];
						matrix[col_index][row_index] = minheight;
					}
					break;
				}
				else{
					col_index++;
					direction='r';
					i--; 
				}
				
		}
	}
	return waternum;
}
int min(int a, int b){
	return a >= b ? b : a;	
	
}
void freeMatrix(int** matrix, int n, int m){
	int i;
	for(i = 0; i < n; i++){
		free(matrix[i]);
	}
	free(matrix);
}
