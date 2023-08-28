#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
  FILE *f1,*f2,*f3,*f4,*fl;
  int locctr,startadd,op1,o,len,programlength;
  char pos[20],la[20],mne[20],op[20],otp[20],n[20];
  f1=fopen("input.txt","r");
  f3=fopen("symtab.txt","w");
  f4=fopen("inter.txt","w");
  fscanf(f1,"%s%s%x",la,mne,&op1);
  if(strcmp(mne,"START")==0)
  {
    startadd=op1;
    locctr=op1;
    printf("\t%s\t%s\t%x\n",la,mne,op1);
    fprintf(f4,"\t%s\t%s\t00%x\t",la,mne,op1);
  }
  else
  {
    locctr=0;
  }
  fscanf(f1,"%s%s%s",la,mne,op);
  while(!feof(f1))
  {
    strcpy(n,op);
    printf("\n%x\t%s\t%s\t%s\t",locctr,la,mne,op);
    fprintf(f4,"\n%x\t%s\t%s\t%s\t",locctr,la,mne,op);

    f2=fopen("optab.txt","r");
    fscanf(f2,"%s%d",otp,&o);
    if(strcmp(la,"-")!=0)
    {
      fprintf(f3,"%s\t%x\n",la,locctr);
    }
    while(!feof(f2))
    {
      if(strcmp(mne,otp)==0)
      {
              locctr=locctr+3;
              break;
      }
      fscanf(f2,"%s%d",otp,&o);
    }
      fclose(f2);


      if(strcmp(mne,"WORD")==0)
      {

              locctr=locctr+3;
      }
      else if(strcmp(mne,"RESW")==0)
      {

              op1=atoi(op);
              locctr=locctr+(3*op1);
      }
      else if(strcmp(mne,"BYTE")==0)
      {

              if(n[0]=='X')
              {
                      locctr=locctr+1;
              }
              else
              {
                      len=strlen(op)-2;
                      locctr=locctr+len;
              }
      }
      else if(strcmp(mne,"RESB")==0)
      {
              op1=atoi(op);
              locctr=locctr+op1;
      }

    printf("\n");
    fscanf(f1,"%s%s%s",la,mne,op);
  }
  programlength= locctr-startadd;
  fl=fopen("plength.txt","w");
  fprintf(fl,"%x",programlength);
  fclose(fl);
  fclose(f1);
  fclose(f3);
}
