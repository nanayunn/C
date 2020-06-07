/*int형 배열을 선언하고, 두 개의 선언된 포인터가 각각 배열 내의 최솟값과 최댓값을 가리키도록 하는 코드입니다.*/
#include<stdio.h>
#include<string.h>

#define MAX_LENGTH 5
#define CLEAR_VALUE 0

void input(void);
void view_input(unsigned int *input_arr);

int main(void)
{
	input();
	return 0;
}

void input(void)
{
	unsigned int input_arr[MAX_LENGTH];
	int input_num = 0;
	int index = 0;

	memset(input_arr, 0, 5);

	if (input_arr == NULL) {
		printf("input_arr의 초기화가 맞게 이루어지지 않았습ㄴ다.");
	}

	printf("다섯 개의 자연수를 차례대로 입력해주세요. 한 번에 하나의 숫자를 입력 후 엔터를 쳐주세요.\n");

	for (index = 0; index < MAX_LENGTH; index++) {
		printf("input_arr[%d] 자리의 정수 입력 : \n", index);
		scanf("%d", &input_num);


		if (input_num < 0) {
			printf("0 또는 0보다 큰 정수를 입력해주세요. 입력한 수 : %u\n", input_num);
			continue;
		}
		input_arr[index] = input_num;

	}
	view_input(input_arr);
	return;
}

void view_input(unsigned int *input_arr)
{
	int index = 0;
	int your_input = 0;
	for (index = 0; index < MAX_LENGTH; index++) {
		your_input = input_arr[index];

		printf("입력된 정수 : %u", your_input);
		
	}
	return;
}
