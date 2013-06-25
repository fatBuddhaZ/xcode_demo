//
//  ViewController.h
//  PBike
//
//  Created by suny on 13-6-24.
//  Copyright (c) 2013年 Peter.Sun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MAMapKit.h" 

@interface ViewController : UIViewController<MAMapViewDelegate>
@property (nonatomic, strong) MAMapView *mapView; 
@property (strong, nonatomic) IBOutlet UIView *mapContainer;

@end
