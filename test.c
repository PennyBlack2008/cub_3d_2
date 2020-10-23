#include <stdio.h>

/*
** a 배열에 담긴 0 ~ 30 숫자들을 b 배열에서 정한 값 중심으로 위로 아래로 배열 정리하기
** 만약에 3이면0 0 0 1 2 3 4 5 6 7 의 배열로 담겨야한다.
*/

int main(void)
{
	int a[31];
	int	i;
	int b[10]; // pixel
	int	j;
	int	k;
	int standard; // w->player.height

	standard = 3;

	i = 0;
	while (i < 31)
	{
		a[i] = i;
		i++;
	} // a[i] 는 pjtd_height;
	
	//--------- 시작
	k = 10 / 2; // 배열의 중간값 계산
	j = standard;
	while (k >= 0) // 중간에서 위로 올리기
	{
		if (j < 0) // 천장 찍기
			j = 0;
		b[k] = j; // j를 중심을 픽셀 찍기
		j--;
		k--;
	}
	k = 10 / 2; // 배열의 중간값 계산
	j = standard;
	while (k < 10)
	{
		b[k] = j;
		j++;
		k++;
	}

	j = 0;
	while (j < 10)
	{
		printf("b[%d] = %d\n", j, b[j]);
		j++;
	}

	return (0);
}
