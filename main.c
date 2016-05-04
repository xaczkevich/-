#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"
#include <conio.h>
#include <memory.h>

int check_no_conflict(const int* const arr, const int* const off, int num);
int test(int arr[]);
void print_start(int const arr[][9]);
void print_result(const int arrS[][9], const int arrR[][9]);
int* memchr_int(const void* buf, int c, size_t count);

// http://sudoku.bestcrosswords.ru/gen.php?id=1&level=5 справочный материал
// для консольки оптимальный вариант заполнения судоку

int showNum, currNum = 0;
int arrShu[9][9] = {
	0, 2, 0, 0, 7, 4, 0, 0, 0,
	1, 5, 0, 0, 0, 3, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 4, 0, 9,
	0, 0, 6, 0, 0, 0, 1, 0, 0,
	0, 0, 2, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 4, 0, 0, 0, 2,
	0, 1, 3, 9, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 8, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 9, 1, 0
};// Размещенные снаружи для того, чтобы можно вызвать, когда более чем один ответ.
int arrR[9][9] = { 0 };

int main(int argc, char* argv[])
{
	char tempchar;

	print_start(arrShu);
	printf("How many answers? (1-9)");
	tempchar = _getch();
	if (tempchar >= '1' && tempchar <= '9')
	{
		_putch(tempchar);
		showNum = tempchar - '0';
	}
	else
	{
		_putch('1');
		showNum = 1;
	}
	printf("\nStart\n");

	test((int *)arrShu);

	if (showNum == 1)
	{
		print_result(arrShu, arrR);
	}
	else if (showNum > currNum)
	{
		printf("There is no more answers\n");
	}
	printf("End\n");
	_getch();

	return 0;
}

int test(int arr[])
{
	int result;
	// 1: ответ найден
	// 0: ошибка или ответа нету
	int p[81];
	int* p0;
	int num;
	int next;

	memcpy(p, arr, 81 * sizeof(int));

	// выяснить, была ли она заполнена
	p0 = memchr_int(p, 0, 81);
	if (p0)
	{
		result = 0;// еще в начале не было найдено
		for (num = 1; num <= 9; num++)
		{
			// проверка на заполняемость
			if (check_no_conflict(p, p0, num))
			{// всё тип-топ
				*p0 = num;

				next = test(p);// рекурсия
				if (next == 0)
				{// не находит, попробуй след. число
					continue;
				}
				else// if (next == 1)
				{
					result = 1;// ищет в этой группе
					if (showNum != 1 && currNum < showNum) { continue; }
					break;
				}
			}
			else
			{
				// ошибка, попробуйте следующюю цифру
				continue;
			}
		}
		// заполнение
	}
	else
	{// заполнен
		memcpy(arrR, p, 81 * sizeof(int));// мб записан обратно массивом
		result = 1;
		if (showNum != 1)
		{
			printf("%d.\n", ++currNum);
			print_result(arrShu, arrR);
		}
	}

	return result;
}

int check_no_conflict(const int* const arr, const int* const off, int num)
{
	int row = (off - arr) / 9;
	int col = (off - arr) % 9;
	int blk = row / 3 * 3 + col / 3;
	int i;
	int r;

	r = 1;

	for (i = 0; i < 9; i++)
	{
		if ((arr[row * 9 + i] == num) ||
			(arr[col + i * 9] == num) ||
			(arr[blk / 3 * 27 + blk % 3 * 3 + i / 3 * 9 + i % 3] == num))
		{
			r = 0;
			break;
		}
	}

	return r;
}

void print_start(const int arr[][9])
{
	int i, j;
	int c;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			c = arr[i][j];
			if (c)
			{
				printf("[%d]", c);
			}
			else
			{
				printf(" . ");
			}
		}
		printf("\n");
	}
}

void print_result(const int arrS[][9], const int arrR[][9])
{
	int i, j;
	//
	if (memchr_int(arrR, 0, 81))
	{
		printf("There is no result yet.\n");
	}
	else
	{
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				if (arrS[i][j] == arrR[i][j])
				{
					printf("(%d)", arrR[i][j]);
				}
				else
				{
					printf(" %d ", arrR[i][j]);
				}
			}
			printf("\n");
		}
		_getch();
	}
}

int* memchr_int(const void* buf, int c, size_t count)
{
	int* p;
	size_t i;

	p = NULL;
	for (i = 0; i < count; i++)
	{
		if (*((int *)buf + i) == c)
		{
			p = (int *)buf + i;
			break;
			_getch();
		}
	}
	return p;
	_getch();
}

