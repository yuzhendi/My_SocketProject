/*************************************************************************
	> File Name: server.c
	> Author: yu zhen di
	> Mail: 1316215578@qq.com
	> Created Time: 2020年03月31日 星期二 11时41分18秒
 ************************************************************************/

#include "../common/head.h"//绝对路径
#include "../common/common.h"
#include "../common/tcp_server.h"

struct User{
    char name[20];
    int online;
    pthread_t tid;
    int fd;
};
char *conf = "./server.conf";

struct User *client;

int find_sub() {
    for(int i = 0; i < MAX_CLIENT; i++) {
        if(!client[i].online) return i;//找到空位置
    }
    return -1;

}
void *work(void *arg) {
    printf("client login!\n");
    return ;
}

bool check_online(char *name) {
    for(int i = 0; i < MAX_CLIENT; i++) {
        if(client[i].online && !strcmp(name,client[i].name))  {
            printf("D: %d is online\n");
            return true;
        }

    }
    return false;
}

int main() {
    int port, server_listen, fd;
    struct RecvMsg recvmsg;
    client = (struct User *)calloc(MAX_CLIENT, sizeof(struct User));

    port = atoi(get_value(conf, "SERVER_PORT"));
    if((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        return 1;
    }
    while(1) {
        if( (fd = accept(server_listen,NULL, NULL)) < 0 ) {
            perror("accept");
            continue;
        }
        recvmsg = chat_recv(fd);
        if(recvmsg.retval < 0) {
            close(fd);
            continue;
        }
        if(check_online(recvmsg.msg.from)) {
            //拒绝连接
            
        } else {
            int sub;
            sub = find_sub();
            client[sub].online = 1;
            client[sub].fd = fd;
            strcpy(client[sub].name, recvmsg.msg.from);
            pthread_t(&client[sub].fd,NULL,work,NULL);
        }

    }
    


    return 0;
}
