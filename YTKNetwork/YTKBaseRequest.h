//
//  FenbiBaseRequest.h
//  Solar
//
//  Created by tangqiao on 8/4/14.
//  Copyright (c) 2014 fenbi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFNetworking.h"
#import "AFDownloadRequestOperation.h"

typedef NS_ENUM(NSInteger , YTKRequestMethod) {
    YTKRequestMethodGet = 0,
    YTKRequestMethodPost,
    YTKRequestMethodHead,
    YTKRequestMethodPut,
    YTKRequestMethodDelete,
};

typedef NS_ENUM(NSInteger , YTKRequestSerializerType) {
    YTKRequestSerializerTypeHTTP = 0,
    YTKRequestSerializerTypeJSON,
};

typedef void (^AFConstructingBlock)(id<AFMultipartFormData> formData);
typedef void (^AFDownloadProgressBlock)(AFDownloadRequestOperation *operation, NSInteger bytesRead, long long totalBytesRead, long long totalBytesExpected, long long totalBytesReadForFile, long long totalBytesExpectedToReadForFile);

@class YTKBaseRequest;

@protocol YTKRequestDelegate <NSObject>

- (void)requestFinished:(YTKBaseRequest *)request;
- (void)requestFailed:(YTKBaseRequest *)request;

@optional
- (void)clearRequest;

@end

@interface YTKBaseRequest : NSObject

/// Tag
@property (nonatomic) NSInteger tag;

/// User info
@property (nonatomic, strong) NSDictionary *userInfo;

/// the animating text
@property (nonatomic, strong) NSString *animatingText;

@property (nonatomic, strong) AFHTTPRequestOperation *requestOperation;

/// request delegate object
@property (nonatomic, weak) id<YTKRequestDelegate> delegate;

/// the animating view
@property (nonatomic, weak) UIView *animatingView;

@property (nonatomic, strong, readonly) NSDictionary *responseHeaders;

@property (nonatomic, strong, readonly) NSString *responseString;

@property (nonatomic, strong, readonly) id responseJSONObject;

@property (nonatomic, readonly) NSInteger responseStatusCode;

@property (nonatomic, copy) void (^successCompletionBlock)(YTKBaseRequest *);

@property (nonatomic, copy) void (^failureCompletionBlock)(YTKBaseRequest *);

/// append self to request queue
- (void)start;

/// remove self from request queue
- (void)stop;

- (BOOL)isExecuting;

// block回调
- (void)startWithCompletionBlockWithSuccess:(void (^)(YTKBaseRequest *request))success
                                    failure:(void (^)(YTKBaseRequest *request))failure;

- (void)setCompletionBlockWithSuccess:(void (^)(YTKBaseRequest *request))success
                              failure:(void (^)(YTKBaseRequest *request))failure;

// 把block置nil来打破循环引用
- (void)clearCompletionBlock;

/// 以下方法由子类继承来覆盖默认值

// 请求成功的回调
- (void)requestCompleteFilter;

// 请求失败的回调
- (void)requestFailedFilter;

// 请求的URL
- (NSString *)requestUrl;

// 请求的CdnURL
- (NSString *)cdnUrl;

// 请求的BaseURL
- (NSString *)baseUrl;

// 请求的参数列表
- (id)requestArgument;

// 用于在cache结果，计算cache文件名时，忽略掉一些指定的参数
- (id)cacheFileNameFilterForRequestArgument:(id)argument;

// Http请求的方法
- (YTKRequestMethod)requestMethod;

// 请求的SerializerType
- (YTKRequestSerializerType)requestSerializerType;

// 请求的Server用户名和密码
- (NSArray *)requestAuthorizationHeaderFieldArray;

// 构建自定义的UrlRequest，
// 若这个方法返回非nil对象，会忽略requestUrl, requestArgument, requestMethod, requestSerializerType
- (NSURLRequest *)buildCustomUrlRequest;

// 是否使用CDN的host地址
- (BOOL)useCDN;

// 用于检查JSON是否合法的对象
- (id)jsonValidator;

// 用于检查Status Code是否正常的方法
- (BOOL)statusCodeValidator;

// 当POST的内容带有文件等富文本时使用
- (AFConstructingBlock)constructingBodyBlock;

// 当需要断点续传时，指定续传的地址
- (NSString *)resumableDownloadPath;

// 当需要断点续传时，获得下载进度的回调
- (AFDownloadProgressBlock)resumableDownloadProgressBlock;

@end