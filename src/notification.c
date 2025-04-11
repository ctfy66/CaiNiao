// notification.c - 简化通知模块实现

#include "station.h"

// 模拟发送包裹到达通知(给收件人)
void sendPackageArrivalNotification(const Package* package) {
    if (package == NULL) {
        return;
    }
    
    printf("\n==== 通知发送 ====\n");
    printf("接收人手机: %s\n", package->user_phone_number);
    printf("通知类型: 包裹到达\n");
    printf("内容: 您有一个包裹已到达，单号：%s，取件码：%s，请尽快前来取件。\n", 
           package->tracking_number, package->pickup_code);
    printf("==== 通知结束 ====\n\n");
}


