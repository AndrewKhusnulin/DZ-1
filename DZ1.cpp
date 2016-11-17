// DZ1.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;
void crypt(char original [256], int key, char result [256])
{
	int Gamma;
	int SizeLastBlock, copy_blocksize;
	int blocksize = 4;
	unsigned int Block1, Block2;
	int blocks;
	int strsize = strlen(original);

	blocks = strsize / blocksize;
	SizeLastBlock = strsize - blocks * 4;

	if (SizeLastBlock != 0)	blocks++;
	
	srand(key);
	
	for (int i = 0; i < blocks; i++)
	{
		Gamma = rand();

		if ((i != blocks) || (SizeLastBlock = 0))
			copy_blocksize = blocksize;
		else 
			copy_blocksize = SizeLastBlock;
		
		memcpy(&Block1, original + (blocksize * i), copy_blocksize);
		Block2 = Block1^Gamma;
		memcpy(result + (blocksize * i), &Block2, copy_blocksize);
	}
}
void main()
{

	setlocale(LC_ALL, "Russian");
	char s[256] = "_1Andrew2Andrew3Andrew";
	char s_Res[256] = "";
	int key = 123;
	//cout << "¬ведите исходный текст:";
	//cin.getline(s,256);

	cout << s << endl;
	crypt(s, key, s_Res);
	cout << s_Res << endl;
	crypt(s_Res, key, s);
	cout << s << endl;

	system("pause");
}