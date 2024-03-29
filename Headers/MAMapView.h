//
//  MAMapView.h
//  MAMapKitDemo
//
//  Created by songjian on 12-12-21.
//  Copyright (c) 2012年 songjian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MATypes.h"
#import "MAOverlay.h"
#import "MAOverlayView.h"
#import "MAAnnotationView.h"
#import "MAAnnotation.h"

enum {
	MAUserTrackingModeNone = 0, // the user's location is not followed
	MAUserTrackingModeFollow, // the map follows the user's location
	MAUserTrackingModeFollowWithHeading, // the map follows the user's location and heading
};

typedef NSInteger MAUserTrackingMode;

@class MAUserLocation;

@protocol MAMapViewDelegate;

/*!
 @brief 地图view
 */
@interface MAMapView : UIView

/*!
 @brief 代理
 */
@property (nonatomic, assign) id <MAMapViewDelegate> delegate;

/*!
 @brief 地图类型
 */
@property (nonatomic) MAMapType mapType;

/*!
 @brief logo位置, 必须在mapView.bounds之内，否则会被忽略
 */
@property (nonatomic) CGPoint logoCenter;

/*!
 @brief logo的宽高
 */
@property (nonatomic, readonly) CGSize logoSize;

/*!
 @brief 是否显示交通
 */
@property (nonatomic, getter = isShowTraffic) BOOL showTraffic;

/*!
 @brief 是否支持缩放
 */
@property (nonatomic, getter = isZoomEnabled) BOOL zoomEnabled;

/*!
 @brief 是否支持平移
 */
@property (nonatomic, getter = isScrollEnabled) BOOL scrollEnabled;

/*!
 @brief 是否支持旋转
 */
@property (nonatomic, getter = isRotateEnabled) BOOL rotateEnabled;

/*!
 @brief 设置地图旋转角度(逆时针为正向)
 */
@property (nonatomic) CGFloat rotationDegree;

/*!
 @brief 设置地图旋转角度(逆时针为正向)
 @param animated 动画
 @param duration 动画时间
 */
- (void)setRotationDegree:(CGFloat)rotationDegree animated:(BOOL)animated duration:(CFTimeInterval)duration;

/*!
 @brief 设置地图相机角度(范围为[0.f, 45.f])
 */
@property (nonatomic) CGFloat cameraDegree;

- (void)setCameraDegree:(CGFloat)cameraDegree animated:(BOOL)animated duration:(CFTimeInterval)duration;

/*!
 @brief 是否支持camera旋转
 */
@property (nonatomic, getter = isRotateCameraEnabled) BOOL rotateCameraEnabled;

/*!
 @brief 当前地图的经纬度范围，设定的该范围可能会被调整为适合地图窗口显示的范围
 */
@property (nonatomic) MACoordinateRegion region;
- (void)setRegion:(MACoordinateRegion)region animated:(BOOL)animated;

/*!
 @brief 当前地图的中心点，改变该值时，地图的比例尺级别不会发生变化
 */
@property (nonatomic) CLLocationCoordinate2D centerCoordinate;
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;

/*!
 @brief 根据当前地图视图frame的大小调整region范围
 @param region 要调整的经纬度范围
 @return 调整后的经纬度范围
 */
- (MACoordinateRegion)regionThatFits:(MACoordinateRegion)region;

/*!
 @brief 可见区域
 */
@property (nonatomic) MAMapRect visibleMapRect;
- (void)setVisibleMapRect:(MAMapRect)mapRect animated:(BOOL)animate;

/*!
 @brief 调整投影矩形比例
 @param mapRect 要调整的投影矩形
 @return 调整后的投影矩形
 */
- (MAMapRect)mapRectThatFits:(MAMapRect)mapRect;

/*!
 @brief 根据当前地图视图frame的大小调整投影范围
 @param mapRect 要调整的投影范围
 @return 调整后的投影范围
 */
- (void)setVisibleMapRect:(MAMapRect)mapRect edgePadding:(UIEdgeInsets)insets animated:(BOOL)animate;

/*!
 @brief 根据嵌入数据来调整投影矩形比例
 @param mapRect 要调整的投影矩形
 @param insets 嵌入数据
 @return 调整后的投影矩形
 */
- (MAMapRect)mapRectThatFits:(MAMapRect)mapRect edgePadding:(UIEdgeInsets)insets;

/*!
 @brief 将经纬度转换为指定view坐标系的坐标
 @param coordinate 经纬度
 @param view 指定的view
 @return 基于指定view坐标系的坐标
 */
- (CGPoint)convertCoordinate:(CLLocationCoordinate2D)coordinate toPointToView:(UIView *)view;

/*!
 @brief 将指定view坐标系的坐标转换为经纬度
 @param point 指定view坐标系的坐标
 @param view 指定的view
 @return 经纬度
 */
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(UIView *)view;

/*!
 @brief 将经纬度region转换为指定view坐标系的rect
 @param region 经纬度region
 @param view 指定的view
 @return 指定view坐标系的rect
 */
- (CGRect)convertRegion:(MACoordinateRegion)region toRectToView:(UIView *)view;

/*!
 @brief 将指定view坐标系的rect转换为经纬度region
 @param rect 指定view坐标系的rect
 @param view 指定的view
 @return 经纬度region
 */
- (MACoordinateRegion)convertRect:(CGRect)rect toRegionFromView:(UIView *)view;

/*!
 @brief 是否显示用户位置
 */
@property (nonatomic) BOOL showsUserLocation;

/*!
 @brief 当前的位置数据
 */
@property (nonatomic, readonly) MAUserLocation *userLocation;

/*!
 @brief 定位用户位置的模式
 */
@property (nonatomic) MAUserTrackingMode userTrackingMode;
- (void)setUserTrackingMode:(MAUserTrackingMode)mode animated:(BOOL)animated;

/*!
 @brief 当前位置再地图中是否可见
 */
@property (nonatomic, readonly, getter=isUserLocationVisible) BOOL userLocationVisible;

/*!
 @brief 向地图窗口添加标注，需要实现MAMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 @param annotation 要添加的标注
 */
- (void)addAnnotation:(id <MAAnnotation>)annotation;

/*!
 @brief 向地图窗口添加一组标注，需要实现MAMapViewDelegate的-mapView:viewForAnnotation:函数来生成标注对应的View
 @param annotations 要添加的标注数组
 */
- (void)addAnnotations:(NSArray *)annotations;

/*!
 @brief 移除标注
 @param annotation 要移除的标注
 */
- (void)removeAnnotation:(id <MAAnnotation>)annotation;

/*!
 @brief 移除一组标注
 @param annotation 要移除的标注数组
 */
- (void)removeAnnotations:(NSArray *)annotations;

/*!
 @brief 标注数组
 */
@property (nonatomic, readonly) NSArray *annotations;

/*!
 @brief 获取指定投影矩形范围内的标注
 @param mapRect 投影矩形范围
 @return 标注集合
 */
- (NSSet *)annotationsInMapRect:(MAMapRect)mapRect;

/*!
 @brief 根据标注数据过去标注view
 @param annotation 标注数据
 @return 对应的标注view
 */
- (MAAnnotationView *)viewForAnnotation:(id <MAAnnotation>)annotation;

/*!
 @brief 从复用内存池中获取制定复用标识的annotation view
 @param identifier 复用标识
 @return annotation view
 */
- (MAAnnotationView *)dequeueReusableAnnotationViewWithIdentifier:(NSString *)identifier;

/*!
 @brief 选中标注数据对应的view
 @param annotation 标注数据
 @param animated 是否有动画效果
 */
- (void)selectAnnotation:(id <MAAnnotation>)annotation animated:(BOOL)animated;

/*!
 @brief 取消选中标注数据对应的view
 @param annotation 标注数据
 @param animated 是否有动画效果
 */
- (void)deselectAnnotation:(id <MAAnnotation>)annotation animated:(BOOL)animated;

/*!
 @brief 处于选中状态的标注数据数据(其count == 0 或 1)
 */
@property (nonatomic, copy) NSArray *selectedAnnotations;

/*!
 @brief annotation 可见区域
 */
@property (nonatomic, readonly) CGRect annotationVisibleRect;

@end

/*!
 @brief 地图view关于overlay类别
 */
@interface MAMapView (OverlaysAPI)

/*!
 @brief 向地图窗口添加Overlay，需要实现MAMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 @param overlay 要添加的overlay
 */
- (void)addOverlay:(id <MAOverlay>)overlay;

/*!
 @brief 向地图窗口添加一组Overlay，需要实现BMKMapViewDelegate的-mapView:viewForOverlay:函数来生成标注对应的View
 @param overlays 要添加的overlay数组
 */
- (void)addOverlays:(NSArray *)overlays;

/*!
 @brief 移除Overlay
 @param overlay 要移除的overlay
 */
- (void)removeOverlay:(id <MAOverlay>)overlay;

/*!
 @brief 移除一组Overlay
 @param overlays 要移除的overlay数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/*!
 @brief 在指定的索引处添加一个Overlay
 @param overlay 要添加的overlay
 @param index 指定的索引
 */
- (void)insertOverlay:(id <MAOverlay>)overlay atIndex:(NSUInteger)index;

/*!
 @brief 在交换指定索引处的Overlay
 @param index1 索引1
 @param index2 索引2
 */
- (void)exchangeOverlayAtIndex:(NSUInteger)index1 withOverlayAtIndex:(NSUInteger)index2;

/*!
 @brief 在指定的Overlay之上插入一个overlay
 @param overlay 带添加的Overlay
 @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <MAOverlay>)overlay aboveOverlay:(id <MAOverlay>)sibling;

/*!
 @brief 在指定的Overlay之下插入一个overlay
 @param overlay 带添加的Overlay
 @param sibling 用于指定相对位置的Overlay
 */
- (void)insertOverlay:(id <MAOverlay>)overlay belowOverlay:(id <MAOverlay>)sibling;

/*!
 @brief Overlay数组
 */
@property (nonatomic, readonly) NSArray *overlays;

/*!
 @brief 查找指定overlay对应的View，如果该View尚未创建，返回nil
 @param overlay 指定的overlay
 @return 指定overlay对应的View
 */
- (MAOverlayView *)viewForOverlay:(id <MAOverlay>)overlay;

@end

/*!
 @brief 地图view关于截图的类别
 */
@interface MAMapView (Snapshot)

/*!
 @brief 在指定区域内截图(默认会包含该区域内的annotationView)
 @param rect 指定的区域
 @return 截图image
 */
- (UIImage *)takeSnapshotInRect:(CGRect)rect;

@end

/*!
 @brief 地图view关于离线下载的类别
 */
@interface MAMapView (Offline)

/*!
 @brief 将离线地图解压到 Documents/3dvmap/ 目录下后，调用此函数使离线数据生效,
 对应的回调分别是 offlineDataWillReload:(MAMapView *)mapView, offlineDataDidReload:(MAMapView *)mapView.
 */
- (void)reloadMap;

@end

/*!
 @brief 地图view的delegate
 */
@protocol MAMapViewDelegate <NSObject>
@optional

/*!
 @brief 地图区域即将改变时会调用此接口
 @param mapview 地图View
 @param animated 是否动画
 */
- (void)mapView:(MAMapView *)mapView regionWillChangeAnimated:(BOOL)animated;

/*!
 @brief 地图区域改变完成后会调用此接口
 @param mapview 地图View
 @param animated 是否动画
 */
- (void)mapView:(MAMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

/*!
 @brief 地图开始加载
 @param mapview 地图View
 */
- (void)mapViewWillStartLoadingMap:(MAMapView *)mapView;

/*!
 @brief 地图加载成功
 @param mapView 地图View
 @param dataSize 数据大小
 */
- (void)mapViewDidFinishLoadingMap:(MAMapView *)mapView dataSize:(NSInteger)dataSize;

/*!
 @brief 地图加载失败
 @param mapView 地图View
 @param error 错误信息
 */
- (void)mapViewDidFailLoadingMap:(MAMapView *)mapView withError:(NSError *)error;

/*!
 @brief 根据anntation生成对应的View
 @param mapView 地图View
 @param annotation 指定的标注
 @return 生成的标注View
 */
- (MAAnnotationView *)mapView:(MAMapView *)mapView viewForAnnotation:(id <MAAnnotation>)annotation;

/*!
 @brief 当mapView新添加annotation views时，调用此接口
 @param mapView 地图View
 @param views 新添加的annotation views
 */
- (void)mapView:(MAMapView *)mapView didAddAnnotationViews:(NSArray *)views;

/*!
 @brief 当选中一个annotation views时，调用此接口
 @param mapView 地图View
 @param views 选中的annotation views
 */
- (void)mapView:(MAMapView *)mapView didSelectAnnotationView:(MAAnnotationView *)view;

/*!
 @brief 当取消选中一个annotation views时，调用此接口
 @param mapView 地图View
 @param views 取消选中的annotation views
 */
- (void)mapView:(MAMapView *)mapView didDeselectAnnotationView:(MAAnnotationView *)view;

/*!
 @brief 在地图View将要启动定位时，会调用此函数
 @param mapView 地图View
 */
- (void)mapViewWillStartLocatingUser:(MAMapView *)mapView;

/*!
 @brief 在地图View停止定位后，会调用此函数
 @param mapView 地图View
 */
- (void)mapViewDidStopLocatingUser:(MAMapView *)mapView;

/*!
 @brief 用户位置更新后，会调用此函数
 @param mapView 地图View
 @param userLocation 新的用户位置
 */
- (void)mapView:(MAMapView *)mapView didUpdateUserLocation:(MAUserLocation *)userLocation;

/*!
 @brief 定位失败后，会调用此函数
 @param mapView 地图View
 @param error 错误号，参考CLError.h中定义的错误号
 */
- (void)mapView:(MAMapView *)mapView didFailToLocateUserWithError:(NSError *)error;

/*!
 @brief 拖动annotation view时view的状态变化，ios3.2以后支持
 @param mapView 地图View
 @param view annotation view
 @param newState 新状态
 @param oldState 旧状态
 */
- (void)mapView:(MAMapView *)mapView annotationView:(MAAnnotationView *)view didChangeDragState:(MAAnnotationViewDragState)newState
fromOldState:(MAAnnotationViewDragState)oldState;

/*!
 @brief 根据overlay生成对应的View
 @param mapView 地图View
 @param overlay 指定的overlay
 @return 生成的覆盖物View
 */
- (MAOverlayView *)mapView:(MAMapView *)mapView viewForOverlay:(id <MAOverlay>)overlay;

/*!
 @brief 当mapView新添加overlay views时，调用此接口
 @param mapView 地图View
 @param overlayViews 新添加的overlay views
 */
- (void)mapView:(MAMapView *)mapView didAddOverlayViews:(NSArray *)overlayViews;

/*!
 @brief 标注view的accessory view(必须继承自UIControl)被点击时，触发该回调
 @param mapView 地图View
 @param annotationView callout所属的标注view
 @param control 对应的control
 */
- (void)mapView:(MAMapView *)mapView annotationView:(MAAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;

/*!
 @brief 当userTrackingMode改变时，调用此接口
 @param mapView 地图View
 @param mode 改变后的mode
 @param animated 动画
 */
- (void)mapView:(MAMapView *)mapView didChangeUserTrackingMode:(MAUserTrackingMode)mode animated:(BOOL)animated;

/*!
 @brief 离线地图数据将要被加载, 调用reloadMap会触发该回调，离线数据生效前的回调.
 @param mapview 地图View
 */
- (void)offlineDataWillReload:(MAMapView *)mapView;

/*!
 @brief 离线地图数据加载完成, 调用reloadMap会触发该回调，离线数据生效后的回调.
 @param mapview 地图View
 */
- (void)offlineDataDidReload:(MAMapView *)mapView;

@end
