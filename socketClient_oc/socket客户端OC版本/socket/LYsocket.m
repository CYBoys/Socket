//
//  LYsocket.m
//  socket客户端OC版本
//
//  Created by chairman on 15/10/25.
//  Copyright © 2015年 LaiYong. All rights reserved.
//

#import "LYsocket.h"

@implementation LYsocket
- (void)loadDataFromServerWithURL:(NSURL *)url {
    NSString *host = [url host];
    NSNumber *port = [url port];
    
    //Create socket
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor==-1) {
        NSLog(@"Failed to create soket.");
        return;
    }
    //Get IP address from host
    struct hostent *remoteHostEnt = gethostbyname([host UTF8String]);
    if (remoteHostEnt == NULL) {
        close(socketFileDescriptor);
        [self networkFailedWithErrorMessage:@"Unable to resolve the hostname of the warehouse server."];
        return;
    }
    struct in_addr *remoteInAddr = (struct in_addr *)remoteHostEnt->h_addr_list[0];
    
    //Set the socket parameters
    struct sockaddr_in socketparameters;
    socketparameters.sin_family  = AF_INET;
    socketparameters.sin_addr = *remoteInAddr;
    socketparameters.sin_port = htons([port intValue]);
    
    //Connect the socket
    int ret = connect(socketFileDescriptor, (struct sockaddr *) &socketparameters, sizeof(socketparameters));
    if (ret == -1) {
        close(socketFileDescriptor);

        NSString *errorInfo = [NSString stringWithFormat:@">> Friled to connect to %@:%@",host,port];
        [self networkFailedWithErrorMessage:errorInfo];
        return;
    }
    
    NSLog(@">>Successfully connect to %@:%@",host,port);
    
    NSMutableData *data = [[NSMutableData alloc]init];
    BOOL waitingForData = YES;
    
    //Continually receive data until we reach the end of the date
    
    int maxCount = 5;
    int i=0;
    while (waitingForData && i < maxCount) {
        const char *buffer[1024];
        int length = sizeof(buffer);
        
        //Read a buffer's amount of data from the socker; the number of bytes read is returned;
        NSInteger result = recv(socketFileDescriptor, &buffer, length, 0);
        if (result > 0) {
            [data appendBytes:buffer length:result];
        } else {
            //if we didn't get any data, stop the receive loop
            waitingForData = NO;
        }
        ++i;
    }
    //close the socket
    close(socketFileDescriptor);
    [self networkSucceedWithData:data];
    
}
- (void)networkFailedWithErrorMessage:(NSString *)message {
    //Update UI
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        NSLog(@"%@",message);

//        self//??
        //???三个控件
    }];

}
- (void)networkSucceedWithData:(NSData *)data {
    //Update UI
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        NSString *resultString  = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@">>Received string :'%@'",resultString);
        //三个控件 
    }];

}
@end










