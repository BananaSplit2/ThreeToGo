typedef struc token{
    int couleur;
    int forme;
    struct token* suivant;
    struct token* precedent;
}Tokens, *Liste;