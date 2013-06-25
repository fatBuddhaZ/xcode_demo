//
//  ViewController.m
//  PBike
//
//  Created by suny on 13-6-24.
//  Copyright (c) 2013年 Peter.Sun. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize mapView,mapContainer;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    mapView  = [[MAMapView alloc] initWithFrame:CGRectMake
                (0, 0, 0, 0)];
    mapView.mapType = MAMapTypeStandard;
    mapView.delegate = self;
    CLLocationCoordinate2D location;
    location.latitude=39.855539;
    location.longitude=116.419037;
    mapView.region=MACoordinateRegionMake(location,
                                          MACoordinateSpanMake(0.05, 0.05));
    mapView.delegate = self;
    
    
    
    [mapContainer addSubview:mapView];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    CLLocationCoordinate2D polylineCoords[4];
    polylineCoords[0].latitude = 39.855539;
    polylineCoords[0].longitude = 116.419037;
    polylineCoords[1].latitude = 39.858172;
    polylineCoords[1].longitude = 116.520285;
    polylineCoords[2].latitude = 39.795479;
    polylineCoords[2].longitude = 116.520859;
    polylineCoords[3].latitude = 39.788467;
    polylineCoords[3].longitude = 116.426786;
    MAPolyline *polyline = [MAPolyline polylineWithCoordinates:polylineCoords
                                                         count:4];
    
    [mapView insertOverlay:polyline atIndex:0];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
