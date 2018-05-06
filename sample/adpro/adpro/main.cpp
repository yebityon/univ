
/*
 ============================================================================
 Name        : shell-a.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
using namespace std;
//for debug
#define true 1
#define false 0
void coutd(int d){printf("%d\n",d); return;}
#define CC cout("hoge");
int pidlist[1024]={0};
int pidcount=0;
int fgpid=0;
//fix the string and return length of s
int StringFix(char *s){int i=0;for(i=0;;i++){if(s[i]=='\n'){s[i]='\0';break;}}return i+1;}
/*when use exit or quit command*/
void sighandler(int signame){
    if(fgpid==0){
        puts("No fg");
    }
    kill(fgpid,SIGINT);
}
void printe(int signame){puts("hoge");}
int  IsEnd(char *s){
    char tmp[1024]={};
    int i=0,j=0;
    while(s[i]!='\0'){
        tmp[j]=s[i];
        i++,j++;
    }
    if((!strcmp(tmp,"exit"))||(!(strcmp(tmp,"quit"))))return true;
    else return false;
}
/*divide strings and return boolean flag*/
int  DivideString(char **pargs,char *str,int ssize){
    ssize=strlen(str);
    int i;
    int bg_flag=false;
    if(str[ssize-2]=='&'){
        str[ssize-2]='\0';
        bg_flag=true;
        ssize-=2;
    }
    for(i=0;i<ssize;i++)if(str[i]==' ')str[i]='\0';
    int index=0;
    for(i=0;i<ssize-bg_flag;i++){
        if(!i){pargs[index++]=str;}
        if(str[i]=='\0')pargs[index++]=&str[i+1];
    }
    return bg_flag;
}
/**erase [index] element*/
void  EraseArray(int *array,int index){
    //coutd(index);
    int _size=1024;
    int sub=0;
    int i=0;
    int dp[1024]={};
    for(i=0;i<_size;i++)dp[i]=array[i];
    for(i=0;i<_size;i++){
        if(i!=index){
            array[sub++]=dp[i];
        }
    }
    --pidcount;
}
int FindElement(int *array,int val){
    int _size=1024;
    int i=0;
    for(i=0;i<_size;i++)if(array[i]==val)return i;
    return false;
}
void command_jobs(){
    int i=0;
    for(;i<pidcount;i++){
        printf("%d番目のプロセス :",i);
    }
    return;
}
void command_fg(){
    int changeBg;
    int status;
    scanf("%d",&changeBg);
    coutd(changeBg);
    char gomi;
    scanf("%c",&gomi);
    if(changeBg>pidcount-1){
        //cout("error!");
        return;
    }else{
        fgpid=pidlist[changeBg];
        waitpid(pidlist[changeBg],&status,0);
        EraseArray(pidlist,changeBg);
    }
    return;
}
int main(void) {
    while(1){
        char str[1024]={};
        int status;
        int PidIsExit=waitpid(-1,&status,WNOHANG);
        if(PidIsExit>0){
            int candi=FindElement(pidlist,PidIsExit);
            EraseArray(pidlist,candi);
        }
        char *env=getenv("SHELL");
        printf("$");
        signal(SIGINT,sighandler);
        signal(SIGKILL,printe);
        fgets(str,1024,stdin);           
        int strLen=StringFix(str);
        if(IsEnd(str))return puts("プロセスが終了しました")*0;
        if(!strcmp(str,"jobs")){command_jobs();continue;}
        if(!strcmp(str,"fg")){command_fg();continue;}
        char *pargs[1024];
        int IsBg=false;
        strcat(env,str);
        IsBg=DivideString(pargs,env,strLen);
        int pid=fork();
        if(pid==-1){
            puts("error!");
            continue;
        }
        if(pid==0){
            execv(str,pargs);
            setpgid(0,0);
            exit(0);
        }else{
            if(IsBg){
                fgpid=pid;
                pidlist[pidcount++]=pid;
                waitpid(pid,&status,WNOHANG);
            }else{
                fgpid=pid;
                waitpid(pid,&status,0);
            }
        }
    }
}

