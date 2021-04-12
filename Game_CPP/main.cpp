#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <list>
#include <thread>

using namespace sf;
using namespace std;

const int szer=1366;
const int wys=768;
float prom=0.017453f;

class animacje
{
public:
    float Frame, v;
    Sprite sprite;
    vector<IntRect> frames;

    animacje(){}
    animacje(Texture &t, int x, int y, int szer, int wys, int count, float V)
    {
        Frame=0;
        V=v;

        for (int i=0;i<count;i++)
            frames.push_back(IntRect(x+i*szer,y,szer, wys));

        sprite.setTexture(t);
        sprite.setOrigin(szer/2,wys/2);
        sprite.setTextureRect(frames[0]);
    }
    void update()
    {
     Frame+= v;
     int n=frames.size();
     if (Frame >= n) Frame -=n;
     if(n>0) sprite.setTextureRect(frames[int(Frame)]);
    }


};

class przeszkoda
{
public:
    float x,y,dx,dy,R,angle;
    bool life;
    string name;
    animacje anim;

    przeszkoda() {life=1;}

    void wymiary(animacje &a, int X, int Y, float Angle=0, int r=1)
    {
        x=X;
        y=Y;
        anim=a;
        angle=Angle; R=r;
    }
    virtual void update(){};

    void draw (RenderWindow &proj)
    {
        anim.sprite.setPosition(x,y);
        anim.sprite.setRotation(angle+90);
        proj.draw(anim.sprite);
    }

};

class glaz: public przeszkoda
{
public:
    glaz()
    {
        dx=rand()%8-4;
        dy=rand()%8-4;
        name="glaz";
    }
    void update()
    {
        x+=dx;
        y+=dy;
        if (x>szer) x=0; if (x<0) x=szer;
        if (y>wys) y=0; if (y<0) y=wys;
    }
};

class laser: public przeszkoda
{
public:
    laser()
    {
        name="laser";
    }

    void update()
    {
        dx=cos(angle*prom)*6;
        dy=sin(angle*prom)*6;
        x+=dx;
        y+=dy;
        if(x>szer || x<0 || y>wys ||y<0) life=0;
    }
};

class gracz: public przeszkoda
{
public:

    bool temp;

 gracz()
{
    name="gracz";
}

void update()
{
    if (temp)
      { dx+=cos(angle*prom)*0.2;
        dy+=sin(angle*prom)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int vmax=15;
    float v = sqrt(dx*dx+dy*dy);
    if (v>vmax)
     { dx *= vmax/v;
       dy *= vmax/v; }

    x+=dx;
    y+=dy;

    if (x>szer) x=0; if (x<0) x=szer;
    if (y>wys) y=0; if (y<0) y=wys;
   }
};

bool kolizja(przeszkoda *a, przeszkoda *b)
{
    return(b->x - a->x)*(b->x -a->x)+(b->y -a->y)*(b->y -a->y)<(a->R + b->R)*(a->R + b->R);
}
void muzyczka(){
PlaySound("1.wav", NULL, SND_FILENAME|SND_LOOP);
}
int main()
{
  thread t(muzyczka);
  RenderWindow proj(VideoMode(szer,wys),"Projekcik");
  proj.setFramerateLimit(60);


  Texture tlo,gracz,rock,pocisk,krem,kam,krem2;
  tlo.loadFromFile("tekstury/back.jpg");
  gracz.loadFromFile("tekstury/s5.png");
  rock.loadFromFile("tekstury/ro.png");
  pocisk.loadFromFile("tekstury/2.png");
  krem.loadFromFile("tekstury/krem1.png");
  kam.loadFromFile("tekstury/kamyk_maly.png");
  krem2.loadFromFile("tekstury/krem222.png");

  animacje sPocisk(pocisk, 0,0,32,64,16,0.8);

  Sprite sTlo(tlo), sGracz(gracz);
  sGracz.setTextureRect(IntRect(40,0,40,40));
  sGracz.setOrigin(20,20);

  float Frame=0;
  float pranimacji = 0.4;
  int framecount = 20;

  animacje sRock(rock, 0,0,64,64, 26, 0.2);
  sRock.sprite.setPosition(400,400);
  animacje skrem(krem, 0,0,64,64, 26, 0.4);
  skrem.sprite.setPosition(400,400);
  animacje sRock_small(kam,0,0,64,64, 26, 0.4);
  sRock_small.sprite.setPosition(400,400);
  animacje skrem_small(krem2,0,0,64,64, 26, 0.4);
  skrem_small.sprite.setPosition(400,400);

  list<przeszkoda*> przeszkody;

  for(int i=0;i<15;i++)
  {
      glaz *a = new glaz();
      a->wymiary(sRock, rand()%szer, rand()%wys, rand()%360, 25);
      przeszkody.push_back(a);

  }
  for(int i=0;i<15;i++)
  {
      glaz *k = new glaz();
      k->wymiary(skrem, rand()%szer, rand()%wys, rand()%360, 25);
      przeszkody.push_back(k);
  }

  float x=300, y=300;
  float dx=0,dy=0,angle=0;
  bool temp;

  while (proj.isOpen())
  {
      Event event;
      while (proj.pollEvent(event))
      {
          if (event.type == Event::Closed)
            proj.close();

           if (event.type ==Event::KeyPressed)
            if(event.key.code==Keyboard::Space)
           {
               laser *p = new laser();
               p->wymiary(sPocisk,x,y,angle,10);
               przeszkody.push_back(p);
           }
      }

    Frame+=pranimacji;
    if (Frame>framecount) Frame-=framecount;

    if (Keyboard::isKeyPressed(Keyboard::D)) angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::A)) angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::W)) temp=true;
    else temp=false;

    for(auto a:przeszkody)
    for(auto b:przeszkody)
        if(a->name=="glaz" && b->name=="laser")
        if(kolizja(a,b))
           {

            a->life=false;
            b->life=false;
            przeszkoda *e = new przeszkoda();
            przeszkody.push_back(e);

            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             przeszkoda *e = new glaz();
             e->wymiary(sRock_small,a->x,a->y,rand()%360,15);
             przeszkody.push_back(e);

            }
            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             przeszkoda *k = new glaz();
             k->wymiary(skrem_small,a->x,a->y,rand()%360,15);
             przeszkody.push_back(k);

            }

           }

    if (temp)
    { dx+=cos(angle*prom)*0.2;
      dy+=sin(angle*prom)*0.2;}
    else
    { dx*=0.99;
      dy*=0.99;}

    int vmax=15;

    float v=sqrt(dx*dx+dy*dy);
    if (v>vmax)
    { dx*=vmax/v;
      dy*=vmax/v;}

    x+=dx;
    y+=dy;

    if (x>szer) x=0; if(x<0) x=szer;
    if (y>wys) y=0; if (y<0) y=wys;

    sGracz.setPosition(x,y);
    sGracz.setRotation(angle+90);

    for(auto i=przeszkody.begin(); i!=przeszkody.end();)
    {
        przeszkoda *e=*i;
        e->update();
        e->anim.update();

        if (e->life==false) {i=przeszkody.erase(i); delete e;}
        else i++;
    }
      sRock.update();
      proj.clear();
      proj.draw(sTlo);
      proj.draw(sGracz);
      for(auto i:przeszkody) i->draw(proj);
      proj.display();


  }
t.join();
    return 0;
}
