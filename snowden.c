#include <stdio.h>
#include <omp.h>
#include "include\conio.h"
#include "include\conio.c"
#include <windows.h>
#define ENTER 13
#define NLIN 23
#define NCOL 60
#define MAXSCORE 6

typedef long time_t;
time_t time( time_t *x);
#define CLOCKS_PER_SEC 1000000
typedef long clock_t;
clock_t clock( void);

void move_cursor(int x, int y)
{
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//Pega texto de um txt e printa na tela
void print_image(FILE *fptr)
{
    char read_string[128];
    int x=15,y=8;
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
    {
        move_cursor (x,y);
        printf("%s",read_string);
        y++;
    }

}

void print_intrusctions(FILE *fptr)
{
    char read_string[256];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
    {
        printf("%s",read_string);
    }

}

//le o arquivo gameover.txt e imprime a ASC art na tela
gameovertitle()
{
    char *filename = "extras/gameover.txt";
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
    }
    textcolor (15);
    print_image(fptr);

    move_cursor (20,17);

    fclose(fptr);
    Sleep (5000);
    system ("cls");
}
//escreve a titlescreen
escrevetitle()
{
    char *filename = "extras/snowden.txt";
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
    textcolor (15);
    print_image(fptr);

    move_cursor (20,17);
    printf ("By Mario & Ricardo");

    fclose(fptr);
    Sleep (5000);
    system ("cls");
    fflush(stdin);
    return 0;
}
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< //

//struct do highscores
typedef struct score_entry
{
    char nome[40];
    int score;
} score_entry;

escreveintro() /*escreve a intro do game, falta colocar a title screen!*/
{
    char texto[] = "Em 2013, um homem revelou ao mundo um sistema global de vigilancia em massa que chocou o planeta.\n\n\nNos mostrou que um futuro distopico onde um governo controla todos seus cidadaos nao eh exclusivo de obras ficticias ou filmes de hollywood.\n\n\nEle era um homem comum com um emprego comum, porem as circunstancias e seu senso de dever etico perante outros seres humanos ditaram que ele entraria para a historia como a pessoa que arriscou sua vida e a propria liberdade para poder revelar esta infame quebra ao direito a privacidade.";
    char pretitle[] = "Ele era apenas um mero tecnico de seguranca\n                 E seu nome era...";
    int i=0,j=0, skip = 1;


    do
    {
        textcolor(15);
        if (kbhit())
            skip = 0;
        if (texto[i]== '\0')
        {
            Sleep (3000);
            system("cls");
            move_cursor (15, 10);
            while (pretitle[j] != '\0')
            {
                printf ("%c",pretitle[j]);
                j++;
                Sleep(100);
            }
            Sleep(3000);
            //colocar title screen aqui, antes do skip!
            skip = 0;
        }
        else
        {
            printf ("%c",texto[i]);
            Sleep(100);
        }
        i++;
    }
    while (skip!=0);


}


instrucoes()
{
    char *filename = "extras/instrucoes.txt";
    FILE *fptr = NULL;
    int exit = 1;

    system ("cls");
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
    textcolor (15);
    print_intrusctions(fptr);

    fclose(fptr);
    fflush(stdin);
    do{
    {if (kbhit())
    exit = 0;
    }}
    while (exit ==1);
    fflush(stdin);
    system ("cls");
    return 0;
    }

//funcao ordena e da display nos highscores
le_score ()
{
    score_entry entrada,exchange,listaentries[5];
    char *filename = "highscores.bin";
    FILE *fptr = NULL;
    int i=0,j,trocou,skip=0,x,y;

    if((fptr = fopen(filename,"r+b")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
    }
    rewind (fptr);
    for (i=0; i<5; i++)
    {
        fread (&entrada,sizeof(score_entry),1,fptr);
        listaentries[i]=entrada;
    }

    for (i=0; i<5; i++)
    {
        for(j=0; j<4; j++)
        {
            if (listaentries[j].score < listaentries[j+1].score)
            {
                exchange = listaentries[j+1];
                listaentries[j+1] = listaentries[j];
                listaentries[j] = exchange;
            }
        }
    }
    move_cursor(29,3);
    textcolor (10);
    printf ("===  HIGHSCORES ===\n");
    x=15;
    y=10;
    for (i=0; i<5; i++)
    {
        move_cursor (x,y);
        printf ("%-40s%10d\n",listaentries[i].nome,listaentries[i].score);
        y++;
    }
    fflush(stdin);
    do
    {if (kbhit())
        skip=1;
    }while (skip ==0);

    fclose(fptr);

}


imprimemenu (int possetax,int possetay,char ummenu[7][35]) /* da print no menu*/
{
    int i=0,y=25,x=6,j,posx,posy;

    for (i=0; i<7; i++)
    {
        move_cursor(y,x);
        for(j=0; j<25; j++)
        {
            if (i==possetax && j==possetay)
            {
                textcolor (4);
                printf("%c", '>');
            }
            else
            {
                textcolor(2);
                printf ("%c", ummenu[i][j]);
            }
        }
        x=x+2;
    }

}

//Funcao pega um numero, pergunta o nome do jogador e guarda o nome & score

verifica_score (int number)
{
    score_entry entrada;
    char *filename = "highscores.bin";
    FILE *fptr = NULL;
    int cont=0,cont2=0;
    int i;
    int lowest = 20000000,poslowest=0;
    int encontrou = 0;

    if((fptr = fopen(filename,"r+b")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
    }
    rewind (fptr);
    while (cont<5 && (encontrou == 0))
    {   cont++;
        fread (&entrada,sizeof(score_entry),1,fptr);
        if (entrada.score<lowest)
        {
            lowest=entrada.score;
            poslowest = cont-1;
        }
    }

    if (number > lowest)
    {
        system("cls");
        entrada.score = number;
        textcolor(WHITE);
        move_cursor(25,10);
        printf("|------- HIGH SCORE----------------------|\n");
        move_cursor(25,12);
        printf("|------- --------------------------------|\n");
        move_cursor(25,11);
        printf ("|-entre com seu nome: ");

        gets (entrada.nome);
        fseek (fptr,poslowest*(sizeof (score_entry)),SEEK_SET);
        fwrite(&entrada,sizeof(score_entry),1,fptr);
    }
    fclose(fptr);


}

/* move a seta '>' vermelha para cima e para baixo, fiz com poteiros para que "gamemenu"
pudesse acessar a posicao da tela, que eh usada para determinar a opcao selecionada*/

int movmenu (int *px, int *py, int cimabaixo)
{
    _setcursortype(_NOCURSOR);
    if (cimabaixo == 0)
    {
        if ((*px)<16)
        {
            move_cursor (*py,*px);
            printf (" ");
            *px= *px + 2;
            move_cursor (*py,*px);
            textcolor (4);
            printf (">");
        }
    }
    else if ((*px)>8)
    {
        move_cursor (*py,*px);
        printf (" ");
        *px= *px - 2;
        move_cursor (*py,*px);
        textcolor (4);
        printf (">");
    }
}

int gamemenu() /*funçao cria o menu (usando imprimemenu) e faz manipulações (usando movmenu) returna um numero q representa a opcao do menu selecionada (o numero eh a coordenada da flecha vermelha*/
{
    int possetax= 1,possetay=1,skip =0,x=8,y=26,px=x,py=y,cimabaixo,opcao;
    char tecla;
    char menu[7][35]= {"* * * * * * * * * * * * * * * * *",
                       "  (1)Novo Jogo\n",
                       "  (2)Carregar Jogo",
                       "  (3)Ajuda",
                       "  (4)High Scores",
                       "  (5)Sair",
                       "* * * * * * * * * * * * * * * * *"
                      };


    imprimemenu (possetax, possetay,menu);

    move_cursor (12,20);
    textcolor (2);
    printf ("** Use W & S para selecionar a opcao e F para confirmar **");
    move_cursor (29,3);
    printf ("===  SNOWDEN ===");


    /* se quisermos printar qualquer outra coisa no menu, colocar commando aqui, antes do "do", lembrando que n pode sobescrever a matriz do menu */

    do
    {
        if (kbhit())
        {
            tecla=getch();
            /* tenho quer ver como trocar s,w e f por setas e enter, segundo a tabela ASC "enter" eh o numero 13 mas n funciona*/
            switch (tecla)
            {
            case 's':
                cimabaixo = 0;
                movmenu (&px,&py,cimabaixo);
                break;
            case 'w':
                cimabaixo = 1;
                movmenu(&px,&py,cimabaixo);
                break;
            case '1':
                opcao = 8;
                skip = 1;
                break;
            case '2':
                opcao = 10;
                skip = 1;
                break;
            case '3':
                opcao = 12;
                skip = 1;
                break;
            case '4':
                opcao = 14;
                skip = 1;
                break;
            case '5':
                opcao = 16;
                skip = 1;
                break;
            case 'f':
                opcao =px;
                skip = 1;
                break;
            }

        }

    }
    while (skip== 0);
    return opcao;
}
int menu()
{
    /* variavel opçao fica como variavel do main, da pra fazer por ponteiros, mas acho mais organizado assim */
    int opcao;
    system ("cls");
    opcao = gamemenu();
    textcolor (15);
    system ("cls");
    switch (opcao)
    {
    case 8:
        opcao = 1;
        break;
    case 10:
        opcao = 3;
        break;
    case 12:
        instrucoes();
        fflush(stdin);
        break;
    case 14:
        le_score();
        break;
    case 16:
        opcao = 5;
    }
    return opcao;
}
//**********************************************************//

//**************** FUNCOES MENORES ************************//
void user_interface ()
{
    move_cursor(62,1);
    textcolor(15);
    printf("|---------------|\n");
    move_cursor(62,2);
    printf("|--- SNOWDEN ---|\n");
    move_cursor(62,3);
    printf("|---------------|\n");
    move_cursor(0,0);
}

void game_score(int score)
{
    textcolor(15);
    move_cursor(62,5);
    printf("|---------------|\n");
    move_cursor(62,6);
    printf("|-SCORE: %.4d --|\n", score);
    move_cursor(62,7);
    printf("|---------------|\n");

}

void abre_caminho(int x,int y,char matrix[23][60])
{
    matrix[y-1][x-1]='v';

}
//***********************************************************//

//************** DEFINIÇÕES DE ESTRUTURAS ******************//
struct snowden
{
    int x;
    int y;
    int last_pos;
    int score;
};

struct fantasmas
{
    int x;
    int y;
    int last_pos;
    int direcao;
} T_GHOST;

struct score
{
    char nome[40];
    int score;
} TIPO_SCORE;

struct disparo
{
    int ativo;
    int x;
    int y;
    int direcao;
};
//**********************************************************//

continua()
{
    system("cls");
    printf("Continuar (S/N) ?");
    int tecla;
    do
    {
        if(kbhit())
        {
            tecla = getch();
            tecla = toupper(tecla);
            switch(tecla)
            {
            case 'N':
                system("cls");
                //menu();
                break;
            case 'S':
                system("cls");
                //new_game();
                break;
            default:
                system("cls");
                // continua();
            }
        }

    }
    while((tecla != 'N') || (tecla != 'S'));
}

int imprime(FILE *fase,char matrix[23][60], struct snowden *snowden,int local_ninho[])
{
    int i;
    int frutas;
    int letra;
    int j;

    //preenche a matriz atraves do arquivo.
    for(i=0; i<23; i++)
    {
        for(j=0; j<60; j++)
        {
            matrix[i][j] = fgetc(fase);
        }
        //recebe o '\n' para nao ser lido na matrix
        letra = fgetc(fase);
    }

    //coloca a borda superior.
    for(i=0; i<62; i++)
    {
        textcolor(4);
        printf("%c",178);
    }
    printf("\n");

    //imprime a matriz de acordo com cada caracter
    for(i = 0; i < 23; i++)
    {
        //borda lateral esquerda
        textcolor(4);
        printf("%c",178);

        for(j=0; j<60; j++)
        {
            switch(matrix[i][j])
            {
            //Substituição na impressão de v por caminhos paro Lord.
            case 'v':
                printf("%c",32);
                break;
            //Substituição na impressão de p por paredes que bloqueiam a passagem dos fantasmas.
            case 'p':
                textcolor(7);
                printf("%c",176);
                break;
            //Representa o ninho de fantasmas na cor roxa.
            case 'n':
                //guarda as coordenadas do ninho.
                textcolor(5);
                printf("%c",206);
                local_ninho[0] = j+1;
                local_ninho[1] = i+1;
                matrix[i][j] = 'v';
                break;
            //Representação do Lord na cor Verde-água claro.
            case 'd':
                printf("%c",32);
                snowden->x=j+1;
                snowden->y=i+1;
                break;
            //Representação das Futras na cor Vermelha;
            case 'f':
                textcolor(4);
                printf("%c",229);
                frutas++;
                break;
            //Representação das Fantasmas na cor Branca;
            case 'i':
                textcolor(15);
                printf("%c",153);
                break;

            }
        }
        //coloca a borda lateral direita
        textcolor(4);
        printf("%c",178);
        printf("\n");
    }

    //coloca a borda inferior.
    for(i=0; i<62; i++)
    {
        textcolor(4);
        printf("%c",178);
    }
    return frutas;

}

char save_game(char matrix[23][60], struct snowden snowden)
{
    char opcao;
    int parou;
    int i;
    int j;
    FILE *arq;

    arq = fopen("continuar.txt","w");
    if(arq== NULL)
        printf("\nErro ao abrir arquivo!");
    else
    {
        move_cursor(20,26);
        textcolor(15);
        printf("Salvar progresso? (S/N):");
        do
        {
            if(kbhit())
            {
                opcao = getch();
                opcao = toupper(opcao);
                if(opcao == 'N')
                {
                    parou = 1;
                    move_cursor(20,26);
                    printf("                        ");

                }
                else if(opcao == 'S')
                {
                    parou = 1;
                    move_cursor(20,26);
                    printf("                        ");
                    for(i=0; i<NLIN; i++)
                    {
                        for(j=0; j<NCOL; j++)
                        {
                            fputc(matrix[i][j],arq);
                        }
                        fputc('\n',arq);
                    }
                    system("cls");
                    printf("\n Arquivo salvo com sucesso!!");
                    Sleep(1500);
                    fclose(arq);
                    return opcao;
                }
                else parou = 0;

            }
        }
        while(parou != 1);
    }

}

int move_lord(struct snowden *snowden,char matrix[23][60],int local_ninho[], int game_over)
{
    int direcao;
    srand( (unsigned)time(NULL) );

    int tecla;
    char gravar;
    int pause=0;
    int frutas = 32;
    int posicao =1;
    int ninho = 1;
    char cima,baixo,esquerda,direita;
    //variaveis para os fantasmas
    struct fantasmas fantasmas[10];
    int i;
    int x,y,x_ant,y_ant;
    int ind;
    int num_fantasmas=0;
    int ativa=01;
    //**************************
    struct disparo tiro;
    tiro.ativo == 0;
    _setcursortype(_NOCURSOR);
    game_score(snowden->score);

    do
    {
        //****************************** EFETUA DISPARO ********************************//
        if(tiro.ativo == 1)
        {
            if(tiro.x > 0 && tiro.x < 61)
            {
                if(tiro.y > 0 && tiro.y < 24)
                {
                    for(ind=0; ind<num_fantasmas; ++ind)
                    {
                        if(tiro.y == fantasmas[ind].y && tiro.x == fantasmas[ind].x)
                          {
                              fantasmas[ind].y = -1;
                              snowden->score += 10;
                              game_score(snowden->score);
                              tiro.ativo =0;
                          }

                    }

                    if(matrix[tiro.y-1][tiro.x-1]== 'v' || matrix[tiro.y-1][tiro.x-1]== 'n')
                    {
                        move_cursor(tiro.x,tiro.y);
                        textcolor(15);
                        printf("%c",250);
                        Sleep(25);
                        move_cursor(tiro.x,tiro.y);
                        printf("%c",32);

                    }
                    else if(matrix[tiro.y-1][tiro.x-1]== 'i')
                    {
                        snowden->score += 10;
                        game_score(snowden->score);
                        move_cursor(tiro.x,tiro.y);
                        printf("%c",32);
                        matrix[tiro.y-1][tiro.x-1]= 'v';
                        tiro.ativo =0;
                    }
                    else if(matrix[tiro.y-1][tiro.x-1]== 'f')
                    {
                        move_cursor(tiro.x,tiro.y);
                        printf("%c",32);
                        matrix[tiro.y-1][tiro.x-1]= 'v';
                        tiro.ativo =0;
                    }
                    else
                        tiro.ativo =0;

                    switch(tiro.direcao)
                    {
                    case 1:
                        tiro.y--;
                        break;
                    case 2:
                        tiro.x++;
                        break;
                    case 3:
                        tiro.y++;
                        break;
                    case 4:
                        tiro.x--;
                        break;


                    }
                }
                else tiro.ativo =0;
            }
            else tiro.ativo =0;
        }
        //*************************************************************************//

        //define o tempo para os fantasmas
        i = clock()/1000;
        i = i%3;

        // cria um fantasma a cada tres segundos
        if(num_fantasmas <10)
        {
            if(i == 2)
                ativa = 0;

            if(i == 0 && ativa == 0 )
            {
                // recebe a coordenada x do ninho
                fantasmas[num_fantasmas].x = local_ninho[0];
                fantasmas[num_fantasmas].y = local_ninho[1];
                fantasmas[num_fantasmas].direcao = 3;
                ativa =1;
                num_fantasmas ++;
            }
        }
        //********************** movimenta fantasma***********************//

        if(num_fantasmas!= 0)
        {
            for(ind=0; ind<num_fantasmas; ++ind)
            {
                direcao = rand();
                x = fantasmas[ind].x;
                y = fantasmas[ind].y;
                esquerda = matrix[y-1][x-2];
                direita = matrix[y-1][x];
                cima = matrix[y-2][x-1];
                baixo = matrix[y][x-1];
                if(fantasmas[ind].y != -1)
                if(x > 0 && x < 60 && y > 0 && y < 23)
                {
                    //se a direcao do fantasmas for para baixo, entao verifca quais os possiveis caminhos.
                    if(fantasmas[ind].direcao  == 3)
                    {
                        //se houver caminho para baixo, esquerda e direita sorteia uma das tres direções
                        if(baixo == 'v' && esquerda == 'v' && direita == 'v')
                        {
                            fantasmas[ind].direcao = direcao%3;
                            if(fantasmas[ind].direcao == 0)
                                fantasmas[ind].direcao == 3;
                        }
                        //se houver apenas caminho para esquerda e direita
                        else if(esquerda == 'v' && direita == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao == 0)
                                fantasmas[ind].direcao == 2;
                        }
                        //se houver caminho apenas para esquerda e para baixo
                        else if(baixo == 'v' && esquerda == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            fantasmas[ind].direcao == 3;
                        }
                        //se houver caminho apenas para direita e para baixo
                        else if(baixo == 'v' && direita == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                                fantasmas[ind].direcao == 3;

                        }
                        //senao se houver apenas caminho a esquerda.
                        else if(esquerda == 'v')
                            fantasmas[ind].direcao == 2;
                        //senao se houver apenas caminho a direita.
                        else if(direita == 'v')
                            fantasmas[ind].direcao == 1;
                        //senao se houver apenas caminho para baixo , entao mantem a direcao
                        else if(baixo == 'v')
                            fantasmas[ind].direcao == 3;
                        //senao nao ha caminhos possiveis, entao retorna para o caminho de origem.
                        else
                            fantasmas[ind].direcao == 0;
                    }

//senao se a direcao do fantasma for para cima então verifca quais os possiveis caminhos.
                    else if(fantasmas[ind].direcao == 0)
                    {
                        //se houver caminho para cima, esquerda e direita sorteia umas das tres direcoes.
                        if(cima == 'v' && esquerda == 'v' && direita == 'v')
                            fantasmas[ind].direcao = direcao%3;
                        //senao se houver apenas caminhos para a direita e esquerda , entao sorteia  uma das duas.
                        else if(esquerda == 'v' && direita == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao == 0)
                                fantasmas[ind].direcao == 2;
                        }
                        //senao se houver apenas caminhos para cima e esquerda, entao sorteia uma dos dois.
                        else if(cima == 'v' && esquerda == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                                fantasmas[ind].direcao == 0;

                        }
                        //senao se houver apenas caminhos para cima e direita, entao sorteia uma dos dois.
                        else if(cima == 'v' && direita == 'v')
                        {
                            fantasmas[ind].direcao = 0;
                        }
                        //senao se houver apenas caminho a esquerda.
                        else if(esquerda == 'v')
                            fantasmas[ind].direcao = 2;
                        //senao se houver apenas caminho a direita.
                        else if(direita == 'v')
                            fantasmas[ind].direcao = 1;
                        //senao se houver apenas caminho para cima.
                        else if(cima == 'v')
                            fantasmas[ind].direcao = 0;
                        //senao nao ha caminhos possiveis, entao  retorna para o caminho de origem.
                        else fantasmas[ind].direcao = 3;
                    }
//senao se a direcao do fantasma for para a esquerda entao verifica quais os possiveis caminhos.
                    else if(fantasmas[ind].direcao == 2)
                    {
                        //se houver caminho para esquerda, cima e baixo, entao sorteia uma das tres direcoes.
                        if(esquerda == 'v' && cima == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%3;
                            if(fantasmas[ind].direcao = 1)
                                fantasmas[ind].direcao = 3;
                        }
                        //senao se houver caminhos para cima e baixo, entao sorteia um dos dois.
                        else if(cima == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao = 1)
                                fantasmas[ind].direcao = 3;
                        }
                        //senao se houver caminhos para a esquerda e para baixo.
                        else if(esquerda == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao = 0)
                                fantasmas[ind].direcao = 2;
                            else
                                fantasmas[ind].direcao = 3;

                        }
                        //senao se houver caminhos para esquerda e para cima.
                        else if(esquerda == 'v' && cima == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao = 1)
                                fantasmas[ind].direcao = 2;
                        }
                        //senao se houver apenas caminho para cima.
                        else if(cima == 'v')
                            fantasmas[ind].direcao = 0;
                        //senao se houver apenas caminho para baixo.
                        else if(baixo == 'v')
                            fantasmas[ind].direcao = 3;
                        //senao se houver apenas caminho a esquerda.
                        else if(esquerda == 'v')
                            fantasmas[ind].direcao = 2;
                        //senao nao ha caminhos possiveis, entao retornar para o caminho de origem (direita).
                        else
                            fantasmas[ind].direcao = 1;

                    }
//senao a direcao do fantasmas é a direita, entao verifica quais os possiveis caminhos
                    else
                    {
                        //se houver caminhos para direita, cima e baixo, entao sorteia uma das tres direcoes.
                        if(direita == 'v' && cima == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%3;
                            if(fantasmas[ind].direcao = 2)
                                fantasmas[ind].direcao = 3;
                        }
                        //senao se houver caminhos para cima e baixo , entao sorteia um dos dois caminhos.
                        else if(cima == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao = 1)
                                fantasmas[ind].direcao = 3;

                        }
                        //senao se houver caminhos para direita e cima.
                        else if(direita == 'v' && cima == 'v')
                            fantasmas[ind].direcao = direcao%2;
                        //senao se houver caminhos para direita e baixo.
                        else if(direita == 'v' && baixo == 'v')
                        {
                            fantasmas[ind].direcao = direcao%2;
                            if(fantasmas[ind].direcao = 0)
                                fantasmas[ind].direcao = 3;
                        }
                        //senao se houver apenas caminho para cima.
                        else if(cima == 'v')
                            fantasmas[ind].direcao = 0;
                        //senao se houver apenas caminho para baixo.
                        else if(baixo == 'v')
                            fantasmas[ind].direcao = 3;
                        //senao se houver apenas caminho a direita, entao mantem mesma direcao.
                        else if(direita == 'v')
                            fantasmas[ind].direcao = 1;
                        //senao nao ha caminho possivel, entao retornar para o caminho de origem (esquerda).
                        else fantasmas[ind].direcao = 2;
                    }



                    //printa o fantasma
                    move_cursor(x,y);
                    textcolor(15);
                    printf("%c",153);
                    //guarda a posição antiga do fantasma
                    x_ant = x;
                    y_ant = y;


                    switch(fantasmas[ind].direcao)
                    {
                    case 0:
                        fantasmas[ind].y--;
                        break;
                    case 1:
                        fantasmas[ind].x++;
                        break;
                    case 2:
                        fantasmas[ind].x--;
                        break;
                    case 3:
                        fantasmas[ind].y++;

                        break;
                    }
                    x = fantasmas[ind].x;
                    y = fantasmas[ind].y;


                    move_cursor(fantasmas[ind].x,fantasmas[ind].y);
                    textcolor(15);
                    printf("%c",153);

                    move_cursor(x_ant,y_ant);
                    printf("%c",32);
                    Sleep(150/num_fantasmas);

                }
            }
        }
        //****************************************************************************************/


        //verifica se o snowden esta dentro dos limites do cenário para executar o proximo movimento.
        if(snowden->x > 0 && snowden->x < 61)
        {

            if(snowden->y > 0 && snowden->y < 24)
            {
                move_cursor(snowden->x,snowden->y);
                textcolor(11);
                printf("%c",227);

                //verifica a colisao do snowden com o fantasma.
                for(ind=0; ind<num_fantasmas; ind++)
                {
                    if(snowden->y-1 == fantasmas[ind].y-1 && snowden->x-1 == fantasmas[ind].x-1)
                    {

                        Sleep(1000);
                        system("cls");
                        game_over = 1;
                        i = -1;
                        gameovertitle();
                    }
                }

                //verifica se o snowden pegou uma fruta.
                if (matrix[snowden->y-1][snowden->x-1]=='f')
                {
                    abre_caminho(snowden->x,snowden->y,matrix);
                    snowden->score = snowden->score +50;
                    game_score(snowden->score);
                    frutas--;
                }

                if(ninho == 1)
                {
                    move_cursor(local_ninho[0],local_ninho[1]);
                    textcolor(5);
                    printf("%c",206);
                }
                //aguarda o player pressionar alguma tecla
                if(kbhit())
                {
                    tecla = getch();
                    switch(tolower(tecla))
                    {
                    case 'w':
                        move_cursor(snowden->x,snowden->y);
                        if(matrix[snowden->y-1][snowden->x-1]!='n')
                            abre_caminho(snowden->x,snowden->y,matrix);
                        printf("%c",32);
                        snowden->y--;
                        posicao = 1;
                        break;
                    case 'd':
                        move_cursor(snowden->x,snowden->y);
                        if(matrix[snowden->y-1][snowden->x-1]!='n')
                            abre_caminho(snowden->x,snowden->y,matrix);
                        printf("%c",32);
                        snowden->x++;
                        posicao = 2;
                        break;
                    case 's':
                        move_cursor(snowden->x,snowden->y);
                        if(matrix[snowden->y-1][snowden->x-1]!='n')
                            abre_caminho(snowden->x,snowden->y,matrix);
                        printf("%c",32);
                        snowden->y++;
                        posicao = 3;
                        break;
                    case 'a':
                        move_cursor(snowden->x,snowden->y);
                        if(matrix[snowden->y-1][snowden->x-1]!='n')
                            abre_caminho(snowden->x,snowden->y,matrix);
                        printf("%c",32);
                        snowden->x--;
                        posicao = 4;
                        break;
                    case 32:
                        printf("\a");
                        if(tiro.ativo != 1)
                        {
                            tiro.ativo = 1;
                            tiro.x = snowden->x;
                            tiro.y = snowden->y;
                            tiro.direcao = posicao;
                        }
                        break;
                    case 'p':

                        matrix[snowden->y][snowden->x] = 'd';
                        matrix[local_ninho[1]][local_ninho[0]] = 'n';
                        gravar = save_game(matrix,*snowden);
                        if(gravar == 'S')
                        game_over = 1;

                        break;
                    default:
                        break;

                    }

                }
            }
            //se o snowden atingir a paredes então volta para a posição anterios.
            else if(snowden->y>=23)
                snowden->y--;
            else
                snowden->y++;
        }
        //se o snowden atingir a paredes então volta para a posição anterios.
        else if(snowden->x>=60)
            snowden->x--;
        else
            snowden->x++;

        if(frutas == 0)
        {
            game_over = 1;
        }

    }//Fim do laco principal
    while(game_over == 0 && i != -1 && frutas != 0);
    // verifica se o jogador fez uma pontuacao maior que as anteriores
    if(frutas != 0)
    {
        verifica_score(snowden->score);
        return 0;
    }
    else
        return 1;
}
epilogue()
{
    char *filename = "extras/epilogue.txt";
    char *filename2 = "extras/endtext.txt";
    FILE *fptr = NULL;
    int exit= 1;

    system("cls");
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
    }
    textcolor (15);
    print_image(fptr);

    move_cursor (20,17);

    fclose(fptr);
    move_cursor (0,0);
    Sleep (2000);

    system ("cls");

    if((fptr = fopen(filename2,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename2);
        return 1;
    }
    textcolor (15);
    print_intrusctions(fptr);

    fclose(fptr);
    fflush(stdin);
    do{
    {if (kbhit())
    exit = 0;
    }}
    while (exit ==1);
    fflush(stdin);
    system ("cls");

}

main()
{
    char matrix[23][60];
    int local_ninho[2];
    FILE *fase;
    int next;
    int opcao;
    int game_over =0;
    struct snowden snowden;

    escreveintro();
    system ("cls");
    escrevetitle();

    do
    {
        opcao = menu();

        //caso a opcao for igual a 1 então inicia um novo jogo.
        if(opcao == 1)
        {
            fase = fopen("fase1.txt", "rt");
            if(fase == NULL)
            {
                printf("Nao foi possivel carregar a fase...\n");
            }
            else
            {
                //quando for um novo jogo escore zero.
                user_interface();
                snowden.score = 0;
                imprime(fase,matrix,&snowden,local_ninho);
                next = move_lord(&snowden,matrix,local_ninho, game_over);
                if(next == 1)
                {
                    system("cls");
                    move_cursor(32, 13);
                    textcolor(WHITE);
                    printf("**-----Level 2-----*** ");
                    Sleep(1500);
                    system("cls");
                    move_cursor(0,0);
                    fase = fopen("fase2.txt", "rt");
                    if(fase == NULL)
                        printf("Nao foi possivel carregar a fase...\n");
                    else
                    {
                        //quando proseguir para proxima faze continua com score anterior
                        user_interface();
                        imprime(fase,matrix,&snowden,local_ninho);
                        next  = move_lord(&snowden,matrix,local_ninho, game_over);
                        if(next == 1)
                        {
                            verifica_score(snowden.score);
                            epilogue();
                        }


                    }

                }
            }

        }

        //senao continua o jogo salvo se existir.
        else if(opcao  == 3)
        {
            fase = fopen("continuar.txt", "rt");
            if(fase == NULL)
            {
                printf("Voce nao possui nenhum jogo salvo...\n");
                Sleep(2500);
            }
            else
            {
                snowden.score = 0;
                user_interface();
                //quando carregar o jogo salvo carrega o score salvo.
                imprime(fase,matrix,&snowden,local_ninho);
                move_lord(&snowden,matrix,local_ninho, game_over);
            }
        }


    }
    while(opcao!=5);

}




