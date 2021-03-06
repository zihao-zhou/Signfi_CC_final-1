//
//  AWSContentManager.h
//
// Copyright 2017 Amazon.com, Inc. or its affiliates (Amazon). All Rights Reserved.
//
// Code generated by AWS Mobile Hub. Amazon gives unlimited permission to
// copy, distribute and modify it.
//
#import <Foundation/Foundation.h>
#import <AWSS3/AWSS3.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  The error domain for `AWSContentManager`.
 */
FOUNDATION_EXPORT NSString *const AWSContentManagerErrorDomain;

/**
 *  The error codes for `AWSContentManager`.
 */
typedef NS_ENUM(NSInteger, AWSContentManagerErrorType){
    /**
     *  Generic error.
     */
    AWSContentManagerErrorTypeUnknown,
    /**
     *  Initiated a transfer on a content that is already running.
     */
    AWSContentManagerErrorTypeTransferAlreadyInProgress,
    /**
     *  Initiated a transfer on a directory. Directories cannot be downloaded.
     */
    AWSContentManagerErrorTypeDirectoryCannotBeDownloaded,
    /**
     *  A server returned a client exception (e.g. HTTP status code 4xx).
     */
    AWSContentManagerErrorTypeClientException,
    /**
     *  A server returned a service exception (e.g. HTTP status code 5xx).
     */
    AWSContentManagerErrorTypeServiceException,
};

@class AWSContent;
@class AWSContentManagerConfiguration;

/**
 * The Content Manager manages caching and transfer of files from Amazon S3 and/or 
 * Amazon CloudFront. It lists files directly using S3, regardless of whether 
 * Amazon CloudFront is in use. It maintains a size-limited cache for files stored
 * on the local device and provides operations to set the cache size limit and
 * clear files from the local cache. It serves as the application's interface into
 * the Content Delivery feature. Content Manager instances are also used internally
 * for the User Files feature.
 * Requires the AWSS3 framework of AWSiOSSDK.
 */
@interface AWSContentManager : NSObject

/**
 * Local cache size limit in bytes.
 */
@property (nonatomic, assign) NSUInteger maxCacheSize;

/**
 * Local cache bytes used.
 */
@property (nonatomic, readonly) NSUInteger cachedUsedSize;

/**
 * Number of bytes pinned in the cache. Pinned items do not count towards the
 * cache size limit.
 */
@property (nonatomic, readonly) NSUInteger pinnedSize;

/**
 Returns the default Content Manager singleton instance configured using the information provided in `Info.plist` file.
 
 *Swift*
 
    let contentManager = AWSContentManager.default()
 
 *Objective-C*
 
    AWSContentManager *contentManager =  [AWSContentManager defaultContentManager];
 
 */
+ (instancetype)defaultContentManager;

/**
 Creates a helper client for AWSContentManager for specified configuration with mentioned key.
 Use this method only if you require a helper client with specific configuration.
 
 For example, set the configuration in `- application:didFinishLaunchingWithOptions:`
 
 *Swift*
 
     func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
         let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
         let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
         AWSServiceManager.default().defaultServiceConfiguration = configuration
         
         let contentManagerConfiguration = AWSContentManagerConfiguration(bucketName: "myBucket")
         
         AWSContentManager.register(with: contentManagerConfiguration, forKey: "defaultManager")
     }
 
 *Objective-C*
 
     - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
         AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                         identityPoolId:@"YourIdentityPoolId"];
         AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                              credentialsProvider:credentialsProvider];
         AWSServiceManager.defaultServiceManager.defaultServiceConfiguration = configuration;                                                                          
         AWSContentManagerConfiguration *contentManagerConfiguration = [[AWSContentManager alloc] initWithBucketName:@"myBucketName"];
         [AWSContentManager registerUserFileManagerWithConfiguration:contentManagerConfiguration
                                                              forKey:@"defaultManager"];     
         return YES;
     }
 
 Then call the following to get the helper client:
 
 *Swift*
 
    let contentManager = AWSContentManager(forKey: "defaultManager")
 
 *Objective-C*
 
    AWSContentManager *contentManager = [AWSContentManager contentManagerForKey:@"defaultManager"];
 
 @warning After calling this method, do not modify the configuration object. It may cause unspecified behaviors.
 
 @param  contentManagerConfiguration    AWSContentManagerConfiguration object for the manager.
 @param  key                             A string to identify the helper client.
 */
+ (void)registerContentManagerWithConfiguration:(AWSContentManagerConfiguration *)contentManagerConfiguration
                                         forKey:(NSString *)key;

/**
 Retrieves the helper client associated with the key. You need to call `+ registerContentManagerWithConfiguration:forKey:` before invoking this method. If `+ registerContentManagerWithConfiguration:forKey:` has not been called in advance or the key does not exist, this method returns `nil`.
 
 *Swift*
 
	 let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
	 let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
	 AWSServiceManager.default().defaultServiceConfiguration = configuration
	 
	 let contentManagerConfiguration = AWSContentManagerConfiguration(bucketName: "myBucket")
	 
	 AWSContentManager.register(with: contentManagerConfiguration, forKey: "defaultManager")

 *Objective-C*
 
	 AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
																									 identityPoolId:@"YourIdentityPoolId"];
	 AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
																		  credentialsProvider:credentialsProvider];
	 AWSServiceManager.defaultServiceManager.defaultServiceConfiguration = configuration;                                                                          
	 AWSContentManagerConfiguration *contentManagerConfiguration = [[AWSContentManager alloc] initWithBucketName:@"myBucketName"];
	 [AWSContentManager registerUserFileManagerWithConfiguration:userFileManagerConfiguration
														  forKey:@"defaultManager"];     
 
 Then call the following to get the helper client:
 
 *Swift*
 
    let ContentManager = AWSContentManager(forKey: "defaultManager")
 
 *Objective-C*
 
    AWSContentManager *ContentManager = [AWSContentManager ContentManagerForKey:@"defaultManager"];
 
 @param  key  A string to identify the helper client.
 @return An instance of AWSUserFileManager for specified key.
 */
+ (instancetype)ContentManagerForKey:(NSString *)key;

/**
 Removes the helper client associated with the key and release it.
 
 *Swift*
 
    AWSContentManager.remove(forKey: "defaultManager")
 
 *Objective-C*
 
    [AWSContentManager removeContentManagerForKey:@"defaultManager"];
 
 @warning Before calling this method, make sure no method is running on this client.
 
 @param key A string to identify the helper client.
 */
+ (void)removeContentManagerForKey:(NSString *)key;

/**
 Loads the list of available files in the Amazon S3 bucket under the folder specified by the prefix parameter. Results are paged with page size of 100 files. The marker parameter value returned from a call should be passed to a subsequent call, in order to page through the list of files.

 *Swift*
 
    let contentManager = AWSContentManager(forKey: "defaultManager")
    manager.listAvailableContents(withPrefix: "prefix", marker: marker, completionHandler: {(contents: [AWSContent]?, nextMarker: String?, error: Error?) -> Void in
        if let error = error {
            print("Failed to load the list of contents. \(error)")
            // handle content load failure here
        }
        if let contents = contents, contents.count > 0 {
            // Use marker and contents here
        }
        // handle successful result here
    })
 
 *Objective-C*
 
 	AWSContentManager *contentManager = [AWSContentManager contentManagerForKey:@"defaultManager"];
 	[contentManager
        listAvailableContentsWithPrefix:@"prefix"
                                 marker:marker
                      completionHandler:^(NSArray *contents, NSString *nextMarker, NSError *error) {
                        if (error) {
                            NSLog(@"Failed to load the list of contents. %@", error);
                            // handle content load failure here
                        }
                        if (contents.count > 0) {
                            // Use marker and contents here
                        }
                        // handle successful result here
                    }];
 
 @param prefix            Limits the response to keys that begin with the specified prefix.
 @param marker            The key to start with when listing objects in a bucket. It loads object metadata from the S3 bucket in alphabetical order, starting with the key after the marker in order.
 @param completionHandler The completion handler that returns the results and error.
 */
- (void)listAvailableContentsWithPrefix:(nullable NSString *)prefix
                                 marker:(nullable NSString *)marker
                      completionHandler:(void (^)(NSArray<AWSContent *> * _Nullable contents, NSString * _Nullable marker, NSError * _Nullable error))completionHandler;

/**
 Returns a list of contents that fit in the available cache. The list is sorted by last modified date on the S3 bucket, the most recently modified one first.
 
 *Swift*
 
    let contentManager = AWSContentManager(forKey: "defaultManager")
    contentManager.listRecentContents(withPrefix: "prefix", completionHandler: {(result: [AWSContent]?, error: Error?) -> Void in
        if let error = error {
            print("Failed to load the list of recent contents. \(error)")
            // Handle error here
        }
        if let downloadResult: [AWSContent] = result {
            // Handle successful result here
            for content: AWSContent in downloadResult {
                // Handle each of the item in the result
            }
        }
    })
 
 *Objective-C*
 
 	AWSContentManager *contentManager = [AWSContentManager contentManagerForKey:@"defaultManager"];
 	[contentManager listRecentContentsWithPrefix:@"prefix"
                               completionHandler:^(NSArray<AWSContent *> * result, NSError *error) {
                                           if (error) {
                                               NSLog(@"%@", error.description);
                                           }
                                           for (AWSContent *content in result) {
                                               // Handle each of the item in result
                                        	}
	                                    }];

 
 @param prefix            Limits the response to keys that begin with the specified prefix.
 @param completionHandler The completion handler that returns the result and error.
 */
- (void)listRecentContentsWithPrefix:(nullable NSString *)prefix
                   completionHandler:(void (^)(NSArray<AWSContent *> * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 *  Removes all cached contents. It does not modify the remote objects.
 */
- (void)clearCache;

/**
 Returns an instance of `AWSContent` for a given key. You can use this method to download content without first load its metadata using `- loadContentMetadataWithPrefix:marker:completionHandler:`.

 @param key The key of the content.

 @return An instance of `AWSContent`.
 */
- (AWSContent *)contentWithKey:(NSString *)key;

@end

/**
 *  Status of content item download.
 */
typedef NS_ENUM(NSInteger, AWSContentStatusType){
    /**
     *  Unknown status. This should not happen.
     */
    AWSContentStatusTypeUnknown,
    /**
     *  Has been created but has not started running yet.
     */
    AWSContentStatusTypeNotStarted,
    /**
     *  Is running and transferring data from/to the remote server.
     */
    AWSContentStatusTypeRunning,
    /**
     *  Has completed transferring data from/to the remote server.
     */
    AWSContentStatusTypeCompleted,
    /**
     *  Has failed to transfer data from/to the remote server.
     */
    AWSContentStatusTypeFailed,
};

/**
 *  Policy to use when downloading a file.
 */
typedef NS_ENUM(NSInteger, AWSContentDownloadType){
    /**
     *  Downalods a file if not cached locally.
     */
    AWSContentDownloadTypeIfNotCached,
    /**
     *  Downloads a file if not cached locally or the remote version is newer than the locally cached version.
     */
    AWSContentDownloadTypeIfNewerExists,
    /**
     *  Downloads a file and overwrite it if the local cache exists.
     */
    AWSContentDownloadTypeAlways,
};

/**
 *  The content object that holds the cached data and its metadata.
 */
@interface AWSContent : NSObject

/**
 *  The Amazon S3 key associated with the content.
 */
@property (nonatomic, readonly) NSString *key;

/**
 *  Shows if the content is a directory.
 */
@property (nonatomic, readonly, getter=isDirectory) BOOL directory;

/**
 *  The status of the content.
 */
@property (nonatomic, readonly) AWSContentStatusType status;

/**
 *  The transfer progress.
 */
@property (nonatomic, readonly) NSProgress *progress;

/**
 *  The last known size reported by the Amazon S3. May be different from the actual size if the file was modified on the server.
 */
@property (nonatomic, readonly) NSUInteger knownRemoteByteCount;

/**
 *  The last known last modified date reported by the Amazon S3. May be different from the actual last modified date if the file was modified on the server.
 */
@property (nonatomic, readonly) NSDate * _Nullable knownRemoteLastModifiedDate;

/**
 *  The cached data object.
 */
@property (nonatomic, readonly) NSData *cachedData;

/**
 *  The cached data size.
 */
@property (nonatomic, readonly) NSUInteger fileSize;

/**
 *  The date the cached data was downloaded.
 */
@property (nonatomic, readonly) NSDate * _Nullable downloadedDate;

/**
 *  Wheather the content is locally cached.
 */
@property (nonatomic, readonly, getter=isCached) BOOL cached;

/**
 *  Weather the content is pinned. Pinned objects are not subject to the content cache limit.
 */
@property (nonatomic, readonly, getter=isPinned) BOOL pinned;

/**
 Downloads a file from the remote server.
 
 *Swift*
 
 	func downloadContent(content: AWSContent, pinOnCompletion: Bool) {
         content.download(with: .ifNewerExists, pinOnCompletion: pinOnCompletion, progressBlock: { (content: AWSContent, content: Progress) in
                 // Handle progress feedback
             }, completionHandler: { (content: AWSContent?, data: Data?, error: Error?) in
                 if let error = error {
                     print("Failed to download a content from a server.)")
                     // Handle error here
                     return
                 }
                 // Handle successful download here
             })
    }
 
 *Objective-C*
 
 	- (void)downloadContent:(AWSContent *)content
        	pinOnCompletion:(BOOL)pinOnCompletion {
    	[content downloadWithDownloadType:AWSContentDownloadTypeIfNewerExists
                      	  pinOnCompletion:pinOnCompletion
                        	progressBlock:^(AWSContent *content, NSProgress *progress) {
                            // Handle progress feedback
                        }
                    completionHandler:^(AWSContent *content, NSData *data, NSError *error) {
                        if (error) {
                            NSLog(@"Failed to download a content from a server. %@", error);
                            // Handle error here
                            return;
                        }
						// Handle successful download here
                    }];
		}
 
 @param loadingType       Specifies the loading behavior for downloading data.
 @param pinOnCompletion   When set to `YES`, it pins the content on completion. You can download a content that does not fit in the content cache by setting it to `YES`.
 @param progressBlock     The progress feedback block.
 @param completionHandler The completion handler block.
 */
- (void)downloadWithDownloadType:(AWSContentDownloadType)loadingType
                 pinOnCompletion:(BOOL)pinOnCompletion
                   progressBlock:(void(^ _Nullable)(AWSContent *content, NSProgress *progress))progressBlock
               completionHandler:(void(^)(AWSContent * _Nullable content, NSData * _Nullable data, NSError * _Nullable error))completionHandler;

/**
 Gets Presigned URL or the Cloud Front URL for the file.
 
 *Swift*
 
 	func getContentURL(content: AWSContent) {
        content.getRemoteFileURLWithCompletionHandler({ (url: URL?, error: Error?) -> Void in
            guard let url = url else {
                NSLog("Error getting URL for file. \(error)")
                return
            }
            // Handle successfully generated URL here
        })
    }
 
 *Objective-C*
 
 	- (void)getContentURL:(AWSContent *)content {
    	[content getRemoteFileURLWithCompletionHandler:^(NSURL *url, NSError *error) {
        	if (error) {
            	NSLog(@"Failed to get a valid URL from a server. %@", error);
        	}
            // handle successfully generated URL here
    	}];
	}
 
 @param completionHandler The completion handler block.
 */
- (void)getRemoteFileURLWithCompletionHandler:(void(^)(NSURL  * _Nullable url, NSError  * _Nullable error))completionHandler;

/**
 *  Pins the locally cached object. Pinned objects are not subject to the content cache limit.
 */
- (void)pin;

/**
 *  Unpins the pinned object. It may purge the content cache if the content cache does not have enough available space to fit the unpinned data.
 */
- (void)unPin;

/**
 *  Removes locally cached data regardless of the pinning status.
 */
- (void)removeLocal;

@end

/**
 *  `AWSContentManagerConfiguration` is the configuration object for `AWSContentManager` class.
 */
@interface AWSContentManagerConfiguration: NSObject

@property (nonatomic, readonly) AWSServiceConfiguration *serviceConfiguration;
@property (nonatomic, readonly) NSString *bucketName;
@property (nonatomic, readonly, nullable) NSString *cloudFrontURL;


/**
 Returns an instance of `AWSContentManagerConfiguration` using the default service configuration and specified bucket name. Use this as the configuration object for AWSContentManager.

 *Swift*
 
     let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
     let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
     AWSServiceManager.default().defaultServiceConfiguration = configuration
     
     let contentManagerConfiguration = AWSContentManagerConfiguration(bucketName: "myBucket")
     
     AWSContentManager.register(with: contentManagerConfiguration, forKey: "defaultManager")
 
 *Objective-C*
 
     AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                     identityPoolId:@"YourIdentityPoolId"];
     AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                          credentialsProvider:credentialsProvider];
	 AWSServiceManager.defaultServiceManager.defaultServiceConfiguration = configuration;                                                                          
     AWSContentManagerConfiguration *contentManagerConfiguration = [[AWSContentManager alloc] initWithBucketName:@"myBucketName"];
     [AWSContentManager registerUserFileManagerWithConfiguration:userFileManagerConfiguration
                                                          forKey:@"defaultManager"];
 

 @param  bucketName              Name of the bucket for manager
 @return an instance of AWSUserFileManagerConfiguration
 */
- (instancetype)initWithBucketName:(NSString *)bucketName;

/**
 Returns an instance of`AWSContentManagerConfiguration` using the specified bucket name, CloudFront URL and the default service configuration. Use this as the configuration object for AWSContentManager.

 *Swift*
 
     let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
     let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
     AWSServiceManager.default().defaultServiceConfiguration = configuration;
     
     let contentManagerConfiguration = AWSContentManagerConfiguration(bucketName: "myBucket", cloudFrontURL: "https:/a.b.myurl")
     
     AWSContentManager.register(with: contentManagerConfiguration, forKey: "defaultManager")
 
 *Objective-C*
 
     AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                     identityPoolId:@"YourIdentityPoolId"];
     AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                          credentialsProvider:credentialsProvider];
	 AWSServiceManager.defaultServiceManager.defaultServiceConfiguration = configuration;                                                                          
     AWSContentManagerConfiguration *contentManagerConfiguration = [[AWSContentManager alloc] initWithBucketName:@"myBucketName"
     																							   cloudFrontURL:@"https:/a.b.myurl"];
     [AWSContentManager registerUserFileManagerWithConfiguration:userFileManagerConfiguration
                                                          forKey:@"defaultManager"];
 

 @param  bucketName              Name of the bucket for manager
 @param  cloudFrontURL           CloudFront URL for the bucket if enabled; nil otherwise
 @return an instance of AWSUserFileManagerConfiguration
 */
- (instancetype)initWithBucketName:(NSString *)bucketName
                     cloudFrontURL:(nullable NSString *)cloudFrontURL;


/**
 Returns an instance of `AWSContentManagerConfiguration` using the specified bucket name, CloudFront URL and service configuration. Use this as the configuration object for AWSContentManager.

 *Swift*
 
     let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
     let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
     
     let contentManagerConfiguration = AWSContentManagerConfiguration(bucketName: "myBucket", cloudFrontURL: "https:/a.b.myurl", serviceConfiguration: configuration)
     
     AWSContentManager.register(with: contentManagerConfiguration, forKey: "USWest2BucketContentManager")
 
 *Objective-C*
 
     AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                     identityPoolId:@"YourIdentityPoolId"];
     AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                          credentialsProvider:credentialsProvider];
     AWSContentManagerConfiguration *contentManagerConfiguration = [[AWSContentManager alloc] initWithBucketName:@"myBucketName"
     																							   cloudFrontURL:@"https:/a.b.myurl"
     																						serviceConfiguration:configuration];
     [AWSContentManager registerUserFileManagerWithConfiguration:userFileManagerConfiguration
                                                           forKey:@"USWest2BucketContentManager"];
 

 @param  bucketName              Name of the bucket for manager
 @param  cloudFrontURL           CloudFront URL for the bucket if enabled; nil otherwise
 @param  serviceConfiguration    AWSServiceConfiguration for the bucket; nil for default configuration
 @return an instance of AWSUserFileManagerConfiguration
 */
- (instancetype)initWithBucketName:(NSString *)bucketName
                     cloudFrontURL:(nullable NSString *)cloudFrontURL
              serviceConfiguration:(nullable AWSServiceConfiguration *)serviceConfiguration;

@end

NS_ASSUME_NONNULL_END
