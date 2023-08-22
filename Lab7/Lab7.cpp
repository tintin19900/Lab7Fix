#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}
void draw_ship(int x, int y)
{
	gotoxy(x, y); printf(" <-0-> ");
}
void draw_bullet(int x, int y)
{
	gotoxy(x, y); printf("^");
}
void clear_bullet(int x, int y)
{
	gotoxy(x, y); printf(" ");
}
void randomStar(int sx, int sy) {
		sx = rand() / 500;
		sy = rand() / 1000;
		while (sx < 10 || sx>70||cursor(sx,sy)=='*') {
			sx = rand()%100;
		}
		while (sy < 2 || sy>5 || cursor(sx, sy) == '*') {
			sy = rand() / 1000;
		}
		gotoxy(sx, sy);printf("*");
	}
void hitStar(int x, int y) {
	gotoxy(x, y); printf(" ");
	Beep(1000, 700);
}
int main()
{
	srand(time(NULL));
	char ch = '.';
	int x = 38, y = 20, sy=rand()/700, sx=rand()/700, counts = 20;
	int bx, by, i,score=0,xs=90,ys=2;
	int bullet = 0;
	draw_ship(x, y);
		do {
			while (counts != 0) {
				randomStar(sx, sy);
				counts--;
			}
			gotoxy(xs, ys);
			printf("Score = %d", score);
			if (_kbhit()) {
				ch = _getch();
				if (ch == 'a') { draw_ship(--x, y); }
				if (ch == 's') { draw_ship(++x, y); }
				if (bullet != 1 && ch == ' ') { bullet = 1; bx = x + 3; by = y - 1; }
				fflush(stdin);
			}
			if (bullet == 1) {

				clear_bullet(bx, by);
				if (by == 2) { bullet = 0; }
				else { 
					if (cursor(bx, by - 1) == '*') {
						hitStar( bx, by-1);
						counts++;
						score++;
						bullet = 0;
						clear_bullet(bx, by);
					}
					else {
						draw_bullet(bx, --by);
					}
				}

			}
			Sleep(100);
		} while (ch != 'x');
		return 0;
	}
