#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

using namespace std;

int alg_szyb_pot_mod(int a, int b, int m) {
	int w = a;
	for (int i = 1; i < b; i++)
		w = (w * a) % m;
	return w;
}

vector<int> operator+(vector<int> lew_str, vector<int> praw_str)
{
	lew_str.insert(lew_str.end(), praw_str.begin(), praw_str.end());
	return lew_str;
}
vector<int>Fermat2(int a)
{
	int y = 0;
    int x = static_cast<int>(sqrt(a));
	if (x == sqrt(a))
	{
		return vector<int>{x};
	}
	x++;
	while(x<(a + 1)/2)
	{
		y = x*x-a;
		if (y > 0 && (static_cast<int>(sqrt(y)) == sqrt(y)))
		{
			y = static_cast<int>(sqrt(y));
			return Fermat2(x - y) + Fermat2(x + y);
		}
		x++;
	}
	return vector<int>{a};
}
vector<int>Fermat(int a)
{
	vector<int>wynik;
	bool check = 1;
	while (!((a>>0)&1))
	{
		for (auto test : wynik)
		{
			if (test == 2)
				check = 0;
		}
		if (check)
			wynik.emplace_back(2); /// push
		a = a >> 1;
	}
	wynik = wynik + Fermat2(a);
	sort(wynik.begin(), wynik.end());
	wynik.erase(unique(wynik.begin(), wynik.end()), wynik.end());
	return wynik;
}


int main()
{
    int a,b,m,n,q,wynik;
	bool check = 1;
	cout << "(a^b)mod(c)"<<endl;
	cout << "a= ";
	cin >> a;
	cout << "b= ";
	cin >> b;
	cout << "mod= ";
	cin >> m;
	cout << a << "^" << b << " mod m = ";
	cout << alg_szyb_pot_mod(a, b, m) << endl;
    cout << "-----------Fermat:-----------"<< endl;
	cout << "a: ";
	cin >> n;
	for (auto i : Fermat(n))
	{
		cout << i << endl;
	}
    cout << "-----------Lucas:-----------"<< endl;
	cout << "n: ";
	cin >> n;
	cout << "q: ";
	cin >> q;
    cout <<alg_szyb_pot_mod(a, n-1, n)<<endl;
	for (auto i : Fermat(n - 1))
	{
        wynik=alg_szyb_pot_mod(q, (n-1)/i, n);
		cout << wynik << endl;
		if (wynik == 1) check = 0;
	}
	if (check)
		cout << n << " jest liczba pierwsza" << endl;
	else
		cout << "Test nie rozstrzyga" << endl;
	return 0;
}
