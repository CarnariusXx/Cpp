#include <iostream>


#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

typedef unsigned long long ulong;

// 64 bitowy generator pseudolosowy
//---------------------------------
ulong Losuj(ulong a,ulong b)
{
  ulong w;
  int i;

  for(i = 1; i <= 8; i++)
  {
    w <<= 8;
    w &= rand() % 256;
  }
  return a + (w % (b - a));
}

// Funkcja oblicza NWD
//--------------------
ulong NWD(ulong a, ulong b)
{
  ulong t;

  while(b)
  {
    t = b; b = a % b; a = t;
  }
  return a;
}

// Funkcja mnoży a i b mod n
//--------------------------
ulong MnozModulo(ulong a, ulong b, ulong n)
{
  ulong m,w;

  w = 0;
  for(m = 1; m; m <<= 1)
  {
    if(b & m) w = (w + a) % n;
    a = (a << 1) % n;
  }
  return w;
}

// Funkcja oblicza a^e mod n
//--------------------------
ulong PotegujModulo(ulong a, ulong e, ulong n)
{
  ulong m,p,w;

  p = a; w = 1;
  for(m = 1; m; m <<= 1)
  {
    if(e & m) w = MnozModulo(w,p,n);
    p = MnozModulo(p,p,n);
  }
  return w;
}

// Tablica początkowych 169 liczb pierwszych
//------------------------------------------
const ulong lp[] = {
  2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
 71, 73, 79, 83, 89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,
167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,
271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,
389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,
631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,
757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,
883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009};

int main()
{
  ulong p,a;
  int   i;
  bool  t;

  srand((unsigned)time(NULL));
  cin >> p;
  t = true;
  for(i = 0; i < 169; i++)
    if((p != lp[i]) && (p % lp[i] == 0))
    {
      t = false; break;
    }
  if(t && (p > 1009))
  {
    for(i = 1; i <= 10; i++)
    {
      a = Losuj(2,p-1);
      if((NWD(p,a) != 1) || (PotegujModulo(a,p-1,p) != 1))
      {
        t = false; break;
      }
    }
  }
  cout << (t ? "TAK" : "NIE") << endl;
  return 0;
}

/*/
using namespace std;

int alg_szyb_pot_mod(int a, int b, int m) {
	int w = a;
	for (int i = 1; i < b; i++)
		w = (w * a) % m;
	return w;
}

int main() {
	int a, b, m;
	cout << "\t\t\t\t(a^b)mod c"<<endl;
	cout << "a= ";
	cin >> a;
	cout << "b= ";
	cin >> b;
	cout << "mod= ";
	cin >> m;
	cout << a << "^" << b << " mod m = ";
	cout << alg_szyb_pot_mod(a, b, m) << endl;
	return 0;
}
/*/
