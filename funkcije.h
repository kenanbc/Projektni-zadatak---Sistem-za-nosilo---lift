#include <string.h>
#include <stdio.h>

struct nosilo{
    char naziv[100];
    int spratovi;
    int koristenje;
    int servis;
    int blok;
    int trenutni;
    int brojacKoristenja;

};

struct prijava {
    char email[100];
    char password[100];
};

int prijavaAdmina(char *email, char *password)
{
    struct prijava admin;

    FILE *p1 = fopen("admin.txt", "r");

    int verifikacija = 0;
    while (fscanf(p1, "%s %s", admin.email, admin.password) != EOF) {
        if (strcmp(admin.email, email) == 0 && strcmp(admin.password, password) == 0) {
            verifikacija = 1;
            break;
        }
    }

    fclose(p1);
    return verifikacija;
}

int prijavaKorisnika(char *email, char *password)
{
    struct prijava korisnik;
    FILE *p = fopen("korisnici.txt", "r");

    int verifikacija = 0;
    while (fscanf(p, "%s %s", korisnik.email, korisnik.password) != EOF) {
        if (strcmp(korisnik.email, email) == 0 && strcmp(korisnik.password, password) == 0) {
            verifikacija = 1;
            break;
        }
    }

    fclose(p);
    return verifikacija;
}

void kreiranjeKorisnika()
{
    FILE *p1;
    char email[50];
    char sifra[50];
    struct prijava korisnik;

    printf("\n  Unesite email novog korisnika: ");
    scanf("%s", email);

    printf("\n  Unesite sifru novog korisnika: ");
    scanf("%s", sifra);

    p1 = fopen("korisnici.txt","a+");

    fprintf(p1,"\n%s %s", email,sifra);
    fclose(p1);

    //provjerava da li je korisnik unesen u fajl
    FILE *p = fopen("korisnici.txt", "r");
    int verifikacija = 0;
    while (fscanf(p, "%s %s", korisnik.email, korisnik.password) != EOF)
    {
        if (strcmp(korisnik.email, email) == 0 && strcmp(korisnik.password, sifra) == 0)
        {
            verifikacija = 1;
        }
    }
    fclose(p);

    if(verifikacija == 1) printf("\n Korisnik je uspjesno kreiran!\n");
    else printf("\n  Niste uspjesno kreirali korisnika!\n");


}

void kreiranjeNosila()
{
    FILE *p1;
    struct nosilo lift;
    int potvrda;

        printf("\n  Unesite naziv novog nosila: ");
        scanf("%s", lift.naziv);

        if(provjeraPostojanjaNosila(lift.naziv) == 1) printf("\n  Nosilo %s vec postoji!\n", lift.naziv);
        else{
        printf("\n  Unesite broj spratova: ");
        scanf("%d", &lift.spratovi);

        printf("\n  Unesite broj koristenja prije servisa: ");
        scanf("%d", &lift.koristenje);

        lift.servis = 0; //po default je 0, znaci da nije spremno za servis, != 0 znaci da je spremno za servis

        printf("\n  Unesite broj koristenja na kome dolazi do blokiranja: ");
        scanf("%d", &lift.blok);

        lift.trenutni = 1; //prilikom kreiranja lifta uvijek se nalazi na 1 spratu
        lift.brojacKoristenja = 0; //prilikom kreiranja lifta uvijek je 0

    printf("\n  Unesite 1 da snimite podatke: ");
    scanf("%d",&potvrda);
    if(potvrda == 1)
    {
        p1 = fopen("nosila.txt","a+");
        fprintf(p1,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
        fclose(p1);
        printf("\n\tUspjesno ste kreirali nosilo!\n");
    }
    else printf("\n\tNiste potvrdili sadrzaj!\n");
    }
}

void brojKoristenja()
{
    struct nosilo lift;
    char nazivNosila[100];
    FILE *p1 = fopen("nosila.txt", "r");

    //prikazuje nosila koja postoje, kako bi se olaksalo adminu da u sljedecem koraku odabere nosilo koje zeli provjeriti
    printf("\n  Nosila koja postoje su:   ");
    while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
    {
        printf("%s   ", lift.naziv);

    }
    fclose(p1);

    printf("\n\n  Unesite naziv nosila koji zelite provjeriti: ");
    scanf("%s", nazivNosila);

    p1 = fopen("nosila.txt", "r");

    int ver = 0;
    while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
    {
        if (strcmp(lift.naziv, nazivNosila) == 0)
        {
            ver = 1;
            break;
        }
    }
    int razlika = lift.koristenje - lift.brojacKoristenja;

    if (ver == 1)
    {
        printf("\n\tNaziv nosila: %s\n", lift.naziv);
        printf("\tBroj koristenja: %d\n", lift.brojacKoristenja);
        if(razlika > 0)
        {
            printf("\tDo servisa ostalo: %d\n", razlika);
            //printf("Servis na: %d\n", lift.servis);
            //printf("Blokiranje na : %d\n", lift.blok);
        }
        if(lift.brojacKoristenja == lift.blok) printf("\n\tNosilo je blokirano!\n");
        else if(lift.servis != 0) printf("\n\tNosilo je spremno za servisiranje!\n");

    } else {
        printf("\n\tNosilo ne postoji!\n");
    }

    fclose(p1);

}

void servis()
{
    FILE *p1 = fopen("nosila.txt", "r");
    char nazivi[999] = "";
    int ver;
    int reset;
    //printf("\n  Nosila koja su spremna za servisiranje:\n\n");
    struct nosilo lift;
    while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
    {
        if (lift.servis > 0)
        {
            strcat(nazivi, lift.naziv);
            strcat(nazivi, "   ");
            //printf("%s\n", lift.naziv);
            ver = 1;
        }
    }
    fclose(p1);
    if(ver == 1)
    {
        printf("\n  Nosila koja su spremna za servisiranje:  ");
        printf("%s", nazivi);
        printf("\n\n  Unesite 1 da resetujete broj koristenja: ");
        scanf("%d" ,&reset);
    }
    else printf("\n\n  Nema nosila koja su spremna za servisiranje!\n");

    if(reset == 1)
    {
        FILE *p1 = fopen("nosila.txt", "r");
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
        {
            if (ver == 1)
            {
                //ako postoje nosiila za resetovanje, kreira se privemeni fajl koji kopira sve iz fajla nosila.txt
                if(lift.servis > 0) lift.brojacKoristenja = 0;
                lift.servis = 0;
                FILE *p2 = fopen("temp.txt", "a+");
                fprintf(p2,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
                fclose(p2);
            }
        }
        fclose(p1);
        remove("nosila.txt"); //brise postojeci fajl
        rename("temp.txt", "nosila.txt"); //mijenja naziv pomocnog fajla u ime obrisanog fajla
        printf("\n\tNosila su resetovana!\n");

    }
    reset = 0;

}

void blokiranaNosila()
{
    //funkcija dosta slicna resetovanju nosila spremnih za servisiranje uz par promjena
    if(provjeraBlokiranja() == 1)
    {

        FILE *p1 = fopen("nosila.txt", "r");
        int ver = 0;
        printf("\n  Nosila koja su blokirana:");
        struct nosilo lift;
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF) {
            if (lift.blok == lift.brojacKoristenja) {
                printf("  %s\n", lift.naziv); //ispisuje nosila koja su blokirana
                ver = 1;
            }
        }
        fclose(p1);
        int reset;
        if(ver == 1)
        {
            printf("\n  Unesite 1 da resetujete blokirana nosila: ");
            scanf("%d" ,&reset);
        }
        if(reset == 1)
        {
            FILE *p1 = fopen("nosila.txt", "r");
            while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
            {
                if (ver == 1)
                {
                    //ako postoje nosiila za resetovanje, kreira se privemeni fajl koji kopira sve iz fajla nosila.txt
                    if(lift.blok == lift.brojacKoristenja)
                    {   lift.brojacKoristenja = 0;
                        lift.servis = 0;
                    }
                    FILE *p2 = fopen("temp.txt", "a+");
                    fprintf(p2,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
                    fclose(p2);
                }
            }
            fclose(p1);
            remove("nosila.txt"); //brise postojeci fajl
            rename("temp.txt", "nosila.txt"); //mijenja naziv pomocnog fajla u ime obrisanog fajla
            printf("\n  Nosila su resetovana!\n");

        }
        else printf("\n  Niste resetovali blokirana nosila!\n");
    }
    else printf("\n  Nema blokiranih nosila!\n");
}


//KORISNIK
char aktivacijaNosila(char *email)
{
    char naziv[100];
    struct nosilo lift;
    FILE *p = fopen("nosila.txt", "r");

    //prikazuje nosila koja postoje, kako bi se olaksalo korisniku da u sljedecem koraku odabere nosilo koje zeli da aktivira za svoj profil
    printf("\n  Nosila koja postoje su:   ");
    while (fscanf(p, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF) {
            printf("%s   ", lift.naziv);

    }
    fclose(p);
    printf("\n\n  Unesite naziv nosila koji zelite aktivirati za svoj profil: ");
    scanf("%s", naziv);

    if(provjeraPostojanjaNosila(naziv) == 1)
    {

        if(provjeraAktiviranogNosila(email, naziv) == 1) printf("\n  Nosilo je vec aktivirano na vasem profilu!\n");
        else {
        FILE *p1 = fopen("aktiviranaNosila.txt", "a+");
        fprintf(p1,"\n%s %s", email, naziv);
        printf("\n  Nosilo je uspjesno aktivirano!\n");
        fclose(p1);
        }
    }
    else printf("\n  Unesen je naziv nepostojeceg nosila!\n");

}

char koristenjeNosila(char *email)
{
    struct nosilo lift;
    struct prijava korisnik;
    int s;
    int trenutno;
    int brojac;
    int promjenaSprata;
    char naziv[100];

    FILE *p = fopen("aktiviranaNosila.txt", "r");
    printf("\n  Nosila koja su aktivirana na vasem profilu su: ");
    while (fscanf(p, "%s %s", korisnik.email, lift.naziv) != EOF) {
        if (strcmp(korisnik.email, email) == 0) {
            printf("%s  ", lift.naziv);
        }
    }
    fclose(p);

    printf("\n\n  Unesite nosilo koji zelite koristiti: ");
    scanf("%s", naziv);

    FILE *p1 = fopen("aktiviranaNosila.txt", "r");

    int ver = 0;
    while (fscanf(p1, "%s %s", korisnik.email, lift.naziv) != EOF) {
        if (strcmp(lift.naziv, naziv) == 0 && strcmp(korisnik.email, email) == 0) {
            ver = 1; //provjerava da li nosilo aktivirano za korisnika
            break;
        }
    }
    fclose(p1);
    if(ver == 1)
    {

        if(provjeraKoristenja(naziv) == 1) printf("\n  Vase nosilo je blokirano!\n");
        else
        {
        //ako je nosilo aktivirano
        FILE *p2 = fopen("nosila.txt", "r");

        int koristenje = 0;
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF) {
            if (strcmp(lift.naziv, naziv) == 0) {
                koristenje = lift.koristenje; //prikuplja podatke o nosilu
                s = lift.spratovi;
                trenutno = lift.trenutni;
                brojac = lift.brojacKoristenja;
                break;
            }
        }
        fclose(p2);
        int mojSprat;   //varijabla za unos trenutne pozicije korisnika
        int zeljaSprat; //varijabla za unos sprata na koji korisnik zeli da ode
        printf("\n  Vas lift se nalazi na %d spratu! (Ukupno spratova: %d)\n",trenutno,s);

        printf("\n  Unesite na kojem spratu se vi nalazite: ");
        scanf("%d",&mojSprat);
        promjenaSprata = mojSprat;
        if(mojSprat > lift.spratovi) printf("\n  Ne postoji toliko spratova!\n");
        else
        {
        //poredjenje da li je lift iznad ili ispod korisnika
        if(mojSprat > trenutno)
        {
            liftGore(trenutno, s, mojSprat);
            brojac++;
            promjenaSprata = mojSprat;

        }
        else if(mojSprat < trenutno)
        {
            liftDole(trenutno, s, mojSprat);
            brojac++;
            promjenaSprata = mojSprat;
        }

        brojUpotrebe(brojac, naziv); //poziv funkcije za promjenu broja koristenja
        promjenaKata(promjenaSprata, naziv); //poziv funkcije za promjenu sprata na kojem se lift nalazi

        if(provjeraKoristenja(naziv) == 1) printf("\n  Nosilo se blokiralo, kontaktirajte admina!\n"); //provjera da li se nosilo u medjuvremenu blokiralo

        else
        {
            printf("\n  Unesite na koji sprat zelite ici: ");
            scanf("%d",&zeljaSprat);
        if(zeljaSprat > lift.spratovi) printf("\n  Ne postoji toliko spratova!\n");
        else{
        //provjera da li lift treba da ide gore ili dole
        if(zeljaSprat > mojSprat)
        {
            liftGore(mojSprat, s, zeljaSprat);
            brojac++;
            promjenaSprata = zeljaSprat;
        }
        else if(zeljaSprat < mojSprat)
        {
            liftDole(mojSprat,s,zeljaSprat);
            brojac++;
            promjenaSprata = zeljaSprat;
        }
        else printf("\n  Vec se nalazite na tom spratu!\n");
        }
        brojUpotrebe(brojac, naziv); //poziv funkcije za promjenu broja koristenja
        promjenaKata(promjenaSprata, naziv); //poziv funkcije za promjenu sprata na kojem se lift nalazi
        provjeraServisa(naziv);
        }
    }
    }
    }
    else printf("\n  Taj lift nije registrovan na vase ime ili ne postoji!\n");
}

void liftDole(int trenutno, int s, int mojSprat){


        int d = mojSprat;
        int u = s - trenutno; //s je broj spratova u zgradi, trenutno je trenutna pozicija lifta, varijabla u je uvedena zbog obrnutog indeksiranja u odnosu na broj spratova
        //int razlika = s - u; mozda je suvisno, sve je objasnjeno na slici filozofija kretanja lifta
        int niz[s];
        int i;
        int o = s; //sluzi za prikaz brojeva(broj sprata), samo za ispis
        system("cls");

        for(i = 0; i < s; i++ )
        {
            niz[i] = 32;
        }

        niz[u] = 95; //postavlja graficki prikaz lifta na trenutnu poziciju lifta

        for(i = 0; i < s; i++ )
        {
            printf("%d\t|%c|\n",o,niz[i]);
            o--;
        }
        o = s;
        int p = u;  //sluzi za indeksiranje pomjeranja crtica
        int z = p + 1;  //sluzi za indeksiranje pomjeranja crtica
        int sprat = trenutno - d; //sprat varijabla sluzi kako bi se lift zaustavio na pravom spratu
        sleep(2);
        system("cls");
        for(int k = 1; k <= s; k++)
        {
            for(i = 0; i < s; i++ )
            {
                niz[p] = 32;
                niz[z] = 95;
                printf("%d\t|%c|\n",o,niz[i]);
                o--;
            }
            o = s;
            p++;
            z++;
            if(k == sprat)
            {
                //prekidanje kretanja lifta
                printf("\a");
                break;
            }
            sleep(1);
            system("cls");
        }

    }

void liftGore(int trenutno, int s, int mojSprat)
{
        int d = mojSprat;
        int niz[s];
        int u = s - trenutno; //s je broj spratova u zgradi, trenutno je trenutna pozicija lifta
        //int razlika = s - u; mozda je suvisno, sve je objasnjeno na slici filozofija kretanja lifta
        int sprat = d - trenutno; //sprat varijabla sluzi kako bi se lift zaustavio na pravom spratu
        int i;
        system("cls");

            for(i = 0; i < s; i++ )
            {
                niz[i] = 32;
            }

        niz[u] = 95; //postavlja graficki prikaz lifta na trenutnu poziciju lifta
        int o = s;
        for(i = 0; i < s;i++ )
        {
            printf("%d\t|%c|\n",o, niz[i]);
            o--;
        }
        o = s;
        int p = u; //sluzi za indeksiranje pomjeranja crtica
        int z = p - 1; //sluzi za indeksiranje pomjeranja crtica
        sleep(2);
        system("cls");
        for(int k = 1; k <= s; k++)
        {
                for(i = 0; i < s;i++ )
                {
                    niz[p] = 32;
                    niz[z] = 95;
                    printf("%d\t|%c|\n",o, niz[i]);
                    o--;
                }
            o = s;
            p--;
            z--;
            if(k == sprat)
            {
                //prekidanje kretanja lifta
                printf("\a");
                break;
            }
            sleep(1);
            system("cls");
        }
}

void brojUpotrebe(int brojac, char *naziv)
{
    //uvecava broj koristenja u fajlu
    struct nosilo lift;
    FILE *p1 = fopen("nosila.txt", "r");
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
        {
            if (strcmp(lift.naziv, naziv) == 0)
            {
                lift.brojacKoristenja = brojac;
            }
            FILE *p2 = fopen("temp.txt", "a+");
            fprintf(p2,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
            fclose(p2);

        }
        fclose(p1);

    remove("nosila.txt"); //brise postojeci fajl
    rename("temp.txt", "nosila.txt"); //mijenja naziv pomocnog fajla u ime obrisanog fajla
}


void promjenaKata(int promjenaSprata, char *naziv)
{
    //mijenja sprat na kome se nalazi lift
    struct nosilo lift;
    FILE *p1 = fopen("nosila.txt", "r");
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
        {
            if (strcmp(lift.naziv, naziv) == 0)
            {
                lift.trenutni = promjenaSprata;
            }
            FILE *p2 = fopen("temp.txt", "a+");
            fprintf(p2,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
            fclose(p2);

        }
        fclose(p1);

    remove("nosila.txt"); //brise postojeci fajl
    rename("temp.txt", "nosila.txt"); //mijenja naziv pomocnog fajla u ime obrisanog fajla
}


int provjeraKoristenja(char *naziv)
{
    //sluzi za provjeru blokiranja tokom kretanja
    struct nosilo lift;
    int blokiraj = 0;
    FILE *p1 = fopen("nosila.txt", "r");
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
        {
            if (strcmp(lift.naziv, naziv) == 0)
            {
                if(lift.brojacKoristenja == lift.blok)
                {
                    blokiraj = 1;
                }
                else blokiraj = 0;
                break;
            }
        }
    fclose(p1);

    return blokiraj;

}

void provjeraServisa(char *naziv)
{
    //mijenja "zastavicu" za servis ako je potrebno
    struct nosilo lift;

    FILE *p1 = fopen("nosila.txt", "r");
        while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF)
        {
            if(strcmp(lift.naziv, naziv) == 0)
            {

                if (lift.brojacKoristenja >= lift.koristenje)
                {
                    lift.servis = 1;

                }
            }
                FILE *p2 = fopen("temp.txt", "a+");
                fprintf(p2,"\n%s %d %d %d %d %d %d", lift.naziv,lift.spratovi,lift.koristenje,lift.servis, lift.blok, lift.trenutni, lift.brojacKoristenja);
                fclose(p2);
        }
        fclose(p1);

            remove("nosila.txt"); //brise postojeci fajl
            rename("temp.txt", "nosila.txt"); //mijenja naziv pomocnog fajla u ime obrisanog fajla
}

int provjeraAktivacije(char *email)
{
    //funkcija provjerava da li korisnik ima aktivirane liftove na svom profilu
    struct nosilo lift;
    struct prijava korisnik;
    FILE *p = fopen("aktiviranaNosila.txt", "r");
    int verifikacija = 0;
    while (fscanf(p, "%s %s", korisnik.email, lift.naziv) != EOF) {
        if (strcmp(korisnik.email, email) == 0) {
            verifikacija = 1;
        }
    }
    fclose(p);

    return verifikacija;

}

int provjeraBlokiranja()
{
    FILE *p1 = fopen("nosila.txt", "r");
    int ver = 0;

    struct nosilo lift;
    while (fscanf(p1, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF) {
        if (lift.blok == lift.brojacKoristenja)
        {
            ver = 1;
        }
    }
    fclose(p1);

    return ver;

}

int provjeraAktiviranogNosila(char *email, char *naziv)
{
    //funkcija provjerava da li korisnik ima  vec aktiviran taj lift na svom profilu
    struct nosilo lift;
    struct prijava korisnik;
    FILE *p = fopen("aktiviranaNosila.txt", "r");
    int verifikacija = 0;
    while (fscanf(p, "%s %s", korisnik.email, lift.naziv) != EOF) {
        if (strcmp(korisnik.email, email) == 0 && strcmp(lift.naziv, naziv) == 0) {
            verifikacija = 1;
        }
    }
    fclose(p);

    return verifikacija;

}


int provjeraPostojanjaNosila(char *naziv)
{
    //funkcija provjerava da li nosilo postoji
    struct nosilo lift;

    FILE *p = fopen("nosila.txt", "r");
    int verifikacija = 0;
    while (fscanf(p, "%s %d %d %d %d %d %d", lift.naziv, &lift.spratovi, &lift.koristenje, &lift.servis, &lift.blok, &lift.trenutni, &lift.brojacKoristenja) != EOF) {
        if (strcmp(lift.naziv, naziv) == 0) {
            verifikacija = 1;
        }
    }
    fclose(p);

    return verifikacija;

}

