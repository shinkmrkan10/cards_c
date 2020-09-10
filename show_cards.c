/*   showcards.c   */
/*   ポーカーの役を判定する   */
/*   Shin Kimura 2015-05-25   */

#include<stdio.h>
#include<stdlib.h>

#define SEED   100         /*   シャッフルの乱数シード   */
#define OFFSET  0         /*   先頭の番号(0または1)　   */
#define TOTAL  52         /*   カードの総数             */
#define CUT     6         /*   カードをカットする枚数   */
#define ROW     4         /*   表示する行数　　　　　   */
#define COL    13         /*   表示する列数             */
#define START   0


/*   配列をコピーする関数   */

void copy(int deck1[], int deck2[], int total)
{
    int i ;
    for( i = 0 ; i < total ; i++ ){
        deck2[i] = deck1[i];            /*   deck1からdeck2へコピー   */

    }
}


/*   カードのマークを返す関数   */

char suit(int index)
{

    char mark[4] = { 'S', 'H', 'D', 'C' } ;


    return mark[ index / 13 ] ;
}


/*   カードの数字を返す関数   */

char number(int index)
{

    char numbers[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', '+', 'J', 'Q', 'K' } ;


    return numbers[ index % 13 ] ;
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


/*   配列のカードを表示する関数   */

void display_card(int deck[], int row, int col)
{
    int i, j ;
    for( i = 0 ; i < row ; i++ ){
        for( j = 0 ; j < col ; j++ ){
            printf("  %c%c",suit(deck[col * i + j]), number(deck[col * i + j]));
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
    int card_in_use[52] = {0} ;            /*   未使用 0 で初期化   */

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
    int deck2[52] ;

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
    int deck2[52] ;

    copy(deck1, deck2, total) ;                           /*   コピーを作る   */
    for( i=0 ; i < total ; i++ ){
        deck1[i % total]   = deck2[(i + cut) % total];    /*   totalの剰余を利用する   */
    }
}


/*   手札の役を判定する関数   */

void judge( int hand[] )
{
    int i, j, tmp ;
    int sum, multi ;

    int fl_straight = 0 ;
    int fl_flush = 0 ;


/*   sum, multiを計算   */

    sum = 0 ;
    multi = 1;
    for (i=0 ; i < 5 ; i++ ){
        sum   += hand[i]/13;
        multi *= hand[i]/13;
    }

/*   手札がフラッシュであるか？   */

    if (sum == 0 || sum == 15) fl_flush = 1 ;
    else if (sum == 5 && multi == 1) fl_flush = 1 ;
    else if (sum == 10 && multi == 32) fl_flush = 1 ;
    else  fl_flush = 0 ;


/*   手札を数でソート   */

    for (i = 0; i < 4; i++){
        for(j = 4; j>i; j--){
            if (hand[j-1]%13 > hand[j]%13){
                tmp = hand[j];
                hand[j] = hand[j-1];
                hand[j-1] =tmp;
            }
        }
    }


/*   手札を数の順で表示   */

    printf("\n手札整列\n");
    for (i=0 ; i < 5 ; i++ ){
        printf("  %c%c",suit(hand[i]), number(hand[i]));
    }


/*   手札がストレートであるか？   */

    if ( hand[4]%13 - hand[0]%13 == 4 )
    {
        if ( hand[1]%13 == hand[0]%13 + 1 && 
             hand[2]%13 == hand[1]%13 + 1 &&
             hand[3]%13 == hand[2]%13 + 1 )   fl_straight = 1 ;
    }else if (hand[0]%13 == 0 && hand[1]%13 == 9 &&
              hand[2]%13 == 10 && hand[3]%13 == 11 &&
              hand[4]%13 == 12 )    fl_straight = 1 ;
    else   fl_straight = 0 ;


/*   ストレートフラッシュの判定   */

    if ( fl_flush == 1 && fl_straight ==1 ) printf("　ストレートフラッシュです。\n");
    else if ( fl_flush == 1 ) printf("　フラッシュです。\n");
    else if ( fl_straight ==1 ) printf("　ストレートです。\n");

/*   フォーカードの判定   */

    else if ( hand[0]%13 == hand[3]%13 || hand[1]%13 == hand[4]%13) printf("　フォーカードです。\n");

/*   フルハウスの判定   */

    else if ( (hand[0]%13 == hand[2]%13 && hand[3]%13 == hand[4]%13) || (hand[0]%13 == hand[1]%13 && hand[2]%13 == hand[4]%13)) printf("　フルハウスです。\n");

/*   スリーカードの判定   */

    else if ( hand[0]%13 == hand[2]%13 || hand[1]%13 == hand[3]%13 || hand[2]%13 == hand[4]%13) printf("　スリーカードです。\n");

/*   ツーペアの判定   */

    else if ( (hand[0]%13 == hand[1]%13 && hand[2]%13 == hand[3]%13) || 
              (hand[0]%13 == hand[1]%13 && hand[3]%13 == hand[4]%13) || 
              (hand[1]%13 == hand[2]%13 && hand[3]%13 == hand[4]%13) )
               printf("　ツーペアです。\n");

/*   ワンペアの判定   */

    else if ( hand[0]%13 == hand[1]%13 || hand[1]%13 == hand[2]%13 || hand[2]%13 == hand[3]%13 || 
              hand[3]%13 == hand[4]%13 )  printf("　ワンペアです。\n");

    else printf("　ノーペアです。\n");

}


/*   メイン関数   */

int main(void)
{
    int i, j, k;

    int fl_straight = 0 ;
    int fl_flush = 0 ;

    int deck[TOTAL];              /*   カード格納配列　　　   */
    int hand[5];                  /*   手札格納配列  　　　   */

/*   deckに番号順に格納する   */

    set(deck, TOTAL, OFFSET);

    printf("\n配列（整列）\n");
    display_card(deck, ROW, COL);

/*   deckを半分に分け交互に格納する（シャッフル）   */

    shuffle(deck, TOTAL);
    printf("\n配列（シャッフル）\n");
    display_card(deck, ROW, COL);

/*   deckをCUTだけずらして格納する（カット）   */

    cut(deck, TOTAL, CUT);
    printf("\n配列（カット　%d）\n", CUT);
    display_card(deck, ROW, COL);

/*   deckにランダムに格納する   */

    srand(SEED);

/*   5回繰り返す   */

    for ( k = 0 ; k < 5 ; k++ )
    {
        printf("\nnew deck %d\n", k+1);

   set_random(deck, TOTAL, OFFSET);

    printf("\n配列（ランダム　SEED=%d）\n", SEED);
    display(deck, ROW, COL);

/*   5枚ずつ10回配る   */

    for ( j = 0 ; j < 10 ; j++ )
    {


/*   手札を配る   */

    for (i=0 ; i < 5 ; i++ ){
        hand[i] = deck[i + j * 5] ;
     }

/*   handを固定して役の判定を検査する場合   

     hand[0]= 8;
     hand[1]= 11;
     hand[2]= 25;
     hand[3]= 9;
     hand[4]= 49;
*/

/*   手札を表示   */

    printf("\n手札\n");
    for (i=0 ; i < 5 ; i++ ){
        printf("  %c%c",suit(hand[i]), number(hand[i]));
     }

/*   手札の役を表示   */

    judge( hand ) ;

    }
    }

    return 0;
}