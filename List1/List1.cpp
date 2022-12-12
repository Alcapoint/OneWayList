#include <iostream>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
char x1(8), x2(7), x3(7), x4(7), x5(7), x6(7), x7(7), n(0);
int dlina(0);
void SetColor(char code)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(code));
}
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void cls(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
// это вместо system("cls")

void menu()
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hStdout);
	SetColor(x1); printf("1. Создать список\n"); SetColor(7);
	SetColor(x2); printf("2. Удалить список\n"); SetColor(7);
	SetColor(x3); printf("3. Добавить элемент\n"); SetColor(7);
	SetColor(x4); printf("4. Удалить элемент\n"); SetColor(7);
	SetColor(x5); printf("5. Изменить элемент\n"); SetColor(7);
	SetColor(x6); printf("6. Отсортировать\n"); SetColor(7);
	SetColor(x7); printf("7. Выход\n"); SetColor(7);
}
struct list
{
	int field; // хранение данных
	list* ptr; // указатель на след элемент
};
list* init(int dlina, int nach)
{
	list* lst = nullptr,
		* next = nullptr;
	for (unsigned i = dlina + nach - 1; i >= nach; i--)
	{
		lst = new list;
		lst->ptr = next;
		lst->field = i;
		next = lst;
	}
	return(lst);
}
void listprint(list* lst)
{
	list* p;
	p = lst;
	int i = 1;
	int xpos = 0; int ypos = 10;
	if (lst) {
		do { // здесь мудреная запись но тебе нужно только 1 4 и 5 строчки
			for (i; i < dlina + 1; i++) {
				gotoxy(xpos, ypos);
				cout << " (" << setw(1) << left << i << ")" << "[" << setw(1) << left << p->field << "] " << "\n";
				/*printf(" (%d)-[%d]", i, p->field*/
				p = p->ptr;
				ypos++;
				if (i % 10 == 0) {
					xpos += 17;
					ypos -= 10;
				}
				if (i % 70 == 0) {
					ypos += 11;
					xpos = 0;
				}
			}
		} while (p);
	}
}
list* DelList(list* lst) {
	while (lst != NULL) {
		list* pr = lst;
		lst = lst->ptr;
		delete pr;
	}
	return lst;
}
list* Add(list* lst, int data, int num)
{
	list* p = lst;
	int i = 1;
	while (i < num && p->ptr != NULL) {
		p = p->ptr;
		i++;
	}
	list* tmp = new list;
	tmp->field = data;
	tmp->ptr = p->ptr;
	p->ptr = tmp;
	return lst;

}
list* AddFirst(int data, list* lst) {
	list* tmp = new list;
	tmp->field = data;
	tmp->ptr = lst;
	return tmp;
}
list* AddLast(int data, list* lst) {
	list* tmp = new list, * cur = lst;
	tmp->field = data;
	tmp->ptr = nullptr;
	while (cur->ptr != NULL) {
		cur = cur->ptr;
	}
	cur->ptr = tmp;
	return lst;
}
list* Del(int n, list* lst)
{
	list* tmp = lst, * p = NULL;
	unsigned i = 0;
	for (i; i < n - 1; i++) {
		p = tmp;
		tmp = tmp->ptr;
	}
	p->ptr = tmp->ptr;
	delete tmp;
	return lst;
}
list* DelLast(list* lst) {
	list* cur = lst;
	while (cur->ptr->ptr != NULL) {
		cur = cur->ptr;
	}
	delete cur->ptr;
	cur->ptr = NULL;
	return lst;
}
list* DelFirst(list* lst) {
	list* next = NULL;
	next = lst->ptr;
	delete lst;
	lst = next;
	return lst;
}
list* ChangeFirst(list* lst, int data) {
	list* tmp = lst;
	tmp->field = data;
	return tmp;
}
list* ChangeLast(list* lst, int data) {
	list* tmp = lst;
	while (tmp->ptr != NULL) {
		tmp = tmp->ptr;
	}
	tmp->field = data;
	return lst;
}
list* Change(list* lst, int data, int n) {
	list* tmp = lst, * p = NULL;
	unsigned i = 0;
	for (i; i < n - 1; i++) {
		p = tmp;
		tmp = tmp->ptr;
	}
	tmp->field = data;
	return lst;
}
list* Sort(list* lst) {
	list* q, * out, * p, * pr;
	out = NULL;
	while (lst != NULL)
	{
		q = lst; lst = lst->ptr;
		for (p = out, pr = NULL; p != NULL && q->field > p->field; pr = p, p = p->ptr);
		if (pr == NULL)
		{
			q->ptr = out;
			out = q;
		}
		else
		{
			q->ptr = p;
			pr->ptr = q;
		}
	}
	return out;
}
int main()
{
	long nach(0), Change2(0), data(0); int num(0), del(0), del1(0), Change1(0), n(0), dob(0);
	short amix(0); unsigned short ch(0);

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	cls(hStdout);
	setlocale(LC_ALL, "Russian");
	bool exit = false;
	list* lst = nullptr;
	while (!exit)
	{
		menu();
		gotoxy(0, 10);
		if (lst) {
			listprint(lst); // проверка на то чтобы не выводился пустой список
		}
		gotoxy(0, amix);
		ch = getch();
		if (ch == 224)
			ch = getch();
		switch (ch)
		{
		case 27: exit = true; break;
		case 72: amix--; break;
		case 80: amix++; break;
		case 13:
			if (amix == 0)
			{
				if (dlina > 0) {

					gotoxy(20, 0);
					printf("Чтобы создать новый список нужно удалить предыдущий");
					n = getch();
				}
				else {
					gotoxy(1, 8); cout << "С какого числа начнется список:"; gotoxy(33, 8);
					while (!(cin >> nach) || (cin.peek() != '\n') || (nach <= 0) || (nach >= 99999002))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 14);
						listprint(lst);
						gotoxy(33, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "С какого числа начнется список:"; gotoxy(49, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(1, 8); cout << "Длина списка:"; gotoxy(14, 8);
					while (!(cin >> dlina) || (cin.peek() != '\n') || ((dlina > 1000) || (dlina <= 0)))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 14);
						listprint(lst);
						gotoxy(14, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Длина списка:"; gotoxy(30, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					lst = init(dlina, nach);
					listprint(lst);
				}
			}
			else if (amix == 1)
			{
				if (dlina == 0) {
					gotoxy(19, 1);
					printf("Список удален или еще не объявлен");
					n = getch();
				}
				else
				{
					gotoxy(0, 10);
					lst = DelList(lst);
					dlina = 0;
				}
			}
			else if (amix == 2)
			{
				if (dlina == 0) {
					gotoxy(21, 2);
					printf("Список удален или еще не объявлен");
					n = getch();
				}
				else if (dlina == 1000) {
					gotoxy(21, 2);
					printf("Список переполнен");
					n = getch();
				}
				else {
					gotoxy(1, 8);  cout << "Введите порядковый номер элемента после которого хотите добавить:"; gotoxy(69, 8);
					while (!(cin >> num) || (cin.peek() != '\n') || (num < 0) || (num > dlina))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(69, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Введите порядковый номер элемента после которого хотите добавить:"; gotoxy(85, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					listprint(lst);
					gotoxy(1, 8); cout << "Введите добавляемое число:"; gotoxy(28, 8);
					while (!(cin >> data) || (cin.peek() != '\n') || (data > 99999999999))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(28, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Введите добавляемое число:"; gotoxy(44, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					listprint(lst);
					gotoxy(1, 8); cout << "Введите кол-во добавлений:"; gotoxy(28, 8);
					while (!(cin >> dob) || (cin.peek() != '\n') || (dob + num > 1000) || (dob <= 0))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(28, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Введите кол-во добавлений:"; gotoxy(44, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);

					if (num == 0) {
						data = data + dob - 1;
						while (dob != 0) {
							lst = AddFirst(data, lst);
							dlina++;
							dob--;
							data--;
						}
					}
					else if (num == dlina) {

						while (dob != 0) {
							lst = AddLast(data, lst);
							dlina++;
							data++;

							dob--;
						}
					}
					else {
						data = data + dob - 1;
						while (dob != 1) {

							lst = Add(lst, data, num);
							dlina++;
							dob--;
							data--;
						}
						lst = Add(lst, data, num);
						dlina++;
					}
					listprint(lst);
				}
			}
			else if (amix == 3)
			{
				if (dlina == 0) {
					gotoxy(21, 3);
					printf("Список удален или еще не объявлен");
					n = getch();
				}
				else
				{
					gotoxy(1, 8); cout << "Введите порядковый номер удаляемого элемента:"; gotoxy(47, 8);
					while (!(cin >> del) || (cin.peek() != '\n') || (del > dlina) || (del <= 0))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(47, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Введите порядковый номер удаляемого элемента:"; gotoxy(63, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					listprint(lst);
					gotoxy(1, 8); cout << "Укажите кол-во удаляемых элементов:"; gotoxy(37, 8);


					while (!(cin >> del1) || (cin.peek() != '\n') || (del + del1 > dlina + 1) || (del1 <= 0))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(38, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Укажите кол-во удаляемых элементов:"; gotoxy(54, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					if (del == 1) {
						while (del1 != 0) {
							lst = DelFirst(lst);
							dlina--;
							del1--;
						}
					}
					else if (del == dlina) {
						lst = DelLast(lst);
						dlina--;
					}

					else {
						while (del1 != 0) {
							lst = Del(del, lst);
							dlina--;
							del1--;
						}
					}
					listprint(lst);
				}
			}
			else if (amix == 4)
			{
				if (dlina == 0) {
					gotoxy(21, 4);
					printf("Список удален или еще не объявлен");
					n = getch();
				}
				else
				{
					gotoxy(1, 8); cout << "Укажите номер элемента который хотите изменить:"; gotoxy(48, 8);
					while (!(cin >> Change1) || (cin.peek() != '\n') || (Change1 <= 0) || (Change1 > dlina))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(48, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Укажите номер элемента который хотите изменить:"; gotoxy(64, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					listprint(lst);
					gotoxy(1, 8); cout << "Введите изменяемое число:"; gotoxy(27, 8);
					while (!(cin >> Change2) || (cin.peek() != '\n') || (Change2 > 99999999999))
					{
						cin.clear();
						while (cin.get() != '\n');
						cls(hStdout);
						menu();
						gotoxy(0, 10);
						listprint(lst);
						gotoxy(27, 8); printf("Введите заново:");
						gotoxy(1, 8); cout << "Введите изменяемое число:"; gotoxy(43, 8);
					}
					cls(hStdout);
					menu();
					gotoxy(0, 10);
					if (Change1 == 1) {
						lst = ChangeFirst(lst, Change2);
					}
					else if (Change1 == dlina) {
						lst = ChangeLast(lst, Change2);
					}
					else {
						lst = Change(lst, Change2, Change1);
					}
					gotoxy(0, 10);
					listprint(lst);
				}
			}
			else if (amix == 5)
			{
				if (dlina == 0) {
					gotoxy(18, 5);
					printf("Список удален или еще не объявлен");
					n = getch();
				}
				else
				{
					gotoxy(0, 10);
					lst = Sort(lst);
					listprint(lst);
				}
			}
			else if (amix == 6)
			{
				_Exit(1);
				n = getch();
			}
			break;
		}
		if (ch == 49) { amix = 0; x1 = 8, x2 = x3 = x4 = x5 = x6 = x7 = 7; }
		else if (ch == 50) { amix = 1; x2 = 8, x1 = x3 = x4 = x5 = x6 = x7 = 7; }
		else if (ch == 51) { amix = 2; x3 = 8, x2 = x4 = x1 = x5 = x6 = x7 = 7; }
		else if (ch == 52) { amix = 3; x4 = 8, x3 = x5 = x1 = x2 = x6 = x7 = 7; }
		else if (ch == 53) { amix = 4; x5 = 8, x4 = x6 = x1 = x2 = x3 = x7 = 7; }
		else if (ch == 54) { amix = 5; x6 = 8, x5 = x7 = x1 = x2 = x3 = x4 = 7; }
		else if (ch == 55) { amix = 6; x7 = 8, x6 = x1 = x2 = x3 = x4 = x5 = 7; }
		if (amix < 0) amix = 6;
		if (amix > 6) amix = 0;
		if (amix == 0) { x1 = 8, x2 = x7 = 7; }
		else if (amix == 1) { x2 = 8, x1 = x3 = 7; }
		else if (amix == 2) { x3 = 8, x2 = x4 = 7; }
		else if (amix == 3) { x4 = 8, x3 = x5 = 7; }
		else if (amix == 4) { x5 = 8, x4 = x6 = 7; }
		else if (amix == 5) { x6 = 8, x5 = x7 = 7; }
		else if (amix == 6) { x7 = 8, x6 = x1 = 7; }
	}
	return 3;

}