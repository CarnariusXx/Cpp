#include<iostream>
#include<math.h>
#include <conio.h>
#include <array>
#define ll long long
using namespace std;

ll modular_pow(ll base, ll exponent, int modulus)
{
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main()
{
    int a,b,pierw,p,q,n,m,x,y,t,pom,e,d;
    int *tab;
    cout << "Podaj miejsce szukanej 1st liczby pierwszej: "<< endl;;
    cin >> p;
    cout << endl;
    cout << "Podaj miejsce szukanej 2nd liczby pierwszej: "<< endl;;
    cin >> q;
    pierw=(int)sqrt((double)100000000);
tab = new int[100000000];
    for (a = 0; a <= 100000000; a++)
        tab[a] = a;

    for (a = 2; a <= pierw; a++)
    {
        if (tab[a] != 0)
            for (b = 2 * a; b <= 100000000; b += a)
                tab[b] = 0;
    }
    /*/
    cout << "Liczby pierwsze z przedzialu <2," << liczba << "> to:\n";
    for (a = 2; a <= liczba; a++)
    if (tablica[a] != 0)
    cout << tablica[a] << " ";
    cout << endl;
    /*/

    int temp = 0;

    for (unsigned long int a = 2; a < 100000000; a++) /// liczy na którym miejscu jest dana liczba pierwsza i przypisuje wartość jezeli znajdzie poszukiwaną liczbe
    {
        if (tab[a]) /// tzn. jeżeli różne od 0
        {
            temp++;
        }
        if (temp == p)
        {
            p = a; /// zapisuje indeks pod którym znajduje sie szukana liczba
            temp = 0;
            break;
        }
    }

    if (temp) /// tzn. jezeli jest liczbą inną niż 0
    {
        cout << "Nie znaleziono liczby pierwszej, za maly 100000000 liczb";
    }
    else
    {
        cout << "Szukana liczba pierwsza " << tab[p] << endl;
    }

     for (unsigned long int a = 2; a < 100000000; a++) /// liczy na którym miejscu jest dana liczba pierwsza i przypisuje wartość jezeli znajdzie poszukiwaną liczbe
    {
        if (tab[a]) /// tzn. jeżeli różne od 0
        {
            temp++;
        }
        if (temp == q)
        {
            q = a; /// zapisuje indeks pod którym znajduje sie szukana liczba
            temp = 0;
            break;
        }
    }

    if (temp) /// tzn. jezeli jest liczbą inną niż 0
    {
        cout << "Nie znaleziono liczby pierwszej, za maly 100000000 liczb";
    }
    else
    {
        cout << "Szukana liczba pierwsza " << tab[q] << endl;
    }

n=p*q;
m=(p-1)*(q-1);
cout<<"n: "<<n<<endl;
cout<<"m: "<<m<<endl;

cin >> e;
    //zachowanie pierwotnych wartosci
    int e0 = e, m0 = m;

    //Zapewnia spelnienie niezmiennika p*a0 + q*m0 = a oraz r*a0 + s*m0 = b
    int nx = 1, ny = 0, r = 0, s = 1;
    int c, quot, new_r, new_s;

    //algorytm
    while (m != 0)
        {
        c = e % m;
        quot = (e/m);
        e = m;
        m = c;
        new_r = nx - quot * r;
        new_s = nx - quot * s;
        nx = r; ny = s;
        r = new_r; s = new_s;
    }
    cout << "NWD(a,b) = e * x + m * y\n"
        << "NWD(" << e0 << "," << m0 << ") = "
        << e0 << " * " << nx << " + "
        <<  m0 << " * " << ny << '\n';
        d=e*nx+m*ny;
        cin>>t;


   // int mod;
    cout<<"Enter Base Value: ";
    //cin>>t;
    cout<<"Enter Exponent: ";
   //cin>>e;
    cout<<"Enter Modular Value: ";
    //cin>>mod;
    cout<<q<<" "<<p<<" "<<e<<" "<<t<<""<<n<<endl;
    cout<<modular_pow(t, e , p*q);
    return 0;

}
