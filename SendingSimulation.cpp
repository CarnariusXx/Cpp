#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Pakiet
{
	Pakiet(uint32_t index, uint32_t size);
	uint32_t index = 0;
	uint32_t size = 0;

	friend ostream& operator<<(ostream& os, Pakiet& obj);
};

Pakiet::Pakiet(uint32_t index, uint32_t size)
{
	this->index = index;
	this->size = size;
}

bool operator<(Pakiet const& x, Pakiet const& y)
{
	return x.index < y.index;
}

ostream& operator<<(ostream& os, Pakiet& obj)
{
	os.write((char*)& obj.index, sizeof(obj.index));
	os.write((char*)& obj.size, sizeof(obj.size));
	return os;
}
class Transfer
{
public:
	void odbior(const char*  plik_odb);
	void wysylka(const char* plik_wys, const char* wysylka_to, int rozmiar_max);

private:
	void zaw_pliku(bool type, int rozmiar_max = 0);
	void get_zaw_pliku(const char* nazawa_pliku);
	void set_zaw_pliku(const char* nazawa_pliku, int rozmiar_max = 0);

	vector<char> zawart;
	vector<Pakiet> PakietyV;
	vector<Pakiet*> WskV;
};
void Transfer::odbior(const char* plik_odb)
{
	get_zaw_pliku(plik_odb);
	zaw_pliku(1);

	sort(begin(WskV), end(WskV),
		[](Pakiet* const& x, Pakiet* const& y) -> bool { return x->index < y->index; });

	char* wsk;
	cout << "odbior message..." << endl;
	for (auto v : WskV)
	{
		cout << v->index << v->size << " | ";
		wsk = reinterpret_cast<char*>(v) + sizeof(Pakiet);
		for (int i = 0; i < v->size; i++)
		{
			cout << wsk[0];
			wsk++;
		}
		cout << endl;
	}
}

void Transfer::wysylka(const char* plik_wys, const char* wysylka_to, int rozmiar_max)
{
	get_zaw_pliku(plik_wys);
	zaw_pliku(0, rozmiar_max);
	cout << "Wiadomosc: \n";
	for (auto i = 0, j = 0; i < this->PakietyV.size(); i++)
	{
		cout << this->PakietyV[i].index << this->PakietyV[i].size << " | " ;
		for (auto k = j; k < this->PakietyV[i].size + j; k++)
			cout << zawart[k];
		cout << endl;
		j += this->PakietyV[i].size;
	}
	set_zaw_pliku(wysylka_to, rozmiar_max);
}

void Transfer::set_zaw_pliku(const char* nazawa_pliku, int rozmiar_max)
{
	ofstream out(nazawa_pliku, ios::out | ios::binary);
	if (out.is_open())
	{
		for (int i = zawart.size(); i >= 0; i -= rozmiar_max)
		{
			if (i / rozmiar_max >= PakietyV.size())
				continue;
			out << PakietyV[ i / rozmiar_max ];
			for (auto j = 0; j < PakietyV[i / rozmiar_max].size; j++)
			{
				out << zawart[j + (PakietyV[i / rozmiar_max].index * rozmiar_max)];
			}
		}
		out.close();
	}
}

void Transfer::zaw_pliku(bool type, int rozmiar_max)
{
	if (!this->PakietyV.empty())
		this->PakietyV.clear();
	switch (type)
	{
	case 0:
		PakietyV.reserve(zawart.size() / rozmiar_max);
		for (unsigned int i = 0; (i + rozmiar_max - 1) < zawart.size(); i += rozmiar_max)
		{
			PakietyV.emplace_back(Pakiet(i / rozmiar_max, rozmiar_max));
		}
		if (zawart.size() % rozmiar_max != 0)
			PakietyV.emplace_back(Pakiet(PakietyV.back().index + 1, zawart.size() % rozmiar_max));
		break;
	case 1:
		Pakiet * wsk;
		WskV.reserve(zawart.size() / (8 + rozmiar_max));
		wsk = reinterpret_cast<Pakiet*>(data(zawart));
		for (int i = 0, j = 0; i < zawart.size(); j++)
		{
			if(j)
				wsk = reinterpret_cast<Pakiet*>(reinterpret_cast<char*>(wsk) + sizeof(Pakiet) + wsk->size);
			WskV.push_back(wsk);
			i += sizeof(Pakiet) + WskV[j]->size;
		}
		break;
	}
}

void Transfer::get_zaw_pliku(const char* nazawa_pliku)
{
	if (!this->zawart.empty())
		this->zawart.clear();
	ifstream in(nazawa_pliku, ios::in | ios::binary);
	if (in)
	{
		in.seekg(0, ios::end);
		this->zawart.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&this->zawart[0], this->zawart.size());
		in.close();
		return;
	}
}


int main()
{
	Transfer test;
	int blok;
	cout<<"Podaj wielkosc bloku"<<endl;
	cin>>blok;
	test.wysylka("1.txt", "2.txt", blok);
	test.odbior("2.txt");
    cout<<endl;
	cout << "Rozmiar pakieteu: " << sizeof(Pakiet) << endl;
	return 0;
}


