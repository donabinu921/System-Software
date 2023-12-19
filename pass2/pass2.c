#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *fint,*fopt,*fsym,*flen;
    int len,i;
    char add[30],label[30],opcode[30],operand[30],start[30];
    char mnemonic[30],code[30];
    char locctr[30],symbol[30];

    fint=fopen("input.txt","r");
    fopt=fopen("optab.txt","r");
    fsym=fopen("symtab.txt","r");
    flen=fopen("length.txt","r");

    fscanf(fint,"%s %s %s %s",add,label,opcode,operand);

    if(strcmp(opcode,"START")==0)
    {
        strcpy(start,operand);
        fscanf(flen,"%d",&len);
   
    }
    printf("H^%s^%s^%d\nT00%s^",label,start,len,start);
    fscanf(fint,"%s%s%s%s",add,label,opcode,operand);
    while(strcmp(opcode,"END")!=0)
    {
        fscanf(fopt,"%s%s",code,mnemonic);
        while(!feof(fopt))
        {
            if(strcmp(opcode, code)==0)
            {
                fclose(fopt);
                fscanf(fsym,"%s%s",locctr,symbol);
                while(!feof(fsym))
                {
                    if(strcmp(operand,symbol)==0)
                    {
                        printf("%s%s^",mnemonic,locctr);
                        break;
                    }
                    else
                    {
                        fscanf(fsym,"%s%s",locctr,symbol);
                    }
                }
                break;
            }
            else
            {
                fscanf(fopt,"%s%s",code,mnemonic);
            }
        }
        if(strcmp(opcode,"WORD")==0)
        {
            printf("0000%s^",operand);
        }
        else if(strcmp(opcode,"BYTE")==0)
        {
            len=strlen(operand);
            for(i=2;i<len;i++)
            {
                printf("%d",operand[i]);
            }
            printf("^");
        }
        fscanf(fint,"%s%s%s%s",add,label,opcode,operand);
        fopt = fopen("optab.txt","r");
        fseek(fopt,SEEK_SET,0);
    }
    printf("\nE^00%s",start);
    fclose(fint);
    fclose(fopt);
    fclose(fsym);
    fclose(flen);

}