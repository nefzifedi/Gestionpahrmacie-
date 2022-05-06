#include <stdio.h>
#include <stdlib.h>
struct client
{
 int code_cli;
 char nom[30];
 float remise;
};
typedef struct client CLIENT;

struct article
{
  int code;
  char des[30];
  int classe;
  int qua;
  float prix;
};

typedef struct article ARTICLE;

struct achat
{
  int code_cli;
  int code_art;
  int nbr_art;
  char date[10];
};
typedef struct achat ACHAT;



struct L_ARTICLE
{
    ARTICLE a ;
    struct L_ARTICLE *next ;
};
typedef struct L_ARTICLE L_ARTICLE ;

struct L_CLIENT
{
    CLIENT c ;
    struct L_CLIENT *next ;
};
typedef struct L_CLIENT  L_CLIENT ;

struct L_ACHAT
{
    ACHAT b ;
    struct L_ACHAT *next ;
};
typedef struct L_ACHAT L_ACHAT ;


//Q1

void insert_tete_article(L_ARTICLE **first,ARTICLE a)
{
 L_ARTICLE *p;
 p=(L_ARTICLE*)malloc(sizeof(L_ARTICLE));
 p->a=a;
 p->next=*first;
 *first=p;

}
int load_article(ARTICLE *a,FILE *fp)
{
   char chaine[1000];

    if(!fgets(chaine,1000,fp))
        return(0);

     sscanf(chaine,"%4d %30s %d %4d %7.3f",&a->code,&a->des,&a->classe,&a->qua,&a->prix);
     return(1);
}


L_ARTICLE *charger_article(FILE *fp  )
{
L_ARTICLE *first;
ARTICLE a;


    for (first=NULL;load_article(&a,fp);)
    {
       insert_tete_article(&first,a);

    }
    return(first);

 }




 //Q2
void insere_tete_client(L_CLIENT **first ,CLIENT c)
{
   L_CLIENT *p;
   p=(L_CLIENT*)malloc(sizeof(L_CLIENT));
   p->c=c ;
   p->next=*first ;
   *first=p ;
}

int load_client(CLIENT *c,FILE *fp)
{
    char chaine[1000];
    if(!fgets(chaine,1000,fp))
        return(0);

     sscanf(chaine,"%4d %s[30] %5.2",&c->code_cli,&c->nom,&c->remise);
     return(1);
}


 L_CLIENT *charger_client(FILE *fp)
{
    L_CLIENT *first ;
    CLIENT c ;

    for(first=NULL;load_client(&c,fp);)
    {

      insere_tete_client(&first,c);


    }

 return(first);
}




 //Q3

 void insere_tete_achat(L_ACHAT **first,ACHAT a)
{
 L_ACHAT *p;
 p=(L_ACHAT*)malloc(sizeof(L_ACHAT));
 p->b=a;
 p->next=*first;
 *first=p;

}


int load_achat(ACHAT *a,FILE *fp)
{
   char s[1000];
    if(!fgets(s,1000,fp))
        return(0);

     sscanf(s,"%4d %4d %2d %s",&a->code_cli,&a->code_art,&a->nbr_art,&a->date);
     return(1);

}

 L_ACHAT *charger_achat(FILE *fp )
{


L_ACHAT *first;
ACHAT a;



    for (first=NULL;load_achat(&a,fp);)
    {
        insere_tete_achat(&first,a);

    }
    return(first);

}
//Q4

int quantite(L_ACHAT *first,int c,char *date_d,char *date_f)  //quantite achetée d'un article donné
 {
     L_ACHAT *p;
     int quantite;
     quantite=0;

     for(p=first;p;p=p->next)
     {
         if (p->b.code_art==c)
         {
            if (test_date(p->b.date,date_d,date_f))

                quantite=quantite+p->b.nbr_art;
         }


     }

   return(quantite);

 }

 int test_date(char *date,char *date_d,char *date_f)   //teste si une date compris entre date début et date fin
{
    if (compare_date(date,date_d)>=0&&compare_date(date,date_f)<=0)
        return(1);
    return(0);
}

 int compare_date(char *date1,char *date2)
{
 char chaine1[20],chaine2[20];
 memcpy(chaine1,date1+6,4); memcpy(chaine1+4,date1+3,2); memcpy(chaine1+6,date1,2);
*(chaine1+8)='\0';
 memcpy(chaine2,date2+6,4); memcpy(chaine2+4,date2+3,2); memcpy(chaine2+6,date2,2);
*(chaine2+8)='\0';
 return(strcmp(chaine1,chaine2));
}



//Q5


void prix_medic_classe(L_ACHAT *ach ,L_ARTICLE *art ,char *date_d,char *date_f)  //PRIX de chaque classe de medicament dans une periode donnée
 {
     L_ARTICLE *p;
     L_ACHAT *k;
     float mont;
     int i ;

mont=0;
   for (i=1;i<=9;i++)    // ona 9 classe
 {
     for (p=art;p;p=p->next)     //parcour de liste des articles
     {
        if(p->a.classe==i)        //determination de la classe de l'article
        {




           for (k=ach;k;k=k->next)
           {
               if((p->a.code==k->b.code_art)&&test_date(k->b.date,date_d,date_f))  //determination de la montant des medicament de cette classe
                 mont+=(p->a.prix)*(k->b.nbr_art);

           }

       }


     }
     printf("montant de medicament de  classe %d est : %7.3f ",i,mont);     //affichage

mont=0;

 }

 }






//Q6


void montant(L_ARTICLE *art,L_CLIENT *C,L_ACHAT *ach)
{

int Table_client[1000];
float Tm[1000];
L_ACHAT *p;
L_CLIENT *l;
L_ARTICLE *k;

int i,j;
float mont;
mont=0;

for (l=C,i=0;l;l=l->next,i++)
{
  Table_client[i]=(l->c).code_cli;    // T contient tous les codes des clients

}

for(j=0;j<=i-1;j++)
{

 for (p=ach;p;p=p->next)                    //parcour liste des achat
 {
     if(p->b.code_cli==Table_client[j])    //teste si le client appartient aux table client
     {
      for(k=art;k;k=k->next)               //parcour liste des aaticles
      {
        if(k->a.code==p->b.code_art)
        {


            mont+=(p->b.nbr_art)*(k->a.prix);  // ajout de la montant dans la table de montant Tm
           for(l=C;l;l=l->next)
           {
               if(l->c.code_cli==Table_client[j])  //soustraction  de la remise
               mont-=mont*(l->c.remise /100);
           }
        }

      }

     }

 }


 Tm[j]=mont;
}
tri(Table_client,Tm,i);
 for(j=i;j>0;j--)
{



    printf("%4d %7.3f\n",Table_client[j],Tm[j]);      //affichage
}
}


void tri(int T1[],float T2[],int n)
{

int i=0,i_min;
while(i<n-1)
{
i_min=get_i_min(T2,n,i);
if(i_min != i)
 {
   permuter(&T1[i],&T1[i_min]);
  permuter(&T2[i],&T2[i_min]);
 }
i++;
}
}

int get_i_min(int t[],int n, int i)
{
int j,i_min;
i_min=i;
j=i+1;
while(j<n)
{
if(t[j]<t[i_min])
i_min=j;
j++;
}
return(i_min);
}


void permuter(float *a, float *b)
{
float c;
c=*a;
*a=*b;
*b=c;

}


int main()
{
  FILE *F1,*F2,*F3;
  L_ARTICLE *articl;
  L_CLIENT *clien ;
  L_ACHAT *ach;
  int c;
  char date_d[11],date_f[11];


  F1=fopen("article.txt","r");
  if (F1 == NULL)
    {
        printf("erreur d'ouvrir le fichier");
        exit(0);
    }
   F2=fopen("client.txt","r");
   if (F2 == NULL)
    {
        printf("erreur d'ouvrir le fichier");
        fclose(F1);
        exit(0);
    }
  F3=fopen("achat.txt","r");
  if (F3 == NULL)
    {
        printf("erreur d'ouvrir le fichier");
        fclose(F1);
        fclose(F2);
        exit(0);
    }
   articl=charger_article(F1);
   clien=charger_client(F2);
   ach=charger_achat(F3);




   printf("date 1:") ; scanf("%s",&date_d);
   printf("date 2:") ; scanf("%s",&date_f);
   printf("code:") ; scanf("%4d",&c) ;
   printf("la quantite des produits  %4d achetee entre les deux date  %s et %s est  : %d \n",c,date_d,date_f,quantite(ach,c,date_d,date_f));
   prix_medic_classe(articl,ach,date_d,date_f);   //affiche les prix des medicaments dans cette classe
   montant(articl,clien,ach);




fclose(F1);
fclose(F2);
fclose(F3);

}
