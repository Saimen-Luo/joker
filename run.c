// Copyright (c) 2019-present Cloud <cloud@txthinking.com>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of version 3 of the GNU General Public
// License as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "joker.h"

void run(int argc, char *argv[])
{
    pid_t pid1 = fork();
    if (pid1 > 0) {
        waitpid(pid1, NULL, 0);
    }
    if (pid1 == 0) {
        pid_t pid2 = fork();
        if (pid2 > 0) {
            exit(0);
        }
        if (pid2 == 0) {
            int io[2];
            if (pipe(io) != 0){
                perror("can't create io");
                return;
            }
            pid_t pid = fork();
            if(pid == 0){
#ifdef __linux__
                prctl(PR_SET_PDEATHSIG, SIGHUP);
#endif
                close(io[0]);

                char *l[argc];
                int i = 1;
                for(;i<argc;i++){
                    l[i-1] = (char *)malloc(strlen(argv[i])+1);
                    l[i-1] = strcpy(l[i-1], argv[i]);
                }
                l[i-1] = NULL;

                dup2(io[1], STDOUT_FILENO);
                dup2(io[1], STDERR_FILENO);
                execvp(l[0], l);

                i=0;
                for(;i<argc-1;i++){
                    free(l[i]);
                }
                close(io[1]);
            }
            if(pid > 0){
                signal(SIGCHLD, SIG_IGN);
                // TODO ignore kill-like signal
                close(io[1]);

                char *s = (char *) malloc(9*100 + 7*100);
                sprintf(s, "/tmp/joker.log");
                FILE *f = fopen(s, "a+");
                if(!f) {
                    perror("can not open log file");
                    free(s);
                    close(io[0]);
                    return;
                }

                // http://t.zoukankan.com/Harley-Quinn-p-7481593.html Linux的文件描述符fd与文件指针FILE*互相转换
                FILE *fp = fdopen(io[0], "r");
                char *baseName = basename(argv[1]);

                for(;;){
                    char s[1024];
                    char *n = fgets(s, 1024-1, fp);
                    if(n == NULL){
                        break;
                    }
                    // s[n] = 0;
                    // -->
                    // https://blog.csdn.net/WU9797/article/details/76922323 <C语言>打印（输）出系统时间-----time相关函数
                    time_t t;
                    struct tm *p;
                    time(&t);
                    p = localtime(&t); // 取得当地时间
                    char *stamp = (char *) malloc(9*100 + 7*100);
                    sprintf(stamp, "[%d/%02d/%02d %02d:%02d:%02d] ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
                    fputs(stamp, f);
                    // <--
                    fputs(baseName, f);
                    fputs(": ", f);
                    int i = fputs(s, f);
                    if (i<0){
                        perror("append log failed");
                        break;
                    }
                    fflush(f);
                }
                close(io[0]);
                fclose(f);
                chmod(s, 0666);
                free(s);
            }
        }
    }
}
