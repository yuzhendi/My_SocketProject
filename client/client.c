/*************************************************************************
	> File Name: client.c
	> Author: yuzhendi
	> Mail: 1316215578.com
	> Created Time: 二  3/231 17:06:21 2020
 ************************************************************************/


#include "../common/chatroom.h"
#include "../common/tcp_client.h"
#include "../common/common.h"

char *conf = "./client.conf";



int main(int argc, char **argv) {
    int port, sockfd;
    char ip[20];
    struct Msg msg;
    port = atoi(get_value(conf, "SERVER_PORT"));
    strcpy(ip, get_value(conf, "SERVER_IP"));

    printf("ip = %s, port = %d\n",ip,port);

    if((sockfd = socket_connect(ip, port)) < 0) {
        perror("connect");
        return 1;
    }
    strcpy(msg.from, get_value(conf, "MY_NAME"));
    msg.flag = 2;//服务端通知信息flag = 2

    if(chat_send(msg,sockfd) < 0) {
        return 2;
    }


    return 0;
} 
