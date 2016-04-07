
// 全部accept
#include <iostream>
using namespace std;

#define MAXLENGTH 23
int input[MAXLENGTH];
int output[MAXLENGTH];
int judge[10];

int main()
{
  char buffer[MAXLENGTH];
  int length = 0;
  int carry = 0;                // 乘法进位
  bool flag = true;
  

  cin.getline(buffer, MAXLENGTH);
  
  while ('\0' != buffer[length])
  {
    ++length;
  }

  for (int i = MAXLENGTH-1, j = length-1; j != -1; --i, --j)
  {
    input[i] = buffer[j] - '0';
  }

  for (int i = MAXLENGTH-1; i != -1; --i)
  {
    output[i] = (input[i]*2+carry)%10;
    carry = (input[i]*2+carry)/10;
  }
  
  for (int i = MAXLENGTH-1; i != MAXLENGTH-length-1; --i)
  {
    ++judge[input[i]];
    --judge[output[i]];
  }

  for (int i = 0; i != 10; ++i)
  {
    if (0 != judge[i])
    {
      flag = false;
      break;
    }
  }

  if (flag)
  {
    cout << "Yes" << endl;
  }
  else
  {
    cout << "No" << endl;
  }
  
  flag = false;
  for (int i = 0; i != MAXLENGTH; ++i)
  {
    if (0 != output[i])
    {
      flag = true;
    }
    if (flag)
    {
      cout << output[i];
    }
  }
  cout << endl;


  system("pause");
  return 0;
}

// 有一个case不过
#if 0
#include <iostream>
using namespace std;

#define MAXLENGTH 23
int input[MAXLENGTH];
int output[MAXLENGTH];
int judge[10];

int main()
{
	char buffer[MAXLENGTH];
	int length = 0;
	int carry = 0;								// 乘法进位
	bool flag = true;
	

	cin.getline(buffer, MAXLENGTH);
	
	while ('\0' != buffer[length])
	{
		++length;
	}

	for (int i = MAXLENGTH-1, j = length-1; j != -1; --i, --j)
	{
		input[i] = buffer[j] - '0';
	}

	for (int i = MAXLENGTH-1; i != -1; --i)
	{
		output[i] = (input[i]*2+carry)%10;
		carry = (input[i]*2+carry)/10;
	}
	
	for (int i = MAXLENGTH-1; i != -1; --i)
	{
		++judge[input[i]];
		--judge[output[i]];
	}

	for (int i = 1; i != 10; ++i)
	{
		if (0 != judge[i])
		{
			flag = false;
			break;
		}
	}

	if (flag)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	
	flag = false;
	for (int i = 0; i != MAXLENGTH; ++i)
	{
		if (0 != output[i])
		{
			flag = true;
		}
		if (flag)
		{
			cout << output[i];
		}
	}
	cout << endl;


	system("pause");
	return 0;
}

#endif