//
//  Annotation.h
//  CoreGraphics
//
//  Created by xindong on 2017/9/22.
//  Copyright © 2017年 xindong. All rights reserved.
//

******************************* <CoreGraphics>: CGImageRef **************************************

## 1. CGImageCreate()
 /**
  通过参数`CGDataProviderRef`来创建一个位图。
 
  @param width             所需图像的宽度，以像素为单位。
  @param height            所需图像的高度，以像素为单位。
  @param bitsPerComponent  源像素中每个组件的位数，例如：RGB共24位，则每个8位。
  @param bitsPerPixel      一个源像素中的总位数。
  @param bytesPerRow       内存中位图每一个行的字节数。
  @param space             图片的颜色空间。被`reatain`了，注意`release`。
 
  @param bitmapInfo        位图信息常量，它指定位图是否应该包含一个alpha通道，和它在一个像素中的相对位置，以及这些组件是浮点数还是整数值。
 
  @param provider          位图的源数据，被`retain`了，注意`release`。
  @param decode            图片的解码数组，如果不想对图像的颜色值进行重新映射，传NULL。对于图像的颜色空间中的每个颜色组件(包括alpha组件)，一个解码数组提供一对值，表示范围的上下限。例如，RGB颜色空间中的源图像的解码数组将包含6个条目，每个条目由一对红色、绿色和蓝色组成。当图像呈现时，<CoreGraphics>使用一个线性转换将原始组件值映射到指定范围内的相对数字，适合目标颜色空间。
 
  @param shouldInterpolate 该值指定是否应该发生插值。插值设置指定<CoreGraphics>是否应该对图像应用像素平滑算法。在没有插值的情况下，在分辨率高于图像数据的输出设备上，图像可能会出现锯齿或像素化。
 
 @param intent             指定了<CoreGraphics>应该如何处理位于图形上下文的目标颜色空间范围内的颜色。渲染目的确定用于将颜色从一个颜色空间映射到另一个颜色空间的精确方法。
     `kCGRenderingIntentDefault`              -> 默认.
     `kCGRenderingIntentAbsoluteColorimetric` —> 绝对色阶匹配.
     `kCGRenderingIntentSaturation`           -> 色彩饱和度.
     `kCGRenderingIntentRelativeColorimetric` -> 相对色阶匹配.
     `kCGRenderingIntentPerceptual`           -> 通过压缩色域, 来保证不同设备输出在视觉上
                                                 保持一致.

  @return 一个新的位图，注意要调用`CGImageRelease()`.
  */
 CGImageRef CGImageCreate(size_t width,
                          size_t height,
                          size_t bitsPerComponent,
                          size_t bitsPerPixel,
                          size_t bytesPerRow,
                          CGColorSpaceRef space,
                          CGBitmapInfo bitmapInfo,
                          CGDataProviderRef provider,
                          const CGFloat *decode,
                          bool shouldInterpolate,
                          CGColorRenderingIntent intent);


## 2. CGImageCreateCopy()
/**
 创建一个位图的副本.
 
 @param image 源位图.
 @return 位图副本.
 */
CGImageRef CGImageCreateCopy(CGImageRef image);


## 3. CGImageCreateCopyWithColorSpace()
/**
 创建一个位图的副本，并替换它的颜色空间.

 @param image 源位图
 @param space 目标颜色空间, 此颜色空间中的组件数必须与指定图像中的相同.
 @return 位图副本. 如果颜色空间组件数不同, 则会返回`NULL`.
 */
CGImageRef CGImageCreateCopyWithColorSpace(CGImageRef image, CGColorSpaceRef space);


## 4. CGImageCreateWithJPEGDataProvider()
/**
 使用JPEG编码的数据创建位图, 参数意思和上述函数1相同.
 */
CGImageRef CGImageCreateWithJPEGDataProvider(CGDataProviderRef source,
                                             const CGFloat *decode, //通常传`NULL`
                                             bool shouldInterpolate,
                                             CGColorRenderingIntent intent);

## 5. CGImageCreateWithPNGDataProvider()
/**
 使用PNG编码的数据创建位图, 参数意思和上述函数1相同.
 */
CGImageRef CGImageCreateWithPNGDataProvider(CGDataProviderRef source,
                                            const CGFloat *decode, //通常传`NULL`
                                            bool shouldInterpolate,
                                            CGColorRenderingIntent intent);


## 6. CGImageCreateWithImageInRect()
/**
 使用现有位图的子区域内的数据创建位图.

 @param image 现有的位图
 @param rect  需要创建位图的矩形坐标区域
 @return 新位图. 如果参数`rect`不在现有位图区域内, 则会返回`NULL`.
 
 @Note 新生成的位图保留对源位图的引用, 这意味着在调用此函数后, 可以释放源位图.
 */
CGImageRef CGImageCreateWithImageInRect(CGImageRef image, CGRect rect);


## 7. CGImageCreateWithMask()
/**
 从现有的图片和图片遮罩创建位图.

 @param image 将遮罩参数应用于此图片, 该图片不能是遮罩并且也不能包含遮罩信息.
 @param mask  如果遮罩是一个图片, 则必须在DeviceGray颜色空间中且不能包含透明通道, 也不能被遮罩
              或遮罩颜色遮挡, 如果尺寸和`image`不同, 将会按比例缩放来匹配`image`.
 @return 需要调用`CGImageRelease`.
 */
CGImageRef CGImageCreateWithMask(CGImageRef image, CGImageRef mask);


## 8. CGImageCreateWithMaskingColors()
/**
 通过提供的颜色值遮罩现有的图片来创建位图.

 @param image      将遮罩参数应用于此图片, 该图片不能是遮罩并且也不能包含遮罩信息, 并且不能包含
                   透明通道.
 @param components 颜色组件数组.
 @return 需要调用`CGImageRelease`.
 */
CGImageRef CGImageCreateWithMaskingColors(CGImageRef image, const CGFloat *components);


## 9. CGImageMaskCreate()
/**
 通过参数`CGDataProviderRef`提供的数据来创建一个位图遮罩.
 
 参数与上述函数1类似.
 @return 需要调用`CGImageRelease`.
 @Note 图片遮罩的颜色组件必须是1、2、4或者8位.
 */
CGImageRef CGImageMaskCreate(size_t width,
                             size_t height,
                             size_t bitsPerComponent,
                             size_t bitsPerPixel,
                             size_t bytesPerRow,
                             CGDataProviderRef provider,
                             const CGFloat *decode,
                             bool shouldInterpolate);


## 10. CGImageGetTypeID()
/**
 返回`CGImage`对象的类型标识符.
 */
CFTypeID CGImageGetTypeID(void);


## 11. CGImageGetAlphaInfo()
/**
 返回一个位图的透明通道信息.

 @param image 位图
 @return 透明通道信息:
     kCGImageAlphaFirst              -> alpha组件存储在每个像素最重要的部分.
     kCGImageAlphaLast               -> alpha组件存储在每个像素中最不重要的部分.
     kCGImageAlphaNone               -> 没有透明通道.
     kCGImageAlphaNoneSkipFirst      -> 有alpha分量，但是忽略该值，相当于没有透明通道. 如果像素的总尺寸大于色空间中颜色组件数量所要求的空间, 那么最高有效位就被忽略了.
     kCGImageAlphaOnly               -> 没有颜色数据, 只有透明通道.
     kCGImageAlphaNoneSkipLast       -> 有alpha分量，但是忽略该值，相当于没有透明通道.
     kCGImageAlphaPremultipliedFirst —> alpha组件存储在每个像素的最高有效位, 并且各颜色组件已经和alpha值进行相乘.
     kCGImageAlphaPremultipliedLast  -> alpha组件存储在每个像素的最低有效位, 并且各颜色组件已经和alpha值进行相乘.
 */
CGImageAlphaInfo CGImageGetAlphaInfo(CGImageRef image);

## 12. CGImageGetBitmapInfo()
/**
 获取一张位图的位图信息.

 @param image 位图
 @return 位图的组件信息.
 
 @Note 使用ARGB格式存储像素数据的App必须注意它们读取数据的方式。如果代码写得不正确，就有可能导致颜色或alpha出现错误的数据。字节顺序常数指定像素格式的字节顺序。请使用位或运算符将适当的常量与bitmapInfo参数组合在一起来指定字节顺序.
 */
CGBitmapInfo CGImageGetBitmapInfo(CGImageRef image);



******************************* <CoreGraphics>: CGDataProviderRef *************************************
/*数据提供者, 用来读取数据, 并消除了管理原始内存缓冲区的需要.*/

## 1. CGDataProviderCreate()

/**
 创建一个顺序访问的数据提供者.

 @param info      任意数据类型的指针或者为NULL, 当caller指定`callBack`参数时，会将该参数回调给caller。
 @param callbacks 一个结构体指针的回调，在回调实现中读取数据流。
 @return 需要调用`CGDataProviderRelease`.
 */
CGDataProviderRef CGDataProviderCreate(void *info, const CGDataProviderCallbacks *callbacks);

/// @param callbacks
struct CGDataProviderCallbacks {
    CGDataProviderGetBytesCallback getBytes;           // 函数指针，用来从provider中拷贝数据。
    CGDataProviderSkipBytesCallback skipBytes;         // 函数指针，提取provider提供的数据流。
    CGDataProviderRewindCallback rewind;               // 函数指针，倒回到数据流的起点。
    CGDataProviderReleaseInfoCallback releaseProvider; // 函数指针，释放provider。
};
typedef struct CGDataProviderCallbacks CGDataProviderCallbacks;



## 2. CGDataProviderCreateDirectAccess()
/**
 创建一个直接访问的provider.
 
 @param info      可以为NULL
 @param size      provider包含的字节数
 @param callbacks 回调
 @return 需要调用`CGDataProviderRelease`.
 */
CGDataProviderRef CGDataProviderCreateDirectAccess (void *info, size_t size, const CGDataProviderDirectAccessCallbacks *callbacks);

/// @param callbacks
struct CGDataProviderDirectAccessCallbacks {
    CGDataProviderGetBytePointerCallback getBytePointer; // 不能为NULL
    CGDataProviderReleaseBytePointerCallback releaseBytePointer;
    CGDataProviderGetBytesAtOffsetCallback getBytes;     // 不能为NULL
    CGDataProviderReleaseInfoCallback releaseProvider;
};
typedef struct CGDataProviderDirectAccessCallbacks  CGDataProviderDirectAccessCallbacks;


## 3. CGDataProviderCreateWithData()
/**
 通过提供的数据来创建provider。

 @param info        可以为NULL
 @param data        数据数组的指针
 @param size        provider包含的字节数
 @param releaseData 用来释放data
 @return provider
 */
CGDataProviderRef CGDataProviderCreateWithData(void *info, const void *data, size_t size, CGDataProviderReleaseDataCallback releaseData);




