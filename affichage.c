
void affiche_jeu (grille g, int taille)
{
	printf("Le joueur J1 a place ses navires, etat de sa grille :\n");
	printf("  ");
	int i,j;
	//premiere ligne (numero colones)
	for(i=0;i<taille;i++)
	{
		printf("  %d",i);
	}
	printf("\n");
	
	for(i=0;i<taille;i++)
	{
		printf("%d  ",i);
		for(j=0;i<taille;j++)
		{
			if(g[i][j]==BLANC)
			{
				printf("   ");
			}
			else
			{
				printf("  N");
			}
		}
	}
	
}
