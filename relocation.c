#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void objConversion();

void main()
{
FILE *obj,*inter;
char type[2],pname[10];
int startaddr,length;
int readdr,effaddr;
int addr,len;
char cod[10],cod1[10];
int x,ad,codi,l;
objConversion();
obj=fopen("inter.txt","r");
inter=fopen("memory.txt","w+");
fscanf(obj,"%s%s%x%x",type,pname,&startaddr,&length);
printf("Enter the relocating address : ");
scanf("%x",&readdr);
effaddr=readdr-startaddr;
while(1)
{
  fscanf(obj,"%s%x%x",type,&addr,&len);
  if(feof(obj))
    break;
  if(strcmp(type,"T")==0)
  {
    fscanf(obj,"%s",cod);
    while(strcmp(cod,"T")!=0&&strcmp(cod,"M")!=0)
    {
      fprintf(inter,"%x\t%s\n",addr+effaddr,cod);
      addr=addr+(strlen(cod)/2);
      fscanf(obj,"%s",cod);
    }
    fseek(obj,-1,SEEK_CUR);
  }
  if(strcmp(type,"M")==0)
  {
    fseek(inter,0,SEEK_SET);
    x=addr-1;
    while(1)
    {
      fscanf(inter,"%x%s",&ad,cod1);
      if(feof(inter))
        break;
      if(x+effaddr==ad)
      {
        fseek(inter,-1*strlen(cod1),SEEK_CUR);
        fscanf(inter,"%x",&codi);
        fseek(inter,-1*strlen(cod1),SEEK_CUR);
        l=strlen(cod1);
        codi=codi+effaddr;
        fprintf(inter,"00%x",codi);
        fseek(inter,0,SEEK_END);
        break;
      }
    }
  }
}

fseek(inter,0,SEEK_SET);
while(1)
{
  fscanf(inter,"%x%s",&ad,cod);
  if(feof(inter))
    break;
  l=strlen(cod)/2;
  for(int i=0;i<l;++i)
  {
    printf("%x\t%c%c\n",ad,cod[i*2],cod[i*2+1]);
    ad++;
  }
}

fclose(inter);
fclose(obj);

}

void objConversion()
{
  FILE *obj,*obj1;
  obj=fopen("objectcode.txt","r");
  obj1=fopen("inter.txt","w+");
  char c;
  while(1)
  {
    c=getc(obj);
    if(feof(obj))
      break;
    if(c=='^')
    {
      c=' ';
    }
    putc(c,obj1);
  }
  fclose(obj);
  fclose(obj1);
}
