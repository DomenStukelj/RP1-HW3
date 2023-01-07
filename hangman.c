#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char *select_word(char *word);
void draw_hangman(int hits);
void draw_word(char word[], char good_guesses[]);
void used_letters(char guesses[]);
char *input_check(char input[]);
int guess_match(char guess[], char word[]);
void invalid_input();

int main()
{
    char word[14];
    select_word(word);
    int attempt_counter = 1;

    //stringe ugibov zapolnjeni z null, ker ce ostanejo undefined je glavobol
    char wrong_guesses[12] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    char good_guesses[14] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    
    int misses = 0;
    int hits = 0;
    //printf("%s\n", word);

    printf("Igra vislic. Besede so naključno izbrane iz seznama 444 najbolj uporabljanih slovenskih besed daljših od 3 črk.\n");
    printf("Prosim, uporabljajte le VELIKE ČRKE za vnos ugiba.\n\n");

    while (1)
    {
        printf("Preostala življenja: %i\n\n", 12 - misses);
        draw_hangman(misses);

        printf("\n\n");

        draw_word(word, good_guesses);
        printf("\n\nDolžina besede: %i\n\n", strlen(word));

        printf("\n\nŽe ugibane črke: ");
        used_letters(wrong_guesses);

        printf("\n\nČe želite ugibati črko, vnesite eno VELIKO črko.\n");
        printf("Če želite ugibati besedo napišite celotno besedo.\n");
        printf("Vsi ugibi z več kot eno veliko črko so šteti kot ugibi besed.\n");
        printf("Vnesite svoj ugib: ");

        char input[14];
        fgets(input, 14, stdin);
        char *guess = input_check(input);
        if (guess == 0)
        {
            printf("Vaš vnos je neveljaven, ker vsebuje črko, ki ni VELIKA ali ne spada v slovensko abecedo\n");
            continue;
        }
        

        int match = guess_match(guess, word);
        if (match == 0)
        {
            wrong_guesses[misses] = guess[0];
            misses++;
            printf("\nUgibali ste narobe.\n");
        }
        else if (match == 1)
        {
            good_guesses[hits] = guess[0];
            hits++;
            printf("\nUgibali ste pravilno.\n");
        }
        
        if (hits == strlen(word))
        {
            break;
        }
        

        attempt_counter++;
    }

    printf("Čestitke, uspeli ste uganiti besedo v %i poskusih!\n\n", attempt_counter);
    printf("Beseda: %s", word);
    draw_hangman(misses);
}

int guess_match(char guess[], char word[])
{
    printf("%i", strlen(guess));
    if (strlen(guess)-1 == 1)
    {
        
        for (int i = 0; i < strlen(word); i++)
        {
            if (guess[0] == word[i])
            {
                return 1;
            }
        }
        return 0;
    }
    else
    {
        for (int i = 0; i < strlen(word); i++)
        {
            for (int j = 0; j < strlen(guess); j++)
            {
                if (word[i] != guess[j])
                {
                    return 0;
                }
            }
        }
    }
}

char *input_check(char input[])
{
    char slo_alphabet[25] =
        {'A', 'B', 'C', 'Č', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
         'M', 'N', 'O', 'P', 'R', 'S', 'Š', 'T', 'U', 'V', 'Z', 'Ž'};

    char *guess;

    for (int i = 0; i < strlen(input); i++) //strlen, ker char_arrray_length povzroci segfault
    {
        for (int j = 0; j < strlen(slo_alphabet); j++)
        {
            if (input[i] == slo_alphabet[j])
            {
                break;
            }
        }
    }

    return guess;
}

void used_letters(char wrong_guesses[])
{
    for (int i = 0; i < strlen(wrong_guesses); i++)
    {
        printf("%c ,", wrong_guesses[i]);
    }
}


void draw_word(char word[], char good_guesses[])
{
    for (int i = 0; i < strlen(word); i++)
    {
        bool found = false;
        for (int j = 0; j < strlen(good_guesses); j++)
        {
            if (word[i] == good_guesses[j])
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            printf("%c", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }
}

void draw_hangman(hits)
{
    char ASCII_hangman_steps[13][125] = {
        "\n\n\n\n\n\n\n=============\n",
        "\n\n\n\n\n     _ _\n    /   \\\n=============\n",
        "\n      |\n      |\n      |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |\n      |\n      |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/\n      |\n      |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |\n      |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |    |\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |   /|\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |   /|\\\n      |\n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |   /|\\\n      |	  / \n      |\n     _|_\n    /   \\\n=============\n\n",
        "\n      ______\n      |/   |\n      |    O\n      |   /|\\\n      |	  / \\\n      |\n     _|_\n    /   \\\n=============\n\n"};

    printf("%s", ASCII_hangman_steps[hits]);
}

char *select_word(char *word)
{
    srand(time(NULL));

    int selection = rand() % 443;

    // urejen seznam najbolj uporabljanih slovenskih besed z 3 do 14 crkami
    char wordlist[444][14] =
        {
            "ALEKSANDER",
            "ALPSKI",
            "ANGLIJA",
            "ARHITEKT",
            "AVSTRALIJA",
            "AVTORSKI",
            "BARVEN",
            "BAZA",
            "BENCINSKI",
            "BIH",
            "BITJE",
            "BITKA",
            "BLAGAJNA",
            "BOMBA",
            "BORZEN",
            "BOŽIČEN",
            "BOŽJI",
            "BREZPOSELN",
            "BREŽICE",
            "BRUSELJ",
            "BRUTO",
            "BUSH",
            "CERKVEN",
            "CONA",
            "CVET",
            "CVETJE",
            "ČASNIK",
            "ČASOVEN",
            "ČEBULA",
            "ČETRT",
            "ČIŠČENJE",
            "ČLANSTVO",
            "DATOTEKA",
            "DELITEV",
            "DEMOKRAT",
            "DESNO",
            "DEŽ",
            "DIALOG",
            "DISK",
            "DOBESEDNO",
            "DOBRODOŠEL",
            "DODAN",
            "DOKUMENTAREN",
            "DOLGOROČEN",
            "DOLOČILO",
            "DOPOLNITEV",
            "DOSEŽEN",
            "DOSTOPEN",
            "DRAGOCEN",
            "DRUGJE",
            "DRUGOD",
            "DUHOVEN",
            "DUHOVNIK",
            "ELEKTRARNA",
            "ELEKTRIKA",
            "ENAJST",
            "ENERGETSKI",
            "ENOSTAVEN",
            "ETAPA",
            "FAVORIT",
            "FRANCE",
            "GENERAL",
            "GLOBALEN",
            "GOSPODAR",
            "GOSTITI",
            "GOSTOVANJE",
            "GRAFIČEN",
            "GRČIJA",
            "GROŽNJA",
            "GRŠKI",
            "HIŠEN",
            "HOLDING",
            "HRANITI",
            "HRVAŠKO",
            "IDEALEN",
            "IDENTITETA",
            "IMENOVANJE",
            "INFORMATIVEN",
            "INVESTICIJSKI",
            "INVESTITOR",
            "IZBOLJŠANJE",
            "IZGRADNJA",
            "IZKLJUČNO",
            "IZKUŠEN",
            "IZOGIBATI",
            "IZOLA",
            "IZPELJATI",
            "IZRAČUN",
            "IZRAEL",
            "IZRAELSKI",
            "IZVOZ",
            "JABOLKO",
            "JAN",
            "JANKO",
            "JESENSKI",
            "JUG",
            "JUHA",
            "JURIJ",
            "KADROVSKI",
            "KAKRŠENKOLI",
            "KANDIDATKA",
            "KAPITALSKI",
            "KATARINA",
            "KATOLIŠKI",
            "KITAJSKA",
            "KLET",
            "KLIC",
            "KLINIČEN",
            "KLUBSKI",
            "KNJIŽEN",
            "KOČEVJE",
            "KOLEKTIVEN",
            "KOLENO",
            "KOLESARSKI",
            "KONČNICA",
            "KONJICE",
            "KONKURENČEN",
            "KONTROLA",
            "KORENINA",
            "KOROŠKI",
            "KOZAREC",
            "KRAJAN",
            "KRALJICA",
            "KRANJ",
            "KRAT",
            "KRAVA",
            "KRIMINALIST",
            "KRIVDA",
            "KRIŽANKA",
            "KRŠČANSKI",
            "KRVEN",
            "KUČAN",
            "KUHATI",
            "KUP",
            "KVALITETA",
            "LEGENDA",
            "LETNO",
            "LEVO",
            "LISTINA",
            "LJUBEZENSKI",
            "LJUBLJANČAN",
            "LOČEN",
            "LOČITI",
            "LOVITI",
            "LUKA",
            "LUKNJA",
            "MADŽARSKI",
            "MAR",
            "MASLO",
            "MATERIALEN",
            "MATIČEN",
            "MEHANIZEM",
            "MEHEK",
            "MENJAVA",
            "MESEČEN",
            "MEŠAN",
            "MINIMALEN",
            "MIRAN",
            "MLADOST",
            "MNOŽIČEN",
            "MODA",
            "MOKA",
            "MOSKVA",
            "NADOMESTILO",
            "NADSTROPJE",
            "NAHAJATI",
            "NAJEM",
            "NAKLJUČJE",
            "NANIZANKA",
            "NAPASTI",
            "NAPETOST",
            "NAPIS",
            "NARAVNOST",
            "NATAŠA",
            "NAVDUŠITI",
            "NAVSEZADNJE",
            "NAZIV",
            "NEDAVNO",
            "NEGA",
            "NEHATI",
            "NEKAJKRAT",
            "NENADOMA",
            "NENEHNO",
            "NIKAKRŠEN",
            "NINA",
            "NIVO",
            "OBČASNO",
            "OBČUTITI",
            "OBDELAVA",
            "OBLJUBA",
            "OBLJUBLJATI",
            "OBMOČEN",
            "OBNOVITI",
            "OBRAT",
            "OBRESTEN",
            "OBROK",
            "OBRTEN",
            "OBSEŽEN",
            "OBSTOJ",
            "ODDAJATI",
            "ODLOČNO",
            "ODSEK",
            "ODSTOP",
            "ODŠTETI",
            "OGLASITI",
            "OGROMEN",
            "OHRANJATI",
            "OKO",
            "OKROŽEN",
            "OPERA",
            "OPOZORILO",
            "OPRAVILO",
            "ORGANIZACIJSKI",
            "OSKRBA",
            "OSMI",
            "OSTANEK",
            "PALICA",
            "PAMET",
            "PARKIRIŠČE",
            "PARTIZAN",
            "PAVEL",
            "PETRA",
            "PIVO",
            "PLANINA",
            "PLAT",
            "PLUS",
            "POBEGNITI",
            "PODALJŠATI",
            "PODELITEV",
            "PODEŽELJE",
            "POGON",
            "POGREŠATI",
            "POIMENOVATI",
            "POLET",
            "POLICA",
            "POLJSKI",
            "POLNO",
            "POMOČNIK",
            "PON",
            "PONAVLJATI",
            "POOBLASTILO",
            "PORTOROŽ",
            "POSEBNOST",
            "POSREDOVANJE",
            "POSTREČI",
            "POŠILJATI",
            "POTEK",
            "POTRJEVATI",
            "POUK",
            "POVEČAN",
            "POVEZOVANJE",
            "POVPRAŠEVANJE",
            "POZDRAVITI",
            "POZVATI",
            "PRAKTIČEN",
            "PRAVLJICA",
            "PREDATI",
            "PREDEL",
            "PREDSTAVLJEN",
            "PREDVIDOMA",
            "PREGLEDATI",
            "PREIZKUSITI",
            "PRENEHATI",
            "PREOSTATI",
            "PREPOZNATI",
            "PRESEGATI",
            "PRESOJA",
            "PREŠERNOV",
            "PRETEŽNO",
            "PREVOD",
            "PRIČATI",
            "PRIDELEK",
            "PRIDOBIVANJE",
            "PRIIMEK",
            "PRIJATELJSKI",
            "PRIKAZOVATI",
            "PRIKLJUČEK",
            "PRILAGODITI",
            "PRIMORSKI",
            "PRIPOMOČEK",
            "PRIPRAVLJENOST",
            "PRISLUHNITI",
            "PRISPETI",
            "PRIVLAČEN",
            "PRIZNAVATI",
            "PRIZOR",
            "PRODAJALEC",
            "PRODUKCIJA",
            "PROFESIONALEN",
            "PROMOCIJA",
            "PROŠNJA",
            "PROTEST",
            "RADOVLJICA",
            "RAHLO",
            "RAZGLASITI",
            "RAZISKOVANJE",
            "RAZMEROMA",
            "RAZOČARAN",
            "RAZŠIRJEN",
            "REČ",
            "REDKO",
            "REVEN",
            "REVOLUCIJA",
            "RIMSKI",
            "RISANKA",
            "ROMANTIČEN",
            "SALON",
            "SAN",
            "SANACIJA",
            "SAŠA",
            "SEGATI",
            "SENAT",
            "SENCA",
            "SESTATI",
            "SESTAVITI",
            "SHOW",
            "SIR",
            "SIV",
            "SKLENJEN",
            "SKLEPATI",
            "SKRAJEN",
            "SLAVKO",
            "SLIKAR",
            "SLO",
            "SLOVAN",
            "SLOVENŠČINA",
            "SLOVESNOST",
            "SMUČANJE",
            "SNEMATI",
            "SOJENJE",
            "SOLATA",
            "SORODNIK",
            "SORTA",
            "SPOL",
            "SPOPAD",
            "SPOŠTOVAN",
            "SPOZNANJE",
            "SPREHOD",
            "SRB",
            "SRČEN",
            "SREBRN",
            "SREČEVATI",
            "STADION",
            "STAVEK",
            "STAVKA",
            "STEČAJ",
            "STOL",
            "STROG",
            "STROKA",
            "SUPER",
            "SVETEL",
            "ŠIBEK",
            "ŠIRITEV",
            "ŠKODLJIV",
            "ŠTUDIJSKI",
            "ŠVICA",
            "TAJEN",
            "TAKOLE",
            "TEKMOVALEN",
            "TENIS",
            "TENIŠKI",
            "TOVORNJAK",
            "TRAK",
            "TRAKTOR",
            "TRAVA",
            "TRDEN",
            "TRENIRATI",
            "TRPETI",
            "TURČIJA",
            "UČEN",
            "UČINKOVITOST",
            "UDARITI",
            "UGLEDEN",
            "UREDNIŠTVO",
            "USLUŽBENEC",
            "USPEŠNICA",
            "USTANOVLJEN",
            "USTREZNO",
            "USTVARJALEC",
            "USTVARJALEN",
            "UVELJAVITI",
            "UVOD",
            "UŽITEK",
            "VAROVATI",
            "VEČEREN",
            "VEČINSKI",
            "VEDENJE",
            "VEN",
            "VERIGA",
            "VESTNIK",
            "VEZAN",
            "VGRAJEN",
            "VHOD",
            "VIKEND",
            "VINSKI",
            "VIRUS",
            "VITAMIN",
            "VKLJUČNO",
            "VLADIMIR",
            "VLAGANJE",
            "VOLIVEC",
            "VONJ",
            "VRAT",
            "VREDNOSTEN",
            "VREMENSKI",
            "VRHNIKA",
            "VRHOVEN",
            "VRHUNEC",
            "VSELEJ",
            "VSOTA",
            "VZDUŠJE",
            "VZPON",
            "VZPOSTAVITI",
            "WASHINGTON",
            "ZABAVATI",
            "ZAČENJATI",
            "ZADOVOLJSTVO",
            "ZADRŽATI",
            "ZAGOTOVLJEN",
            "ZAGOVARJATI",
            "ZAHVALA",
            "ZAJETI",
            "ZALOGA",
            "ZANESLJIV",
            "ZAPELJATI",
            "ZAPLETEN",
            "ZAPORED",
            "ZASTOPATI",
            "ZATEM",
            "ZATRDITI",
            "ZATRJEVATI",
            "ZAVEST",
            "ZAVZEMATI",
            "ZAZNAMOVATI",
            "ZDRAVNIŠKI",
            "ZGLED",
            "ZGRAJEN",
            "ZLORABA",
            "ZMANJKATI",
            "ZMANJŠEVATI",
            "ZNANEC",
            "ZRASTI",
            "ŽELEZNICA",
            "ŽIVALSKI",
        };

    strcpy(word, wordlist[selection]);
}
