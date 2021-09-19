/**********************************************************************
 *  Knäcka lösenord readme.txt
 **********************************************************************/

 Ungefärligt antal timmar spenderade på labben (valfritt):
 8 timmar ungefär

/**********************************************************************
 *  Ge en högnivåbeskrivning av ditt program decrypt.c.
 **********************************************************************/
Vi går igenom hälften av alla bitar och sparar dem hashade i en unordered_map<Key,vector<Key>> vi använder oss utav std::hash<string>
med inargument våra digits konvertterade till en sträng föär att få unika värden. 

Sedan loopar vi igenom andra halvan för att få den resterande halvan bitar, vi hashar dem sedan räknar vi ut vad den hashade som vi sparade innan skulle vara
genom att ta a**2 = c**2 - b**2. sedan gör vi ett uppslag i vår unordered unordered_map och kollar om det då finns ett a**2 i vår unordered map.
om det finns en sådan så sparar vi alla de ohashade a+b som en potentiell lösning. 

/**********************************************************************
 *  Beskriv symboltabellen du använt för decrypt.c.
 **********************************************************************/
Vi har använde oss utav det hashade a:t som nyckel och sedan pushade på det potentiella ohashade i en vector 


/**********************************************************************
 *  Ge de dekrypterade versionerna av alla lösenord med 8 och 10
 *  bokstäver i uppgiften du lyckades knäca med DIN kod.
 **********************************************************************/


8 bokstäver                           10 bokstäver
-----------                           ------------
xwtyjjin --> congrats , ibqfehan ;    h554tkdzti --> completely , nbryjimvrd
rpb4dnye --> youfound , mqubzd45 ;    oykcetketn --> unbreakable      
kdidqv4i --> theright            ;    bkzlquxfnt --> cryptogram
m5wrkdge --> solution , aeigrsd4 ;    wixxliygk1 --> ormaybenot

/****************************************************************************
 *  Hur lång tid använder brute.c för att knäcka lösenord av en viss storlek?
 *  Ge en uppskattning (baserad på tidskomplexiteten)  markerad med en asterisk
 *  om det tar längre tid än vad du orkar vänta. Ge en kort motivering för
 *  dina uppskattningar.
 ***************************************************************************/


Char     Brute     
--------------
 4       0s (0,059 s)
 5       1s (1,887 s)
 6       76s (75,25 s)
 8       * tidskomplexiteten är ca O(2^n) vilket gör att för varje extra bokstav så måste man multiplöicera tiden med *32 vilket innebör att det tar va 21,33333 h att brutea proggrammet


/******************************************************************************
 *  Hur lång tid använder decrypt.c för att knäcka lösenord av en viss storlek?
 *  Hur mycket minne använder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)    Minne (bytes)
----------------------------------------
                        Använder valgrind
6       0s (0,02s)      2 500 000 bytes
8       1s (1,149 s)   81 611 904 bytes
10      51S (51,745 s) 3 002 290 554 bytes
12      *Tar för mycket minne tror jag

8*5 = 40

20  20

2^20 *2 = 2^21

10*5 = 50;

25      25

2^25 + 2^25 = 2*2^25 == 2^26

O(2^((n/2)+1))

/*************************************************************************
 * Hur många operationer använder brute.c för ett N-bitars lösenord?
 * Hur många operationer använder din decrypt.c för ett N-bitars lösenord?
 * Använd ordo-notation.
 *************************************************************************/
Brute använder sig utav O(2^n) många operationer (+ konstanter såklart)
decrypt använder sig utav O(2^((n/2)+1)) många operationer (+ konstanter såklart)

/*************************************************************************
 * Vilka egenskaper skulle ni leta efter i en hashfunktion för att
 * försäkra er om att den är "säker"?
 *************************************************************************/
Att inte ha enkla mönster, kanske random är att föredra