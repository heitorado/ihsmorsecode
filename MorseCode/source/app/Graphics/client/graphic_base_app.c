#include "ACore.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200

#define LARGURA 728
#define ALTURA 546
#define MAX_LOG_SIZE 17

char morseCode[5] = {".-.-"};

void printMorse(char str[]);


int main() 
{
    //A primeira coisa a ser feita é inicializar os módulos centrais. Caso algum deles falhe, o programa já para por aí.
    if (!coreInit())
        return -1;

    //Agora vamos criar a nossa janela. Largura e Altura em pixels, o título é uma string.
    if (!windowInit(LARGURA, ALTURA, "IHS Morse Code"))
        return -1;

    //Agora inicializamos nosso teclado e mouse, para que a janela responda às entradas deles
    if (!inputInit())
        return -1;

    //Agora inicializamos nossas fontes
    if(!fontInit())
      return -1;

    //E por fim todas as imagens que vamos utilizar no programa.
    if(!loadGraphics())
        return -1;

    //para sair do jogo
    bool running = true;

    int i;
    

    while(running)
    {
        startTimer();

        printMorse(morseCode);

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        FPSLimit();
    }

  allegroEnd();
  return 0;
}

//========================================================FUNCTIONS========================================================
void printMorse(char str[])
{
    al_draw_bitmap(menuScreen,0,0,0);

    al_draw_text(start, al_map_rgb(255, 0, 0), LARGURA / 2, 30, ALLEGRO_ALIGN_CENTRE, "Type In your Morse Code");

    if (strlen(str) > 0)
    {
        al_draw_text(start, al_map_rgb(255, 0, 0), LARGURA / 2,
                     (ALTURA - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }
    else
    {
        al_draw_text(start, al_map_rgb(255, 255, 255), LARGURA / 2,
                     (ALTURA - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "Sem entrada");
    }
}