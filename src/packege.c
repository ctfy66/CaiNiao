//包裹管理与业务流程模块
//created by ctfy 

#include "../include/station.h"

// 创建一个新的包裹并初始化
Package* createPackage(const char* tracking_number, const char* user_phone_number, double weight, double distance, int is_insured, double insured_value) {
    Package* new_package = (Package*)malloc(sizeof(Package));
    if (new_package == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    
    // 初始化包裹信息
    strcpy(new_package->tracking_number, tracking_number);
    strcpy(new_package->user_phone_number, user_phone_number);
    new_package->weight = weight;
    new_package->distance = distance;
    new_package->is_insured = is_insured ? INSURED_YES : INSURED_NO;
    new_package->insured_value = is_insured ? insured_value : 0.0;
    
    // 初始状态为入库
    new_package->status = STATUS_INSTOCK;
    
    // 生成取件码
    generatePickupCode(new_package->pickup_code);
    
    // 计算费用 (假设默认属性为普通包裹)
    new_package->cost = calculatePackageCost(weight, distance, is_insured, insured_value, ATTRIBUTE_NORMAL);
    
    new_package->next = NULL;
    
    return new_package;
}

// 将新包裹添加到链表中
void addPackage(Package** head, Package* new_package) {
    if (head == NULL || new_package == NULL) {
        return;
    }
    
    // 如果链表为空，新包裹成为头节点
    if (*head == NULL) {
        *head = new_package;
        return;
    }
    
    // 将新包裹添加到链表尾部
    Package* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_package;
}

// 根据单号查找包裹
Package* findPackageByTrackingNumber(const char* tracking_number, const Package* head) {
    if (head == NULL || tracking_number == NULL) {
        return NULL;
    }
    
    const Package* current = head;
    while (current != NULL) {
        if (strcmp(current->tracking_number, tracking_number) == 0) {
            // 返回匹配的包裹
            return (Package*)current;  // 去除const限定符，因为函数返回类型不是const
        }
        current = current->next;
    }
    
    return NULL; // 未找到匹配的包裹
}

// 根据手机号查找包裹
Package* findPackagesByPhone(const char* phone_number, const Package* head) {
    if (head == NULL || phone_number == NULL) {
        return NULL;
    }
    
    // 找到第一个匹配的包裹
    const Package* current = head;
    while (current != NULL) {
        if (strcmp(current->user_phone_number, phone_number) == 0) {
            // 返回第一个匹配的包裹
            return (Package*)current;  // 去除const限定符
        }
        current = current->next;
    }
    
    return NULL; // 未找到匹配的包裹
}

// 更新包裹状态
void updatePackageStatus(const char* tracking_number, int new_status, Package* head) {
    if (head == NULL || tracking_number == NULL) {
        return;
    }
    
    // 查找并更新包裹状态
    Package* package = findPackageByTrackingNumber(tracking_number, head);
    if (package != NULL) {
        // 检查状态值是否有效
        if (new_status >= STATUS_INSTOCK && new_status <= STATUS_RETURNED) {
            package->status = (packagestatus)new_status;
            printf("包裹 %s 状态已更新为: %d\n", tracking_number, new_status);
        } else {
            printf("无效的包裹状态值: %d\n", new_status);
        }
    } else {
        printf("未找到单号为 %s 的包裹\n", tracking_number);
    }
}

// 从链表中移除包裹
void removePackage(Package** head, const char* tracking_number) {
    if (head == NULL || *head == NULL || tracking_number == NULL) {
        return;
    }
    
    Package* current = *head;
    Package* prev = NULL;
    
    // 如果头节点就是要删除的包裹
    if (strcmp(current->tracking_number, tracking_number) == 0) {
        *head = current->next;
        free(current);
        printf("包裹 %s 已从系统中移除\n", tracking_number);
        return;
    }
    
    // 查找要删除的包裹
    while (current != NULL && strcmp(current->tracking_number, tracking_number) != 0) {
        prev = current;
        current = current->next;
    }
    
    // 如果找到了包裹
    if (current != NULL) {
        prev->next = current->next;
        free(current);
        printf("包裹 %s 已从系统中移除\n", tracking_number);
    } else {
        printf("未找到单号为 %s 的包裹\n", tracking_number);
    }
}

// 生成取件码
void generatePickupCode(char* pickup_code) {
    if (pickup_code == NULL) {
        return;
    }
    
    // 取件码格式：一位大写字母+一位小写字母+四位数字
    srand((unsigned int)time(NULL));
    
    // 生成大写字母 (A-Z: 65-90)
    pickup_code[0] = 'A' + rand() % 26;
    
    // 生成小写字母 (a-z: 97-122)
    pickup_code[1] = 'a' + rand() % 26;
    
    // 生成4位数字 (0-9)
    for (int i = 2; i < 6; i++) {
        pickup_code[i] = '0' + rand() % 10;
    }
    
    // 字符串结束符
    pickup_code[6] = '\0';
}

// 计算包裹费用
double calculatePackageCost(double weight, double distance, int is_insured, double insured_value, int attribute) {
    // 基础计算费用公式示例
    double base_cost = 8.0;  // 基础费用
    double weight_factor = 2.0;  // 每公斤增加费用
    double distance_factor = 0.05;  // 每公里增加费用
    double insurance_factor = 0.01;  // 保价费率 (1%)
    double attribute_factor = 1.0;  // 属性倍率
    
    // 根据包裹属性调整倍率
    switch (attribute) {
        case ATTRIBUTE_FRAGILE:
            attribute_factor = 1.5;  // 易碎品加价50%
            break;
        case ATTRIBUTE_REFRIGERATED:
            attribute_factor = 2.0;  // 冷藏品加价100%
            break;
        case ATTRIBUTE_OVERSIZE:
            attribute_factor = 1.8;  // 大件加价80%
            break;
        case ATTRIBUTE_HIGHVALUE:
            attribute_factor = 2.5;  // 贵重物品加价150%
            break;
        default:  // ATTRIBUTE_NORMAL
            attribute_factor = 1.0;  // 普通包裹无额外费用
            break;
    }
    
    // 计算基础费用
    double cost = (base_cost + weight * weight_factor + distance * distance_factor) * attribute_factor;
    
    // 如果保价，添加保价费用
    if (is_insured && insured_value > 0) {
        cost += insured_value * insurance_factor;
    }
    
    // 四舍五入到两位小数
    return round(cost * 100) / 100;
}



// 包裹入库流程
void processPackageInbound(Package** package_head, System* system_data, User* user_head) {
    if (package_head == NULL || system_data == NULL) {
        printf("系统错误：无效的数据指针\n");
        return;
    }
    
    char tracking_number[TRACKING_NUM_LEN];
    char user_phone[PHONE_NUMBER_LEN];
    double weight, distance;
    int is_insured;
    double insured_value = 0.0;
    int attribute;
    
    // 获取包裹信息
    printf("\n=== 包裹入库 ===\n");
    printf("请输入快递单号: ");
    scanf("%s", tracking_number);
    
    // 检查单号是否已存在
    if (findPackageByTrackingNumber(tracking_number, *package_head) != NULL) {
        printf("错误：该单号已存在于系统中\n");
        return;
    }
    
    printf("请输入收件人手机号: ");
    scanf("%s", user_phone);
    
    // 验证手机号是否在系统中
    User* receiver = findUserByPhone(user_phone, user_head);
    if (receiver == NULL) {
        char choice;
        printf("警告：该手机号未注册，是否继续? (Y/N): ");
        scanf(" %c", &choice);
        if (choice != 'Y' && choice != 'y') {
            printf("操作已取消\n");
            return;
        }
    }
    
    printf("请输入包裹重量(kg): ");
    scanf("%lf", &weight);
    
    printf("请输入运输距离(km): ");
    scanf("%lf", &distance);
    
    printf("请选择包裹属性:\n");
    printf("1. 普通包裹\n");
    printf("2. 易碎品\n");
    printf("3. 冷藏品\n");
    printf("4. 大件物品\n");
    printf("5. 贵重物品\n");
    printf("请选择: ");
    scanf("%d", &attribute);
    if (attribute < 1 || attribute > 5) {
        attribute = ATTRIBUTE_NORMAL;  // 默认为普通包裹
    }
    
    printf("是否保价? (0-否, 1-是): ");
    scanf("%d", &is_insured);
    
    if (is_insured) {
        printf("请输入保价金额: ");
        scanf("%lf", &insured_value);
    }
    
    // 创建包裹并添加到系统
    Package* new_package = createPackage(tracking_number, user_phone, weight, distance, is_insured, insured_value);
    if (new_package == NULL) {
        printf("创建包裹失败\n");
        return;
    }
    
    // 重新计算正确的费用（含属性）
    new_package->cost = calculatePackageCost(weight, distance, is_insured, insured_value, attribute);
    
    // 添加到链表
    addPackage(package_head, new_package);
    
    // 更新系统数据
    system_data->total_packages++;
    system_data->package_int_storage_count++;
    system_data->total_revenue += new_package->cost;
    
    // 更新用户包裹数量
    if (receiver != NULL) {
        receiver->package_received_count++;
    }
    
    printf("\n包裹入库成功!\n");
    printf("单号: %s\n", tracking_number);
    printf("取件码: %s\n", new_package->pickup_code);
    printf("费用: %.2f 元\n", new_package->cost);
}

// 包裹出库流程
void processPackageOutbound(Package** package_head, System* system_data) {
    if (package_head == NULL || system_data == NULL || *package_head == NULL) {
        printf("系统错误：无效的数据指针或包裹列表为空\n");
        return;
    }
    
    char tracking_or_pickup[PICKUP_CODE_LEN];
    int search_by;
    
    printf("\n=== 包裹出库 ===\n");
    printf("1. 通过快递单号出库\n");
    printf("2. 通过取件码出库\n");
    printf("请选择: ");
    scanf("%d", &search_by);
    
    if (search_by != 1 && search_by != 2) {
        printf("无效的选择\n");
        return;
    }
    
    if (search_by == 1) {
        printf("请输入快递单号: ");
    } else {
        printf("请输入取件码: ");
    }
    scanf("%s", tracking_or_pickup);
    
    // 查找包裹
    Package* current = *package_head;
    Package* prev = NULL;
    int found = 0;
    
    while (current != NULL) {
        if ((search_by == 1 && strcmp(current->tracking_number, tracking_or_pickup) == 0) ||
            (search_by == 2 && strcmp(current->pickup_code, tracking_or_pickup) == 0)) {
            found = 1;
            break;
        }
        prev = current;
        current = current->next;
    }
    
    if (!found) {
        printf("未找到相关包裹\n");
        return;
    }
    
    // 显示包裹信息
    printf("\n包裹信息:\n");
    printf("单号: %s\n", current->tracking_number);
    printf("收件人手机: %s\n", current->user_phone_number);
    printf("取件码: %s\n", current->pickup_code);
    printf("重量: %.2f kg\n", current->weight);
    printf("费用: %.2f 元\n", current->cost);
    printf("状态: %d\n", current->status);
    
    // 确认出库
    char confirm;
    printf("\n确认出库此包裹? (Y/N): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'Y' || confirm == 'y') {
        // 更新包裹状态为已取
        current->status = STATUS_PICKEDUP;
        
        // 更新系统库存计数
        if (system_data->package_int_storage_count > 0) {
            system_data->package_int_storage_count--;
        }
        
        printf("包裹已成功出库\n");
    } else {
        printf("操作已取消\n");
    }
}

// 寄件流程
void processSendPackage(Package** package_head, User** user_head, System* system_data) {
    if (package_head == NULL || user_head == NULL || system_data == NULL) {
        printf("系统错误：无效的数据指针\n");
        return;
    }
    
    char sender_phone[PHONE_NUMBER_LEN];
    char receiver_phone[PHONE_NUMBER_LEN];
    char tracking_number[TRACKING_NUM_LEN];
    double weight, distance;
    int is_insured, attribute;
    double insured_value = 0.0;
    
    printf("\n=== 寄件服务 ===\n");
    
    // 寄件人信息
    printf("请输入寄件人手机号: ");
    scanf("%s", sender_phone);
    
    // 检查寄件人是否为注册用户
    User* sender = findUserByPhone(sender_phone, *user_head);
    if (sender == NULL) {
        char choice;
        printf("该用户未注册，是否为其注册? (Y/N): ");
        scanf(" %c", &choice);
        
        if (choice == 'Y' || choice == 'y') {
            char username[USERNAME_LEN];
            char password[PASSWORD_LEN];
            int pay_method, settle_method;
            
            printf("请输入用户名: ");
            scanf("%s", username);
            printf("请设置密码: ");
            scanf("%s", password);
            printf("请选择支付方式 (1-现金, 2-微信, 3-支付宝, 4-其他): ");
            scanf("%d", &pay_method);
            printf("请选择结算方式 (1-一件一结, 2-月付): ");
            scanf("%d", &settle_method);
            
            // 创建并添加新用户
            User* new_user = createUser(username, sender_phone, password, pay_method, settle_method);
            if (new_user != NULL) {
                addUser(user_head, new_user);
                sender = new_user;
                system_data->user_count++;
                printf("用户注册成功!\n");
            } else {
                printf("用户创建失败，无法继续寄件流程\n");
                return;
            }
        } else {
            printf("未注册用户无法寄件，操作已取消\n");
            return;
        }
    }
    
    // 收件人信息
    printf("请输入收件人手机号: ");
    scanf("%s", receiver_phone);
    
    // 生成快递单号 (简化版：时间戳后10位)
    time_t now = time(NULL);
    sprintf(tracking_number, "CN%ld", now % 10000000000);
    
    // 包裹信息
    printf("请输入包裹重量(kg): ");
    scanf("%lf", &weight);
    
    printf("请输入运输距离(km): ");
    scanf("%lf", &distance);
    
    printf("请选择包裹属性:\n");
    printf("1. 普通包裹\n");
    printf("2. 易碎品\n");
    printf("3. 冷藏品\n");
    printf("4. 大件物品\n");
    printf("5. 贵重物品\n");
    printf("请选择: ");
    scanf("%d", &attribute);
    if (attribute < 1 || attribute > 5) {
        attribute = ATTRIBUTE_NORMAL;  // 默认为普通包裹
    }
    
    printf("是否保价? (0-否, 1-是): ");
    scanf("%d", &is_insured);
    
    if (is_insured) {
        printf("请输入保价金额: ");
        scanf("%lf", &insured_value);
    }
    
    // 创建包裹
    Package* new_package = createPackage(tracking_number, receiver_phone, weight, distance, is_insured, insured_value);
    if (new_package == NULL) {
        printf("创建包裹失败\n");
        return;
    }
    
    // 重新计算正确的费用（含属性）
    new_package->cost = calculatePackageCost(weight, distance, is_insured, insured_value, attribute);
    
    // 显示费用并确认
    printf("\n寄件信息确认:\n");
    printf("快递单号: %s\n", tracking_number);
    printf("收件人手机: %s\n", receiver_phone);
    printf("包裹重量: %.2f kg\n", weight);
    printf("运输距离: %.2f km\n", distance);
    printf("包裹费用: %.2f 元\n", new_package->cost);
    
    char confirm;
    printf("\n确认寄件? (Y/N): ");
    scanf(" %c", &confirm);
    
    if (confirm == 'Y' || confirm == 'y') {
        // 支付流程
        char payment_confirm;
        int payment_successful = 0;
        
        printf("请选择支付方式:\n");
        printf("1. 现金支付\n");
        printf("2. 微信支付\n");
        printf("3. 支付宝支付\n");
        int payment_choice;
        scanf("%d", &payment_choice);
        
        printf("确认支付 %.2f 元? (Y/N): ", new_package->cost);
        scanf(" %c", &payment_confirm);
        
        if (payment_confirm == 'Y' || payment_confirm == 'y') {
            // 模拟支付过程
            printf("处理支付中...\n");
            payment_successful = 1;  // 实际应用中应有真实支付验证
            
            if (payment_successful) {
                // 添加包裹到系统
                addPackage(package_head, new_package);
                
                // 更新系统数据
                system_data->total_packages++;
                system_data->package_int_storage_count++;
                system_data->total_revenue += new_package->cost;
                system_data->operating_funds += new_package->cost;
                
                // 更新用户数据
                sender->package_sent_count++;
                
                printf("\n寄件成功！\n");
                printf("请保留快递单号: %s\n", tracking_number);
            } else {
                printf("支付失败，寄件取消\n");
                free(new_package);  // 释放包裹内存
            }
        } else {
            printf("支付已取消，寄件取消\n");
            free(new_package);  // 释放包裹内存
        }
    } else {
        printf("寄件已取消\n");
        free(new_package);  // 释放包裹内存
    }
}

// 异常处理函数
void handleExceptions(int error_code, const char* message) {
    printf("错误 [%d]: %s\n", error_code, message);
    
    // 根据错误码处理不同类型的异常
    switch (error_code) {
        case 1:  // 包裹损坏
            printf("处理措施: 记录损坏情况，联系相关人员进行赔付处理\n");
            break;
        case 2:  // 包裹丢失
            printf("处理措施: 启动包裹追踪程序，联系快递公司和客户\n");
            break;
        case 3:  // 误领/冒领
            printf("处理措施: 核实领取人身份，联系正确收件人，启动安全程序\n");
            break;
        case 4:  // 包裹拒收
            printf("处理措施: 记录拒收原因，通知寄件人，准备退回处理\n");
            break;
        default:
            printf("通用处理措施: 记录异常，联系相关人员\n");
            break;
    }
    
    // 记录异常到日志
    FILE* log_file = fopen("error_log.txt", "a");
    if (log_file != NULL) {
        time_t now = time(NULL);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
        
        fprintf(log_file, "[%s] 错误 [%d]: %s\n", time_str, error_code, message);
        fclose(log_file);
    }
}