#include<stdio.h>
#include<string.h>
#include<ctype.h>

void checkstr(char str[]){
    int i =0;
    for(i=0;i<100;i++){
     if(!isdigit(str[i])){
    if((str[i]=='-'||str[i]=='+')&&i==0){
        continue;
    }else{
        printf("Not a number");
        break;
    }
    if(str[i]=='.'){
         continue;
    }else{
        printf("Not a number");
        break;
    }
    }
}
}


int main(){
char input[100];
printf("Enter your String:");
scanf("%[^\n]", input);
checkstr(input);

return 0;
}

