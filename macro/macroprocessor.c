#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct arg{
  char name[100];
  int p;
}arg[50];

int argp=0;

void changeop(char [100]);

void main()
{
FILE *fin,*fnam,*farg,*fdef,*fout;
char la[100],mne[100],op[100];
int pos,b,e,i;
char name[100];
char *token,*token1;
int flag1,flag2,argno;
char dmne[100],dop[100];
char aarg[100],temp[100];
int ano;
fin=fopen("input.txt","r");
fnam=fopen("namtab.txt","w+");
farg=fopen("argtab.txt","w+");
fdef=fopen("deftab.txt","w+");
fout=fopen("output.txt","w");
while(1)
{
  fscanf(fin,"%s%s%s",la,mne,op);
  if(feof(fin))
    break;
  if(strcmp(mne,"END")==0)
    break;
  if(strcmp(mne,"MACRO")==0)
  {
    fseek(fnam,0,SEEK_END);
    fseek(fdef,0,SEEK_END);
    pos=ftell(fdef);
    fprintf(fnam,"%s\t\t%d",la,pos);
    fprintf(fdef,"%s\t%s\n",la,op);
    token=strtok(op,",");
    i=0;
    while(token!=NULL)
    {
      strcpy(arg[argp].name,token);
      arg[argp].p=i+1;
      argp++;
      i++;
      token=strtok(NULL,",");
    }
    while(1)
    {
      fscanf(fin,"%s%s%s",la,mne,op);
      changeop(op);
      fprintf(fdef,"%s\t%s\n",mne,op);
      if(strcmp(mne,"MEND")==0)
        break;
    }
    fprintf(fnam,"\t\t%ld\n",ftell(fdef));
  }
  else
  {
    flag1=0;
    fseek(fnam,0,SEEK_SET);
    while(1)
    {
      fscanf(fnam,"%s%d%d",name,&b,&e);
      if(feof(fnam))
        break;
      if(strcmp(name,mne)==0)
      {
        flag1=1;
        break;
      }
    }
    if(flag1==0)
    {
      fprintf(fout,"%s\t%s\t%s\n",la,mne,op);
    }
    else
    {
      argno=1;
      token=strtok(op,",");
      fseek(farg,0,SEEK_END);
      while(token!=NULL)
      {
        fprintf(farg,"%s\t%d\n",token,argno);
        argno++;
        token=strtok(NULL,",");
      }
      fseek(fdef,b,SEEK_SET);
      fscanf(fdef,"%s%s",dmne,dop);
      while(ftell(fdef)<e)
      {
        fscanf(fdef,"%s%s",dmne,dop);
        if(strcmp(dmne,"MEND")==0)
          break;
        strcpy(temp,dop);
        token=strtok(temp,"?");
        flag2=0;
        strcpy(dop,"");
        while(token!=NULL)
        {
          for(i=1;i<10;++i)
          {
            if(token[0]==i+48)
            {
              flag2=1;
              break;
            }
          }
          if(flag2==1)
          {
            fseek(farg,0,SEEK_SET);
            while(1)
            {
              fscanf(farg,"%s%d",aarg,&ano);
              if(feof(farg))
                break;
              if(i==ano)
              {
                strcat(dop,aarg);
                break;
              }
            }
          }
          if(flag2==1)
            token1=token+1;
          else
            strcpy(token1,token);
          strcat(dop,token1);
          token=strtok(NULL,"?");
        }
        fprintf(fout,"%s\t%s\t%s\n","-",dmne,dop);
      }
    }



  }
}
fprintf(fout,"%s\t%s\t%s\n",la,mne,op);
}



void changeop(char s[100])
{
  char temp[100],*ps,*token1;
  int len;
  for(int i=0;i<argp;++i)
  {
    strcpy(temp,s);
    ps=strstr(temp,arg[i].name);
    while(ps!=NULL)
    {
      len=strlen(arg[i].name);
      *ps='?';
      *(ps+1)=arg[i].p+48;
      for(int j=2;j<len;++j)
      {
        *(ps+j)='$';
      }
      token1=strtok(temp,"$");
      strcpy(s,"");
      while(token1!=NULL)
      {
        strcat(s,token1);
        token1=strtok(NULL,"$");
      }
      strcpy(temp,s);
      ps=strstr(temp,arg[i].name);
    }
  }
}
