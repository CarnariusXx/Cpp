#include<iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <bitset>
#include <string>
#include <sstream>
#include <math.h>
#include <time.h>
using namespace std;

bitset<8> bin(char b)
{
    return bitset<8>(b);
}

string crcxor( string operat , string wielomian)
{


	for ( int i = 0 ; i <= (operat.size() - wielomian.size()) ; )
	{
		for( int j=0 ; j < wielomian.size() ; j++)
		{
			operat[i+j] = operat[i+j] == wielomian[j] ? '0' : '1' ;
		}
	for( ; i< operat.size() && operat[i] != '1' ; i++) ;

	}

	return operat;
}

int main()
{
    streampos size;
    char* str;
    vector<char>mess;
    vector<int>bit;
    vector<int>bit2;
    vector<int>round1;
    vector<int>round2;

    string file_name;
    cout<<"Enter name of file: ";
    cin>>file_name;

    ifstream file(file_name+".txt", ios::in|ios::binary|ios::ate);
    if(file.is_open())
    {
        size = file.tellg();
        str = new char[size];
        file.seekg(0,ios::beg);
        file.read(str,size);
        file.close();

    }else{
        cout << "Can't open file, bye, bye" << endl;
        exit(1);
    }
    //cout << "Text from file: ";
    for(int i=0; i<size; i++)
    {
        //cout  << str[i];
        mess.push_back(str[i]);
    }
    cout <<"\n------------------------------------------Parity bit------------------------------------------\n";
   /// cout << endl << "Converted to bin: ";
    for( char b: mess)
    {
       bitset<8> binary=bin(b);
       for(int i=7; i>=0;i--)
       {
            ///cout << binary[i];
            bit.push_back(binary[i]);
            bit2.push_back(binary[i]);
            round1.push_back(binary[i]);
            round2.push_back(binary[i]);
       }

    }
    cout << endl;
    int s1=0;
    for(int i=0; i<round1.size(); i++)
    {
        s1=s1+round1[i];
    }

    if(s1 % 2==0) round1.push_back(0);
    else round1.push_back(1);

    cout <<"Parity bit: ";
    for(int i=0; i<round1.size(); i++)
    {
        cout << round1[i];
        round2.push_back(round1[i]);
    }
    cout <<"\n---------------------------------------------------------------------------------------\n";
    ofstream new_bit("After_first_round_PB.txt");
    string new_sbit1;
    for (int i = 0; i < round2.size(); ++i) {
    new_sbit1 += to_string(round2[i]);
    if (i+1 != round2.size()) {
        new_sbit1 += "";
    }
}
  string smessage;
      for (int i = 0; i < mess.size(); ++i) {
      smessage += mess[i];
      if (i+1 != mess.size()) {
          smessage += "";
      }
  }

    cout<<new_sbit1<<endl;
    new_bit<<new_sbit1;
    new_bit.close();
    cout<<"Enter the percentage of interferences: \n";
    int choice, p, randNum;
    cin>>choice;
    p=(new_sbit1.size()*choice)/100;
    srand (time(NULL));
    cout<<"Positions to change: "<< p <<endl;

    for(int i = 1; i <= p; i++)
    {
       int randNum = rand() % new_sbit1.size();
       cout<<randNum<<endl;
       new_sbit1[randNum]^=1;
       cout<<new_sbit1<<endl;
  }
    cout<<"After change: "<<new_sbit1<<endl;
    int s2=0;
    for(int i=0; i<new_sbit1.size(); i++)
    {
        s2=s2+new_sbit1[i];
    }
    if(s2 % 2==0) new_sbit1.push_back('0');
    else new_sbit1.push_back('1');
    cout <<"Parity bit2: ";
    for(int i=0; i<new_sbit1.size(); i++)
    {
        cout << new_sbit1[i];
    }
    ofstream bitfinal("Parity_bit_final.txt");
    bitfinal<<new_sbit1;
    bitfinal.close();
    cout <<"\n-------------------------------------------Modulo sum-----------------------------------------\n";
    int sum=0;
    for (int i = 0; smessage[i] != '\0'; i++)
         sum = sum + smessage[i];
    cout << "Sum of all characters : " << sum <<endl;
    cout << "Modulo sum : " << sum%128 <<endl;
    int x=(sum%128);
    cout <<"\n----------------------------------------------------------------------------------------\n";
    vector<int>modulo_res;
    modulo_res.push_back(x);
    vector<int>modulo_to_string;

    for( char b: modulo_res)
        {
        bitset<8> binary=bin(b);
        for(int i=7; i>=0;i--)
        {
            modulo_to_string.push_back(binary[i]);
        }

        }
    ofstream modulo_res_file("After_first_round_M.txt");
    string s_modulo_res;
    for (int i = 0; i < modulo_to_string.size(); ++i)
    {
        s_modulo_res += to_string(modulo_to_string[i]);
        if (i+1 != modulo_to_string.size())
      {
        s_modulo_res += "";
      }
    }
    string modulo_mess;
    for (int i = 0; i < bit.size(); ++i)
    {
        modulo_mess += to_string(bit[i]);
        if (i+1 != bit.size())
        {
            modulo_mess += "";
        }
    }
    string modulo_after_first_r=modulo_mess+s_modulo_res;
    modulo_res_file<<modulo_after_first_r<<endl;
    modulo_res_file.close();
    cout<<"After changes: "<<modulo_after_first_r<<endl;
    cout<<"\n----------------------------------------Modulo sum2----------------------------------------\n";
    cout<<"Enter the percentage of interferences: \n";
    int choice2, p2, randNum2;
    cin>>choice2;
    p2=(modulo_after_first_r.size()*choice2)/100;
    cout<<p2<<endl;
    for(int i = 1; i <= p2; i++)
    {
       int randNum2 = rand() % modulo_after_first_r.size();
       cout<<randNum2<<endl;
       modulo_after_first_r[randNum2]^=1;
       cout<<modulo_after_first_r<<endl;
    }
cout<<"--------------------------------\n";
cout<<"--------------------------------\n";

    stringstream sstream(modulo_after_first_r);
    string output;
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
    //cout <<output<<endl;
    int sum2=0;
    for (int i = 0; output[i] != '\0'; i++)
        sum2 = sum2 + output[i];
    cout << "Sum of all characters : " << sum2 <<endl;
    cout << "Modulo sum2 : " << sum2%128 <<endl;
    cout <<"\n---------------------------------------------CRC----------------------------------------------\n";
	string sbit2;
    for (int i = 0; i < bit2.size(); ++i)
    {
        sbit2 += to_string(bit2[i]);
        if (i+1 != bit2.size())
      {
        sbit2 += "";
      }
    }

	string wielomian , operat = "";
	cout<<"Enter Data bits: "<<endl;


	cout<<"Enter Generator: "<<endl;
	cin>>wielomian;

	operat += sbit2;

	int datalen = sbit2.size();


	for(int i=1 ; i <= (wielomian.size() - 1) ; i++)
		operat += '0';

	operat = crcxor(operat , wielomian);
	string odejm;
	odejm=operat.substr(operat.size() - wielomian.size() + 1);
	cout<<"Checksum generated is: ";
	cout<<odejm<<endl<<endl;

	vector<int>crc_res;

	string scrc_res;
    for (int i = 0; i < crc_res.size(); ++i)
    {
        scrc_res += to_string(crc_res[i]);
        if (i+1 != crc_res.size())
      {
        scrc_res += "";
      }
    }
    string crc_ress=sbit2+odejm;
	ofstream crc1("crc.txt");
	crc1<<crc_ress;
	crc1.close();

	cout<<"Enter the percentage of interferences: \n";
    int choice3, p3, randNum3;
    cin>>choice3;
    p3=(crc_ress.size()*choice3)/100;
    cout<<"Positions to change: "<< p3 <<endl;

    for(int i = 1; i <= p3; i++)
    {
       int randNum3 = rand() % crc_ress.size();
       cout<<"Pos: "<<randNum3<<endl;
       crc_ress[randNum3]^=1;
       cout<<crc_ress<<endl;
  }

  operat += crc_ress;

	int datalen2 = crc_ress.size();


	for(int i=1 ; i <= (wielomian.size() - 1) ; i++)
		operat += '0';

	operat = crcxor(operat , wielomian);
	string odejm2;
	odejm2=operat.substr(operat.size() - wielomian.size() + 1);
	cout<<"Checksum2 generated is: ";
	cout<<odejm2<<endl<<endl;


    return 0;
}
