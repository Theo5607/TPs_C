#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void vers_binaire(unsigned int x, unsigned char b[])
{
    unsigned n = pow(2, 32) - 1;
    unsigned y = x;
    for (int i = 0; i < 32; i++)
    {
        if (y >= pow(2, 32 - i - 1))
        {
            b[31 - i] = 1;
            y = y - pow(2, 31 - i);
        } else { b[31 - i] = 0; }
    }
}

bool test_vers_binaire()
{
    bool valide = true;
    unsigned char b[32];
    unsigned char out[] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    vers_binaire(123457, b);
    for(int i =0; i < 32; i++)
    {
        if (b[i] != out[i])
        {
            printf("[Test 1] Erreur en %d : %d != %d\n", i, b[i], out[i]);
            valide = false;
        }
    }
    vers_binaire(4294967295, b);
    for(int i =0; i < 32; i++)
    {
        if (b[i] != 1)
        {
            printf("[Test 2] Erreur en %d : %d != 1\n", i, b[i]);
            valide = false;
        }
    }

    return valide;
}


unsigned int depuis_binaire(unsigned char b[])
{
    unsigned x = 0;
    for (int i = 0; i < 32; i++)
    {
        if (b[i] == 1)
        {
            x += pow(2, i);
        }
    }
    return x;
}

bool test_depuis_binaire()
{
    unsigned char b[] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    if (depuis_binaire(b) != 123457) return false;
    unsigned char c[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    if (depuis_binaire(c) != 4294967295) return false;

    return true;
}


int regle_vois(int g, int c, int d)
{
    if (g == 1 && c == 1 && d == 1)
    {
        return 0;
    }
    else if (g == 1 && c == 1 && d == 0)
    {
        return 0;
    }
    else if (g == 1 && c == 0 && d == 1)
    {
        return 0;
    }
    else if (g == 1 && c == 0 && d == 0)
    {
        return 1;
    }
    else if (g == 0 && c == 1 && d == 1)
    {
        return 1;
    }
    else if (g == 0 && c == 1 && d == 0)
    {
        return 1;
    }
    else if (g == 0 && c == 0 && d == 1)
    {
        return 1;
    }
    else if (g == 0 && c == 0 && d == 0)
    {
        return 0;
    }
}

bool test_regle_vois()
{
    if (regle_vois(0,0,0) != 0) return false;
    if (regle_vois(0,0,1) != 1) return false;
    if (regle_vois(0,1,0) != 1) return false;
    if (regle_vois(0,1,1) != 1) return false;
    if (regle_vois(1,0,0) != 1) return false;
    if (regle_vois(1,0,1) != 0) return false;
    if (regle_vois(1,1,0) != 0) return false;
    if (regle_vois(1,1,1) != 0) return false;
    return true;
}

int regle(int config)
{
    if ( (config >= 5 && config <= 7) || config == 0)
    {
        return 0;
    }
    else { return 1; }
}

bool test_regle()
{
    if (regle(0) != 0) return false;
    if (regle(1) != 1) return false;
    if (regle(2) != 1) return false;
    if (regle(3) != 1) return false;
    if (regle(4) != 1) return false;
    if (regle(5) != 0) return false;
    if (regle(6) != 0) return false;
    if (regle(7) != 0) return false;
    return true;
}

int char_to_nb(char c)
{
    if (c == '#') { return 1; }
    else { return 0; }
}

char nb_to_char(int nb)
{
    if (nb == 1) { return '#'; }
    else { return ' '; }
}

void suivant(char in[], char out[])
{
    for (int i = 0; i < strlen(in); i++)
    {
        if (i == 0) { out[i] = nb_to_char(regle_vois(0, char_to_nb(in[i]), char_to_nb(in[i + 1]))); }
        else if (i == strlen(in) - 1) { out[i] = nb_to_char(regle_vois(char_to_nb(in[i - 1]), char_to_nb(in[i]), 0));}
        else {
            char g = in[i - 1];
            char c = in[i];
            char d = in[i + 1];
            out[i] = nb_to_char(regle_vois(char_to_nb(g), char_to_nb(c), char_to_nb(d)));
        }
    }
}

bool test_suivant()
{
    char in[] =  "    ##   ## ##     #  # # #";
    char out[] = "                           "; // de meme longueur
    suivant(in, out);
    if(strcmp(out, "   ## # ##  # #   ##### # #") != 0) return false;
    return true;
}


void copie_chaine(char tgt[], char src[])
{
    for (int i = 0; i < strlen(src); i++)
    {
        tgt[i] = src[i];
    }
}

bool test_copie_chaine()
{
    char src[] = "toto";
    char tgt[] = "abcd";
    copie_chaine(tgt, src);
    if (strcmp(src, tgt) != 0) return false;
    return true;
}

void itere_regle(char depart[], char temp[], char sortie[], int iterations)
{
    copie_chaine(temp, depart);
    for (int i = 0; i < iterations; i++)
    {
        suivant(temp, sortie);
        copie_chaine(temp, sortie);
    }
}

bool test_itere_regle()
{
    char init[81];
    for(int i = 0; i < 80; i++)
    {
        init[i] = ' ';
    }
    init[80] = '\0';
    char temp[81], sortie[81];
    temp[80] = '\0';
    sortie[80] = '\0';
    strcpy(temp, init);
    strcpy(sortie, init);
    init[40] = '#';
    itere_regle(init, temp, sortie, 30);
    if(strcmp(sortie, "          ##  #    # ###  # ## # #  ##### #  ######  #   # ##   #  #  #         ") != 0)
        return false;
    return true;
}


int regle_gen(int gen, int config)
{
    unsigned char bin[32];
    vers_binaire(gen, bin);
    return bin[config];
}

bool test_regle_gen()
{
    if (regle_gen(30, 2) != 1) return false;
    if (regle_gen(188, 6) != 0) return false;
    if (regle_gen(188, 7) != 1) return false;
    if (regle_gen(188, 2) != 1) return false;
    if (regle_gen(188, 3) != 1) return false;
    return true;
}

int nb_config(char g, char c, char d)
{
    if (g == 1 && c == 1 && d == 1)
    {
        return 7;
    }
    else if (g == 1 && c == 1 && d == 0)
    {
        return 6;
    }
    else if (g == 1 && c == 0 && d == 1)
    {
        return 5;
    }
    else if (g == 1 && c == 0 && d == 0)
    {
        return 4;
    }
    else if (g == 0 && c == 1 && d == 1)
    {
        return 3;
    }
    else if (g == 0 && c == 1 && d == 0)
    {
        return 2;
    }
    else if (g == 0 && c == 0 && d == 1)
    {
        return 1;
    }
    else if (g == 0 && c == 0 && d == 0)
    {
        return 0;
    }
}

void suivant_gen(int gen, char in[], char out[])
{
    for (int i = 0; i < strlen(in); i++)
    {
        if (i == 0) { out[i] = nb_to_char(regle_gen(gen, nb_config(0, char_to_nb(in[i]), char_to_nb(in[i + 1])))); }
        else if (i == strlen(in) - 1) { out[i] = nb_to_char(regle_gen(gen, nb_config(char_to_nb(in[i - 1]), char_to_nb(in[i]), 0)));}
        else {
            char g = in[i - 1];
            char c = in[i];
            char d = in[i + 1];
            out[i] = nb_to_char(regle_gen(gen, nb_config(char_to_nb(g), char_to_nb(c), char_to_nb(d))));
        }
    }
}

bool test_suivant_gen()
{
    char in[] =  "    ##   ## ##     #  # # #";
    char out[] = "                           "; // de meme longueur
    suivant_gen(30, in, out);
    if(strcmp(out, "   ## # ##  # #   ##### # #") != 0) return false;
    suivant_gen(188, in, out);
    if(strcmp(out, "    # #  # ## #    ## #####") != 0) return false;
    return true;
}

void itere_regle_gen(int gen, char depart[], char temp[], char sortie[], int iterations)
{
    copie_chaine(temp, depart);
    for (int i = 0; i < iterations; i++)
    {
        suivant_gen(gen, temp, sortie);
        copie_chaine(temp, sortie);
    }
}

bool test_itere_regle_gen()
{
    char init[81];
    for(int i = 0; i < 80; i++)
    {
        init[i] = ' ';
    }
    init[80] = '\0';
    char temp[81], sortie[81];
    temp[80] = '\0';
    sortie[80] = '\0';
    strcpy(temp, init);
    strcpy(sortie, init);
    init[40] = '#';
    itere_regle_gen(30, init, temp, sortie, 30);
    if(strcmp(sortie, "          ##  #    # ###  # ## # #  ##### #  ######  #   # ##   #  #  #         ") != 0)
        return false;
    itere_regle_gen(188, init, temp, sortie, 30);
    if(strcmp(sortie, "                                        # ### ### ### ### ### ### ### #         ") != 0)
        return false;
    return true;
}

void test(bool b, const char s[])
{
    printf("Test %s : %s\n", s,
            b ? "OK" : "INVALIDE");
}

int main(void)
{
    test(test_vers_binaire(), "vers_binaire");
    test(test_depuis_binaire(), "depuis_binaire");
    test(test_regle_vois(), "regle_vois");
    test(test_regle(), "regle");
    test(test_suivant(), "suivant");
    test(test_copie_chaine(), "copie_chaine");
    test(test_itere_regle(), "itere_regle");
    test(test_regle_gen(), "regle_gen");
    test(test_suivant_gen(), "suivant_gen");
    test(test_itere_regle_gen(), "itere_regle_gen");
}
