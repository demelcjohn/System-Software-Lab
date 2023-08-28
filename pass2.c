#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
FILE *fint,*fopt,*fsym,*flen;
char la[20],mne[20],op[20],len[20],lc[20],start[20];
char opm[20],opad[20];
char symop[20],symad[20];
int flag1,flag2,l,i;
fint = fopen("inter.txt","r");
fscanf(fint,"%s%s%s",la,mne,op);
if(strcmp(mne,"START")==0)
{
  strcpy(start,op);
  flen=fopen("plength.txt","r");
  fscanf(flen,"%s",len);
}
printf("H^%s^%s^%s\n",la,op,len);
printf("T^%s^%s",op,len);
fscanf(fint,"%s%s%s%s",lc,la,mne,op);
while(!feof(fint))
{
  flag1=0;
  fopt=fopen("optab.txt","r");
  fscanf(fopt,"%s%s",opm,opad);
  while(!feof(fopt))
  {
    if(strcmp(mne,opm)==0)
    {
      flag1=1;
      break;
    }
    fscanf(fopt,"%s%s",opm,opad);
  }
  if(flag1==1)
  {

    if(strcmp("-",op)!=0)
    {
      flag2=0;
      fsym=fopen("symtab.txt","r");
      fscanf(fsym,"%s%s",symop,symad);
      while(!feof(fsym))
      {
        if(strcmp(symop,op)==0)
        {
          flag2=1;
          break;
        }
        fscanf(fsym,"%s%s",symop,symad);
      }
      printf("^%s%s",opad,symad);
    }
  }
  else if(strcmp(mne,"BYTE")==0||strcmp(mne,"WORD")==0)
  {
    if(strcmp(mne,"WORD")==0)
      printf("0000%s^",op);
    else
    {
      l=strlen(op);
      for(i=2;i<l;i++)
      {
        printf("%d",op[i]);
      }
      printf("^");
    }
  }


  fscanf(fint,"%s%s%s%s",lc,la,mne,op);
}
printf("\nE^00%s\n",start);
}
