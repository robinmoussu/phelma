enum bool {false, true};

bool equal_arb(Arb arb1, Arb arb2)
{
    if ((Arb1 == 0) xor (Arb2 == 0)) {
        return false;
    } else if ((Arb1 == 0) && (Arb2 == 0)) {
        return true;
    } else {
        return equal_arb(arb1->fils_gauche, arb2->fils_gauche)
               && equal_arb(arb1->fils_droit, arb2->fils_droit);
    }
}

int taille_arb(Arb a)
{
    if (a == 0) {
        return 0;
    } else {
        return 1 + taille_arb(a->fils_gauche) + taille_arb(a->fils_droit);
    }
}

void affiche_croissant_abr(Arb a)
{
    if (a == 0) {
        return;
    } else {
        affiche_croissant_abr(a->fils_gauche);
        printf("%s", a->val);
        affiche_croissant_abr(a->fils_droit);
    }
}


int taille_feuille(Arb a)
{
    if (a == 0) {
        return 0;
    } else {
        return (taille_arb(a->fils_gauche) + taille_arb(a->fils_droit))/2;
    }
}


