#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


struct accounts{
    char uname[100];
    char name[100];
    float balance;
    char password[100];
};

int aexists(char dest[100]);
int transaction();
int deposit();
void balance();
int create();
int delete();
int name_print();
void aexit(char *error);

int name_print(){
    system("cls");
    printf("\n\t\t\tWELCOME TO APLUS BANK");
    printf("\n\t\t\t----------------------\n\n\n");
    return 1;
}

void main(){
    char ch;
    int result=0;
    if(name_print()!=1){
       aexit("Printing Bank Name.");
    }
        printf("\n\t\t\t1.Create Account\n\t\t\t2.Delete Account\n\t\t\t3.Transfer\n\t\t\t4.Deposit\n\t\t\t5.Mini_Statement\n\t\t\t6.Exit\n>");
        ch=getch();
        switch(ch){
            case '1':
                result=create();
                if(result==1){
                    printf("\nAccount Creation Successful..\n\n");
                }
                else{
                    aexit("Account Creation Not Done");
                }
                result=0;
                system("pause");
                main();
                break;
            case '2':
                result=delete();
                if(result==1){
                    printf("\nAccount Deletion Successful..");
                }
                else{
                    aexit("Account Deletion Not Done");
                }
                result=0;
                main();
                break;
            case '3':
                transaction();
                break;
            case '5':
                balance();
                break;
            case '6':
                printf("\n\n\t\t");
                system("pause");
                exit(0);
                break;
            default:
                main();
                break;
        }
        main();
}

void aexit(char *error){
    printf("\n\nError: %s",error);
    printf("\n\n\t\tExiting Application......\n");
    system("pause");
    exit(0);
}


int create(){
    int flag=0;
    FILE *fptr;
    struct accounts b;
    null:
    if(name_print()!=1){
       aexit("Printing Bank Name.");
    }
    if(flag==1){
        printf("\n\nEnter In All The Fields.\n");
    }
    else if(flag==2){
        printf("\n\nAccount Name Already Exists.\n");
    }
    printf("\n\nEnter your account details:\n\n\n");
    printf("\n\t\tUsername:");
    scanf("%s",b.uname);
    printf("\n\t\tName:");
    scanf("%s",b.name);
    printf("\n\t\tPassword:");
    scanf("%s",b.password);
    b.balance=0.00;
    if(b.uname==NULL||b.name==NULL||b.password==NULL){
        flag=1;
        goto null;
    }
    else{
        flag=0;
    }
    if(aexists(b.uname)==1){
        flag=2;
        goto null;
    }
    else{
        fptr=fopen(b.uname,"w");
        fwrite(&b,sizeof(b),1,fptr);
        fclose(fptr);
    }
    return 1;
}

int aexists(char dest[100]){
    FILE *aeptr;
    aeptr=fopen(dest,"r");
    if(aeptr==NULL){
            fclose(aeptr);
        return 0;
    }
    fclose(aeptr);
    return 1;
}

int delete(){
    FILE *deptr;
    struct accounts b;
    int flag=0;
    char name[100],password[100];
    att:
    if(name_print()!=1){
       aexit("Printing Bank Name.");
    }
    if(flag ==1){
        printf("\n\nPasswords Not Matching...");
    }
    printf("\n\nEnter Account Details To Delete:\n\n\n\n");
    printf("\n\t\tUser name:");
    scanf("%s",name);
    printf("\n\t\tPassword:");
    scanf("%s",password);
    if(aexists(name)==0){
            printf("\n\nAccount Not Exists..");
            system("pause");
            main();
    }
    deptr=fopen(name,"r");
    fread(&b,sizeof(b),1,deptr);
    fclose(deptr);
    if(strcmp(password,b.password)==0){
        remove(name);
        return 1;
    }
    else{
        flag=1;
        goto att;
    }
    return 0;
}


void balance(){
    FILE *bptr;
    struct accounts b;
    int flag=0;
    char name[100],password[100];
    att:
    if(name_print()!=1){
       aexit("Printing Bank Name.");
    }
    if(flag ==1){
        printf("\n\nPasswords Not Matching...");
    }
    printf("\n\nEnter Account Details For Statement:\n\n\n\n");
    printf("\n\t\tUsername:");
    scanf("%s",name);
    printf("\n\t\tPassword:");
    scanf("%s",password);
    if(aexists(name)==0){
            printf("\n\nAccount Not Exists..");
            system("pause");
            main();
    }
    bptr=fopen(name,"r");
    fread(&b,sizeof(b),1,bptr);
    fclose(bptr);
    if(strcmp(password,b.password)==0){
        if(name_print()!=1){
            aexit("Printing Bank Name.");
        }
    printf("\n\n\n\nMINI STATEMENT:\n");
        printf("\n\t\t\tName: %s",b.name);
        printf("\n\n\t\t\tBalance: %f",b.balance);
        getch();
    }
    else{
        flag=1;
        goto att;
    }
    main();
}


int transaction(){
    FILE *lptr,*kptr,*temp;
    struct accounts k,d;
    int flag=0;
    float amount=0.0;
    char name[100],password[100],dname[100];
    att:
    if(name_print()!=1){
       aexit("Printing Bank Name.");
    }
    if(flag ==1){
        printf("\n\nPasswords Not Matching...");
    }
    printf("\n\nEnter Account Details For Statement:\n\n\n\n");
    printf("\n\t\tUsername:");
    scanf("%s",name);
    printf("\n\t\tPassword:");
    scanf("%s",password);
    if(aexists(name)==0){
            printf("\n\nAccount Not Exists..");
            system("pause");
            main();
    }
    kptr=fopen(name,"r");
    fread(&k,sizeof(k),1,kptr);
    if(strcmp(password,k.password)==0){
        printf("\n\nEnter the Username to transfer:");
        scanf("%s",dname);
        if(aexists(dname)==0){
            printf("\nAccount Not Exists...\n\n");
            system("pause");
            main();
        }
        lptr=fopen(dname,"r");
        fread(&d,sizeof(d),1,lptr);
        printf("\n\nEnter the Amount: [MUST BE > 500]");
        scanf("%f",&amount);
        if(amount<500 || k.balance<amount){
            printf("\nTransaction Not Success...\n\n");
            system("pause");
            main();
        }
        fclose(kptr);
        fclose(lptr);
        d.balance=d.balance+amount;
        k.balance=k.balance-amount;
        temp=fopen("temp.aplus","w");
        fwrite(&k,sizeof(k),1,temp);
        fclose(temp);
        remove(name);
        rename("temp.aplus",name);
        fflush(stdin);
        printf("\a");
        temp=fopen("temp.aplus","w");
        fwrite(&d,sizeof(d),1,temp);
        fclose(temp);
        remove(dname);
        rename("temp.aplus",dname);
        printf("\a");
        printf("\n\nTransaction Success\n\n");
        system("pause");
    }
    else{
        flag=1;
        goto att;
    }
    main();
}



