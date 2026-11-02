#include "lexer.h"

int main(int argc, char* argv[]){
   
    if(argc<2){
        printf(RED"Error! enter valid C file!\n"RESET);
        return 0;
    }
    
    
    FILE* fin=fopen(argv[1],"r");
    if(fin==NULL){
        printf(RED"Error opening file!\n"RESET);
        return 0;
    }
    
    char word[100];
    int i=0;
    int line=1;
    char ch,next;
    int curly=0,round=0;
    
    
    while((ch=fgetc(fin))!=EOF){
        
        if(ch=='\n'){
            line++;
        }
       
        if(ch == '#'){
            word[i++] = ch;
            while((ch = fgetc(fin)) != '\n'){
                word[i++] = ch;
            }
            word[i] = '\0';
            printf("Line %2d : %-23s :\t%s\n", line, "Preprocessor directive", word);
            i = 0;
            line++;
            continue;
        }
       
        else if(ch=='/'){
            next=fgetc(fin);
            if(next=='/'){
                while((ch=fgetc(fin))!='\n' && ch!=EOF);
                if(ch == '\n') line++;
                continue;
            }
            else if(next=='*'){
                while((ch = fgetc(fin)) != EOF){
                    if(ch == '\n'){
                        line++;
                    }
                    if(ch == '*'){
                        next = fgetc(fin);
                        if(next == '/'){
                            break;
                        }
                        ungetc(next, fin);
                    }
                }
                continue;
            }
            else{
                ungetc(next,fin);
                printf("Line %2d : %-23s :\t%c\n", line, "operator", ch);
                continue;
            }
        }
        
        else if(ch=='\''){
            i=0;
            word[i++]=ch;
            char prev=0;
            while(1){
                ch=fgetc(fin);
                if(ch=='\'' && prev!='\\'){
                    break;
                }
                else if(prev=='\'' && (ch=='\n'||ch==')')){
                    ungetc(ch,fin);
                    ch='\0';
                    break;
                }
                else if(ch==';'){
                    char next=fgetc(fin);
                    if(next=='\''){
                        ungetc(next,fin);
                        prev=ch;
                        word[i++]=ch;
                        continue;
                    }
                    printf(RED"Error: Line %d: string literals not ended\n"RESET, line);
                    return 0;
                }
                prev=ch;
                word[i++]=ch;
            }
            word[i++]=ch;
            word[i]='\0';
            printf("Line %2d : %-23s :\t%s\n", line, "String literals",word);
            i=0;
        }
       
        else if(ch=='"'){
            i=0;
            word[i++]=ch;
            while((ch=fgetc(fin))!='"'){
                if(ch==';'){
                    printf(RED"Error: Line %d: string literals not ended\n"RESET, line);
                    return 0;
                }
                word[i++]=ch;
            }
            word[i++]=ch;
            word[i]='\0';
            printf("Line %2d : %-23s :\t%s\n", line, "String literals", word);
            continue;
            i=0;
        }
        
        else if(ch>='0' && ch<='9'){
            i=0;
            word[i++]=ch;
            ch=fgetc(fin);
            while(ch>='0' && ch<='9'){
                word[i++]=ch;
                ch=fgetc(fin);
            }
            word[i]='\0';
            printf("Line %2d : %-23s :\t%s\n", line, "numeric constant", word);
            i=0;
            ungetc(ch,fin);
            continue;
        }
        
        else if(isalnum(ch)|| ch=='_'){
            i=0;
            word[i++]=ch;
            ch=fgetc(fin);
            while(isalnum(ch)||(ch=='_')){
                word[i++]=ch;
                ch=fgetc(fin);
                if(isalnum(ch)==0&&ch!='_'){
                    break;
                }
            }
            word[i]='\0';
            if(iskeyword(word)){
                printf("Line %2d : %-23s :\t %s\n", line, "Keyword",word);
            }
            else if(is_nondatakeyword(word)){
                printf("Line %2d : %-23s :\t %s\n", line, "non-data keyword",word);
            }
            else{
                printf("Line %2d : %-23s :\t %s\n", line, "identifier",word);
            }
            i=0;
            ungetc(ch,fin);
            continue;
        }
        
        else if(isoperator(ch)){
            printf("Line %2d : %-23s :\t%c\n", line, "operator",ch);
            continue;
             
        }
        
        else if(ch=='('){
            round++;
            printf("Line %2d : %-23s :\t%c\n", line, "round braces opening",ch);
        }
        
        else if(ch==')'){
            round--;
            if(round<0){
                printf(RED"Error: ')' braces not balanced"RESET);
                return 0;
            }
            printf("Line %2d : %-23s :\t%c\n", line, "round braces closing",ch);
        }
       
        else if(ch=='{'){
            curly++;
            printf("Line %2d : %-23s :\t%c\n", line, "curly braces opening",ch);
        }
        
        else if(ch=='}'){
            curly--;
            if(curly<0){
                printf(RED"Error: '}' braces not balanced"RESET);
                return 0;
            }
            printf("Line %2d : %-23s :\t%c\n", line, "curly braces closing",ch);
        }
        
        else if(issymbol(ch)){
            printf("Line %2d : %-23s :\t%c\n", line, "symbol",ch);
        }
    }
    
    
    fclose(fin);
    
    if(curly>0){
        printf(RED"Error: '{' braces not balanced"RESET);
        return 0;
    }
    
    if(round>0){
        printf(RED"Error: '(' braces not balanced"RESET);
        return 0;
    }
    
    printf(GREEN"Successfully parsed\n"RESET);
    return 0;
}