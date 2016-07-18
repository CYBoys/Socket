//
//  LYsocket.h
//  socket客户端OC版本
//
//  Created by chairman on 15/10/25.
//  Copyright © 2015年 LaiYong. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

@interface LYsocket : NSObject
- (void)loadDataFromServerWithURL:(NSURL *)url;
- (void)networkFailedWithErrorMessage:(NSString *)message;
- (void)networkSucceedWithData:(NSData *)data;
@end
