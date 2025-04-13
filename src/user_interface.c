//用户界面模块
//created by ctfy
#include "../include/station.h"

// 显示管理员菜单
void displayAdminMenu() {
    printf("\n");
    printf("╔═════════════════════════════════════════╗\n");
    printf("║       菜鸟驿站管理系统 - 管理员菜单      ║\n");
    printf("╠═════════════════════════════════════════╣\n");
    printf("║ 1. 包裹管理                             ║\n");
    printf("║ 2. 用户管理                             ║\n");
    printf("║ 3. 系统信息                             ║\n");
    printf("║ 4. 异常处理                             ║\n");
    printf("║ 5. 统计报表                             ║\n");
    printf("║ 6. 修改密码                             ║\n");
    printf("║ 0. 退出登录                             ║\n");
    printf("╚═════════════════════════════════════════╝\n");
    printf("用户登录名：%s\n", "管理员");
    printf("请选择操作 [0-6]: ");
}

// 显示用户菜单
void displayUserMenu() {
    printf("\n");
    printf("╔═════════════════════════════════════════╗\n");
    printf("║        菜鸟驿站管理系统 - 用户菜单      ║\n");
    printf("╠═════════════════════════════════════════╣\n");
    printf("║ 1. 查询包裹                             ║\n");
    printf("║ 2. 寄送包裹                             ║\n");
    printf("║ 3. 取件服务                             ║\n");
    printf("║ 4. 个人信息管理                         ║\n");
    printf("║ 5. 费用查询                             ║\n");
    printf("║ 6. 修改密码                             ║\n");
    printf("║ 0. 退出登录                             ║\n");
    printf("╚═════════════════════════════════════════╝\n");
    printf("请选择操作 [0-6]: ");
}

// 显示包裹详细信息
void displayPackageDetails(const Package* package) {
    if (package == NULL) {
        printf("错误：无效的包裹指针\n");
        return;
    }
    
    // 状态描述映射表
    const char* status_desc[] = {
        "未知",
        "入库",
        "待取",
        "已取",
        "拒收",
        "退回"
    };
    
    // 确保状态值在有效范围内
    int status_index = package->status;
    if (status_index < STATUS_INSTOCK || status_index > STATUS_RETURNED) {
        status_index = 0; // 未知状态
    }
    
    printf("\n");
    printf("┌─────────────────────────────────────────┐\n");
    printf("│             包裹详细信息                │\n");
    printf("├────────────────────────────────────────┤\n");
    printf("│ 快递单号: %-30s│\n", package->tracking_number);
    printf("│ 收件人手机: %-28s│\n", package->user_phone_number);
    printf("│ 取件码: %-32s│\n", package->pickup_code);
    printf("│ 重量: %-35.2f│\n", package->weight);
    printf("│ 距离: %-35.2f│\n", package->distance);
    printf("│ 状态: %-35s│\n", status_desc[status_index]);
    printf("│ 保价: %-35s│\n", package->is_insured == INSURED_YES ? "是" : "否");
    
    if (package->is_insured == INSURED_YES) {
        printf("│ 保价金额: %-31.2f │\n", package->insured_value);
    }
    
    printf("│ 费用: %-35.2f │\n", package->cost);
    printf("└─────────────────────────────────────────┘\n");
}

// 显示用户详细信息
void displayUserDetails(const User* user) {
    if (user == NULL) {
        printf("错误：无效的用户指针\n");
        return;
    }
    
    // 支付方式描述映射表
    const char* payment_desc[] = {
        "未知",
        "现金",
        "微信",
        "支付宝",
        "其他"
    };
    
    // 确保支付方式在有效范围内
    int payment_index = user->pay_method;
    if (payment_index < PAY_CASH || payment_index > PAY_OTHER) {
        payment_index = 0; // 未知支付方式
    }
    
    // 结算方式描述
    const char* settlement_desc[] = {
        "未知",
        "一件一结",
        "月付"
    };
    
    // 确保结算方式在有效范围内
    int settlement_index = user->settle_method;
    if (settlement_index < SETTLE_PER_ITEM || settlement_index > SETTLE_MONTHLY) {
        settlement_index = 0; // 未知结算方式
    }
    
    printf("\n");
    printf("┌─────────────────────────────────────────┐\n");
    printf("│             用户详细信息                │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│ 用户名: %-33s │\n", user->username);
    printf("│ 手机号: %-33s │\n", user->phone_number);
    printf("│ 支付方式: %-31s │\n", payment_desc[payment_index]);
    printf("│ 结算方式: %-31s │\n", settlement_desc[settlement_index]);
    printf("│ 寄出包裹: %-31d │\n", user->package_sent_count);
    printf("│ 收到包裹: %-31d │\n", user->package_received_count);
    printf("└─────────────────────────────────────────┘\n");
}

// 显示系统信息
void displaySystemInfo(const System* system) {
    if (system == NULL) {
        printf("错误：无效的系统信息指针\n");
        return;
    }
    
    // 获取当前日期和时间
    time_t now = time(NULL);
    struct tm* local_time = localtime(&now);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    
    printf("\n");
    printf("┌─────────────────────────────────────────┐\n");
    printf("│             系统信息概览                │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│ 当前时间: %-31s │\n", time_str);
    printf("│ 运营资金: %-31.2f │\n", system->operating_funds);
    printf("│ 总收入: %-33.2f │\n", system->total_revenue);
    printf("│ 注册用户数: %-29d │\n", system->user_count);
    printf("│ 历史总包裹数: %-27d │\n", system->total_packages);
    printf("│ 库存包裹数: %-29d │\n", system->package_int_storage_count);
    printf("└─────────────────────────────────────────┘\n");
}

// 包裹查询界面
void packageQueryInterface(const Package* package_head,const User* current_user) {
    int choice;
    char tracking_number[TRACKING_NUM_LEN];
    char phone_number[PHONE_NUMBER_LEN];
    char pickup_code[PICKUP_CODE_LEN];
    
    do {
        printf("\n");
        printf("╔═════════════════════════════════════════╗\n");
        printf("║           包裹查询界面                  ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ 1. 按快递单号查询                       ║\n");
        printf("║ 2. 按手机号查询                         ║\n");
        printf("║ 3. 按取件码查询                         ║\n");
        printf("║ 4. 查看所有待取包裹                     ║\n");
        printf("║ 0. 返回上级菜单                         ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("请选择操作 [0-4]: ");
        scanf("%d", &choice);
        
        Package* found_package = NULL;
        
        switch (choice) {
            case 1: // 按快递单号查询
                printf("请输入快递单号: ");
                scanf("%s", tracking_number);
                found_package = findPackageByTrackingNumber(tracking_number, package_head);
                if (found_package != NULL) {
                    displayPackageDetails(found_package);
                } else {
                    printf("未找到单号为 %s 的包裹\n", tracking_number);
                }
                break;
                
            case 2: // 按手机号查询
                printf("请输入手机号: ");
                scanf("%s", phone_number);
                
                // 查找与手机号匹配的所有包裹
                int found_count = 0;
                const Package* current = package_head;
                
                printf("\n查询结果：\n");
                while (current != NULL) {
                    if (strcmp(current->user_phone_number, phone_number) == 0) {
                        displayPackageDetails(current);
                        found_count++;
                    }
                    current = current->next;
                }
                
                if (found_count == 0) {
                    printf("未找到与手机号 %s 关联的包裹\n", phone_number);
                } else {
                    printf("共找到 %d 个包裹\n", found_count);
                }
                break;
                
            case 3: // 按取件码查询
                printf("请输入取件码: ");
                scanf("%s", pickup_code);
                
                // 查找与取件码匹配的包裹
                found_count = 0;
                current = package_head;
                
                while (current != NULL) {
                    if (strcmp(current->pickup_code, pickup_code) == 0) {
                        displayPackageDetails(current);
                        found_count++;
                        break; 
                    }
                    current = current->next;
                }
                
                if (found_count == 0) {
                    printf("未找到取件码为 %s 的包裹\n", pickup_code);
                }
                break;
                
            case 4: // 查看所有待取包裹
                printf("\n待取包裹列表：\n");
                found_count = 0;
                current = package_head;
                
                while (current != NULL) {
                    if (current->status == STATUS_PENDING_PICKUP && strcmp(current->user_phone_number, current_user->phone_number) == 0) {
                        displayPackageDetails(current);
                        found_count++;
                    }
                    current = current->next;
                }
                
                if (found_count == 0) {
                    printf("当前没有待取包裹\n");
                } else {
                    printf("共有 %d 个待取包裹\n", found_count);
                }
                break;
                
            case 0:
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            getchar(); // 消耗之前输入的换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}

// 个人信息管理界面
void userProfileInterface(User* current_user) {
    if (current_user == NULL) {
        printf("错误：未登录用户\n");
        return;
    }
    
    int choice;
    int new_pay_method, new_settle_method;
    char old_password[PASSWORD_LEN];
    char new_password[PASSWORD_LEN];
    char confirm_password[PASSWORD_LEN];
    
    do {
        printf("\n");
        printf("╔═════════════════════════════════════════╗\n");
        printf("║           个人信息管理                  ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ 1. 查看个人信息                         ║\n");
        printf("║ 2. 修改支付方式                         ║\n");
        printf("║ 3. 修改结算方式                         ║\n");
        printf("║ 4. 修改密码                             ║\n");
        printf("║ 0. 返回上级菜单                         ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("请选择操作 [0-4]: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 查看个人信息
                displayUserDetails(current_user);
                break;
                
            case 2: // 修改支付方式
                printf("\n当前支付方式: ");
                switch (current_user->pay_method) {
                    case PAY_CASH:
                        printf("现金\n");
                        break;
                    case PAY_WECHAT:
                        printf("微信\n");
                        break;
                    case PAY_ALIPAY:
                        printf("支付宝\n");
                        break;
                    case PAY_OTHER:
                        printf("其他\n");
                        break;
                    default:
                        printf("未知\n");
                }
                
                printf("请选择新的支付方式：\n");
                printf("1. 现金\n");
                printf("2. 微信\n");
                printf("3. 支付宝\n");
                printf("4. 其他\n");
                printf("请选择 [1-4]: ");
                scanf("%d", &new_pay_method);
                
                if (new_pay_method >= PAY_CASH && new_pay_method <= PAY_OTHER) {
                    updateUser(current_user, new_pay_method, current_user->settle_method);
                    printf("支付方式已更新\n");
                } else {
                    printf("无效的选择，支付方式未更改\n");
                }
                break;
                
            case 3: // 修改结算方式
                printf("\n当前结算方式: ");
                switch (current_user->settle_method) {
                    case SETTLE_PER_ITEM:
                        printf("一件一结\n");
                        break;
                    case SETTLE_MONTHLY:
                        printf("月付\n");
                        break;
                    default:
                        printf("未知\n");
                }
                
                printf("请选择新的结算方式：\n");
                printf("1. 一件一结\n");
                printf("2. 月付\n");
                printf("请选择 [1-2]: ");
                scanf("%d", &new_settle_method);
                
                if (new_settle_method >= SETTLE_PER_ITEM && new_settle_method <= SETTLE_MONTHLY) {
                    updateUser(current_user, current_user->pay_method, new_settle_method);
                    printf("结算方式已更新\n");
                } else {
                    printf("无效的选择，结算方式未更改\n");
                }
                break;
                
            case 4: // 修改密码
                printf("请输入当前密码: ");
                scanf("%s", old_password);
                
                if (strcmp(current_user->password, old_password) != 0) {
                    printf("密码错误，无法修改\n");
                    break;
                }
                
                printf("请输入新密码: ");
                scanf("%s", new_password);
                
                printf("请再次输入新密码确认: ");
                scanf("%s", confirm_password);
                
                if (strcmp(new_password, confirm_password) != 0) {
                    printf("两次输入的密码不一致，修改失败\n");
                    break;
                }
                
                // 更新密码
                if (updateUserPassword(current_user, old_password, new_password)) {
                    printf("密码修改成功\n");
                } else {
                    printf("密码修改失败\n");
                }
                break;
                
            case 0:
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            getchar(); // 消耗之前输入的换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}

// 费用查询界面
void feeQueryInterface(const Package* package_head, User* current_user) {
    if (current_user == NULL) {
        printf("错误：未登录用户\n");
        return;
    }
    
    int choice;
    
    do {
        printf("\n");
        printf("╔═════════════════════════════════════════╗\n");
        printf("║             费用查询                    ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ 1. 查看待支付费用                       ║\n");
        printf("║ 2. 费用计算器                           ║\n");
        printf("║ 3. 查看历史支付记录                     ║\n");
        printf("║ 0. 返回上级菜单                         ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("请选择操作 [0-3]: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 查看待支付费用
                printf("\n待支付费用清单：\n");
                int found_count = 0;
                double total_fee = 0.0;
                const Package* current = package_head;
                
                while (current != NULL) {
                    // 未付款的包裹是状态为入库或待取的包裹
                    if ((current->status == STATUS_INSTOCK || current->status == STATUS_PENDING_PICKUP) && 
                        strcmp(current->user_phone_number, current_user->phone_number) == 0) {
                        printf("单号: %s, 费用: %.2f 元\n", current->tracking_number, current->cost);
                        total_fee += current->cost;
                        found_count++;
                    }
                    current = current->next;
                }
                
                if (found_count == 0) {
                    printf("当前没有待支付费用\n");
                } else {
                    printf("\n共 %d 个包裹，总计费用: %.2f 元\n", found_count, total_fee);
                }
                break;
                
            case 2: // 费用计算器
                printf("\n费用计算器\n");
                double weight, distance;
                int is_insured, attribute;
                double insured_value = 0.0;
                
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
                    attribute = ATTRIBUTE_NORMAL;
                    printf("使用默认值：普通包裹\n");
                }
                
                printf("是否保价? (0-否, 1-是): ");
                scanf("%d", &is_insured);
                
                if (is_insured) {
                    printf("请输入保价金额: ");
                    scanf("%lf", &insured_value);
                }
                
                // 计算费用
                double estimated_cost = calculatePackageCost(weight, distance, is_insured, insured_value, attribute);
                
                printf("\n预估费用: %.2f 元\n", estimated_cost);
                break;
                
            case 3: // 查看历史支付记录
                printf("\n历史支付记录：\n");
                found_count = 0;
                total_fee = 0.0;
                current = package_head;
                
                printf("%-15s %-10s %-10s\n", "单号", "状态", "费用");
                printf("----------------------------------\n");
                
                while (current != NULL) {
                    // 已取件的包裹视为已支付
                    if (current->status == STATUS_PICKEDUP && 
                        strcmp(current->user_phone_number, current_user->phone_number) == 0) {
                        
                        // 获取状态描述
                        const char* status_desc = "未知";
                        if (current->status == STATUS_PICKEDUP) {
                            status_desc = "已取";
                        }
                        
                        printf("%-15s %-10s %-10.2f\n", 
                               current->tracking_number, 
                               status_desc, 
                               current->cost);
                        
                        total_fee += current->cost;
                        found_count++;
                    }
                    current = current->next;
                }
                
                if (found_count == 0) {
                    printf("没有历史支付记录\n");
                } else {
                    printf("----------------------------------\n");
                    printf("共 %d 条记录，总计支付: %.2f 元\n", found_count, total_fee);
                }
                break;
                
            case 0:
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            getchar(); // 消耗之前输入的换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}

// 异常处理界面
void exceptionHandlingInterface() {
    int choice;
    int error_code;
    char message[100];
    
    do {
        printf("\n");
        printf("╔═════════════════════════════════════════╗\n");
        printf("║             异常处理                    ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ 1. 包裹损坏处理                         ║\n");
        printf("║ 2. 包裹丢失处理                         ║\n");
        printf("║ 3. 误领/冒领处理                        ║\n");
        printf("║ 4. 包裹拒收处理                         ║\n");
        printf("║ 5. 其他异常处理                         ║\n");
        printf("║ 0. 返回上级菜单                         ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("请选择操作 [0-5]: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 包裹损坏处理
                printf("请简述包裹损坏情况: ");
                getchar(); // 消耗之前输入的换行符
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0; // 移除换行符
                handleExceptions(1, message);
                break;
                
            case 2: // 包裹丢失处理
                printf("请提供丢失包裹的相关信息: ");
                getchar();
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                handleExceptions(2, message);
                break;
                
            case 3: // 误领/冒领处理
                printf("请提供误领/冒领情况的详细描述: ");
                getchar();
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                handleExceptions(3, message);
                break;
                
            case 4: // 包裹拒收处理
                printf("请提供拒收原因: ");
                getchar();
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                handleExceptions(4, message);
                break;
                
            case 5: // 其他异常处理
                printf("请选择异常类型代码 [5-9]: ");
                scanf("%d", &error_code);
                
                if (error_code < 5 || error_code > 9) {
                    printf("无效的异常代码，请使用 5-9 之间的数字\n");
                    break;
                }
                
                printf("请描述异常情况: ");
                getchar();
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = 0;
                handleExceptions(error_code, message);
                break;
                
            case 0:
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            if (choice != 5) getchar(); // 如果不是选项5，需要消耗换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}

// 统计报表界面
void statisticsReportInterface(const Package* package_head, const User* user_head, const System* system_data) {
    int choice;
    
    do {
        printf("\n");
        printf("╔═════════════════════════════════════════╗\n");
        printf("║             统计报表                    ║\n");
        printf("╠═════════════════════════════════════════╣\n");
        printf("║ 1. 包裹状态统计                         ║\n");
        printf("║ 2. 用户活跃度统计                       ║\n");
        printf("║ 3. 收入趋势分析                         ║\n");
        printf("║ 4. 系统运营概览                         ║\n");
        printf("║ 0. 返回上级菜单                         ║\n");
        printf("╚═════════════════════════════════════════╝\n");
        printf("请选择操作 [0-4]: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: { // 包裹状态统计
                int status_counts[6] = {0}; // 索引0不使用，1-5对应枚举值
                const Package* current = package_head;
                
                // 统计各状态包裹数量
                while (current != NULL) {
                    if (current->status >= STATUS_INSTOCK && current->status <= STATUS_RETURNED) {
                        status_counts[current->status]++;
                    }
                    current = current->next;
                }
                
                int total_packages = status_counts[1] + status_counts[2] + status_counts[3] + status_counts[4] + status_counts[5];
                
                printf("\n包裹状态统计：\n");
                printf("-------------------------------\n");
                printf("入库包裹: %d (%.1f%%)\n", status_counts[1], 
                       total_packages > 0 ? (float)status_counts[1] / total_packages * 100 : 0);
                printf("待取包裹: %d (%.1f%%)\n", status_counts[2], 
                       total_packages > 0 ? (float)status_counts[2] / total_packages * 100 : 0);
                printf("已取包裹: %d (%.1f%%)\n", status_counts[3], 
                       total_packages > 0 ? (float)status_counts[3] / total_packages * 100 : 0);
                printf("拒收包裹: %d (%.1f%%)\n", status_counts[4], 
                       total_packages > 0 ? (float)status_counts[4] / total_packages * 100 : 0);
                printf("退回包裹: %d (%.1f%%)\n", status_counts[5], 
                       total_packages > 0 ? (float)status_counts[5] / total_packages * 100 : 0);
                printf("-------------------------------\n");
                printf("总包裹数: %d\n", total_packages);
                
                break;
            }
                
            case 2: // 用户活跃度统计
                // 调用用户统计函数
                generateUserStatistics(user_head);
                break;
                
            case 3: // 收入趋势分析
                printf("\n收入趋势分析：\n");
                printf("总收入: %.2f 元\n", system_data->total_revenue);
                printf("运营资金: %.2f 元\n", system_data->operating_funds);
                
                break;
                
            case 4: // 系统运营概览
                displaySystemInfo(system_data);
                break;
                
            case 0:
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            getchar(); // 消耗之前输入的换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}

// 主菜单函数 - 进入系统后的总控制台
void mainMenuInterface(User* current_user, Package** package_head, User** user_head, System* system_data, Admin* admin_data) {
    if (current_user == NULL) {
        printf("错误：未登录用户\n");
        return;
    }
    
    int choice;
    char buffer[64]; // 用于清除输入缓冲区的buffer
    
    do {
        // 显示用户菜单
        displayUserMenu();
        
        // 读取用户选择，并检查是否成功读取了一个整数
        if (scanf("%d", &choice) != 1) {
            // 读取失败，清除输入缓冲区
            printf("无效的输入，请输入一个数字\n");
            scanf("%*[^\n]"); // 清除当前行中的所有字符
            getchar(); // 清除换行符
            
            // 将choice设为无效值，会触发default分支
            choice = -1;
            continue;
        }
        
        switch (choice) {
            case 1: // 查询包裹
                packageQueryInterface(*package_head, current_user);
                break;
                
            case 2: // 寄送包裹
                processSendPackage(package_head, user_head, system_data);
                break;
                
            case 3: // 取件服务
                processPackageOutbound(package_head, system_data);
                break;
                
            case 4: // 个人信息管理
                userProfileInterface(current_user);
                break;
                
            case 5: // 费用查询
                feeQueryInterface(*package_head, current_user);
                break;
                
            case 6: // 修改密码
                {
                    char old_password[PASSWORD_LEN];
                    char new_password[PASSWORD_LEN];
                    char confirm_password[PASSWORD_LEN];
                    
                    printf("\n修改密码\n");
                    printf("请输入当前密码: ");
                    scanf("%s", old_password);
                    
                    printf("请输入新密码: ");
                    scanf("%s", new_password);
                    
                    printf("请再次输入新密码确认: ");
                    scanf("%s", confirm_password);
                    
                    if (strcmp(new_password, confirm_password) != 0) {
                        printf("两次输入的密码不一致，修改失败\n");
                        break;
                    }
                    
                    if (changePassword(current_user->username, old_password, new_password, *user_head, admin_data)) {
                        printf("密码修改成功\n");
                    } else {
                        printf("密码修改失败，请确认旧密码是否正确\n");
                    }
                }
                break;
                
            case 0: // 退出登录
                printf("谢谢使用，再见！\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        // 消耗输入缓冲区中的字符，准备下一次输入
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            scanf("%*[^\n]");  // 清除输入缓冲区中的任何剩余数据
            getchar();         // 消耗换行符
        }
        
    } while (choice != 0);
}

// 管理员控制台 - 管理员登录后的总控制台
void adminConsoleInterface(Package** package_head, User** user_head, System* system_data, Admin* admin_data) {
    int choice;
    
    do {
        // 显示管理员菜单
        displayAdminMenu();
        
        // 读取用户选择，并检查是否成功读取了一个整数
        if (scanf("%d", &choice) != 1) {
            // 读取失败，清除输入缓冲区
            printf("无效的输入，请输入一个数字\n");
            scanf("%*[^\n]"); // 清除当前行中的所有字符
            getchar(); // 清除换行符
            
            // 将choice设为无效值，会触发default分支
            choice = -1;
            continue;
        }
        
        switch (choice) {
            case 1: // 包裹管理
                packageManagementMenu(package_head, system_data, *user_head);
                break;
                
            case 2: // 用户管理
                userManagementMenu(user_head, system_data);
                break;
                
            case 3: // 系统信息
                displaySystemInfo(system_data);
                printf("\n按 Enter 键继续...");
                scanf("%*[^\n]");  // 清除输入缓冲区中的任何剩余数据
                getchar(); // 消耗换行符
                break;
                
            case 4: // 异常处理
                exceptionHandlingInterface();
                break;
                
            case 5: // 统计报表
                statisticsReportInterface(*package_head, *user_head, system_data);
                break;
                
            case 6: // 修改密码
                {
                    char old_password[PASSWORD_LEN];
                    char new_password[PASSWORD_LEN];
                    
                    printf("\n修改管理员密码\n");
                    printf("请输入当前密码: ");
                    scanf("%s", old_password);
                    
                    if (strcmp(admin_data->password, old_password) != 0) {
                        printf("密码错误，无法修改\n");
                        break;
                    }
                    
                    printf("请输入新密码: ");
                    scanf("%s", new_password);
                    
                    // 更新管理员密码
                    strcpy(admin_data->password, new_password);
                    saveAdmin(admin_data);
                    
                    printf("管理员密码已成功更新\n");
                }
                printf("\n按 Enter 键继续...");
                scanf("%*[^\n]");  // 清除输入缓冲区中的任何剩余数据
                getchar(); // 消耗换行符
                break;
                
            case 0: // 退出登录
                printf("管理员已退出登录\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
                // 在这里可以添加一个等待按键继续的提示
                printf("\n按 Enter 键继续...");
                scanf("%*[^\n]");
                getchar();
        }
        
        // 如果不是退出选项，确保输入缓冲区是干净的
        if (choice != 0 && choice != -1) { // choice != -1 是因为已经在无效输入时清理过了
            // 某些情况下可能已经清理过了，但为了确保一致性，这里再检查一次
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        
    } while (choice != 0);
}

// 欢迎界面
void welcomeScreen() {
    //system("clear");
    
    printf("\n\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                                                          ║\n");
    printf("║                 欢迎使用菜鸟驿站管理系统                 ║\n");
    printf("║                                                          ║\n");
    printf("║                   Welcome to CaiNiao                     ║\n");
    printf("║             Station Management System v1.0               ║\n");
    printf("║                                                          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    printf("           按 Enter 键继续...");
    getchar(); // 等待用户按键
}

// 登录界面
int loginInterface(User** user_head, Admin* admin_data, User** current_user) {
    int choice;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    
    do {
        printf("\n");
        printf("╔══════════════════════════════════════════╗\n");
        printf("║               登录系统                   ║\n");
        printf("╠══════════════════════════════════════════╣\n");
        printf("║ 1. 用户登录                              ║\n");
        printf("║ 2. 管理员登录                            ║\n");
        printf("║ 3. 注册新用户                            ║\n");
        printf("║ 0. 退出系统                              ║\n");
        printf("╚══════════════════════════════════════════╝\n");
        printf("请选择操作 [0-3]: ");

        if (scanf("%d", &choice) != 1) {
            // 清空输入缓冲区
            while (getchar() != '\n');
            printf("无效的输入，请输入一个数字\n");
            continue;  // 跳过当前循环的剩余部分，重新开始
        }
        
        switch (choice) {
            case 1: // 用户登录
                printf("\n=== 用户登录 ===\n");
                printf("请输入用户名: ");
                scanf("%s", username);
                printf("请输入密码: ");
                scanf("%s", password);
                
                *current_user = userLogin(username, password, *user_head);
                if (*current_user != NULL) {
                    printf("登录成功！欢迎回来，%s\n", (*current_user)->username);
                    return 1; // 用户登录成功
                } else {
                    printf("登录失败：用户名或密码错误\n");
                }
                break;
                
            case 2: // 管理员登录
                printf("\n=== 管理员登录 ===\n");
                printf("请输入管理员用户名: ");
                scanf("%s", username);
                printf("请输入密码: ");
                scanf("%s", password);
                
                if (adminLogin(username, password, admin_data)) {
                    printf("管理员登录成功！\n");
                    return 2; // 管理员登录成功
                } else {
                    printf("登录失败：管理员用户名或密码错误\n");
                }
                break;
                
            case 3: // 注册新用户
                printf("\n=== 注册新用户 ===\n");
                printf("请输入用户名: ");
                scanf("%s", username);
                printf("请输入手机号: ");
                char phone_number[PHONE_NUMBER_LEN];
                scanf("%s", phone_number);
                printf("请输入密码: ");
                scanf("%s", password);
                
                int pay_method, settle_method;
                printf("请选择支付方式 (1-现金, 2-微信, 3-支付宝, 4-其他): ");
                scanf("%d", &pay_method);
                printf("请选择结算方式 (1-一件一结, 2-月付): ");
                scanf("%d", &settle_method);
                
                if (registerUser(username, phone_number, password, pay_method, settle_method, user_head)) {
                    printf("用户注册成功！请登录\n");
                } else {
                    printf("注册失败：用户名可能已存在\n");
                }
                break;
                
            case 0: // 退出系统
                printf("感谢使用菜鸟驿站管理系统，再见！\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
    } while (choice != 0 && choice != 1 && choice != 2);
    
    return choice == 0 ? 0 : -1; // 0表示退出，-1表示其他情况
}

// 包裹管理菜单实现 
void packageManagementMenu(Package** head, System* system_data, User* user_head) {
    int choice;
    char tracking_number[TRACKING_NUM_LEN];
    char user_phone[PHONE_NUMBER_LEN];
    char filename[100];
    int status;
    int filter_status = 0;
    
    do {
        printf("\n=== 包裹管理菜单 ===\n");
        printf("1. 添加新包裹\n");
        printf("2. 查找包裹\n");
        printf("3. 更新包裹状态\n");
        printf("4. 删除包裹\n");
        printf("5. 显示所有包裹\n");
        printf("6. 按状态筛选包裹\n");
        printf("0. 返回上级菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 添加新包裹
                processPackageInbound(head, system_data, user_head);
                break;
                
            case 2: // 查找包裹
                printf("\n--- 查找包裹 ---\n");
                printf("1. 按单号查找\n");
                printf("2. 按手机号查找\n");
                printf("请选择查找方式: ");
                int search_method;
                scanf("%d", &search_method);
                
                Package* found_package = NULL;
                if (search_method == 1) {
                    printf("请输入快递单号: ");
                    scanf("%s", tracking_number);
                    found_package = findPackageByTrackingNumber(tracking_number, *head);
                    
                    if (found_package != NULL) {
                        displayPackageDetails(found_package);
                    } else {
                        printf("未找到单号为 %s 的包裹\n", tracking_number);
                    }
                } else if (search_method == 2) {
                    printf("请输入手机号: ");
                    scanf("%s", user_phone);
                    
                    // 显示所有匹配的包裹
                    int count = 0;
                    Package* current = *head;
                    
                    while (current != NULL) {
                        if (strcmp(current->user_phone_number, user_phone) == 0) {
                            displayPackageDetails(current);
                            count++;
                        }
                        current = current->next;
                    }
                    
                    if (count == 0) {
                        printf("未找到与手机号 %s 关联的包裹\n", user_phone);
                    } else {
                        printf("共找到 %d 个包裹\n", count);
                    }
                } else {
                    printf("无效的选择\n");
                }
                break;
                
            case 3: // 更新包裹状态
                printf("\n--- 更新包裹状态 ---\n");
                printf("请输入包裹单号: ");
                scanf("%s", tracking_number);
                
                printf("请选择新状态:\n");
                printf("1. 入库\n");
                printf("2. 待取\n");
                printf("3. 已取\n");
                printf("4. 拒收\n");
                printf("5. 退回\n");
                printf("请选择: ");
                scanf("%d", &status);
                
                if (status >= 1 && status <= 5) {
                    updatePackageStatus(tracking_number, status, *head);
                } else {
                    printf("无效的状态选择\n");
                }
                break;
                
            case 4: // 删除包裹
                printf("\n--- 删除包裹 ---\n");
                printf("请输入要删除的包裹单号: ");
                scanf("%s", tracking_number);
                
                // 确认删除
                char confirm;
                printf("确定要删除包裹 %s? (Y/N): ", tracking_number);
                scanf(" %c", &confirm);
                
                if (confirm == 'Y' || confirm == 'y') {
                    Package* package = findPackageByTrackingNumber(tracking_number, *head);
                    if (package != NULL) {
                        removePackage(head, tracking_number);
                        if (system_data->package_int_storage_count > 0) {
                            system_data->package_int_storage_count--;
                        }
                    } else {
                        printf("未找到单号为 %s 的包裹\n", tracking_number);
                    }
                } else {
                    printf("取消删除操作\n");
                }
                break;
                
            case 5: // 显示所有包裹
                printf("\n所有包裹列表：\n");
                int count = 0;
                Package* current = *head;
                
                if (current == NULL) {
                    printf("系统中没有包裹记录\n");
                    break;
                }
                
                while (current != NULL) {
                    displayPackageDetails(current);
                    count++;
                    current = current->next;
                }
                
                printf("共 %d 个包裹\n", count);
                break;
                
            case 6: // 按状态筛选包裹
                printf("\n--- 按状态筛选包裹 ---\n");
                printf("请选择包裹状态:\n");
                printf("1. 入库\n");
                printf("2. 待取\n");
                printf("3. 已取\n");
                printf("4. 拒收\n");
                printf("5. 退回\n");
                printf("请选择: ");
                scanf("%d", &filter_status);
                
                if (filter_status < 1 || filter_status > 5) {
                    printf("无效的状态选择\n");
                    break;
                }
                
                printf("\n状态为 %d 的包裹列表：\n", filter_status);
                count = 0;
                current = *head;
                
                while (current != NULL) {
                    if (current->status == filter_status) {
                        displayPackageDetails(current);
                        count++;
                    }
                    current = current->next;
                }
                
                if (count == 0) {
                    printf("没有状态为 %d 的包裹\n", filter_status);
                } else {
                    printf("共 %d 个包裹\n", count);
                }
                break;
                
            
                
            
            case 0: // 返回上级菜单
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
        
        if (choice != 0) {
            printf("\n按 Enter 键继续...");
            getchar(); // 消耗之前输入的换行符
            getchar(); // 等待用户按 Enter
        }
        
    } while (choice != 0);
}