#include <iostream>
using namespace std;
const int N = 3, M = 4;
class s_fract {
	friend bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f);
protected:
	int a, b;
public:
	s_fract(int x, int y);
	void print();
	void sum(s_fract fr1, s_fract fr2);
	void diff(s_fract fr1, s_fract fr2);
	void mult(s_fract fr1, s_fract fr2);
	void div(s_fract fr1, s_fract fr2);
	void red();
	bool eq0();
};
s_fract::s_fract(int x = 0, int y = 1)
{
	if (y > 0)
	{
		a = x;
		b = y;
		red();
	}
	else if (y < 0)
	{
		a = -x;
		b = -y;
		red();
	}
	else
	{
		a = 0;
		b = 0;
	}
}
void s_fract::print()
{
	if ((b != 0) && (b != 1))
		cout << a << "/" << b;
	else if ((b != 0) && (b == 1))
		cout << a;
	else
		cout << INFINITY;
}
void s_fract::sum(s_fract fr1, s_fract fr2)
{
	s_fract obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	if (fr1.b < fr2.b)
	{
		obm = fr1;
		fr1 = fr2;
		fr2 = obm;
	}

	if (fr1.b == fr2.b)
	{
		a = fr1.a + fr2.a;
		b = fr1.b;
	}
	else if (fr1.b % fr2.b != 0)
	{
		a = fr1.a * fr2.b + fr2.a * fr1.b;
		b = fr1.b * fr2.b;
	}
	else if (fr1.b % fr2.b == 0)
	{
		a = fr1.a + fr2.a * (fr1.b / fr2.b);
		b = fr1.b;
	}
	if (eq0())
		b = 1;
	red();
}
void s_fract::diff(s_fract fr1, s_fract fr2)
{
	fr2.a *= -1;
	sum(fr1, fr2);
}
void s_fract::mult(s_fract fr1, s_fract fr2)
{
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	a = fr1.a * fr2.a;
	b = fr1.b * fr2.b;
	if (eq0())
		b = 1;
	red();
}
void s_fract::div(s_fract fr1, s_fract fr2)
{
	int obm;
	if ((fr1.b == 0) || (fr2.b == 0))
		return;
	obm = fr2.a;
	fr2.a = fr2.b;
	fr2.b = obm;
	if (fr2.b < 0)
	{
		fr2.a *= -1;
		fr2.b *= -1;
	}
	mult(fr1, fr2);
}
void s_fract::red()
{
	int x, y, obm;
	if ((a == 0) || (b == 0))
		return;
	for (x = abs(a), y = abs(b); x != y; y -= x)
	{
		if (x > y)
		{
			obm = x;
			x = y;
			y = obm;
		}
	}
	a /= x;
	b /= x;
}
bool s_fract::eq0()
{
	if ((a == 0) && (b != 0))
		return true;
	else
		return false;
}



bool fr1_gr_fr2(s_fract fr1, s_fract fr2, bool f = false)
{
	int t;
	if ((fr1.b == 0) || (fr2.b == 0))
		return false;

	if (f)
	{
		fr1.a = abs(fr1.a);
		fr2.a = abs(fr2.a);
	}

	if (((fr1.b > fr2.b) && (fr1.b % fr2.b != 0)) || ((fr1.b <= fr2.b) && (fr2.b % fr1.b != 0)))
	{
		t = fr1.b;
		fr1.a *= fr2.b;
		fr1.b *= fr2.b;
		fr2.a *= t;
		fr2.b *= t;
	}
	else if ((fr1.b > fr2.b) && (fr1.b % fr2.b == 0))
	{
		fr2.a *= (fr1.b / fr2.b);
		fr2.b = fr1.b;
	}
	else if ((fr1.b <= fr2.b) && (fr2.b % fr1.b == 0))
	{
		fr1.a *= (fr2.b / fr1.b);
		fr1.b = fr2.b;
	}

	if (fr1.a > fr2.a)
		return true;
	else
		return false;
}

void print_m(s_fract A[N][M + 1])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= M; j++)
		{
			cout << "\t";
			A[i][j].print();
		}
		cout << endl;
	}
}



int fact(int a)
{
	int i, res = 1;
	for (i = 1; i <= a; i++)
		res *= i;
	return res;
}

int soch(int C[M], int r)
{
	int i, j;
	for (i = r - 1; i >= 0; i--)
	{
		if (C[i] < M - r + i + 1)
		{
			C[i]++;
			for (j = i + 1; j < r; j++)
				C[j] = C[j - 1] + 1;
			return 1;
		}
	}
	return 0;
}

/*int baz_res(s_fract A[N][M + 1], int C[M], int r, s_fract res[M])
{
	int i, j, k;
	for (i = 0, j = 0; (i < M) && (j < r); i++)
	{
		if (C[j] - 1 == i)
		{
			for (k = 0; k < r; k++)
			{
				if ((k != j) && !A[k][i].eq0())
					break;
			}
			if (k != r)
			{
				cout << " Нет базисного решения.";
				return 0;
			}
			res[i] = A[j++][M];
		}
		else
			res[i] = 0;
	}
	return 1;
}*/
void baz(s_fract A[N][M + 1], int C[M], int r)
{
	int i, j, j2, k, i2, i_l = -1;
	s_fract B[N][M + 1], t, t2, res[M];
	for (i = 0; i < N; i++)
	{
		for (j = 0; j <= M; j++)
			B[i][j] = A[i][j];
	}
	for (i = 0; i < r; i++)
	{
		j2 = C[i] - 1;
		for (j = 0, k = 0; j < r; j++)
		{
			if (!B[j][j2].eq0())
			{
				i2 = j;
				k++;
			}
		}

		t = B[i2][j2];
		if (t.eq0())
		{
			cout << " Нет базисного решения.";
			return;
		}
		if (k > 1)
		{
			print_m(B);
			for (j = 0; j <= M; j++)
				B[i2][j].div(B[i2][j], t);
			cout << "\n (1 в диагонали)\n ~";
			print_m(B);

			for (j = 0; j < N; j++)
			{
				if ((r - 1 == j) || (B[j][j2].eq0()))
					continue;
				t.diff(s_fract(0), B[j][j2]);
				for (k = 0; k <= M; k++)
				{
					t2.mult(t, B[r - 1][k]);
					B[j][k].sum(B[j][k], t2);
				}
			}
			cout << "\n (нули)\n ~";
			print_m(B);
		}
		else if ((i_l != -1) && (i2 == i_l))
		{
			cout << " Нет базисного решения.";
			return;
		}
		res[j2] = B[i][M];
		i_l = i2;
	}

	/*if (C[r - 1] > r)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j <= M; j++)
				B[i][j] = A[i][j];
		}

		for (i = r - 1; i >= 0; i--)
		{
			if (C[i] > r)
			{
				j2 = C[i] - 1;
				break;
			}
		}
		print_m(B);

		t = B[r - 1][j2];
		for (i = 0; i <= M; i++)
			B[r - 1][i].div(B[r - 1][i], t);
		cout << "\n (1 в диагонали)\n ~";
		print_m(B);

		for (i = 0; i < N; i++)
		{
			if ((r - 1 == i) || (B[i][j2].eq0()))
				continue;
			t.diff(s_fract(0), B[i][j2]);
			for (j = 0; j <= M; j++)
			{
				t2.mult(t, B[r - 1][j]);
				B[i][j].sum(B[i][j], t2);
			}
		}
		cout << "\n (нули)\n ~";
		print_m(B);
		if (!baz_res(B, C, r, res))
			return;
	}
	else
	{
		print_m(A);
		if (!baz_res(A, C, r, res))
			return;
	}*/
	cout << " Базисное решение: (";
	for (i = 0; i < M; i++)
	{
		cout << " ";
		res[i].print();
	}
	cout << " )";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	bool fl;
	int i, j, k, j2, r = 0, C[M];
	s_fract A[N][M + 1] =
	{
		/*s_fract(1), s_fract(1), s_fract(0), s_fract(0),
		s_fract(0), s_fract(1), s_fract(1), s_fract(0),
		s_fract(0), s_fract(0), s_fract(0), s_fract(0),

		s_fract(2), s_fract(-3), s_fract(5), s_fract(7), s_fract(1),
		s_fract(4), s_fract(-6), s_fract(2), s_fract(3), s_fract(2),
		s_fract(2), s_fract(-3), s_fract(-11), s_fract(-15), s_fract(1),

		s_fract(1), s_fract(3), s_fract(0), s_fract(1),
		s_fract(2), s_fract(0), s_fract(-3), s_fract(2),

		s_fract(2), s_fract(-1), s_fract(1), s_fract(2), s_fract(3), s_fract(2),
		s_fract(6), s_fract(-3), s_fract(2), s_fract(4), s_fract(5), s_fract(3),
		s_fract(6), s_fract(-3), s_fract(4), s_fract(8), s_fract(13), s_fract(9),
		s_fract(4), s_fract(-2), s_fract(1), s_fract(1), s_fract(2), s_fract(1),

		s_fract(2), s_fract(-1), s_fract(1), s_fract(-1), s_fract(3),
		s_fract(2), s_fract(-1), s_fract(0), s_fract(1), s_fract(2),
		s_fract(3), s_fract(0), s_fract(-1), s_fract(-1), s_fract(-1),*/

		//s_fract(1), s_fract(1), s_fract(1), s_fract(1),			// 1
		//s_fract(0), s_fract(0), s_fract(3), s_fract(2),
		//s_fract(0), s_fract(1), s_fract(4), s_fract(3),

		//s_fract(1), s_fract(4), s_fract(0), s_fract(2), s_fract(1),			// 2
		//s_fract(0), s_fract(0), s_fract(1), s_fract(1), s_fract(2),
		//s_fract(1), s_fract(0), s_fract(1), s_fract(2), s_fract(3),

		s_fract(1), s_fract(4), s_fract(0), s_fract(2), s_fract(1),			// 3
		s_fract(0), s_fract(0), s_fract(1), s_fract(1), s_fract(2),
		s_fract(0), s_fract(0), s_fract(1), s_fract(5), s_fract(3),

		//s_fract(5), s_fract(-16), s_fract(8), s_fract(-9), s_fract(8), s_fract(1),			// 4
		//s_fract(12), s_fract(-11), s_fract(23), s_fract(-26), s_fract(2), s_fract(10),
		//s_fract(11), s_fract(17), s_fract(9), s_fract(5), s_fract(-3), s_fract(20),
		//s_fract(31), s_fract(30), s_fract(20), s_fract(23), s_fract(5), s_fract(52),
	}, t, t2;
	for (i = 0; i < M; i++)
		C[i] = i + 1;
	print_m(A);

	for (i = 0; i < N; i++)
	{
		//cout << "\n " << i << " строка:";

		fl = false;
		for (j2 = i; j2 < M; j2++)
		{
			for (j = i; j < N; j++)
			{
				if (!A[j][j2].eq0())
				{
					fl = true;
					break;
				}
			}
			if (fl)
				break;
		}
		if (j2 == M)
		{
			if (!A[i][M].eq0())
			{
				cout << "\n______________________\n Решений нет.";
				return 0;
			}
		}

		for (j = i + 1, k = i; j < N; j++)
		{
			if (fr1_gr_fr2(A[j][j2], A[k][j2], true))
				k = j;
		}
		if (k != i)
		{
			for (j = 0; j <= M; j++)
			{
				t = A[i][j];
				A[i][j] = A[k][j];
				A[k][j] = t;
			}
			//cout << "\n (обмен строк)\n ~";
			//print_m(A);
		}

		t = A[i][j2];
		for (j = 0; j <= M; j++)
			A[i][j].div(A[i][j], t);
		//cout << "\n (1 в диагонали)\n ~";
		//print_m(A);

		for (j = 0; j < N; j++)
		{
			if ((i == j) || (A[j][j2].eq0()))
				continue;
			t.diff(s_fract(0), A[j][j2]);
			for (k = 0; k <= M; k++)
			{
				t2.mult(t, A[i][k]);
				A[j][k].sum(A[j][k], t2);
			}
		}
		//cout << "\n (нули)\n ~";
		//print_m(A);
	}

	cout << "\n 1 в диагонали:\n";
	print_m(A);



	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (!A[i][j].eq0())
			{
				r++;
				break;
			}
		}
	}
	cout << " r = " << r << "\n C(" << M << ", " << r << ") = " << fact(M) / (fact(r) * fact(M - r));
	i = 1;
	do
	{
		cout << "\n______________________\n " << i++ << ")";
		for (j = 0; j < r; j++)
			cout << " x" << C[j] - 1;
		cout << endl;
		baz(A, C, r);
	} while (soch(C, r));
	return 0;
}