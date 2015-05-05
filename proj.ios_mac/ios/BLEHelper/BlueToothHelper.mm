//
//  BlueToothHelper.m
//  Guitars
//
//  Created by allen on 15-3-16.
//
//

#import "BlueToothHelper.h"

static BlueToothHelper *sharedAccountManagerInstance =nil;


//外设UUID
static NSString *peripheralUUID=@"527E2AB8-E7D1-9105-1E15-9C24C2E767AA";
//  static NSString *peripheralUUID=@"B5410B69-7675-3A73-D2A7-3B83364C2744";
//写入服务UUID
static NSString *writedServiceUUID=@"FFE5";
//订阅服务UUID
static NSString *notifyServiceUUID=@"FFE0";


CBPeripheral *per4Guitar;
CBCharacteristic *writedCharacteristic;
CBCharacteristic *notifyCharacteristic;



BOOL isConnected = false;

@implementation BlueToothHelper


+(BlueToothHelper *)shareManager{
    
    static dispatch_once_t predicate;
 
    dispatch_once(&predicate, ^{
        sharedAccountManagerInstance = [[self alloc] init];
    });
    return sharedAccountManagerInstance;
}


-(id)init{
    if(self =[super init]){
        
    }
    return self;
}

-(void)didLoad{
    self.cbCentralMgr = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    self.peripheralArray = [NSMutableArray array];
    self.PeripheralIdentifiers = [NSMutableArray array];
    [self getcentralManagerStateStr:self.cbCentralMgr];
    
}


-(bool)isConnected{
    return isConnected;
}

-(void) scanPeripherals{
    [self.cbCentralMgr stopScan];
    [self.peripheralArray removeAllObjects];
    [self.PeripheralIdentifiers removeAllObjects];
    
     NSDictionary *options = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],CBCentralManagerScanOptionAllowDuplicatesKey, nil];
    [self.cbCentralMgr scanForPeripheralsWithServices:nil options:options];
    
    [self getcentralManagerStateStr:self.cbCentralMgr];
}

-(void)sendData:(Byte[])dataInfo{
    if (per4Guitar)
    {
        if ([per4Guitar state] != CBPeripheralStateConnected){
            return;
        }
        if(writedCharacteristic == nil){
            return;
        }
        
        
//        Byte byteData2[] = {0xFF,0x11, 0x60,0x02,0x01,0x00,0x01,0x00,0x02,0x00 ,0x04 ,0x00 ,0x04 ,0x00 ,0x01 ,0x00 ,0x01};
        
//        Byte byteData2[] = {0xFF,0x11, 0x6f,0x02,0x00,0x7f,0x00,0x00,0x00,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00};
    

         //Byte byteData2[] = {0xFF,0x11, 0x62,0x02,0x01,0x00,0x00,0x00,0x01,0x00 ,0x00 ,0x00 ,0x02 ,0x00 ,0x04 ,0x00 ,0x04};

         //NSData * data2 = [NSData dataWithBytes:byteData2 length:17];
         //[per4Guitar writeValue:data2 forCharacteristic:writedCharacteristic type:CBCharacteristicWriteWithResponse];
        
        //[NSThread sleepForTimeInterval:1];
        
//
//        
//        [NSThread sleepForTimeInterval:2];
//        Byte byteData7[] = {0xff,0xd ,0x57 ,0x07 ,
//            0x01 ,
//            0x01 ,0x01 ,0x00 ,0x10,
//            0x02 ,
//            0x01 ,0x01 ,0xFF ,0xFF};
//        NSData * data7 = [NSData dataWithBytes:byteData7 length:14];
//        [per4Guitar writeValue:data7 forCharacteristic:writedCharacteristic type:CBCharacteristicWriteWithResponse];
//
//        [NSThread sleepForTimeInterval:2];
//
        
        
        
        
       // NSData * chordData = [NSData dataWithBytes:dataInfo length:17];
       // [per4Guitar writeValue:chordData forCharacteristic:writedCharacteristic type:CBCharacteristicWriteWithResponse];

        
        Byte playDataArray[] = {0xFF, 0x07, 0x6f, 0x03,0x08,0x00,0x00};
        NSData * playData = [NSData dataWithBytes:playDataArray length:7];
        [per4Guitar writeValue:playData forCharacteristic:writedCharacteristic type:CBCharacteristicWriteWithResponse];
    }
}


-(UInt16) swap:(UInt16)s {
    UInt16 temp = s << 8;
    temp |= (s >> 8);
    return temp;
}


- (void)centralManagerDidUpdateState:(CBCentralManager *)central
{
    [self addLog:@"------------centralManagerDidUpdateState---------------"];
    switch (central.state) {
        case CBCentralManagerStateUnknown:
            [self addLog:@"State Unknown"];
        breakcenterMgrStateCentralManagerStateResetting:
            [self addLog:@"State Resetting"];
            break;
            
        case CBCentralManagerStateUnsupported:
            [self addLog:@"State Unsupported"];
            break;
        case CBCentralManagerStateUnauthorized:
            [self addLog:@"State Unauthorized"];
            break;
        case CBCentralManagerStatePoweredOff:
            [self addLog:@"State PoweredOff"];
            break;
        case CBCentralManagerStatePoweredOn:
            [self addLog:@"State PoweredOn"];
            break;
        default:
            [self addLog:@"State 未知"];
            break;
    }
}

//扫描到外设
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
    [self addLog:@"------------didDiscoverPeripheral---------------"];
    [self addLog:peripheral.name];
    [self addLog:[peripheral.RSSI stringValue]];
    [self addLog:[peripheral.identifier UUIDString]];
    
    [self.peripheralArray addObject:peripheral];
    NSString *uuid = [peripheral.identifier UUIDString];
    
    [self addLog:uuid];
    
    if([uuid isEqual:peripheralUUID]){
        per4Guitar = peripheral;
        
        [self.cbCentralMgr connectPeripheral:per4Guitar options:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:CBConnectPeripheralOptionNotifyOnDisconnectionKey]];
    }
}

//连接外设
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
{
    [self addLog:@"-------------didConnectPeripheral-----------------"];
    [self addLog:peripheral.name];
    [self.PeripheralIdentifiers addObject:peripheral];
    
    peripheral.delegate = self;
    [peripheral discoverServices:nil];
    
    isConnected = true;
    
}

//扫描服务
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error
{
    [self addLog:@"-------------didDiscoverServices-----------------"];
    [self addLog:peripheral.name];
    
    for (CBService* service in peripheral.services){
        
        //发送服务
        if([service.UUID isEqual:[CBUUID UUIDWithString:writedServiceUUID]]){
            NSLog(@"Service found with UUID: %@", service.UUID);
            [peripheral discoverCharacteristics:nil forService:service];
            [self addLog:[NSString stringWithFormat:@"%@ uuid:%@",service,service.UUID]];
        //订阅服务
        }else if ([service.UUID isEqual:[CBUUID UUIDWithString:notifyServiceUUID]]){
            [peripheral discoverCharacteristics:nil forService:service];
//            [peripheral discoverIncludedServices:nil forService:service];
            [self addLog:[NSString stringWithFormat:@"%@ uuid:%@",service,service.UUID]];
        }
    }
}

//扫描特征

- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
{
    
    [self addLog:@"-------------didDiscoverCharacteristicsForService-----------------"];
    [self addLog:peripheral.name];
    [self addLog:[NSString stringWithFormat:@"%@",service]];
    for (CBCharacteristic * characteristic in service.characteristics) {
       // [self addLog:[NSString stringWithFormat:@"%@ characteristic:%@",characteristic,characteristic.UUID]];
//        [peripheral setNotifyValue:YES forCharacteristic:characteristic];
        if(characteristic.properties ==CBCharacteristicPropertyNotify){
            [self addLog:[NSString stringWithFormat:@"%@ notify characteristic:%@",characteristic,characteristic.UUID]];
            [peripheral setNotifyValue:YES forCharacteristic:characteristic];
            notifyCharacteristic = characteristic;
        }else if(characteristic.properties == CBCharacteristicPropertyWrite){
            [self addLog:[NSString stringWithFormat:@"%@ write characteristic:%@",characteristic,characteristic.UUID]];
            
            NSString *str = [characteristic.UUID UUIDString];
            if([str isEqualToString:@"FFE9"]){
                writedCharacteristic = characteristic;
            }
        }
    }
}

//读取回执信息
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    [self addLog:@"-------------didUpdateValueForCharacteristic-----------------"];
    [self addLog:peripheral.name];
    [self addLog:[NSString stringWithFormat:@"%@ value:%@",characteristic,characteristic.value]];
    
}


-(NSString*)getcentralManagerStateStr:(CBCentralManager*)central
{
    NSString* result;
    switch (central.state) {
        case CBCentralManagerStatePoweredOff:
            result = @"PoweredOff";
            break;
            
        case CBCentralManagerStatePoweredOn:
            result = @"PoweredOn";
            break;
            
        case CBCentralManagerStateResetting:
            result = @"Resetting";
            break;
            
        case CBCentralManagerStateUnauthorized:
            result = @"Unauthorized";
            break;
            
        case CBCentralManagerStateUnknown:
            result = @"Unknown";
            break;
            
        case CBCentralManagerStateUnsupported:
            result = @"Unsupported";
            break;
            
        default:
            result = @"没有啦";
            break;
    }
    return result;
}

- (void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    [self addLog:@"-------------didFailToConnectPeripheral-----------------"];
    [self addLog:peripheral.name];
}

- (void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    [self addLog:@"-------------didDisconnectPeripheral-----------------"];
    [self addLog:peripheral.name];
    
}


#pragma mark - tool
-(void)addLog:(NSString*)log
{
    NSLog(@"%@",log);
}


//- (void)centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary *)dict
//{
//    [self addLog:@"-------------willRestoreState-----------------"];
//    [self addLog:[NSString stringWithFormat:@"%@",dict]];
//
//
//}
//- (void)centralManager:(CBCentralManager *)central didRetrievePeripherals:(NSArray *)peripherals
//{
//    [self addLog:@"-------------didRetrievePeripherals-----------------"];
//    for (CBPeripheral * peripheral in peripherals) {
//        [self addLog:[NSString stringWithFormat:@"%@ name:%@",peripheral,peripheral.name]];
//    }
//
//}

//- (void)centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals
//{
//    [self addLog:@"-------------didRetrieveConnectedPeripherals-----------------"];
//    for (CBPeripheral * peripheral in peripherals) {
//        [self addLog:[NSString stringWithFormat:@"%@ name:%@",peripheral,peripheral.name]];
//    }
//
//
//}

//- (void)peripheralDidUpdateName:(CBPeripheral *)peripheral NS_AVAILABLE(NA, 6_0)
//{
//    [self addLog:@"-------------peripheralDidUpdateName-----------------"];
//    [self addLog:peripheral.name];
//    
//}
//
//- (void)peripheralDidInvalidateServices:(CBPeripheral *)peripheral NS_DEPRECATED(NA, NA, 6_0, 7_0)
//{
//    [self addLog:@"-------------peripheralDidInvalidateServices-----------------"];
//    [self addLog:peripheral.name];
//    
//}
//
//- (void)peripheral:(CBPeripheral *)peripheral didModifyServices:(NSArray *)invalidatedServices NS_AVAILABLE(NA, 7_0)
//{
//    [self addLog:@"-------------didModifyServices-----------------"];
//    [self addLog:peripheral.name];
//    
//}

//- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral error:(NSError *)error
//{
//    [self addLog:@"-------------peripheralDidUpdateRSSI-----------------"];
//    [self addLog:peripheral.name];
//    
//}

//- (void)peripheral:(CBPeripheral *)peripheral didDiscoverIncludedServicesForService:(CBService *)service error:(NSError *)error
//{
//    [self addLog:@"-------------didDiscoverIncludedServicesForService-----------------"];
//    [self addLog:peripheral.name];
//    //    [self addLogWithService: service];
//    for (CBService * server in service.includedServices) {
//        [self addLog:[NSString stringWithFormat:@"%@ uuid:%@",service,service.UUID]];    }
//    
//}




//- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
//{
//    [self addLog:@"-------------didWriteValueForCharacteristic-----------------"];
//    [self addLog:peripheral.name];
//    if ([[[UIDevice currentDevice] systemVersion] floatValue]>=7.0)
//    {
//        [self addLog:[NSString stringWithFormat:@"%@ value:%@",characteristic,characteristic.value]];//ios7时，这里的value并不是写进去的值
//    }else{
//        [self addLog:[NSString stringWithFormat:@"%@ value:%@",characteristic,characteristic.value]];
//    }
//}

//- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
//{
//    
//    [self addLog:@"-------------didUpdateNotificationStateForCharacteristic-----------------"];
//    [self addLog:peripheral.name];
//    [self addLog:[NSString stringWithFormat:@"%@",characteristic]];
//}

//- (void)peripheral:(CBPeripheral *)peripheral didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
//{
//    [self addLog:@"-------------didDiscoverDescriptorsForCharacteristic-----------------"];
//    [self addLog:peripheral.name];
//    [self addLog:[NSString stringWithFormat:@"%@",characteristic]];
//    
//}

//- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
//{
//    [self addLog:@"-------------didUpdateValueForDescriptor-----------------"];
//    [self addLog:peripheral.name];
//    [self addLog:[NSString stringWithFormat:@"%@",descriptor]];
//    
//}
//
//
//- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForDescriptor:(CBDescriptor *)descriptor error:(NSError *)error
//{
//    [self addLog:@"-------------didWriteValueForDescriptor-----------------"];
//    [self addLog:peripheral.name];
//    [self addLog:[NSString stringWithFormat:@"%@",descriptor]];
//    
//}





@end
