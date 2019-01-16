#include<stdio.h>
#include<malloc.h>
void test(int n, int m);
int** newMatrix(int n, int m);
int pour(int **matrix, int n, int m);
int pourIfPossible(int* a, int b, int c);
int pourIfPossible2(int* a, int b, int c, int d);
int overflowIfPossible(int* a, int b);
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
		for(j = 0; j < m; j++)
			scanf("%d",&matrix[i][j]);
	}
	return matrix;
}
int pour(int **matrix, int n, int m){
	int i, row_index = 0, col_index = 1, circle = 1, minheight, waternum = 0;
	char direction='r';
	for(int i=1;i<=(n-2)*(m-2);i++){
		printf("id: %d\n",i);
		switch (direction){
			case 'r':
				if(++row_index < m-circle-1){
					waternum += pourIfPossible(&matrix[col_index][row_index], matrix[col_index][row_index-1], matrix[col_index-1][row_index]);
					break;
				}else if(row_index < m-circle){
					waternum += pourIfPossible2(&matrix[col_index][row_index], matrix[col_index][row_index-1], matrix[col_index][row_index+1], matrix[col_index-1][row_index]);
					break;
				}else{
					row_index--;
					direction='d';
				}
			case 'd':
				if(++col_index < n-circle-1){
					waternum += pourIfPossible(&matrix[col_index][row_index], matrix[col_index][row_index+1], matrix[col_index-1][row_index]);
					break;
				}else if(col_index < n-circle){
					waternum += pourIfPossible2(&matrix[col_index][row_index], matrix[col_index][row_index+1], matrix[col_index-1][row_index], matrix[col_index+1][row_index]);
					break;
				}else{
					col_index--;
					direction='l';
				}
			case 'l':
				if(--row_index > circle){
					waternum += pourIfPossible(&matrix[col_index][row_index], matrix[col_index][row_index+1], matrix[col_index+1][row_index]);
					break;
				}else if(row_index == circle){
					waternum += pourIfPossible2(&matrix[col_index][row_index], matrix[col_index][row_index+1], matrix[col_index][row_index-1], matrix[col_index+1][row_index]);
					break;
				}else{
					row_index++;
					direction='u';
					circle++;
				}
			case 'u':
				if(--col_index > circle){
					waternum += pourIfPossible(&matrix[col_index][row_index], matrix[col_index][row_index-1], matrix[col_index+1][row_index]);
					break;
				}else if(col_index == circle){
					waternum += pourIfPossible2(&matrix[col_index][row_index], matrix[col_index][row_index-1], matrix[col_index+1][row_index], matrix[col_index-1][row_index]);
					break;
				}else{
					col_index++;
					direction='r';
					i--; 
				}			
		}
	}
	return waternum;
}
int pourIfPossible(int* a, int b, int c){
	int m = min(b, c), n;
	if(*a < m){
		n = m - *a;
		*a = m;
		printf("pour water: %d\n",n);
		return n;
	}
	return 0;
}
int pourIfPossible2(int* a, int b, int c, int d){
	int m = min(b, c), n;
	m = min(m, d);
	if(*a < m){
		n = m - *a;
		*a = m;
		printf("pour water: %d\n",n);
		return n;
	}
	return 0;
}
int overflowIfPossible(int* a, int b){
	if(*a <= b) return 0;
	else{
		int m = *a - b;
		*a = b;
		return m;
	}
}
int min(int a, int b){
	return a >= b ? b : a;	
}
void freeMatrix(int** matrix, int n, int m){
	int i;
	for(i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}
