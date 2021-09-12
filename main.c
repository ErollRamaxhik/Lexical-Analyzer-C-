#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]){
	char keywords[20][10] = {"break","case","char","const","continue","do","else","enum","float","for","goto","if","int","long","record","return","static","while",};
	int i, flag = 0;

	for(i = 0; i < 18; ++i){
            //printf("%s ",keywords[i]);
            //printf("%s ",buffer);
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	return flag;
}

int main(){
	char *text,ch, buffer[100];
	FILE *fp,*fb;
	int i,k,j=0,l,sayi;
	char integer[15];
    int test=0;
	fp = fopen("code.psi.txt","r"); // okuma
    fb= fopen("code.isp.txt","a"); // yazdirma

	if(fp == NULL){ // dosya acma kontrolu
		printf("Dosya acilamadi!!!\n");
		exit(0);
	}

	if(fb == NULL){ // dosya acma kontrolu
		printf("Dosya acilamadi!!!\n");
		exit(0);
	}


	fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    text = malloc(fsize + 1);
    fread(text, 1, fsize, fp);
    fclose(fp);

    text[fsize] = 0;

    /*if(fp){
        while(fgets(text, sizeof(text), fp) != NULL)
    {
        fputs(temp, stdout);

    }
    fclose(fp);
    }*/
	/*if(fp){ // tum karakterleri dizi stringimize aktariyoruz
       fgets(text, 1000, fp);
        text[strlen(text)] = '\0';
    }*/

    //printf("\n%s\n", text);

    for (i=0;i<strlen(text);i++){ //tum karakterleri kucultmek icin loop dongusu
    text[i]=tolower(text[i] );
    }

    //printf("\n%s\n", text);

    for(i=0;i<strlen(text);i++){ // elimizde bulunan stringin sonuna kadar don

                if(isalpha(text[i])){ // alphabetical mi yani alfabeden harf iceriyor mu

                    while(text[i]!=' ' && text[i]!='\0' && text[i]!='\n'){ // space veya sonuna gelene kadar


{
                         //printf("\nUzunluk %d\n",j);
}                        buffer[j++]=text[i]; //
                        i++;
                    }


                    if(isKeyword(buffer) == 1){
                        printf("\nKeyword:",buffer);
                            for(k=0;k<j;k++){
                                printf("%c",buffer[k]);
                            }
                            j=0;
                            fputs("\nKeyword:",fb);
                            fputs(buffer,fb);
                            fputs("\n",fb);

                    }else{
                        //printf("\nKeyword:%s",buffer); // keyword ise

                        printf("\nIdentiffier:",buffer);
                            for(k=0;k<j;k++){
                                //printf("\nUzunluk J:%d",j);
                                printf("%c",buffer[k]);
                                if(k>19){
                                    printf("\n\nHATA !!! Identifier:");
                                    for(k=0;k<j;k++){
                                        printf("%c",buffer[k]);
                                    }
                                    printf("\nIdentifier stringinin maximum kappasitesi (20) asildi !!!\n");
                                    break;
                                }

                            }

                            //printf("\nUzunluk %d\n",j);
                            fputs("\nIdentifier:",fb);
                            for(k=0;k<j;k++)
                            fputc(buffer[k],fb);

                            fputs("\n",fb);

                            j=0;
                    }
                        //printf("\nIdentifier:%s", buffer); // identifier ise



                    memset(buffer,0,strlen(buffer)); //bufferin icini sifirla

            }else if(isdigit(text[i])){ // numara iceriyor mu

                    while(text[i]!=' ' && text[i]!='\0' && text[i]!='\n'){

                            buffer[j++]=text[i];
                            i++;
                        }

                        printf("\nInteger:",buffer);
                            for(k=0;k<j;k++){

                                printf("%c",buffer[k]);
                                if(k>9){
                                    printf("\n\nHATA !!! Integer:");
                                    for(k=0;k<11;k++){
                                        printf("%c",buffer[k]);
                                    }
                                    printf("\nInteger maximum kappasitesi (10) asildi !!!\n");
                                    break;
                                }

                            }
                        j=0;
                        //printf("\nInteger:%s",buffer);

                            fputs("\nInteger:",fb);
                            fputs(buffer,fb);
                            fputs("\n",fb);

                        memset(buffer,0,strlen(buffer));


            }else if(text[i]=='(' && text[i+1]=='*'){

                    buffer[j++]=text[i];
                    buffer[j++]=text[i+1];
                    i+=2; // (* oldugu icin ve i tekrardan * olacagi icin, kisacasi cakismamasi icin direk (* atama yapiyoruz sonra icindekileri tek tek aliyoruz

                    while(text[i]!='*' || text[i+1]!=')'){ // *) gorene kadar dewamke
                            //printf("\n%c",text[i]);
                        if(text[i+1]=='\0'){ //Eger dosyanin sonuna kadar gelip *) bulamadiysa hata vericek ve sonuna kadar olan kismi yazdiracak
                            printf("\n\nHATA !!! Comments:%s",buffer);
                            printf("\nDosyanin sonuna gelindi ve *) yorum parantezi kapatilmadi !!!\n");
                            test=1;
                            break; // sonlandir
                        }
                            buffer[j++]=text[i]; // eger yukardaki degilse o zaman eklemeye devam
                            i++;
                            //printf("\nJ Uzunluk:%d\n",j);


                        }
                        if(test==0){ //eger olurda hata ciakrsa yukarda test 1 yaptik ki buna girmesin hic yani yukarda bitecek bunu pas gececek
                            buffer[j++]=text[i];
                            buffer[j++]=text[i+1];
                            i++;

                            //printf("Uzunluk Bufferin:%d",strlen(buffer));

                            printf("\nComments:",buffer);
                            for(k=0;k<j;k++){
                                printf("%c",buffer[k]);
                            }

                            fputs("\nComments:",fb);
                            fputs(buffer,fb);
                            fputs("\n",fb);
                            j=0;

                        }

                        memset(buffer,0,strlen(buffer)); //bufferi sifirla

            }else if(text[i]=='+' || text[i]=='-' || text[i]=='*' || text[i]=='/' || text[i]==':' || text[i]=='='){ // operator kontrol burayi cok delmiycem

                    while(text[i]!=' ' && text[i]!='\0' && text[i]!='\n'){

                            buffer[j++]=text[i];
                            i++;
                        }
                        /*printf("\nOperator:",buffer);
                            for(k=0;k<j;k++){
                                printf("%c",buffer[k]);
                            }
                            j=0;*/
                        printf("\nOperator:%s",buffer);

                            fputs("\nOperator:",fb);
                            fputs(buffer,fb);
                            fputs("\n",fb);
                        j=0;
                        memset(buffer,0,strlen(buffer));

            }else if (text[i]=='"'){ // string constant isareti gorursek almaya basla
                buffer[j++]=text[i];
                i++;
                while(text[i]!='"'){
                    if(text[i+1]=='\0'){ //yine hata kontrolu olurda dosyanin sonuna gelmissek ve cift tirnak bulamamissak burdaki mantik yukardaki comments mantigiyla ayni sadece burda tek isaret var yukarda cift yani (* vs "
                            printf("\n\nHATA !!! String Constants:%s",buffer);
                            printf("\nDosyanin sonuna gelindi ve '' yorum parantezi kapatilmadi !!!\n");
                            test=1;
                            break;
                        }else{
                            buffer[j++]=text[i];
                            i++;
                        }


                        }
                        if(test==0){
                            buffer[j++]=text[i];

                            printf("\nString Constants:%s",buffer);

                                fputs("\nString Constants:",fb);
                                fputs(buffer,fb);
                                fputs("\n",fb);
                            j=0;
                            memset(buffer,0,strlen(buffer));
                        }
            }else if (text[i]=='('){ // parantez check bunlari zaten biliyorsun
                buffer[j++]=text[i];
                printf("\nLeftPar:%s",buffer);

                fputs("\nLeftPar:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]==')'){
                buffer[j++]=text[i];
                printf("\nRightPar:%s",buffer);

                fputs("\nRightPar:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]=='['){
                buffer[j++]=text[i];
                printf("\nLeftSquareBracket:%s",buffer);

                fputs("\nLeftSquareBracket:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]==']'){
                buffer[j++]=text[i];
                printf("\nRightSquareBracket:%s",buffer);

                fputs("\nRightSquareBracket:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]=='{'){
                buffer[j++]=text[i];
                printf("\nLeftCurlyBracket:%s",buffer);

                fputs("\nLeftCurlyBracket:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]=='}'){
                buffer[j++]=text[i];
                printf("\nRightCurlyBracket:%s",buffer);

                fputs("\nRightCurlyBracket:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }else if (text[i]==';'){ //end of line check
                buffer[j++]=text[i];
                printf("\nEndOfLine:%s",buffer);

                fputs("\nEndOfLine:",fb);
                fputs(buffer,fb);
                fputs("\n",fb);

                j=0;
                memset(buffer,0,strlen(buffer));
            }

    }
    printf("\n");
    fclose(fb);

	return 0;
}
