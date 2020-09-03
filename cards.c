/*   cards.c   */
/*   カードを並べる   */


#include<stdio.h>
#include<stdlib.h>

#define SEED   52         /*   シャッフルの乱数シード   */
#define OFFSET  1         /*   先頭の番号(0または1)　   */
#define TOTAL  52         /*   カードの総数(花札:48)    */
#define CUT     6         /*   カードをカットする枚数   */
#define ROW     4         /*   表示する行数　　　　　   */
#define COL    13         /*   表示する列数(花札:12)    */



/*   配列をコピーする関数   */

void copy(int deck1[], int deck2[], int total)
{
    int i ;
    for( i = 0 ; i < total ; i++ ){
        deck2[i] = deck1[i];            /*   deck1からdeck2へコピー   */

    }
}



/*   配列の要素を表示する関数   */

void display(int deck[], int row, int col)
{
    int i, j ;
    for( i = 0 ; i < row ; i++ ){
        for( j = 0 ; j < col ; j++ ){
            printf("%4d", deck[col * i + j] );
        }
        printf("\n");

    }
}



/*   配列に番号順に格納する関数   */

void set(int deck[], int total, int offset)
{
    int i ;
    for( i = 0 ; i < total ; i++ ){
        deck[i] = i + offset ;
    }
}



/*   配列にランダムに格納する関数   */

void set_random(int deck[], int total, int offset)
{
    int i , pick ;
    int card_in_use[100] = {0} ;           /*   未使用 0 で初期化   */

    for( i=0 ; i<total ; i++ ){
        do
        {
            pick = rand() % total;
        }while(card_in_use[pick] == 1);    /*   未使用を探す        */

        deck[i] = pick + offset;           /*   offsetからの数      */
        card_in_use[pick] = 1;             /*   使用済みは 1        */
    }
}



/*   配列を半分に分け交互に格納する関数（シャッフル）   */

void shuffle(int deck1[], int total)
{

    int i ;
    int deck2[100] ;

    copy(deck1, deck2, total) ;                        /*   コピーを作る   */
    for( i = 0 ; i < total / 2 ; i++ ){
        deck1[i * 2]     = deck2[i] ;                  /*   偶数番目       */
        deck1[i * 2 + 1] = deck2[i + total / 2] ;      /*   奇数番目       */
    }
}



/*   配列をCUTずらして格納する関数（カット）   */
void cut(int deck1[], int total, int cut)
{

    int i ;
    int deck2[100] ;

    copy(deck1, deck2, total) ;                           /*   コピーを作る   */
    for( i=0 ; i < total ; i++ ){
        deck1[i % total]   = deck2[(i + cut) % total];    /*   剰余を利用     */
    }
}






/*   メイン関数   */

int main(void)
{
    int i ;
    int deck[TOTAL];              /*   カード格納配列　　　   */

/*   deckに番号順に格納する   */

    set(deck, TOTAL, OFFSET);

    printf("\n配列（整列）\n");
    display(deck, ROW, COL);

/*   deckを半分に分け交互に格納する（シャッフル）   */

    shuffle(deck, TOTAL);
    printf("\n配列（シャッフル）\n");
    display(deck, ROW, COL);

/*   deckをCUTだけずらして格納する（カット）   */

    cut(deck, TOTAL, CUT);
    printf("\n配列（カット　%d）\n", CUT);
    display(deck, ROW, COL);

/*   deckにランダムに格納する   */

    srand(SEED);

    set_random(deck, TOTAL, OFFSET);

    printf("\n配列（ランダム　SEED=%d）\n", SEED);
    display(deck, ROW, COL);

/*   deckに番号順に格納する   */

    set(deck, TOTAL, OFFSET);

    printf("\nシャッフル\n");
    printf("\n%d回目\n",0);
    display(deck, ROW, COL);

/*   シャッフルを繰り返す   */
    for (i=0 ; i < 8 ; i++ ){
        shuffle(deck, TOTAL);
        printf("\n%d回目\n",i+1);
        display(deck, ROW, COL);
    }


    return 0;
}