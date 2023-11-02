#include <iostream>
#include <pthread.h>
#define SIZE 3
int A[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[SIZE][SIZE];
struct thread_data {
int row;
int col;
};
void *multiply(void *arg) {
struct thread_data *data = (struct thread_data *)arg;
int row = data->row;
int col = data->col;
int sum = 0;
for (int i = 0; i < SIZE; i++) {
sum += A[row][i] * B[i][col];
}
C[row][col] = sum;
pthread_exit(NULL);
}
int main() {
pthread_t threads[SIZE][SIZE];
struct thread_data td[SIZE][SIZE];
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
td[i][j].row = i;
td[i][j].col = j;
pthread_create(&threads[i][j], NULL, multiply, (void *)&td[i][j]);
}
}
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
pthread_join(threads[i][j], NULL);
}
}
std::cout << "Resultant Matrix:" << std::endl;
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
std::cout << C[i][j] << " ";
}
std::cout << std::endl;
}
return 0;
}