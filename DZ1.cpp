// DZ1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
include <math.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;

void crypt(char original[256], int key, char result[256], bool flag_crypt)
{
	int Gamma;
	int blocksize = 4;
	int SizeLastBlock, copy_blocksize;
	
	unsigned int Block1, Block2;
	int blocks;
	int strsize = strlen(original);

	blocks = strsize / blocksize;
	SizeLastBlock = strsize - blocks * blocksize;

	if (SizeLastBlock != 0)	blocks++;

	srand(key);

	for (int i = 0; i < blocks; i++)
	{
		Gamma = (rand() << 8 * 2) | ((rand() << 8 * 2) >> 8 * 2);

		if ((i != blocks) || (SizeLastBlock = 0))
			copy_blocksize = blocksize;
		else
			copy_blocksize = SizeLastBlock;

		memcpy(&Block1, original + (blocksize * i), copy_blocksize);
		
		if (flag_crypt) 
		{
			Block2 = Block1^Gamma;
			unsigned int mask = (Block2 >> 3);
			unsigned int b = Block2 << 8 * 4 - 3;
			Block1 = mask | b;
		}
		else
		{
			unsigned int mask = Block1 << 3;
			unsigned int b = (Block1 >> 8 * 4 - 3) & 0x0007;
			Block2 = mask | b;
			Block1 = Block2^Gamma;
		}
		memcpy(result + (blocksize * i), &Block1, copy_blocksize);
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите исходный текст:";
	char S_Original [256];
	cin.getline(S_Original,256);
	char S_Result [256] = "";
	int key;
	cout << "Введите ключ для шифрования:";
	cin >> key;
	
	cout << "Зашифрованный текст:";
	crypt(S_Original, key, S_Result, true);
	cout << S_Result << endl;

	cout << "Введите ключ для дешифрования:";
	cin >> key;
	cout << "Расшифрованный текст:";
	crypt(S_Result, key, S_Original, false);
	cout << S_Original << endl;

	system("pause");
}
