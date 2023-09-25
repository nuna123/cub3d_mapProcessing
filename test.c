
#include <stdio.h>

int main(void)
{
	char i = 'W';

	int x;
	if (i == 'N')
		x = 0;
	else
		x = 90 * ((i - 61) / 8);
	printf("{%i}\n", x);

return 0;


}

/*
	logic:
		'N' = 78; -> 0°
		'E' = 69; -> 90° = 90 * 1
		'S' = 83; -> 180° = 90 * 2
		'W' = 87; -> 270° = 90 * 3

		apart from N, the other directions are in ascending order.
		first 'IF' is to take care of that exception.
		subtracting 61 makes
			E = 8 (% 8 = 1),
			S = 22 (% 8 = 2),
			W = 26  (% 8 = 3)
 */