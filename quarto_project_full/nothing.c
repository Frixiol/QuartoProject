


bool is_same_name(FILE *ft , FILE* tmp, int *ch, char const *p_name)
{
	
	char name_tab[10];
	
	int i = 0;
	printf("wtf1\n");
	while (((*ch) = fgetc(ft)) != ':')
	{
		name_tab[i] = (*ch);
		fputc((*ch), tmp);
		i++;
	}
	fputc((*ch), tmp);
	name_tab[i] = '\0';
	
	printf("wtf2\n");
	
	if ((strcmp(p_name, name_tab) == 0))
	{
		return true;
	}
	return false;
	
}


// fonction permettent de lire le contenue du hall_of_fame 
void hall_read()
{
	
	FILE *ft;
	char const *f_name = "hall_of_fame.txt";
	int ch;
	ft = fopen(f_name, "r");
	if (ft == NULL)
    {
        fprintf(stderr, "erreur ficher: %s ne s'ouvre pas\n", f_name);
        exit(1);
    }
	while ((ch = fgetc(ft)) != EOF)
    {
        printf("%c", ch);
    }
    
	free(ft);
}


// fonction permettent d'ecrire dans le hall_of_fame apres une victoire
void hall_write(char const *p_name)
{
	FILE *ft;
	char const *f_name = "hall_of_fame.txt";
	ft = fopen(f_name, "a+");
	
	
	int ch;
	
	printf("wtf1\n");
	
	if (ft == NULL)
    {
        fprintf(stderr, "erreur ficher: %s ne s'ouvre pas\n", f_name);
        exit(1);
    }
    
    FILE* tmp = tmpfile();
    if (tmp == NULL)
    {
        fprintf(stderr, "erreur ficher temporaire ne s'ouvre pas\n");
        exit(1);
    }
    
    for (int i = 0; i < 146; i++) 
    {
		ch = fgetc(ft);
		fputc(ch, tmp);
	}
	
	printf("wtf2\n");
	bool found = false;
	while (ch != EOF)
	{
		if (!(found))
		{
			if (ch == \n)
			{
				if ((ch = fgetc(ft)) == EOF)
				{
					break;
				}
			}
			if (is_same_name(ft, tmp, &ch, p_name))
			{
				found = true;
				
				ch = fgetc(ft);
				fputc(ch, tmp);
				
				ch = fgetc(ft);
				fputc((ch + 1), tmp);
			}
		}
	}
	
	if (found == false && ch == EOF)
	{
		fprintf(tmp, "%s: 1 victoire\n", p_name);
	}
	
	printf("wtf3\n");
	
	fclose(ft);
	ft = fopen(f_name, "w");
	rewind(tmp);
	
	while( ( ch = fgetc(tmp) ) != EOF ) 
	{
		fputc(ch, ft);
		printf("%c", ch);
	}
	
	fclose(tmp);
	fclose(ft);
}
