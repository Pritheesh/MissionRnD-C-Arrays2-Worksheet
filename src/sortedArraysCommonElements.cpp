/*
OVERVIEW: You are given 2 bank statements that are ordered by date. Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>

struct transaction 
{
	int amount;
	char date[11];
	char description[20];
};

int islegit(char *date, int *d, int * m, int *y)
{
	int count = 0;
	*d = 0;
	*m = 0;
	*y = 0;
	for (int i = 0; date[i] != '\0'; i++)
	{
		if (count == 0)
		{
			if (date[i] == '/' || date[i] == '-')
				count++;

			else
				*d = *d * 10 + (date[i] - '0');
		}
		else if (count == 1)
		{
			if (date[i] == '/' || date[i] == '-')
				count++;
			else
				*m = *m * 10 + (date[i] - '0');
		}
		else
			*y = *y * 10 + (date[i] - '0');

	}
	if (*d < 0 || *d > 31 || *m < 0 || *m > 12 || *y < 0 || *y > 9999)
		return 0;

	int legitFlag = 0, leap = 0;
	int maxDays[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (*y % 400 == 0 || (*y % 100 != 0 && *y % 4 == 0)) //leap year
		leap = 1;

	if (leap == 1)
		maxDays[1]++;

	if (*d <= maxDays[*m - 1])
	{
		legitFlag = 1;
	}

	return legitFlag;
}

int compareDates(char *date1, char *date2)
{
	int day1, mon1, year1, day2, mon2, year2;
	if (!islegit(date1, &day1, &mon1, &year1) || !islegit(date2, &day2, &mon2, &year2))
		return -1;
	if (year1 > year2 || (year1 == year2 && mon1 > mon2) || (year1 == year2 && mon1 == mon2 && day1 > day2))// 1 is newer
		return 1;
	else if (year2 > year1 || (year1 == year2 && mon2 > mon1) || (year1 == year2 && mon1 == mon2 && day2 > day1))
		return 2;
	return 0;
}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) 
{
	if (!A || !B || ALen < 1 || BLen < 1)
		return NULL;

	int CLen = (ALen < BLen) ? ALen : BLen;
	struct transaction *C = (struct transaction *)malloc(sizeof(struct transaction) * CLen);
	int i = 0, j = 0, count = 0;

	while (i < ALen && j < BLen)
	{
		int comp = compareDates(A[i].date, B[j].date);
		if (comp == -1)
			return NULL;
		else if (!comp)
		{
			C[count++] = A[i];
			i++;
			j++;
		}
		else if (comp == 1)
			i++;
		else
			j++;
	}
	if (count)
		return C;
	return NULL;
}