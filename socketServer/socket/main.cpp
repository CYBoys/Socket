/*
 1）头文件：
 
 sys/socket.h   包含了socket相关的函数，如socket，send 和recv， 以及struct sockaddr等
 
 netinet/in.h    包含了地址结构，如struct sockaddr_in
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, const char * argv[]) {
   //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    /*
     socket()函数创建了一个套接字
     参数:
     AF_INET 表示使用IPv4地址
     SOCK_STREAM 表示使用面向链接的数据传输方式
     IPPROTO_TCP 表示使用TCP协议
     在Linux中，socket也是一种文件，有文件描述符,可以使用write()/read()函数进行I/O操作
    */
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));//每个字接都用0填充
    serv_addr.sin_family = AF_INET;//使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//具体的IP地址
    serv_addr.sin_port = htons(1234);//端口
    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    /*
     bind()函数将套接字serv_sock 与特定的IP地址和端口绑定 IP地址和端口都保存在sockaddr_sin 结构体中
     可以发现，socket()函数确定了套接字的各种属性,bind()函数让套接字与特定的IP地址和端口对应起来,这样客户端才能链接到该套接字
     */
    
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);//个数
    /*
     让套接字处于被动监听状态。所谓被动监听,是指套接字一直处于“睡眠”中，知道客户端发器请求才会被“唤醒”
     */
    
    //接受客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    /*
    accpet()函数用来接收客户端的请求。程序一旦执行到accept就会被阻塞(暂停运行),直到客户端发起请求
     */
    //向客户端发送数据
    char str[] = "Hello world";
    write(clnt_sock, str, sizeof(str));
    /*
     write()函数用来向套接字文件中写入数据,也就是向客户端发送数据
     */
    
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
}



















