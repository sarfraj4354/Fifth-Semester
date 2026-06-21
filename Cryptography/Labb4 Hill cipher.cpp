#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int ctoi(char c){
    return tolower(c)-'a';}
char itoc(int n){
    return 'a'+((n%26+26)%26);
}
int gcd(int a,int b){
    while(b){
        int t=a%b;
        a=b;
        b=t;
    }
    return a;
}
int mod_inverse(int a,int m){
    for(int x=1;x<m;x++)
        if((a*x)%m==1)
            return x;
    return -1;
}
int valid_key(int k[2][2]){
    int det=(k[0][0]*k[1][1]-k[0][1]*k[1][0])%26;
    det=(det+26)%26;
    return gcd(det,26)==1;
}
void inverse_key(int k[2][2],int inv[2][2]){
    int det=(k[0][0]*k[1][1]-k[0][1]*k[1][0])%26;
    det=(det+26)%26;
    int d=mod_inverse(det,26);
    inv[0][0]=(k[1][1]*d)%26;
    inv[0][1]=(-k[0][1]*d+26)%26;
    inv[1][0]=(-k[1][0]*d+26)%26;
    inv[1][1]=(k[0][0]*d)%26;
}
void hill(const char *text,int k[2][2],char *res){
    char a[100]="";
    int n=0;
    for(int i=0;text[i];i++)
        if(isalpha(text[i]))
            a[n++]=tolower(text[i]);
    if(n%2) a[n++]='x';
    for(int i=0;i<n;i+=2){
        int p1=ctoi(a[i]);
        int p2=ctoi(a[i+1]);
        res[i]=itoc((k[0][0]*p1+k[0][1]*p2)%26);
        res[i+1]=itoc((k[1][0]*p1+k[1][1]*p2)%26);
    }
    res[n]='\0';
}
int main(){
    char text[100],enc[100],dec[100];
    int key[2][2],inv[2][2];
    printf("Enter the text: ");
    fgets(text,sizeof(text),stdin);
    text[strcspn(text,"\n")]='\0';
    printf("Enter 2x2 key matrix:\n");
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d",&key[i][j]);
    if(!valid_key(key)){
        printf("Invalid key!\n");
        return 1;
    }
    hill(text,key,enc);
    inverse_key(key,inv);
    hill(enc,inv,dec);
    printf("Encrypted Text: %s\n",enc);
    printf("Decrypted Text: %s\n",dec);
    return 0;
}

