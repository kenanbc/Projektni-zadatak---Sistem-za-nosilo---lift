#include <stdio.h>
#include "funkcije.h"
#include <string.h>

int main()
{
    int odabir;
    int izlaz;
    char email[100];
    char password[100];
    do{
        printf("Unesite svoju email adresu:\t");
        scanf("%s", email);

        printf("Unesite svoju lozinku:\t\t");
        scanf("%s", password);

    if(prijavaAdmina(email,password) != 1 && prijavaKorisnika(email,password) != 1)
    {
        //AKO SU POGRESNI PODACI
        printf("\nPogresni podaci za prijavu, molimo pokusajte ponovo!\n\n");
    }
    if(prijavaAdmina(email,password) == 1)
    {
    //AKO JE ADMIN
    system("cls");
    while(odabir != 6)
    {
    izlaz = 0;
    printf("\n\nAdmin opcije:\n");
    printf("\n\t1. Kreiranje novog korisnika\n");
    printf("\n\t2. Kreiranje novog nosila\n");
    printf("\n\t3. Trenutni broj koristenja nosila\n");
    printf("\n\t4. Nosila spremna za servisiranje\n");
    printf("\n\t5. Blokirana nosila\n");
    printf("\n\t6. Exit\n");

    printf("\nUnesite broj opcije koju zelite koristiti: ");
    scanf("%d", &odabir);
    switch(odabir)
    {
        case 1: kreiranjeKorisnika();
                break;

        case 2: kreiranjeNosila();
                break;

        case 3: brojKoristenja();
                break;

        case 4: servis();
                break;

        case 5: blokiranaNosila();
                break;

        case 6: izlaz = 9;
                break;
    }
    }
    }

    else if(prijavaKorisnika(email, password) == 1)
    {
    //AKO JE KORISNIK
    system("cls");
    izlaz = 0;
    while(odabir != 3)
    {
        printf("\n\nKorisnicke opcije:\n");
        printf("\n\t1. Aktivacija nosila\n");
        printf("\n\t2. Pozivanje i koristenje nosila\n");
        printf("\n\t3. Exit\n");
        printf("\nUnesite broj opcije koju zelite koristiti: ");
        scanf("%d", &odabir);

        switch(odabir)
        {
            case 1: aktivacijaNosila(email);
                    break;

            case 2: if(provjeraAktivacije(email) == 1)
                    {
                        koristenjeNosila(email);
                    }
                    else printf("\nNemate aktiviranih nosila na svom profilu!\n");
                    break;

            case 3: izlaz = 9;
                    break;
        }
    }
    }
        if(izlaz == 9) break; //iz nekog razloga ne radi kad je u while
    }while(prijavaAdmina(email,password) == 0 || prijavaKorisnika(email,password) == 0);

    return 0;
}
