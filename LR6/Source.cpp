#include <iostream>
#include "EvryThng.h"
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string>

#define UNICODE
#define _UNICODE
using namespace std;
int error = 0;
int mode = 0;
string Errmsg = "";

string GetLastErrorStdStr()
{
	if (error)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return "";
}

void Menu()
{
	system("CLS");

	switch (mode)
	{
	case 0:
		cout << "1.Удалить файл (1)" << endl;
		cout << "2.Копировать файл (1,2)" << endl;
		cout << "3.MoveFile (1,2)" << endl;
		cout << "4.MoveFileEx (1,2)" << endl;
		cout << "5.Создать каталог (1)" << endl;
		cout << "6.Удалить каталог (1)" << endl;
		cout << "7.Установить текущий каталог" << endl;
		cout << "8.Получить текущий каталог" << endl;
		cout << "" << endl;
		cout << "9.Exit" << endl;
		break;
	case 1:
		printf("Погорелова Евгения\nИВТ-41-16\n");
		break;
	case 2:
		printf("Error %i:\n", error);
		cout << Errmsg << endl;
		system("pause");
		exit(error);
		break;
	}
}

void TestFileDir(int ch, char *argv[])
{
	switch (ch)
	{
	case '1':
		// удаление файла
		if (_taccess(argv[1], 0) == 0)
		{
			system("CLS");
			//cout << "подтвердите удаление y/n" << endl;
			////printf("Confim delete %s?\n y/n", argv[1]);
			//if (_getch() == 'y')
			//{
				if (0 == DeleteFile(argv[1]))
				{
					mode = 2;
					error = GetLastError();
					Errmsg = GetLastErrorStdStr();
				}
			//}
		}
		else
		{
			mode = 2;
			Errmsg = "файл не найден";
		}
		
		break;
	case '2':
		// копирование файлов
		if (_taccess(argv[1], 0) == 0)
		{
			bool NoReWrite = true;
			if (_taccess(argv[2], 0) == 0)
			{
				system("CLS");
				/*printf("Confim ReWrite %s?\n y/n", argv[2]);
				if (_getch() == 'y')*/
					NoReWrite = false;
			}
			if (0 == CopyFile(argv[1], argv[2], NoReWrite))
			{
				mode = 2;
				error = GetLastError();
				Errmsg = GetLastErrorStdStr();
			}
		}
		else
		{
			mode = 2;
			Errmsg = "file not found";
		}
		break;
	case '3':
		// переименование файла
		if (_taccess(argv[1], 0) == 0)
		{
			if (0 == MoveFile(argv[1], argv[2]))
			{
				mode = 2;
				error = GetLastError();
				Errmsg = GetLastErrorStdStr();
			}
			else {
				system("CLS");
				cout << "Готово" << endl;
			}
		}
		else 
		{
			mode = 2;
			Errmsg = "file not found";
		}
		break;
	case '4':
		// переименование файлов
		if (_taccess(argv[1], 0) == 0)
		{
			bool ReWrite = false;
			if (_taccess(argv[2], 0) == 0)
			{
				system("CLS");
				/*printf("Confim ReWrite %s?\n y/n", argv[2]);
				if (_getch() == 'y')*/
					ReWrite = true;
			}
			if (0 == MoveFileEx(argv[1], argv[2], ReWrite))
			{
				mode = 2;
				error = GetLastError();
				Errmsg = GetLastErrorStdStr();
			}
		}
		else
		{
			mode = 2;
			Errmsg = "file not found";
		}
		break;
	case '5':
		// создать каталог
		TCHAR dir_create[MAX_PATH];
		if (0 == GetCurrentDirectory(sizeof(dir_create), dir_create))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
			return;
		}
		strcat_s(dir_create, "\\");
		strcat_s(dir_create, argv[1]);
		if (0 == CreateDirectory(dir_create, NULL))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
		}
		else {
			system("CLS");
			cout << "Готово" << endl;
		}
		break;
	case '6':
		// удалить каталог
		TCHAR dir_remove[MAX_PATH];
		if (0 == GetCurrentDirectory(sizeof(dir_remove), dir_remove))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
			return;
		}
		strcat_s(dir_remove, "\\");
		strcat_s(dir_remove, argv[1]);
		if (0 == RemoveDirectory(dir_remove))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
		}
		else {
			system("CLS");
			cout << "Готово" << endl;
		}
		break;
	case '7':
		// установить текущий каталог
		TCHAR dir_set[MAX_PATH];
		if (0 == GetCurrentDirectory(sizeof(dir_set), dir_set))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
		}
		else
		{
			strcat_s(dir_set, "\\");
			strcat_s(dir_set, argv[1]);
			SetCurrentDirectory(argv[1]);
			system("CLS");
			cout << "Готово" << endl;
		}
		break;
	case '8':
		// получить текущий каталог
		TCHAR dir[MAX_PATH];
		if (0 == GetCurrentDirectory(sizeof(dir), dir))
		{
			mode = 2;
			error = GetLastError();
			Errmsg = GetLastErrorStdStr();
		}
		else
		{
			system("CLS");
			printf("CurrentDirectory: %s", dir);
			Sleep(5000);
			while (!_kbhit());
		}
		break;
	case '9':
		exit(0);
		break;
	}
}

int main(int argc, char *argv[])
{
	setlocale(0, "RUS");
	if (argc == 3)
	{
		while (true)
		{
			Menu();
			if (_kbhit())
				TestFileDir(_getch(), argv);
			Sleep(500);
		}
	}

	system("pause");
	return 0;
}