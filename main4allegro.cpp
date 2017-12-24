#include <allegro.h>
#include <math.h>
#include <cstdlib>
#include <iostream>


#define szerokosc 7
#define wysokosc 6
#define kratka 100

using namespace std;

BITMAP * bufor = NULL;
BITMAP * czerwony = NULL;
BITMAP * zolty = NULL;
int mx, my, mb;

void myszka() //funkcja obslugujaca mysz na ekranie
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b ) //stale przypisywanie wspolrzednych kursora i stanu przycisku do zmiennych
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
}

void czerwonyNaPole(int x, int y)
{
        masked_blit( czerwony, bufor, 0, 0, x*kratka, y*kratka, kratka, kratka );
}

void zoltyNaPole(int x, int y)
{
       masked_blit( zolty, bufor, 0, 0, x*kratka, y*kratka, kratka, kratka );
}


int main()
{

    int tablicaDoGry[7][6];

    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 6; ++j)
            tablicaDoGry[i][j] = 0;

    mx = my = mb = 0;
    allegro_init();
    install_keyboard();
    set_color_depth( 32 ); //glebia koloru
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, szerokosc*kratka, wysokosc*kratka, 0, 0 ); //rozmiar okna

    clear_to_color( screen, makecol( 128, 128, 128 ) ); //kolor okna
    bufor = create_bitmap( szerokosc*kratka, wysokosc*kratka ); //rozmiar
    czerwony = load_bmp("czerwony.bmp",default_palette);
    zolty = load_bmp("zolty.bmp",default_palette);

    install_mouse(); //mysz
    //select_mouse_cursor(MOUSE_CURSOR_BUSY); //inny kursor myszki
    show_mouse( screen ); //wyswietlanie myszy na ekranie
    unscare_mouse();


    while( !key[ KEY_ESC ] ) //petla stale odsWiezajaca ekran
    {
        clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor tla
        //textprintf_ex( bufor, font, 250, 40, makecol( 200, 200, 200 ), - 1, "GRAJ"); //napis
        //clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor
            myszka();
        for(int i=1; i<7; i++)
        {
            vline(bufor, i*kratka, 0, wysokosc*kratka, makecol(255,255,255));  //rysowanie siatki pol
        }
        for(int i=1; i<6; i++)
        {
            hline(bufor, 0, i*kratka, szerokosc*kratka, makecol(255,255,255));
        }


                int x=NULL, y=NULL;
                if(mb==1)
                {
                    x=floor(mx/kratka); //przerobienie pikseli na wspolrzedne pola
                    y=floor(my/kratka);
                    cout << "czerwony na " << x << " " << y << endl;
                    tablicaDoGry[x][y]=1;
                }
                if(mb==2)
                {
                    x=floor(mx/kratka); //przerobienie pikseli na wspolrzedne pola
                    y=floor(my/kratka);
                    cout << "zolty na " << x << " " << y << endl;
                    tablicaDoGry[x][y]=-1;
                }

    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 6; ++j)
            if(tablicaDoGry[i][j] == 1)
                czerwonyNaPole(i,j);
            else if(tablicaDoGry[i][j]==-1)
                zoltyNaPole(i,j);



        blit( bufor, screen, 0, 0, 0, 0, szerokosc*kratka, wysokosc*kratka ); //przeniesienie z bufora na ekran
        rest(100);
    }
    destroy_bitmap( bufor ); //zwalanianie pamieci


    allegro_exit();
}
END_OF_MAIN();
