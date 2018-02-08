/*
  Author : Matteo Marzio
  Start Date : 07-02-2018
  Finish Date : 08-02-2018
  Current Version : 1.2

  ChangeLog:
    Version 1.2
    ---- Final Build
    ---- Ultime correzioni
    ---- Parti debug commentate e nascoste all'utente finale
    ---- Deployment
      ----Correzione Bug
    Version 1.1
    ---- Miglioramento Stampa valori
    ---- Ancora presente il bug dell' 11esimo valore
    Version 1.0
    ----Initial Build


################################################################################
  Gioco:
  CARTE
  Le carte sono gestite in questo modo
  asso 2 3 4 5 6 7 fante cavallo re
  1    2 3 4 5 6 7 8      9      10

  Se nella lista compare 0, significa che quella carta e' gia' stata presa

  I semi sono gestiti in questo modo:

  denari coppe spade bastoni
  1       2     3      4

  Sia il giocatore che la CPU hanno 3 carte, ognuna con un seme X preciso.
  Ho optato l'utilizzo di una lista multidimensionale con 3 colonne e 2 righe.
  Dopotutto, la prima riga indica il seme della carta, la seconda indica il
  valore della carta stessa.
  Quindi, nella pratica:
    mano_giocatore[2,3] e mano_cpu[2,3]

                    3 colonne
               seme1   seme2   seme3
2 righe        valore1 valore2 valore3

  PUNTI
  Sapendo che ci sono 3 casi, ovvero vincita perdita e pareggio, non ha senso
  controllare chi ha superato 61, come nel gioco. Basta fare un controllo su
  quale tra i due punteggi sia quello piu' grande.
  Quindi, nella pratica:
    punteggio_giocatore e punteggio_CPU, inizializzati a 0

  GESTIONE CARTE
  Qua la faccenda si complica, in quanto esistono due casi:
    * Semi uguali
    * Semi differenti
  Nel caso dei semi differenti la vittoria del turno spetta a chi ha giocato la
  carta, quindi si fa il controllo principale sul seme.
  Nel caso invece in cui le carte abbiano seme uguale, bisogna comparare ulteriormente
  il valore delle carte. Una funzione dovrebbe essere necessaria.
  Quando finisce il turno, nuove carte sono date ai due giocatori. L'eliminazione
  dalla lista dovra' avvenire quando la carta e' effetivamente presa e data al
  corrispettivo giocatore.

  FINE PARTITA
  La partita finisce quando non ci sono piu' carte, ovvero quando CARTE - i
  raggiunge quota 0. Ovviamente pero' se non ci sono piu' carte nel mazzo, che si fa?
  Quando effetivamente non ci sono piu' carte nel mazzo, rimangono ancora 6 carte.
  Quindi, a quota 6 il programma cambia "fase", ovvero l'ultima fase del gioco.
  Quando non rimangono piu' carte, si annuncia il vincitore.

################################################################################
*/
//LIBRERIE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//COSTANTI
#define CARTE 40
// VARIABILI GLOBALI
// Tiene conto delle carte ancora in gioco
int carte_rimanenti = 0;
//FUNZIONI
// Funzione che setta di default ad ogni partita un nuovo mazzo di carte.
void default_carte(int carte[4][10]){
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 10; j++)
      carte[i][j] = j + 1;
}
//Stampa lo status della lista carte
void debug_carte(int carte[4][10]){
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 10; j++)
      printf("%i ", carte[i][j]);
  printf("||");
  }
}
//Stampa lo status di una delle due mani
void debug_mano(int mano[2][3]){
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3 ; j++)
      printf("%i ", mano[i][j]);
}


//Funzione che stampa un valore INT nel corrispettivo della briscola
void print_seme(int seme){
  switch (seme){
    case 1:
      printf(" Denari ");
      break;
    case 2:
      printf(" Coppe ");
      break;
    case 3:
      printf(" Spade ");
      break;
    case 4:
      printf(" Bastoni ");
      break;
    default:
      printf(" X ");
  }
}
//Funzione che stampa un valore INT nel corrispettivo seme della briscola
void print_valore(int valore){
  switch (valore){
      case 1:
        printf(" Asso ");
        break;
      case 8:
        printf(" Fante ");
        break;
      case 9:
        printf(" Cavallo ");
        break;
      case 10:
        printf(" Re ");
        break;
      default:
        printf(" %i ", valore);
  }
}

//Stampa la mano del giocatore
void stampa_mano(int mano[2][3]){
  for (int i = 0; i < 3; i++)
    print_seme(mano[0][i]);

  printf("\n");
  for (int i = 0; i < 3 ; i++)
    print_valore(mano[1][i]);
  printf("\n");

}
//Funzione che gestisce le carte tra il mazzo e le due mani
void random_pick(int ultima_posizione, int mano[2][3], int carte[4][10]){
  int controllo = 1;
  while(controllo && carte_rimanenti < 34){
    int seme = rand() % 4; //considero solamente il seme della lista
    int valore = rand() % 10;
    if (carte[seme][valore] != 0){
      mano[0][ultima_posizione] = seme + 1;
      mano[1][ultima_posizione] = valore + 1;
      carte[seme][valore] = 0;
      controllo = 0;
    }
  }
  if (carte_rimanenti >= 34){
    mano[0][ultima_posizione] = 0;
    mano[1][ultima_posizione] = 0;
  }
}


int convertitore_intero_punto(int carta, int gestione ){
  int punto;
  // se e' uno devo calcolare il punteggio, se 0 devo semplificare la comparazione
  if (gestione == 1){
      switch (carta){
        //Asso
        case 1:
          punto = 11;
          break;
        //Tre
        case 3:
          punto = 10;
          break;
        //fante
        case 8:
          punto = 2;
          break;
        //Cavallo
        case 9:
          punto = 3;
          break;
        //re
        case 10:
          punto = 4;
          break;
        //le altre carte non hanno punti
        default:
          punto = 0;
      }
    }
  if (gestione == 0 ){
    switch (carta){
      //Asso
      case 1:
        punto = 12;
        break;
      //Tre
      case 3:
        punto = 11;
        break;
      default:
        punto = carta;
    }
 }
  return punto;
}

//MAIN
int main(){
  srand(time(NULL));
  //############################################################################
  //VARIABILI
  //Contatori
  int i = 0;
  //Il mazzo delle carte
  int carte[4][10];
  //la posizione 0 e' riservata al giocatore, 1 alla CPU
  int cp[2][2];
  //Seme e valore delle carte per giocatore e CPU
  int seme_giocatore,seme_cpu,valore_giocatore,valore_cpu;
  //tiene in memoria la posizione carta giocata
  int carta_giocatore, carta_cpu;
  //valore della carta
  int mano_giocatore[2][3], mano_cpu[2][3];
  //indica il seme della partita
  int seme_partita = rand() % 4 + 1;
  int seme_partita_temp;
  //Permette di indicare le carti rimanenti. Inizia da 6 perche'
  //Punto del turno
  int punto = 0;
  //vittoria del turno precedente
  int vittoria = 1;
  //Punteggio totale dei giocatori
  int punteggio_giocatore = 0 , punteggio_CPU = 0;
  //Tiene conto della vittoria nel turno, 1 per giocatore 0 per la CPU
  //############################################################################
  //ESECUZIONE

  //ATTENZIONE!!! QUESTO RICHIAMO CI DEVE ESSERE SEMPRE!
  default_carte(carte);
  printf("Ciao! Benvenuto nel gioco della Briscola! Iniziamo :) \n\n");
  //############################################################################
  //OUTPUT
  //Il programma esce dal ciclo se rimangono 6 carte
  printf("La briscola di questa partita e' : ");
  print_seme(seme_partita);
  printf("\n");
  //debug_carte(carte);
  printf("\n");
  //Si danno le carte
  for (i = 0; i < 3; i++)
    random_pick(i,mano_giocatore,carte);
  for (i = 0; i < 3; i++)
    random_pick(i,mano_cpu,carte);


  while((CARTE - carte_rimanenti) > 0){
      //printf("\n");
      //debug_carte(carte);
      //printf("\n");
      //La CPU butta la sua carta
      do{
        i = rand() % 3;
        seme_cpu = mano_cpu[0][i];
        valore_cpu = mano_cpu[1][i];
      }while(seme_cpu == 0);

      //Selezione della Carta
      stampa_mano(mano_giocatore);
      //stampa_mano(mano_cpu);

      do{
        printf("Che carta scegli? 1, 2 o 3? \n");
        scanf("%i", &carta_giocatore);
        carta_giocatore--;
        seme_giocatore = mano_giocatore[0][carta_giocatore];
        valore_giocatore = mano_giocatore[1][carta_giocatore];
      }while(carta_giocatore < 0 || carta_giocatore > 3 || seme_giocatore == 0);
      //La posizione ovviamente deve corrispondere alla posizione nella lista

      /*
        Dobbiamo considerare diversi casi:
        -- I due giocatori hanno lo stesso seme, e quindi non mi interessa della
           Briscola
        -- I due giocatori hanno carte diverse
           -- Uno butta una carta e l'altro una briscola
           -- Entrambi non hanno briscole, e quindi chi ha vinto la partita
              precedente ha la precedenza. Consideriamo come vincitore all'inizio
              sempre il giocatore
      */

      punto = convertitore_intero_punto(valore_giocatore, 1) + convertitore_intero_punto(valore_cpu, 1);

      valore_giocatore = convertitore_intero_punto(valore_giocatore, 0);
      valore_cpu = convertitore_intero_punto(valore_cpu, 0);


      //Primo caso : entrambi hanno lo stesso seme
      if (seme_giocatore == seme_cpu){
        if(valore_giocatore < valore_cpu){
          punteggio_CPU += punto;
          vittoria = 0;
        }else{
          punteggio_giocatore += punto;
          vittoria = 1;
        }
      }
      //Entrambi hanno carte diverse ma uno ha o la briscola o la precedenza
      else{
        //Secondo Caso : Il primo giocatore non ha la briscola e nemmeno la cpu
        if (seme_giocatore != seme_partita && seme_cpu != seme_partita){
          //Il giocatore ha la precedenza, la cpu non ha ne' la briscola ne' la precedenza
          if (vittoria == 1){
            punteggio_giocatore += punto;
            vittoria = 1;
            }else{
              punteggio_CPU += punto;
              vittoria = 0;
          }

        //sapendo che i due semi non possono essere uguali QUA, so gia' che ha vinto
        // il giocatore / cpu
        }else if (seme_giocatore == seme_partita){
          punteggio_giocatore += punto;
          vittoria = 1;
        }else{
          punteggio_CPU += punto;
          vittoria = 0;
        }
      }
      valore_giocatore = mano_giocatore[1][carta_giocatore];
      valore_cpu = mano_cpu[1][i];
      printf("\nIl computer mette : ");
      print_seme(seme_cpu);
      print_valore(valore_cpu);
      printf("\nTu metti : ");
      print_seme(seme_giocatore);
      print_valore(valore_giocatore);

      //printf("\nVittoria : %i\n\n", vittoria);

      /*
        Nel caso di vittoria, il giocatore pesca prima la carta. In caso di sconfitta,
        il contrario
      */
      if (vittoria == 1){
          printf("\nIl giocatore vince il turno!\n\n");
          random_pick(carta_giocatore,mano_giocatore,carte);
          random_pick(i,mano_cpu,carte);
      }
      if (vittoria == 0){
          printf("\nIl computer vince il turno!\n\n");
          random_pick(i,mano_cpu,carte);
          random_pick(carta_giocatore,mano_giocatore,carte);
      }
      //Informa al ciclo che mancano due carte
      carte_rimanenti += 2;
      //printf("Punto : %i  Giocatore : %i  CPU : %i\n" , punto, punteggio_giocatore, punteggio_CPU);
  }

  printf("PUNTEGGIO FINALE\n");
  printf("Giocatore : %i  CPU : %i\n" , punteggio_giocatore, punteggio_CPU);
  if (punteggio_giocatore != punteggio_CPU){
    if (vittoria == 1)
        printf("\nIl giocatore ha vinto la partita!\n\n");
    else
        printf("\nIl computer ha vinto la partita!\n\n");
  }else{
    printf("C'e' stato un pareggio!\n\n");
  }




  return 0;
}
