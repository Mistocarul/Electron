#include <iostream>
#include <fstream>
#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <cstring>
#include <winbgim.h>
#include <windows.h>
#define  NMAX 40

using namespace std;

struct punct_legatura
{
    int x,y;
};
struct componenta
{
    char nume_fisier[NMAX];
    char nume_componenta[NMAX];
    int x,y;
    int nrLegaturi;
    char comanda_desen;
    punct_legatura pLeg[3];
    double constanta;
} piese[10];

struct componente_aflate_schita
{
    int x,y;
    punct_legatura pleg[3];
    char comanda_desen;
    double constanta=0;

} componente_desen[NMAX];

struct legatura
{
    componente_aflate_schita piesa1,piesa2;
    int x1,y1,x2,y2;
} legaturi_aflate_shita[NMAX*10];

int contor_piese,contor_legaturi;
char fisier_de_salvare[NMAX];
bool verificare;

void deseneaza_meniul(int fereastra);
void deseneaza_schema_noua(int fereastra);
void deseneaza_informatii_1(int fereastra);
void deseneaza_informatii_2(int fereastra);
void initializeaza_nume_fisier();
void initializeaza(componenta &P);
void deseneaza_piesa(componenta &P,int culoare,double constanta);
void sursa_alimentare(componenta &P,double constanta);
void rezistenta(componenta &P,double constanta);
void bec(componenta &P, double constanta);
void dioda(componenta &P, double constanta);
void ampermetru(componenta &P,double constanta);
void voltmetru(componenta &P,double constanta);
void condensator(componenta &P,double constanta);
void siguranta(componenta &P,double constanta);
void tranzistor(componenta &P,double constanta);
void amplaseaza(int x,int y);
void deseneaza_legatura(int piesa1, int pleg_piesa1, int piesa2, int pleg_piesa2);
void deseneaza_linie(int x1,int y1,int x2,int y2, int culoare);
int afla_piesa (char comanda);
void repara_desen();
void alege_componenta();
void afla_legaturile_output(int parametrul_piesei,int vec_output[]);
void afla_legaturile_input(int parametrul_piesei,int vec_input[]);
void dreptunghi_componenta_aleasa(int x,int y,int culoare,double constanta);
void muta_componenta(componenta &P,int parametrul_piesei);
void sterge_piesa (componenta &P, int parametru_piesei, double constanta);
void afla_legaturile_output(int parametrul_piesei,int vec_output[]);
void salvare_ca(int fereastra);
void salvare_informatii();
void deschide_schema(int fereastra);
void decripteaza_informatii(int fereastra);
void sterge_informatiile();
void sigur_inapoi_la_meniu (int fereastra);
void informatii (int fereastra);

int main()
{
    int fereastra=initwindow(1400,700,"Electron");
    deseneaza_meniul(fereastra);
    getch();
    closegraph( );

}
void deseneaza_meniul(int fereastra)
{
    setbkcolor(BLACK);
    cleardevice();
    sterge_informatiile();
    while (1)
    {
        int x=getmaxx()/2;
        int y=getmaxy()/4.5;
        int fontul=8;
        int directia=0;
        int marime_font=7;
        settextstyle(fontul, directia, marime_font);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(x,y,"ELECTRON");
        verificare=false;
        int x1=getmaxx()/8.7;
        int y1=getmaxy()/1.4;
        rectangle(x1,y1,x1+300,y1+70);
        fontul=8;
        directia=0;
        marime_font=5;
        settextstyle(fontul, directia, marime_font);
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        outtextxy(x1+10,y1+50,"SCHEMA NOUA");
        int x2=x1+350;
        int y2=getmaxy()/1.4;
        rectangle(x2,y2,x2+410,y2+70);
        outtextxy(x2+10,y2+50,"DESCHIDE SCHEMA");
        int x3=x2+460;
        int y3=getmaxy()/1.4;
        rectangle(x3,y3,x3+275,y3+70);
        outtextxy(x3+10,y3+50,"INFORMATII");
        int x4=1345;
        int y4=33;
        rectangle(1285,-1,1400,50);
        settextstyle(fontul, directia, marime_font);
        settextjustify(CENTER_TEXT,CENTER_TEXT);
        outtextxy(x4,y4,"EXIT");
        for(int i=0; i<=500; i++)
        {
            x=rand()%getmaxx();
            y=rand()%getmaxy();
            putpixel(x,y,15);
        }
        delay(500);
        int x_exit=0,y_exit=0;
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit>=1285&&x_exit<=1400&&y_exit>=0&&y_exit<=50)
            exit(1);
        if (x_exit>=x1&&x_exit<=x1+300&&y_exit>=y1&&y_exit<=y1+70)
            deseneaza_schema_noua(fereastra);
        if (x_exit>=x3&&x_exit<=x3+375&&y_exit>=y3&&y_exit<=y3+70)
            deseneaza_informatii_1(fereastra);
        if (x_exit>=x2&&x_exit<=x2+410&&y_exit>=y2&&y_exit<=y2+70)
            deschide_schema(fereastra);
        cleardevice();

    }
}
void deseneaza_schema_noua(int fereastra)
{
    componenta piesa;
    setbkcolor(BLACK);
    cleardevice();
    if (verificare==1)
    {
        for (int i=1; i<=contor_piese; i++)
        {
            piesa.x=componente_desen[i].x;
            piesa.y=componente_desen[i].y;
            piesa.comanda_desen=componente_desen[i].comanda_desen;
            deseneaza_piesa(piesa,0,componente_desen[i].constanta);
        }
        for (int i=1; i<=contor_legaturi; i++)
            deseneaza_linie(legaturi_aflate_shita[i].x1,legaturi_aflate_shita[i].y1,legaturi_aflate_shita[i].x2,legaturi_aflate_shita[i].y2,0);
    }
    initializeaza_nume_fisier();
    int i,nr_piese=9,c=55;
    for (i=1; i<=nr_piese; i++)
        initializeaza(piese[i]);
    rectangle(1300,100,1400,595);
    rectangle(210,100,1250,595);
    for(i=1; i<=9; i++)
    {
        line(1300,100+c,1400,100+c);
        deseneaza_piesa(piese[i],0,1);
        c=c+55;
    }
    int fontul=8;
    int directia=0;
    int marime_font=5;
    int x_exit=0,y_exit=0;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(fontul, directia, marime_font);
    rectangle(-1,-1,160,50);
    outtextxy(80,30,"INAPOI");
    rectangle(210,-1,510,50);
    outtextxy(360,30,"ALEGE PIESA");
    fontul=8;
    directia=0;
    marime_font=3;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(fontul, directia, marime_font);
    rectangle(-1,100,160,150);
    outtextxy(80,130,"SALVARE");
    rectangle(-1,150,160,200);
    outtextxy(80,180,"SALVARE CA");
    rectangle(-1,200,160,250);
    outtextxy(80,230,"INFORMATII");
    fontul=8;
    directia=0;
    marime_font=5;
    int piesa1,pleg_piesa1,piesa2,pleg_piesa2;
    while (1)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if(x_exit>=1300&&x_exit<=1400&&y_exit>=100&&y_exit<=595)
            amplaseaza(x_exit,y_exit);
        else
        {
            if(x_exit!=-1&&y_exit!=-1&&(x_exit>=210&&x_exit<=1250&&y_exit>=100&&y_exit<=595)&&contor_piese>=2)
                deseneaza_legatura(piesa1,pleg_piesa1,piesa2,pleg_piesa2);
            else if (x_exit>=0&&x_exit<=160&&y_exit>=0&&y_exit<=50&&verificare==0&&contor_piese!=0)
                sigur_inapoi_la_meniu(fereastra);
            else if(x_exit>=0&&x_exit<=160&&y_exit>=0&&y_exit<=50&&contor_piese==0)
                deseneaza_meniul(fereastra);
            else if (x_exit>=0&&x_exit<=160&&y_exit>=0&&y_exit<=50&&verificare==1&&contor_piese!=0)
            {
                salvare_informatii();
                deseneaza_meniul(fereastra);
            }
            else if(x_exit>=0&&x_exit<=160&&y_exit>=200&&y_exit<=250)
                informatii(fereastra);
            else if((x_exit>=0&&x_exit<=160&&y_exit>=150&&y_exit<=210||x_exit>=0&&x_exit<=160&&y_exit>=100&&y_exit<=150&&verificare==0)&&contor_piese!=0)
                salvare_ca(fereastra);
            else if (x_exit>=0&&x_exit<=160&&y_exit>=100&&y_exit<=150&&verificare==1)
                salvare_informatii();
            else if(x_exit>=210&&x_exit<=510&&y_exit>=-1&&y_exit<=50&&contor_piese!=0)
                alege_componenta();
        }
    }
    return;
}
void informatii (int fereastra)
{
    initwindow(700,560,"Informatii");
    setcolor(WHITE);
    int x=getmaxx()/2,y=getmaxy()/8;
    int fontul=8;
    int directia=0;
    int marime_font=5;
    int x_exit=-1,y_exit=-1;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(x,y,"INFORMATII");
    marime_font=1;
    settextstyle(fontul, directia, marime_font);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    outtextxy(40,120,"DESENARE PIESA - Pentru a desena o componenta apasati click");
    outtextxy(10,140,"stanga pe o piesa aflata in chenarul din dreapta, apoi faceti");
    outtextxy(10,160,"click stanga in spatiul de lucrul unde doriti sa amplasati");
    outtextxy(10,180,"componenta.");
    outtextxy(40,220,"REALIZAREA LEGATURII - Pentru a lega doua componente apasati");
    outtextxy(10,240,"click stanga pe punctul de legatura din dreapta piesei. Dupa");
    outtextxy(10,260,"indreptati cursorul spre punctul de legatura din stanga altei");
    outtextxy(10,280,"componente si apasati click stanga.");
    outtextxy(40,320,"STERGEREA PIESEI - Pentru a sterge o piesa si legaturile ei");
    outtextxy(10,340,"trebuie sa apasati click stanga pe butonul ALEGE PIESA si dupa");
    outtextxy(10,360,"sa apasati click stanga pe extremitatea din stanga a piesei.");
    outtextxy(10,380,"Va aparea butonul STERGE iar daca apasati dublu click dreapta,");
    outtextxy(10,400,"piesa si legaturile ei se vor sterge.");
    outtextxy(40,440,"MUTAREA PIESEI - Pentru a muta o piesa si legaturile ei");
    outtextxy(10,460,"trebuie sa apasati click stanga pe butonul ALEGE PIESA si dupa");
    outtextxy(10,480,"sa apasati click stanga pe extremitatea din stanga a piesei.");
    outtextxy(10,500,"Apasati dublu click dreapta si piesa se va muta dupa cursor.");
    outtextxy(10,520,"Apasati click stanga unde doriti sa fie pozitia finala a piesei");
    outtextxy(10,540,"piesei.");
    marime_font=2;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    rectangle(-1,-1,100,50);
    outtextxy(50,28,"INAPOI");
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if(x_exit>=0&&x_exit<=100&&y_exit>=0&&y_exit<=50)
        {
            closegraph(CURRENT_WINDOW);
            setcurrentwindow(fereastra);
            return;
        }
    }
}
void sigur_inapoi_la_meniu (int fereastra)
{
    setcolor(WHITE);
    int fereastra_sigur_inapoi_la_meniu=initwindow(700,500,"Sigur?");
    int x=getmaxx()/2,y=getmaxy()/4.5;
    int fontul=8;
    int directia=0;
    int marime_font=2;
    int x_exit=-1,y_exit=-1;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(x,y,"Inainte de a va intoarce la meniu");
    y=getmaxy()/3.8;
    outtextxy(x,y,"doriti sa salvati schema?");
    y=getmaxy()/2.8;
    outtextxy(x,y,"- Va rugam selectati print-un click comanda dorita -");
    marime_font=4;
    settextstyle(fontul, directia, marime_font);
    rectangle(65,200,220,250);
    outtextxy(140,235,"SALVARE");
    rectangle(450,200,605,250);
    outtextxy(530,235,"MENIU");
    while(1)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit>=450&&x_exit<=605&&y_exit>=200&&y_exit<=250)
        {
            closegraph(CURRENT_WINDOW);
            setcurrentwindow(fereastra);
            deseneaza_meniul(fereastra);
        }
        if (x_exit>=65&&x_exit<=220&&y_exit>=200&&y_exit<=250)
        {
            salvare_ca(fereastra_sigur_inapoi_la_meniu);
            closegraph(CURRENT_WINDOW);
            setcurrentwindow(fereastra);
            deseneaza_meniul(fereastra);
        }
    }
    return;
}
void sterge_informatiile()
{
    for (int i=1; i<=contor_piese; i++)
    {
        componente_desen[i].constanta=0;
        componente_desen[i].x=componente_desen[i].y=0;
        componente_desen[i].comanda_desen='\0';
        componente_desen[i].pleg[0].x=componente_desen[i].pleg[0].y=0;
        componente_desen[i].pleg[1].x=componente_desen[i].pleg[1].y=0;
        componente_desen[i].pleg[2].x=componente_desen[i].pleg[2].y=0;
    }
    for (int i=1; i<=contor_legaturi; i++)
    {
        legaturi_aflate_shita[i].piesa1.x=legaturi_aflate_shita[i].piesa1.y=0;
        legaturi_aflate_shita[i].piesa1.comanda_desen;
        legaturi_aflate_shita[i].piesa1.pleg[0].x=legaturi_aflate_shita[i].piesa1.pleg[0].y=0;
        legaturi_aflate_shita[i].piesa1.pleg[1].x=legaturi_aflate_shita[i].piesa1.pleg[1].y=0;
        legaturi_aflate_shita[i].piesa1.pleg[2].x=legaturi_aflate_shita[i].piesa1.pleg[2].y=0;
        legaturi_aflate_shita[i].piesa2.x=legaturi_aflate_shita[i].piesa2.y=0;
        legaturi_aflate_shita[i].piesa2.comanda_desen='\0';
        legaturi_aflate_shita[i].piesa2.pleg[0].x=legaturi_aflate_shita[i].piesa2.pleg[0].y=0;
        legaturi_aflate_shita[i].piesa2.pleg[1].x=legaturi_aflate_shita[i].piesa2.pleg[1].y=0;
        legaturi_aflate_shita[i].piesa2.pleg[2].x=legaturi_aflate_shita[i].piesa2.pleg[2].y=0;
        legaturi_aflate_shita[i].x1=legaturi_aflate_shita[i].y1=0;
        legaturi_aflate_shita[i].x2=legaturi_aflate_shita[i].y2=0;
    }
    contor_piese=contor_legaturi=0;
    return;
}
void decripteaza_informatii(int fereastra)
{
    ifstream citeste;
    citeste.open(fisier_de_salvare);
    citeste>>contor_piese>>contor_legaturi;
    for (int i=1; i<=contor_piese; i++)
    {
        citeste>>componente_desen[i].constanta;
        citeste>>componente_desen[i].x>>componente_desen[i].y;
        citeste>>componente_desen[i].comanda_desen;
        if (componente_desen[i].comanda_desen!='T')
        {
            citeste>>componente_desen[i].pleg[0].x>>componente_desen[i].pleg[0].y;
            citeste>>componente_desen[i].pleg[1].x>>componente_desen[i].pleg[1].y;
        }
        else
        {
            citeste>>componente_desen[i].pleg[0].x>>componente_desen[i].pleg[0].y;
            citeste>>componente_desen[i].pleg[1].x>>componente_desen[i].pleg[1].y;
            citeste>>componente_desen[i].pleg[2].x>>componente_desen[i].pleg[2].y;
        }
    }
    for (int i=1; i<=contor_legaturi; i++)
    {
        citeste>>legaturi_aflate_shita[i].piesa1.x>>legaturi_aflate_shita[i].piesa1.y;
        citeste>>legaturi_aflate_shita[i].piesa1.comanda_desen;
        if (legaturi_aflate_shita[i].piesa1.comanda_desen!='T')
        {
            citeste>>legaturi_aflate_shita[i].piesa1.pleg[0].x>>legaturi_aflate_shita[i].piesa1.pleg[0].y;
            citeste>>legaturi_aflate_shita[i].piesa1.pleg[1].x>>legaturi_aflate_shita[i].piesa1.pleg[1].y;
        }
        else
        {
            citeste>>legaturi_aflate_shita[i].piesa1.pleg[0].x>>legaturi_aflate_shita[i].piesa1.pleg[0].y;
            citeste>>legaturi_aflate_shita[i].piesa1.pleg[1].x>>legaturi_aflate_shita[i].piesa1.pleg[1].y;
            citeste>>legaturi_aflate_shita[i].piesa1.pleg[2].x>>legaturi_aflate_shita[i].piesa1.pleg[2].y;
        }
        citeste>>legaturi_aflate_shita[i].piesa2.x>>legaturi_aflate_shita[i].piesa2.y;
        citeste>>legaturi_aflate_shita[i].piesa2.comanda_desen;
        if (legaturi_aflate_shita[i].piesa2.comanda_desen!='T')
        {
            citeste>>legaturi_aflate_shita[i].piesa2.pleg[0].x>>legaturi_aflate_shita[i].piesa2.pleg[0].y;
            citeste>>legaturi_aflate_shita[i].piesa2.pleg[1].x>>legaturi_aflate_shita[i].piesa2.pleg[1].y;
        }
        else
        {
            citeste>>legaturi_aflate_shita[i].piesa2.pleg[0].x>>legaturi_aflate_shita[i].piesa2.pleg[0].y;
            citeste>>legaturi_aflate_shita[i].piesa2.pleg[1].x>>legaturi_aflate_shita[i].piesa2.pleg[1].y;
            citeste>>legaturi_aflate_shita[i].piesa2.pleg[2].x>>legaturi_aflate_shita[i].piesa2.pleg[2].y;
        }
        citeste>>legaturi_aflate_shita[i].x1>>legaturi_aflate_shita[i].y1;
        citeste>>legaturi_aflate_shita[i].x2>>legaturi_aflate_shita[i].y2;
    }
    citeste.close();
    closegraph(CURRENT_WINDOW);
    setcurrentwindow(fereastra);
    verificare=true;
    deseneaza_schema_noua(fereastra);
}
void deschide_schema(int fereastra)
{
    initwindow(700,500,"Deschide schema");
    setcolor(WHITE);
    int x=getmaxx()/2,y=getmaxy()/4.5,x_exit=-1,y_exit=-1,contor_nume_fisier=0;
    char litera=NULL;
    int x_scris=55;
    int fontul=8;
    int directia=0;
    int marime_font=2;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(x,y,"Numele fisierului pe care doriti sa-l deschideti");
    rectangle(575,450,700,500);
    outtextxy(635,478,"ENTER");
    line(49,y+50,647,y+50);
    rectangle(-1,-1,100,50);
    outtextxy(50,28,"INAPOI");
    outtextxy(345,y+100,"Apasati enter pentru a confirma numele fisierului");
    while(1)
    {
        while(1)
        {
            x_exit=mousex();
            y_exit=mousey();
            if(x_exit>=0&&x_exit<=100&&y_exit>=0&&y_exit<=50&&ismouseclick(WM_LBUTTONDOWN)==1)
            {
                closegraph(CURRENT_WINDOW);
                setcurrentwindow(fereastra);
                return;
            }
            if(x_exit>=575&&x_exit<=700&&y_exit>=450&&y_exit<=500&&ismouseclick(WM_LBUTTONDOWN)==1)
            {
                fisier_de_salvare[contor_nume_fisier]='\0';
                strcat(fisier_de_salvare,".txt");
                decripteaza_informatii(fereastra);
                return;
            }
            setcolor(WHITE);
            line(x_scris,y+20,x_scris,y+46);
            delay(200);
            setcolor(BLACK);
            line(x_scris,y+20,x_scris,y+46);
            delay(200);
            if(kbhit())
            {
                litera=getch();
                x_scris=x_scris+15;
                break;
            }

        }
        setcolor(WHITE);
        outtextxy(x_scris,y+45,&litera);
        fisier_de_salvare[contor_nume_fisier]=litera;
        contor_nume_fisier++;
        x_scris=x_scris+2;
    }
    fontul=8;
    directia=0;
    marime_font=5;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    return;
}
void salvare_informatii()
{
    fstream fisier;
    fisier.open(fisier_de_salvare,ios::out);
    fisier.close();
    ofstream scrie;
    scrie.open(fisier_de_salvare);
    scrie<<contor_piese<<" "<<contor_legaturi<<"\n";
    for (int i=1; i<=contor_piese; i++)
    {
        scrie<<componente_desen[i].constanta<<'\n';
        scrie<<componente_desen[i].x<<" "<<componente_desen[i].y<<'\n';
        scrie<<componente_desen[i].comanda_desen<<'\n';
        if (componente_desen[i].comanda_desen!='T')
        {
            scrie<<componente_desen[i].pleg[0].x<<" "<<componente_desen[i].pleg[0].y<<'\n';
            scrie<<componente_desen[i].pleg[1].x<<" "<<componente_desen[i].pleg[1].y<<'\n';
        }
        else
        {
            scrie<<componente_desen[i].pleg[0].x<<" "<<componente_desen[i].pleg[0].y<<'\n';
            scrie<<componente_desen[i].pleg[1].x<<" "<<componente_desen[i].pleg[1].y<<'\n';
            scrie<<componente_desen[i].pleg[2].x<<" "<<componente_desen[i].pleg[2].y<<'\n';
        }
    }
    for (int i=1; i<=contor_legaturi; i++)
    {
        scrie<<legaturi_aflate_shita[i].piesa1.x<<" "<<legaturi_aflate_shita[i].piesa1.y<<'\n';
        scrie<<legaturi_aflate_shita[i].piesa1.comanda_desen<<'\n';
        if (legaturi_aflate_shita[i].piesa1.comanda_desen!='T')
        {
            scrie<<legaturi_aflate_shita[i].piesa1.pleg[0].x<<" "<<legaturi_aflate_shita[i].piesa1.pleg[0].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa1.pleg[1].x<<" "<<legaturi_aflate_shita[i].piesa1.pleg[1].y<<'\n';
        }
        else
        {
            scrie<<legaturi_aflate_shita[i].piesa1.pleg[0].x<<" "<<legaturi_aflate_shita[i].piesa1.pleg[0].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa1.pleg[1].x<<" "<<legaturi_aflate_shita[i].piesa1.pleg[1].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa1.pleg[2].x<<" "<<legaturi_aflate_shita[i].piesa1.pleg[2].y<<'\n';
        }
        scrie<<legaturi_aflate_shita[i].piesa2.x<<" "<<legaturi_aflate_shita[i].piesa2.y<<'\n';
        scrie<<legaturi_aflate_shita[i].piesa2.comanda_desen<<'\n';
        if (legaturi_aflate_shita[i].piesa2.comanda_desen!='T')
        {
            scrie<<legaturi_aflate_shita[i].piesa2.pleg[0].x<<" "<<legaturi_aflate_shita[i].piesa2.pleg[0].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa2.pleg[1].x<<" "<<legaturi_aflate_shita[i].piesa2.pleg[1].y<<'\n';
        }
        else
        {
            scrie<<legaturi_aflate_shita[i].piesa2.pleg[0].x<<" "<<legaturi_aflate_shita[i].piesa2.pleg[0].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa2.pleg[1].x<<" "<<legaturi_aflate_shita[i].piesa2.pleg[1].y<<'\n';
            scrie<<legaturi_aflate_shita[i].piesa2.pleg[2].x<<" "<<legaturi_aflate_shita[i].piesa2.pleg[2].y<<'\n';
        }
        scrie<<legaturi_aflate_shita[i].x1<<" "<<legaturi_aflate_shita[i].y1<<'\n';
        scrie<<legaturi_aflate_shita[i].x2<<" "<<legaturi_aflate_shita[i].y2<<'\n';
    }
    scrie.close();
    verificare=true;
    return;
}
void salvare_ca(int fereastra)
{
    setcolor(WHITE);
    initwindow(700,500,"Salvare ca");
    int x=getmaxx()/2,y=getmaxy()/4.5,x_exit=-1,y_exit=-1,contor_nume_fisier=0;
    char litera=NULL;
    int x_scris=55;
    int fontul=8;
    int directia=0;
    int marime_font=2;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    outtextxy(x,y,"Numele fisierului in care doriti sa salvati schema");
    rectangle(575,450,700,500);
    outtextxy(635,478,"ENTER");
    line(49,y+50,647,y+50);
    rectangle(-1,-1,100,50);
    outtextxy(50,28,"INAPOI");
    outtextxy(345,y+100,"Apasati enter pentru a confirma numele fisierului");
    while(1)
    {
        while(1)
        {
            x_exit=mousex();
            y_exit=mousey();
            if(x_exit>=0&&x_exit<=100&&y_exit>=0&&y_exit<=50&&ismouseclick(WM_LBUTTONDOWN)==1)
            {
                closegraph(CURRENT_WINDOW);
                setcurrentwindow(fereastra);
                return;
            }
            if(x_exit>=575&&x_exit<=700&&y_exit>=450&&y_exit<=500&&ismouseclick(WM_LBUTTONDOWN)==1)
            {
                fisier_de_salvare[contor_nume_fisier]='\0';
                strcat(fisier_de_salvare,".txt");
                salvare_informatii();
                closegraph(CURRENT_WINDOW);
                setcurrentwindow(fereastra);
                return;
            }
            setcolor(WHITE);
            line(x_scris,y+20,x_scris,y+46);
            delay(200);
            setcolor(BLACK);
            line(x_scris,y+20,x_scris,y+46);
            delay(200);
            if(kbhit())
            {
                litera=getch();
                x_scris=x_scris+15;
                break;
            }

        }
        setcolor(WHITE);
        outtextxy(x_scris,y+45,&litera);
        fisier_de_salvare[contor_nume_fisier]=litera;
        contor_nume_fisier++;
        x_scris=x_scris+2;
    }
    fontul=8;
    directia=0;
    marime_font=5;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
}
void alege_componenta()
{
    setcolor(WHITE);
    int x_exit=-1,y_exit=-1,i;
    bool click=false;
    componenta piesa_aleasa;
    int fontul=8;
    int directia=0;
    int marime_font=5;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    while (x_exit==-1&&y_exit==-1||click==false)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        for(i=1; i<=contor_piese; i++)
            if(abs(componente_desen[i].x-x_exit)<=10&&abs(componente_desen[i].y-y_exit)<=10)
            {
                click=true;
                piesa_aleasa.x=componente_desen[i].x;
                piesa_aleasa.y=componente_desen[i].y;
                piesa_aleasa.comanda_desen=componente_desen[i].comanda_desen;
                piesa_aleasa.pLeg[0].x=componente_desen[i].pleg[0].x;
                piesa_aleasa.pLeg[0].y=componente_desen[i].pleg[0].y;
                piesa_aleasa.pLeg[1].x=componente_desen[i].pleg[1].x;
                piesa_aleasa.pLeg[1].y=componente_desen[i].pleg[1].y;
                if(componente_desen[i].comanda_desen=='T')
                {
                    piesa_aleasa.pLeg[2].x=componente_desen[i].pleg[2].x;
                    piesa_aleasa.pLeg[2].y=componente_desen[i].pleg[2].y;
                }
                break;
            }
    }
    rectangle(560,-1,730,50);
    outtextxy(645,30,"STERGE");
    rectangle(730,-1,930,50);
    outtextxy(830,30,"MARESTE");
    rectangle(930,-1,1210,50);
    outtextxy(1070,30,"MICSOREAZA");
    double constanta=componente_desen[i].constanta;
    dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,0,constanta);
    while(1)
    {
        getmouseclick(WM_RBUTTONDBLCLK,x_exit,y_exit);
        if(x_exit>=560&&x_exit<=730&&y_exit>=-1&&y_exit<=50)
        {
            sterge_piesa(piesa_aleasa,i,constanta);
            repara_desen();
            break;
        }
        else if (x_exit>=730&&x_exit<=930&&y_exit>=0&&y_exit<=50)
        {
            int vec_output[NMAX],vec_input[NMAX];
            vec_output[1]=vec_input[1]=-1;
            afla_legaturile_output(i,vec_output);
            afla_legaturile_input(i,vec_input);
            if (vec_input[1]==-1&&vec_output[1]==-1)
            {
                dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,1,constanta);
                deseneaza_piesa(piesa_aleasa,1,constanta);
                constanta+=5;
                deseneaza_piesa(piesa_aleasa,0,constanta);
                componente_desen[i].constanta=constanta;
                if(componente_desen[i].comanda_desen!='T')
                {
                    componente_desen[contor_piese].pleg[1].x=componente_desen[contor_piese].pleg[0].x+80+2*constanta;
                }
                else
                {
                    componente_desen[contor_piese].pleg[1].x=componente_desen[contor_piese].pleg[0].x+40+constanta;
                    componente_desen[contor_piese].pleg[1].y=componente_desen[contor_piese].pleg[0].y-10-11-constanta/4;
                    componente_desen[contor_piese].pleg[2].x=componente_desen[contor_piese].pleg[0].x+40+constanta;
                    componente_desen[contor_piese].pleg[2].y=componente_desen[contor_piese].pleg[0].y+10+11+constanta/4;
                }
            }
            else
                dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,1,constanta);
            repara_desen();
            return;
        }
        else if (x_exit>=930&&x_exit<=1210&&y_exit>=0&&y_exit<=50)
        {
            int vec_output[NMAX],vec_input[NMAX];
            vec_output[1]=vec_input[1]=-1;
            afla_legaturile_output(i,vec_output);
            afla_legaturile_input(i,vec_input);
            if (vec_input[1]==-1&&vec_output[1]==-1)
            {
                dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,1,constanta);
                deseneaza_piesa(piesa_aleasa,1,constanta);
                constanta-=5;
                deseneaza_piesa(piesa_aleasa,0,constanta);
                componente_desen[i].constanta=constanta;
                if(componente_desen[i].comanda_desen!='T')
                {
                    componente_desen[contor_piese].pleg[1].x=componente_desen[contor_piese].pleg[0].x+80+2*constanta;
                }
                else
                {
                    componente_desen[contor_piese].pleg[1].x=componente_desen[contor_piese].pleg[0].x+40+constanta;
                    componente_desen[contor_piese].pleg[1].y=componente_desen[contor_piese].pleg[0].y-10-11-constanta/4;
                    componente_desen[contor_piese].pleg[2].x=componente_desen[contor_piese].pleg[0].x+40+constanta;
                    componente_desen[contor_piese].pleg[2].y=componente_desen[contor_piese].pleg[0].y+10+11+constanta/4;
                }
            }
            else
                dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,1,constanta);
            repara_desen();
            return;
        }

        else if(x_exit!=-1&&y_exit!=-1)
        {
            if(constanta==0)
                muta_componenta(piesa_aleasa,i);
            dreptunghi_componenta_aleasa(piesa_aleasa.x,piesa_aleasa.y,1,constanta);
            repara_desen();
            return;
        }
    }
    return;
}
void sterge_piesa (componenta &P, int parametru_piesei, double constanta)
{
    deseneaza_piesa(P,1,constanta);
    dreptunghi_componenta_aleasa(P.x,P.y,1,constanta);
    if(componente_desen[parametru_piesei].comanda_desen!='T')
        for (int j=1; j<=contor_legaturi; j++)
        {

            if (legaturi_aflate_shita[j].x1==P.pLeg[1].x&&legaturi_aflate_shita[j].y1==P.pLeg[1].y)
            {
                deseneaza_linie(P.pLeg[1].x,P.pLeg[1].y,legaturi_aflate_shita[j].x2,legaturi_aflate_shita[j].y2,1);
                for(int i=j; i<=contor_legaturi; i++)
                    legaturi_aflate_shita[i]=legaturi_aflate_shita[i+1];
                contor_legaturi--;
                j--;
            }
            if(legaturi_aflate_shita[j].x2==P.pLeg[0].x&&legaturi_aflate_shita[j].y2==P.pLeg[0].y)
            {
                deseneaza_linie(legaturi_aflate_shita[j].x1,legaturi_aflate_shita[j].y1,P.pLeg[0].x,P.pLeg[0].y,1);
                for(int i=j; i<=contor_legaturi; i++)
                    legaturi_aflate_shita[i]=legaturi_aflate_shita[i+1];
                contor_legaturi--;
                j--;
            }
        }
    else
    {
        for (int j=1; j<=contor_legaturi; j++)
        {

            if (legaturi_aflate_shita[j].x1==P.pLeg[1].x&&legaturi_aflate_shita[j].y1==P.pLeg[1].y)
            {
                deseneaza_linie(P.pLeg[1].x,P.pLeg[1].y,legaturi_aflate_shita[j].x2,legaturi_aflate_shita[j].y2,1);
                for(int i=j; i<=contor_legaturi; i++)
                    legaturi_aflate_shita[i]=legaturi_aflate_shita[i+1];
                contor_legaturi--;
                j--;
            }
            if(legaturi_aflate_shita[j].x2==P.pLeg[0].x&&legaturi_aflate_shita[j].y2==P.pLeg[0].y)
            {
                deseneaza_linie(legaturi_aflate_shita[j].x1,legaturi_aflate_shita[j].y1,P.pLeg[0].x,P.pLeg[0].y,1);
                for(int i=j; i<=contor_legaturi; i++)
                    legaturi_aflate_shita[i]=legaturi_aflate_shita[i+1];
                contor_legaturi--;
                j--;
            }
            if (legaturi_aflate_shita[j].x1==P.pLeg[2].x&&legaturi_aflate_shita[j].y1==P.pLeg[2].y)
            {
                deseneaza_linie(P.pLeg[2].x,P.pLeg[2].y,legaturi_aflate_shita[j].x2,legaturi_aflate_shita[j].y2,1);
                for(int i=j; i<=contor_legaturi; i++)
                    legaturi_aflate_shita[i]=legaturi_aflate_shita[i+1];
                contor_legaturi--;
                j--;
            }

        }
    }
    for (int j=parametru_piesei; j<=contor_piese; j++)
        componente_desen[j]=componente_desen[j+1];
    contor_piese--;
    setcolor(WHITE);
    return;
}
void afla_legaturile_output(int parametrul_piesei,int vec_output[])
{
    int contor_vector_output=1;
    for (int i=1; i<=contor_legaturi; i++)
    {
        if((legaturi_aflate_shita[i].piesa1.pleg[1].x==componente_desen[parametrul_piesei].pleg[1].x&&legaturi_aflate_shita[i].piesa1.pleg[1].y==componente_desen[parametrul_piesei].pleg[1].y&&componente_desen[parametrul_piesei].pleg[1].x!=0&&componente_desen[parametrul_piesei].pleg[1].y!=0)
                ||(legaturi_aflate_shita[i].piesa1.pleg[2].x==componente_desen[parametrul_piesei].pleg[2].x&&legaturi_aflate_shita[i].piesa1.pleg[2].y==componente_desen[parametrul_piesei].pleg[2].y&&componente_desen[parametrul_piesei].pleg[2].x!=0&&componente_desen[parametrul_piesei].pleg[2].y!=0))
        {
            vec_output[contor_vector_output]=i;
            contor_vector_output++;
        }
    }
    vec_output[contor_vector_output]=-1;
    return;
}
void afla_legaturile_input(int parametrul_piesei,int vec_input[])
{
    int contor_vec_input=1;
    for(int i=1; i<=contor_legaturi; i++)
    {
        if(legaturi_aflate_shita[i].piesa2.pleg[0].x==componente_desen[parametrul_piesei].pleg[0].x&&legaturi_aflate_shita[i].piesa2.pleg[0].y==componente_desen[parametrul_piesei].pleg[0].y)
        {
            vec_input[contor_vec_input]=i;
            contor_vec_input++;
        }
    }
    vec_input[contor_vec_input]=-1;
    return;
}
void muta_componenta(componenta &P,int parametrul_piesei)
{
    int x,y,x_exit=-1,y_exit=-1,vec_output[NMAX],vec_input[NMAX],leg;
    afla_legaturile_output(parametrul_piesei,vec_output);
    afla_legaturile_input(parametrul_piesei,vec_input);
    x=mousex();
    y=mousey();
    dreptunghi_componenta_aleasa(P.x,P.y,1,0);
    deseneaza_piesa(P,1,0);
    for (int i=1; vec_output[i]!=-1; i++)
        deseneaza_linie(legaturi_aflate_shita[vec_output[i]].x1,legaturi_aflate_shita[vec_output[i]].y1,legaturi_aflate_shita[vec_output[i]].x2,legaturi_aflate_shita[vec_output[i]].y2,1);
    for (int i=1; vec_input[i]!=-1; i++)
        deseneaza_linie(legaturi_aflate_shita[vec_input[i]].x1,legaturi_aflate_shita[vec_input[i]].y1,legaturi_aflate_shita[vec_input[i]].x2,legaturi_aflate_shita[vec_input[i]].y2,1);
    while(x_exit==-1&&y_exit==-1)
    {
        if(!(x>=180&&x<=1230&&y>=70&&y<=565))
        {
            setcolor(WHITE);
            rectangle(210,100,1250,595);
            return;
        }
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit!=-1&&y_exit!=-1)
        {
            P.x=x_exit;
            P.y=y_exit;
            deseneaza_piesa(P,0,0);
            for (int i=1; vec_output[i]!=-1; i++)
            {
                if(componente_desen[parametrul_piesei].comanda_desen!='T')
                {
                    legaturi_aflate_shita[vec_output[i]].x1=x_exit+80;
                    legaturi_aflate_shita[vec_output[i]].y1=y_exit;
                    componente_desen[parametrul_piesei].pleg[1].x=x_exit+80;
                    componente_desen[parametrul_piesei].pleg[1].y=y_exit;
                    legaturi_aflate_shita[i].piesa1.pleg[1].x=x_exit+80;
                    legaturi_aflate_shita[i].piesa1.pleg[1].y=y_exit;
                }
                else
                {
                    if(componente_desen[parametrul_piesei].pleg[1].x==legaturi_aflate_shita[vec_output[i]].x1&&componente_desen[parametrul_piesei].pleg[1].y==legaturi_aflate_shita[vec_output[i]].y1)
                    {
                        legaturi_aflate_shita[vec_output[i]].x1=x_exit+40;
                        legaturi_aflate_shita[vec_output[i]].y1=y_exit-21;
                        componente_desen[parametrul_piesei].pleg[1].x=x_exit+40;
                        componente_desen[parametrul_piesei].pleg[1].y=y_exit-21;
                        legaturi_aflate_shita[i].piesa1.pleg[1].x=x_exit+40;
                        legaturi_aflate_shita[i].piesa1.pleg[1].y=y_exit-21;

                    }
                    else if(componente_desen[parametrul_piesei].pleg[2].x==legaturi_aflate_shita[vec_output[i]].x1&&componente_desen[parametrul_piesei].pleg[2].y==legaturi_aflate_shita[vec_output[i]].y1)
                    {
                        legaturi_aflate_shita[vec_output[i]].x1=x_exit+40;
                        legaturi_aflate_shita[vec_output[i]].y1=y_exit+21;
                        componente_desen[parametrul_piesei].pleg[2].x=x_exit+40;
                        componente_desen[parametrul_piesei].pleg[2].y=y_exit+21;
                        legaturi_aflate_shita[i].piesa1.pleg[2].x=x_exit+40;
                        legaturi_aflate_shita[i].piesa1.pleg[2].y=y_exit+21;
                    }
                }
            }
            for (int i=1; vec_input[i]!=-1; i++)
            {
                legaturi_aflate_shita[vec_input[i]].x2=x_exit;
                legaturi_aflate_shita[vec_input[i]].y2=y_exit;
                componente_desen[parametrul_piesei].pleg[0].x=x_exit;
                componente_desen[parametrul_piesei].pleg[0].y=y_exit;
                legaturi_aflate_shita[vec_input[i]].piesa2.pleg[0].x=x_exit;
                legaturi_aflate_shita[vec_input[i]].piesa2.pleg[0].y=y_exit;
            }
            if(componente_desen[parametrul_piesei].comanda_desen!='T')
            {
                componente_desen[parametrul_piesei].pleg[0].x=componente_desen[parametrul_piesei].x=x_exit;
                componente_desen[parametrul_piesei].pleg[0].y=componente_desen[parametrul_piesei].y=y_exit;
                componente_desen[parametrul_piesei].pleg[1].x=x_exit+80;
                componente_desen[parametrul_piesei].pleg[1].y=y_exit;
            }
            else
            {
                componente_desen[parametrul_piesei].pleg[0].x=componente_desen[parametrul_piesei].x=x_exit;
                componente_desen[parametrul_piesei].pleg[0].y=componente_desen[parametrul_piesei].y=y_exit;
                componente_desen[parametrul_piesei].pleg[1].x=x_exit+40;
                componente_desen[parametrul_piesei].pleg[1].y=y_exit-21;
                componente_desen[parametrul_piesei].pleg[2].x=x_exit+40;
                componente_desen[parametrul_piesei].pleg[2].y=y_exit+21;
            }
            for (int i=1; vec_output[i]!=-1; i++)
                deseneaza_linie(legaturi_aflate_shita[vec_output[i]].x1,legaturi_aflate_shita[vec_output[i]].y1,legaturi_aflate_shita[vec_output[i]].x2,legaturi_aflate_shita[vec_output[i]].y2,0);
            for (int i=1; vec_input[i]!=-1; i++)
                deseneaza_linie(legaturi_aflate_shita[vec_input[i]].x1,legaturi_aflate_shita[vec_input[i]].y1,legaturi_aflate_shita[vec_input[i]].x2,legaturi_aflate_shita[vec_input[i]].y2,0);
            return ;
        }
        P.x=x;
        P.y=y;
        for (int i=1; vec_output[i]!=-1; i++)
        {
            if(componente_desen[parametrul_piesei].comanda_desen!='T')
            {
                legaturi_aflate_shita[vec_output[i]].x1=x+80;
                legaturi_aflate_shita[vec_output[i]].y1=y;
                componente_desen[parametrul_piesei].pleg[1].x=x+80;
                componente_desen[parametrul_piesei].pleg[1].y=y;
            }
            else
            {
                if(componente_desen[parametrul_piesei].pleg[1].x==legaturi_aflate_shita[vec_output[i]].x1&&componente_desen[parametrul_piesei].pleg[1].y==legaturi_aflate_shita[vec_output[i]].y1)
                    leg=1;
                if(componente_desen[parametrul_piesei].pleg[2].x==legaturi_aflate_shita[vec_output[i]].x1&&componente_desen[parametrul_piesei].pleg[2].y==legaturi_aflate_shita[vec_output[i]].y1)
                    leg=2;
                if(leg==1)
                {
                    componente_desen[parametrul_piesei].pleg[1].x=x+40;
                    componente_desen[parametrul_piesei].pleg[1].y=y-21;
                    legaturi_aflate_shita[vec_output[i]].x1=componente_desen[parametrul_piesei].pleg[1].x;
                    legaturi_aflate_shita[vec_output[i]].y1=componente_desen[parametrul_piesei].pleg[1].y;

                }
                else if(leg==2)
                {
                    legaturi_aflate_shita[vec_output[i]].x1=x+40;
                    legaturi_aflate_shita[vec_output[i]].y1=y+21;
                    componente_desen[parametrul_piesei].pleg[2].x=x+40;
                    componente_desen[parametrul_piesei].pleg[2].y=y+21;
                }
            }
        }
        for (int i=1; vec_input[i]!=-1; i++)
        {
            legaturi_aflate_shita[vec_input[i]].x2=x;
            legaturi_aflate_shita[vec_input[i]].y2=y;
            componente_desen[parametrul_piesei].pleg[0].x=x;
            componente_desen[parametrul_piesei].pleg[0].y=y;
        }
        deseneaza_piesa(P,0,1);
        for (int i=1; vec_output[i]!=-1; i++)
            deseneaza_linie(legaturi_aflate_shita[vec_output[i]].x1,legaturi_aflate_shita[vec_output[i]].y1,legaturi_aflate_shita[vec_output[i]].x2,legaturi_aflate_shita[vec_output[i]].y2,0);
        for (int i=1; vec_input[i]!=-1; i++)
            deseneaza_linie(legaturi_aflate_shita[vec_input[i]].x1,legaturi_aflate_shita[vec_input[i]].y1,legaturi_aflate_shita[vec_input[i]].x2,legaturi_aflate_shita[vec_input[i]].y2,0);
        delay(50);
        deseneaza_piesa(P,1,1);
        for (int i=1; vec_output[i]!=-1; i++)
            deseneaza_linie(legaturi_aflate_shita[vec_output[i]].x1,legaturi_aflate_shita[vec_output[i]].y1,legaturi_aflate_shita[vec_output[i]].x2,legaturi_aflate_shita[vec_output[i]].y2,1);
        for (int i=1; vec_input[i]!=-1; i++)
            deseneaza_linie(legaturi_aflate_shita[vec_input[i]].x1,legaturi_aflate_shita[vec_input[i]].y1,legaturi_aflate_shita[vec_input[i]].x2,legaturi_aflate_shita[vec_input[i]].y2,1);
        x=mousex();
        y=mousey();
    }
    return;
}
void dreptunghi_componenta_aleasa(int x,int y,int culoare, double constanta)
{
    if (culoare==0)
        setcolor(WHITE);
    else
        setcolor(BLACK);
    setlinestyle(DOTTED_LINE,1,NORM_WIDTH);
    line(x-10,y+28+constanta,x-10,y-28-constanta);
    line(x-10,y-28-constanta,x+90+constanta*2,y-28-constanta);
    line(x+90+constanta*2,y-28-constanta,x+90+constanta*2,y+28+constanta);
    line(x+90+constanta*2,y+28+constanta,x-10,y+28+constanta);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    setcolor(WHITE);
}
void deseneaza_linie(int x1,int y1,int x2,int y2,int culoare)
{
    if (culoare==0)
        setcolor(WHITE);
    else
        setcolor(BLACK);
    line(x1+4,y1,(x1+x2)/2,y1);
    line((x1+x2)/2,y1,(x1+x2)/2,y2);
    line((x1+x2)/2,y2,x2-4,y2);
    setcolor(WHITE);
}
void deseneaza_legatura(int piesa1, int pleg_piesa1, int piesa2, int pleg_piesa2)
{
    int x_exit=-1,y_exit=-1;
    bool ok=false;
    while (x_exit==-1&&y_exit==-1||ok==false)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit!=-1&&y_exit!=-1)
        {
            for(int i=1; i<=contor_piese; i++)
                if(abs(componente_desen[i].pleg[1].x-x_exit)<=5&&abs(componente_desen[i].pleg[1].y-y_exit)<=5)
                {
                    piesa1=i;
                    pleg_piesa1=1;
                    ok=true;
                }
                else if(abs(componente_desen[i].pleg[2].x-x_exit)<=5&&abs(componente_desen[i].pleg[2].y-y_exit)<=5)
                {
                    piesa1=i;
                    pleg_piesa1=2;
                    ok=true;
                }
        }
    }
    x_exit=-1;
    y_exit=-1;
    int x1,y1,x,y;
    ok=false;
    x1=componente_desen[piesa1].pleg[pleg_piesa1].x;
    y1=componente_desen[piesa1].pleg[pleg_piesa1].y;
    x=mousex();
    y=mousey();
    while (x_exit==-1&&y_exit==-1||ok==false)
    {
        if (x1!=0&&y1!=0&&x>=209&&y>=101&&x<=1249&&y<=594)
        {
            deseneaza_linie(x1,y1,x,y,0);
            delay(50);
            deseneaza_linie(x1,y1,x,y,1);
        }
        else
            return;
        repara_desen();
        x=mousex();
        y=mousey();
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit!=-1&&y_exit!=-1)
        {
            for(int i=1; i<=contor_piese; i++)
                if(abs(componente_desen[i].pleg[0].x-x_exit)<=5&&abs(componente_desen[i].pleg[0].y-y_exit)<=5)
                {
                    piesa2=i;
                    pleg_piesa2=0;
                    x_exit=componente_desen[i].pleg[0].x;
                    y_exit=componente_desen[i].pleg[0].y;
                    ok=true;
                }
        }
    }
    if (x1!=0&&y1!=0)
        deseneaza_linie(x1,y1,x_exit,y_exit,0);
    contor_legaturi++;
    legaturi_aflate_shita[contor_legaturi].piesa1=componente_desen[piesa1];
    legaturi_aflate_shita[contor_legaturi].piesa2=componente_desen[piesa2];
    legaturi_aflate_shita[contor_legaturi].x1=x1;
    legaturi_aflate_shita[contor_legaturi].y1=y1;
    legaturi_aflate_shita[contor_legaturi].x2=x_exit;
    legaturi_aflate_shita[contor_legaturi].y2=y_exit;
    return;
}

void repara_desen()
{
    int P;
    for(int i=1; i<=contor_piese; i++)
    {
        P=afla_piesa(componente_desen[i].comanda_desen);
        piese[P].x=componente_desen[i].x;
        piese[P].y=componente_desen[i].y;
        deseneaza_piesa(piese[P],0,componente_desen[i].constanta);

    }
    for(int i=1; i<=contor_legaturi; i++)
        deseneaza_linie(legaturi_aflate_shita[i].x1,legaturi_aflate_shita[i].y1,legaturi_aflate_shita[i].x2,legaturi_aflate_shita[i].y2,0);
    return;
}

int afla_piesa (char comanda)
{
    switch (comanda)
    {
    case 'S':
        return 1;
        break;
    case 'R':
        return 2;
        break;
    case 'B':
        return 3;
        break;
    case 'D':
        return 4;
        break;
    case 'A':
        return 5;
        break;
    case 'V':
        return 6;
        break;
    case 'C':
        return 7;
        break;
    case 's':
        return 8;
        break;
    case 'T':
        return 9;
        break;
    }
}
void amplaseaza(int x,int y)
{
    int x_exit=-1,y_exit=-1,P;
    if(y>=100&&y<=155)
        P=1;
    if(y>=156&&y<=210)
        P=2;
    if(y>=211&&y<=265)
        P=3;
    if(y>=266&&y<=320)
        P=4;
    if(y>=321&&y<=375)
        P=5;
    if(y>=376&&y<=435)
        P=6;
    if(y>=436&&y<=490)
        P=7;
    if(y>=491&&y<=545)
        P=8;
    if(y>=546&&y<=600)
        P=9;
    while(x_exit==-1&&y_exit==-1)
    {
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if(x_exit!=-1&&y_exit!=-1&&(x_exit>=210&&x_exit<=1250&&y_exit>=100&&y_exit<=595))
        {
            piese[P].x=x_exit;
            piese[P].y=y_exit;
            if (piese[P].x>=1170&&piese[P].x<=1250)
            {
                piese[P].x=piese[P].x-80;
                x_exit=x_exit-80;
            }
            if (piese[P].x>=210&&piese[P].x<=220)
            {
                piese[P].x=piese[P].x+10;
                x_exit=x_exit+10;
            }
            if (piese[P].y<=120&&piese[P].y>=100)
            {
                piese[P].y=piese[P].y+20;
                y_exit=y_exit+20;
            }
            if (piese[P].y<=595&&piese[P].y>=575)
            {
                piese[P].y=piese[P].y-20;
                y_exit=y_exit-20;
            }
            contor_piese++;
            componente_desen[contor_piese].comanda_desen=piese[P].comanda_desen;
            componente_desen[contor_piese].x=x_exit;
            componente_desen[contor_piese].y=y_exit;
            if(P!=9)
            {
                componente_desen[contor_piese].pleg[0].x=x_exit;
                componente_desen[contor_piese].pleg[0].y=y_exit;
                componente_desen[contor_piese].pleg[1].x=x_exit+80;
                componente_desen[contor_piese].pleg[1].y=y_exit;
            }
            else
            {
                componente_desen[contor_piese].pleg[0].x=x_exit;
                componente_desen[contor_piese].pleg[0].y=y_exit;
                componente_desen[contor_piese].pleg[1].x=x_exit+40;
                componente_desen[contor_piese].pleg[1].y=y_exit-21;
                componente_desen[contor_piese].pleg[2].x=x_exit+40;
                componente_desen[contor_piese].pleg[2].y=y_exit+21;
            }
            deseneaza_piesa(piese[P],0,0);
            break;
        }
    }
}

void deseneaza_piesa(componenta &P,int culoare,double constanta)
{
    if(culoare==0)
        setcolor(WHITE);
    else
        setcolor(BLACK);
    switch (P.comanda_desen)
    {
    case 'S':
        sursa_alimentare(P,constanta);
        break;
    case 'R':
        rezistenta(P,constanta);
        break;
    case 'B':
        bec(P,constanta);
        break;
    case 'D':
        dioda(P,constanta);
        break;
    case 'A':
        ampermetru(P,constanta);
        break;
    case 'V':
        voltmetru(P,constanta);
        break;
    case 'C':
        condensator(P,constanta);
        break;
    case 's':
        siguranta(P,constanta);
        break;
    case 'T':
        tranzistor(P,constanta);
        break;
    }
}
void sursa_alimentare(componenta &P,double constanta)
{
    line(P.x,P.y,P.x+30+constanta,P.y);
    line(P.x+30+20+constanta,P.y,P.x+30+20+30+constanta*2,P.y);
    line(P.x+30+constanta,(P.y-17)-constanta,P.x+30+constanta,(P.y+18)+constanta);
    line(P.x+30+20+constanta,(P.y-17/2)-constanta,P.x+30+20+constanta,(P.y+18/2)+constanta);
    line(P.x+30-10+constanta,P.y-17/1.5,P.x+30-10+constanta,P.y-3);
    line(P.x+30-15+constanta,P.y-17/2,P.x+30-5+constanta,P.y-17/2);
    line(P.x+55+constanta,P.y-17/2,P.x+30+35+constanta,P.y-17/2);
    circle(P.x,P.y,4);
    circle(P.x+30+20+30+constanta*2,P.y,4);
    return;
}
void rezistenta(componenta &P, double constanta)
{
    line(P.x,P.y,P.x+20+constanta,P.y);
    rectangle(P.x+20+constanta,P.y-10-constanta/8,P.x+60+constanta,P.y+10+constanta/8);
    line(P.x+60+constanta,P.y,P.x+60+20+2*constanta,P.y);
    circle(P.x,P.y,4);
    circle(P.x+60+20+2*constanta,P.y,4);
    return;
}
void bec(componenta &P, double constanta)
{
    line(P.x,P.y,P.x+25+constanta,P.y);
    circle(P.x+25+15+constanta,P.y,14+constanta/4);
    line(P.x+25+15+14+constanta,P.y,P.x+25+15+20+20+2*constanta,P.y);
    line(P.x+30+constanta,P.y-10,P.x+30+18+constanta,P.y+10);
    line(P.x+46+constanta,P.y-10,P.x+46-15+constanta,P.y+10);
    circle(P.x,P.y,4);
    circle(P.x+25+15+20+20+2*constanta,P.y,4);
    return;
}
void dioda(componenta &P, double constanta)
{
    line(P.x,P.y,P.x+22+constanta,P.y);
    line(P.x+22+constanta,P.y-15-constanta/2,P.x+22+constanta,P.y+15+constanta/2);
    line(P.x+22+constanta,P.y-15-constanta/2,P.x+22+25+constanta,P.y);
    line(P.x+22+constanta,P.y+15+constanta/2,P.x+22+25+constanta,P.y);
    line(P.x+22+25+constanta,P.y-15,P.x+22+25+constanta,P.y+15);
    line(P.x+22+25+constanta,P.y,P.x+22+25+33+2*constanta,P.y);
    circle(P.x,P.y,4);
    circle(P.x+22+25+33+2*constanta,P.y,4);
    return;
}
void ampermetru(componenta &P, double constanta)
{
    line(P.x,P.y,P.x+25+constanta,P.y);
    circle(P.x+25+15+constanta,P.y,14+constanta/4);
    line(P.x+25+15+14+constanta,P.y,P.x+25+15+20+20+2*constanta,P.y);
    line(P.x+25+15+constanta,P.y-14,P.x+30+constanta,P.y+8);
    line(P.x+25+15+constanta,P.y-14,P.x+49+constanta,P.y+8);
    line(P.x+34+constanta,P.y,P.x+46+constanta,P.y);
    circle(P.x,P.y,4);
    circle(P.x+25+15+20+20+2*constanta,P.y,4);
    return;
}
void voltmetru(componenta &P,double constanta)
{
    line(P.x,P.y,P.x+25+constanta,P.y);
    circle(P.x+25+15+constanta,P.y,14+constanta/4);
    line(P.x+25+15+14+constanta,P.y,P.x+25+15+20+20+constanta*2,P.y);
    line(P.x+25+15+constanta,P.y+12,P.x+25+5+constanta,P.y-10);
    line(P.x+25+15+constanta,P.y+12,P.x+25+24+constanta,P.y-10);
    circle(P.x,P.y,4);
    circle(P.x+25+15+20+20+2*constanta,P.y,4);
    return;
}
void condensator(componenta &P,double constanta)
{
    line(P.x,P.y,P.x+30+constanta,P.y);
    line(P.x+30+20+constanta,P.y,P.x+30+20+30+constanta*2,P.y);
    line(P.x+30+constanta,P.y-17-constanta,P.x+30+constanta,P.y+18+constanta);
    line(P.x+30+20+constanta,P.y-17-constanta,P.x+30+20+constanta,P.y+18+constanta);
    circle(P.x,P.y,4);
    circle(P.x+30+20+30+2*constanta,P.y,4);
    return;
}
void siguranta(componenta &P,double constanta)
{
    line(P.x,P.y,P.x+20+constanta,P.y);
    rectangle(P.x+20+constanta,P.y-5-constanta/4,P.x+60+constanta,P.y+5+constanta/4);
    line(P.x+60+constanta,P.y,P.x+60+20+constanta*2,P.y);
    circle(P.x,P.y,4);
    circle(P.x+60+20+2*constanta,P.y,4);
    return;
}
void tranzistor(componenta &P,double constanta)
{
    circle(P.x+40+constanta,P.y,16+constanta/4);
    line(P.x,P.y,P.x+32+constanta,P.y);
    line(P.x+32+constanta,P.y-8,P.x+32+constanta,P.y+8);
    line(P.x+32+constanta,P.y-3,P.x+32+8+constanta,P.y-10);
    line(P.x+32+8+constanta,P.y-10,P.x+32+8+constanta,P.y-10-11-constanta/4);
    line(P.x+32+constanta,P.y+3,P.x+32+8+constanta,P.y+10);
    line(P.x+32+8+constanta,P.y+10,P.x+32+8+constanta,P.y+10+11+constanta/4);
    circle(P.x,P.y,4);
    circle(P.x+32+8+constanta,P.y-10-11-constanta/4,4);
    circle(P.x+32+8+constanta,P.y+10+11+constanta/4,4);
    return;
}
void initializeaza_nume_fisier()
{
    strcpy(piese[1].nume_fisier,"Sursa_alimentare.txt");
    strcpy(piese[2].nume_fisier,"Rezistor.txt");
    strcpy(piese[3].nume_fisier,"Bec.txt");
    strcpy(piese[4].nume_fisier,"Dioda.txt");
    strcpy(piese[5].nume_fisier,"Ampermetru.txt");
    strcpy(piese[6].nume_fisier,"Voltmetru.txt");
    strcpy(piese[7].nume_fisier,"Condensator.txt");
    strcpy(piese[8].nume_fisier,"Siguranta.txt");
    strcpy(piese[9].nume_fisier,"Tranzistor.txt");
}
void initializeaza(componenta &P)
{
    FILE* f=fopen(P.nume_fisier,"rt");
    fscanf(f,"%s",&P.nume_componenta);
    fscanf(f,"%d%d",&P.x,&P.y);
    fscanf(f,"%d",&P.nrLegaturi);
    for (int i=1; i<=P.nrLegaturi; i++)
        fscanf(f,"%d%d",&P.pLeg[i].x,&P.pLeg[i].y);
    fscanf(f,"\n%c",&P.comanda_desen);
    return;

}
void deseneaza_informatii_1(int fereastra)
{
    setcolor(WHITE);
    cleardevice();
    int x_exit,y_exit,vecx[501],vecy[501];
    int x=getmaxx()/2;
    int y=getmaxy()/10;
    int fontul=8;
    int directia=0;
    int marime_font=5;
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(fontul, directia, marime_font);
    rectangle(-1,-1,160,50);
    outtextxy(80,30,"INAPOI");
    outtextxy(x,y,"INFORMATII - ELEMENTE DE CIRCUIT");
    readimagefile("Sageata.jpg",1300,650,1400,700);
    while(1)
    {

        fontul=8;
        directia=0;
        marime_font=2;
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        settextstyle(fontul, directia, marime_font);
        readimagefile("Sursa_curent.jpg",10,100,150,175);
        outtextxy(160,140,"Sursa de alimentare (ex. baterie, acumulator, generator etc...)");
        readimagefile("Rezistor.jpg",10,200,150,275);
        outtextxy(160,240,"Rezistorul este o componenta care limiteaza fluxul de curent intr-un circuit.");
        readimagefile("Bec.jpg",10,300,150,375);
        outtextxy(160,340,"Becul este o componenta care transforma energia electrica in energie luminoasa.");
        readimagefile("Dioda.jpg",10,400,150,475);
        outtextxy(160,440,"Dioda este o componenta care permite trecerea curentului doar intr-o directie.");
        readimagefile("Ampermetru.jpg",10,500,150,575);
        outtextxy(160,540,"Ampermetru este un dispozitiv care masoara intensitatea curentului care trece intre capetele sale.");
        readimagefile("Voltmetru.jpg",10,600,150,675);
        outtextxy(160,640,"Voltmetrul este un dispozitiv care masoara tensiunea curentului cae trece intre capetele sale.");
        for(int i=0; i<=500; i++)
        {
            x=rand()%getmaxx();
            y=rand()%getmaxy();
            putpixel(x,y,15);
            vecx[i]=x;
            vecy[i]=y;

        }
        delay(500);
        for(int i=0; i<=500; i++)
            putpixel(vecx[i],vecy[i],0);
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit>=1300&&x_exit<=1400&&y_exit>=650&&y_exit<=700)
            deseneaza_informatii_2(fereastra);
        if (x_exit>=0&&x_exit<=160&&y_exit>=0&&y_exit<=50)
            deseneaza_meniul(fereastra);
    }


}
void deseneaza_informatii_2(int fereastra)
{
    setcolor(WHITE);
    cleardevice();
    int x_exit,y_exit,vecx[501],vecy[501];
    int x=getmaxx()/2;
    int y=getmaxy()/10;
    int fontul=8;
    int directia=0;
    int marime_font=5;
    settextstyle(fontul, directia, marime_font);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    rectangle(-1,-1,160,50);
    outtextxy(80,30,"MENIU");
    outtextxy(x,y,"INFORMATII - ELEMENTE DE CIRCUIT");
    fontul=8;
    directia=0;
    marime_font=2;
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    settextstyle(fontul, directia, marime_font);
    readimagefile("Sageata_2.jpg",0,630,115,700);
    while(1)
    {

        readimagefile("Condensator.jpg",10,100,150,175);
        outtextxy(160,140,"Condensatorul este o componenta folosita pentru a stoca temporar sarcina elctrica si energia.");
        readimagefile("Rezistenta.jpg",10,200,150,275);
        outtextxy(160,240,"Siguranta are ca rol buna functionare a circuitului electric, in parametrii normali.");
        readimagefile("Tranzistor.jpg",10,300,150,375);
        outtextxy(160,340,"Tranzistorul actioneaza ca un comutator sau ca un amplificator in circuite electrice.");
        for(int i=0; i<=500; i++)
        {
            x=rand()%getmaxx();
            y=rand()%getmaxy();
            putpixel(x,y,15);
            vecx[i]=x;
            vecy[i]=y;

        }
        delay(500);
        for(int i=0; i<=500; i++)
            putpixel(vecx[i],vecy[i],0);
        getmouseclick(WM_LBUTTONDOWN,x_exit,y_exit);
        if (x_exit>=0&&x_exit<=630&&y_exit>=115&&y_exit<=700)
            deseneaza_informatii_1(fereastra);
        if (x_exit>=0&&x_exit<=160&&y_exit>=0&&y_exit<=50)
            deseneaza_meniul(fereastra);

    }

}
