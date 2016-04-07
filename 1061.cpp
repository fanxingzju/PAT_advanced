// ×¢ÒâÏÞÖÆ·¶Î§
#include <stdio.h>
#include <stdlib.h>
char week[7][4] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
char str1[70];
char str2[70];
char str3[70];
char str4[70];
int DAY, HH, MM;

void first_analyze()
{
	int count = 0;
	for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i)
	{
		if (str1[i] == str2[i])
		{
			if ('A' <= str1[i] && 'G' >= str1[i])
			{
				if (0 == count)
				{
					DAY = str1[i] - 'A';
					++count;
					continue;
				}
			}
			if (1 == count && '0' <= str1[i] && '9' >= str1[i])
			{
				HH = str1[i] - '0';
				break;
			}
			if (1 == count && 'A' <= str1[i] && 'N' >= str1[i])
			{
				HH = str1[i] - 'A' + 10;
				break;
			}
		}
	}
	return ;
}


void second_analyze()
{
	for (MM = 0; str3[MM] != '\0' && str4[MM] != '\0'; ++MM)
	{
		if (str3[MM] == str4[MM])
		{
			if ('a' <= str3[MM] && 'z' >= str3[MM])
			{
				break;
			}
			if ('A' <= str3[MM] && 'Z' >= str3[MM])
			{
				break;
			}
		}
	}
	return ;
}


int main()
{
	scanf("%s", str1);
	scanf("%s", str2);
	scanf("%s", str3);
	scanf("%s", str4);

	first_analyze();
	second_analyze();

	printf("%s %02d:%02d\n", week[DAY], HH, MM);

	system("pause");
	return 0;
}