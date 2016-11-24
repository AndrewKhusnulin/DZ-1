#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
using namespace std;
unsigned int F_Move(unsigned int Block,bool flag_move) // Функция сдвига на 3 бита
{
	unsigned int S_Left, S_Right;
	if (flag_move) 
	{
		S_Left = Block << 3; // Сдвиг 4-ёх байтового блока данных на 3 бита
		S_Right = (Block >> 8 * 4 - 3);
	}
	else
	{
		S_Right = (Block >> 3);
		S_Left = Block << 8 * 4 - 3;
	}
	return (S_Left | S_Right);
}
unsigned int F_Gamma(unsigned int Block) // Функция Гаммирования
{
	int Gamma = (rand() << 8 * 2) | ((rand() << 8 * 2) >> 8 * 2); // Гамма состоит из 2 блоков по 2 байта
	return (Block ^ Gamma);
	
}
void crypt(char original[256], int key, char result[256], bool flag_crypt) 
{
	int const blocksize = 4;
	int SizeLastBlock, copy_blocksize;
	
	unsigned int Block1, Block2;
	int blocks;
	int strsize = strlen(original);

	blocks = strsize / blocksize;
	SizeLastBlock = strsize - blocks * blocksize;

	if (SizeLastBlock != 0)	blocks++;

	srand(key); // Инициализация генератора ПСЧ ключом шифра

	for (int i = 0; i < blocks; i++)
	{

		if ((i != blocks) || (SizeLastBlock = 0)) 
			copy_blocksize = blocksize;           // Вычисление размера текущего блока
		else
			copy_blocksize = SizeLastBlock;		

		memcpy(&Block1, original + (blocksize * i), copy_blocksize); // Копируем заданное кол-во байт Original в Block1

		if (flag_crypt) 
		{
			Block2 = F_Gamma(Block1);
			Block1 = F_Move(Block2,false);
		}
		else
		{
			Block2 = F_Move(Block1, true);
			Block1 = F_Gamma(Block2);
		}
		memcpy(result + (blocksize * i), &Block1, copy_blocksize);
	}
}

void main()
{
	cout << "Enter your text:";
	char S_Original [256] ;
	cin.getline(S_Original,256);
	char S_Result [256] = "";
	int key;
	cout << "enter the encryption key:";
	cin >> key;
	cout << "Encrypted text:";
	crypt(S_Original, key, S_Result, true);
	cout << S_Result << endl;
	cout << "Enter the decryption key:";
	cin >> key;
	cout << "Decrypted text :";
	crypt(S_Result, key, S_Original, false);
	cout << S_Original << endl;
	system("pause");
}
