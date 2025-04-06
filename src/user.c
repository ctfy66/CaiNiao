//用户管理模块
//created by ctfy 

#include "../include/station.h"

// 创建新用户
User* createUser(const char* username, const char* phone_number, const char* password, int pay_method, int settle_method) {
    // 参数有效性检查
    if (username == NULL || phone_number == NULL || password == NULL) {
        printf("错误：用户信息不能为空\n");
        return NULL;
    }
    
    // 检查用户名长度
    if (strlen(username) >= USERNAME_LEN) {
        printf("错误：用户名过长，最大长度为%d\n", USERNAME_LEN - 1);
        return NULL;
    }
    
    // 检查手机号长度
    if (strlen(phone_number) >= PHONE_NUMBER_LEN) {
        printf("错误：手机号过长，最大长度为%d\n", PHONE_NUMBER_LEN - 1);
        return NULL;
    }
    
    // 检查密码长度
    if (strlen(password) >= PASSWORD_LEN) {
        printf("错误：密码过长，最大长度为%d\n", PASSWORD_LEN - 1);
        return NULL;
    }
    
    // 检查支付方式是否有效
    if (pay_method < PAY_CASH || pay_method > PAY_OTHER) {
        printf("警告：无效的支付方式，已设置为默认值（现金）\n");
        pay_method = PAY_CASH;
    }
    
    // 检查结算方式是否有效
    if (settle_method < SETTLE_PER_ITEM || settle_method > SETTLE_MONTHLY) {
        printf("警告：无效的结算方式，已设置为默认值（一件一结）\n");
        settle_method = SETTLE_PER_ITEM;
    }
    
    // 分配内存
    User* new_user = (User*)malloc(sizeof(User));
    if (new_user == NULL) {
        printf("错误：内存分配失败\n");
        return NULL;
    }
    
    // 初始化用户信息
    strcpy(new_user->username, username);
    strcpy(new_user->phone_number, phone_number);
    strcpy(new_user->password, password);
    new_user->pay_method = (payment_method)pay_method;
    new_user->settle_method = (settlement_method)settle_method;
    new_user->package_sent_count = 0;
    new_user->package_received_count = 0;
    new_user->next = NULL;
    
    return new_user;
}

// 添加用户到链表
void addUser(User** head, User* new_user) {
    // 参数有效性检查
    if (head == NULL || new_user == NULL) {
        printf("错误：无效的参数\n");
        return;
    }
    
    // 如果链表为空，新用户成为头节点
    if (*head == NULL) {
        *head = new_user;
        new_user->next = NULL;
        printf("用户 '%s' 已成功添加到系统\n", new_user->username);
        return;
    }
    
    // 检查是否存在相同用户名或手机号
    User* current = *head;
    while (current != NULL) {
        if (strcmp(current->username, new_user->username) == 0) {
            printf("错误：用户名 '%s' 已存在\n", new_user->username);
            free(new_user); // 释放新用户内存以避免内存泄漏
            return;
        }
        
        if (strcmp(current->phone_number, new_user->phone_number) == 0) {
            printf("错误：手机号 '%s' 已被注册\n", new_user->phone_number);
            free(new_user); // 释放新用户内存
            return;
        }
        
        // 如果到达链表末尾，则退出循环
        if (current->next == NULL) {
            break;
        }
        
        current = current->next;
    }
    
    // 将新用户添加到链表末尾
    current->next = new_user;
    new_user->next = NULL;
    printf("用户 '%s' 已成功添加到系统\n", new_user->username);
}

// 通过手机号查找用户
User* findUserByPhone(const char* phone_number, const User* head) {
    // 参数有效性检查
    if (phone_number == NULL || head == NULL) {
        return NULL;
    }
    
    // 遍历链表查找匹配的手机号
    const User* current = head;
    while (current != NULL) {
        if (strcmp(current->phone_number, phone_number) == 0) {
            return (User*)current; // 返回匹配的用户（去除const限定符）
        }
        current = current->next;
    }
    
    return NULL; // 未找到匹配的用户
}

// 通过用户名查找用户
User* findUserByUsername(const char* username, const User* head) {
    // 参数有效性检查
    if (username == NULL || head == NULL) {
        return NULL;
    }
    
    // 遍历链表查找匹配的用户名
    const User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return (User*)current; // 返回匹配的用户（去除const限定符）
        }
        current = current->next;
    }
    
    return NULL; // 未找到匹配的用户
}

// 更新用户信息
void updateUser(User* user, int new_pay_method, int new_settle_method) {
    // 参数有效性检查
    if (user == NULL) {
        printf("错误：无效的用户指针\n");
        return;
    }
    
    // 检查支付方式是否有效
    if (new_pay_method < PAY_CASH || new_pay_method > PAY_OTHER) {
        printf("警告：无效的支付方式，保持原有设置\n");
    } else {
        user->pay_method = (payment_method)new_pay_method;
        printf("支付方式已更新\n");
    }
    
    // 检查结算方式是否有效
    if (new_settle_method < SETTLE_PER_ITEM || new_settle_method > SETTLE_MONTHLY) {
        printf("警告：无效的结算方式，保持原有设置\n");
    } else {
        user->settle_method = (settlement_method)new_settle_method;
        printf("结算方式已更新\n");
    }
}

// 从链表中移除用户
void removeUser(User** head, const char* username) {
    // 参数有效性检查
    if (head == NULL || *head == NULL || username == NULL) {
        printf("错误：无效的参数\n");
        return;
    }
    
    User* current = *head;
    User* prev = NULL;
    
    // 如果头节点是要删除的用户
    if (strcmp(current->username, username) == 0) {
        *head = current->next;
        printf("用户 '%s' 已从系统中移除\n", username);
        free(current);
        return;
    }
    
    // 查找要删除的用户
    while (current != NULL && strcmp(current->username, username) != 0) {
        prev = current;
        current = current->next;
    }
    
    // 如果找到了用户
    if (current != NULL) {
        prev->next = current->next;
        printf("用户 '%s' 已从系统中移除\n", username);
        free(current);
    } else {
        printf("未找到用户名为 '%s' 的用户\n", username);
    }
}

// 显示用户详细信息
void displayUser(const User* user) {
    if (user == NULL) {
        printf("错误：无效的用户指针\n");
        return;
    }
    
    printf("\n=== 用户详细信息 ===\n");
    printf("用户名: %s\n", user->username);
    printf("手机号: %s\n", user->phone_number);
    
    // 显示支付方式
    printf("支付方式: ");
    switch (user->pay_method) {
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
            break;
    }
    
    // 显示结算方式
    printf("结算方式: ");
    switch (user->settle_method) {
        case SETTLE_PER_ITEM:
            printf("一件一结\n");
            break;
        case SETTLE_MONTHLY:
            printf("月付\n");
            break;
        default:
            printf("未知\n");
            break;
    }
    
    printf("发送包裹数量: %d\n", user->package_sent_count);
    printf("接收包裹数量: %d\n", user->package_received_count);
    printf("======================\n");
}

// 列出所有用户
void listAllUsers(const User* head) {
    if (head == NULL) {
        printf("系统中没有注册用户\n");
        return;
    }
    
    printf("\n=== 系统用户列表 ===\n");
    printf("%-20s %-15s %-10s %-10s\n", "用户名", "手机号", "发送包裹", "接收包裹");
    printf("--------------------------------------------------------------\n");
    
    int count = 0;
    const User* current = head;
    while (current != NULL) {
        printf("%-20s %-15s %-10d %-10d\n", 
               current->username, 
               current->phone_number, 
               current->package_sent_count, 
               current->package_received_count);
        
        current = current->next;
        count++;
    }
    
    printf("--------------------------------------------------------------\n");
    printf("总用户数: %d\n", count);
}

// 更新用户密码
int updateUserPassword(User* user, const char* old_password, const char* new_password) {
    // 参数有效性检查
    if (user == NULL || old_password == NULL || new_password == NULL) {
        printf("错误：无效的参数\n");
        return 0;
    }
    
    // 验证旧密码
    if (strcmp(user->password, old_password) != 0) {
        printf("错误：旧密码不正确\n");
        return 0;
    }
    
    // 检查新密码长度
    if (strlen(new_password) >= PASSWORD_LEN) {
        printf("错误：新密码过长，最大长度为%d\n", PASSWORD_LEN - 1);
        return 0;
    }
    
    // 更新密码
    strcpy(user->password, new_password);
    printf("密码已成功更新\n");
    return 1;
}

// 搜索用户
void searchUsers(const User* head, const char* search_term) {
    if (head == NULL || search_term == NULL) {
        printf("错误：无效的参数\n");
        return;
    }
    
    printf("\n=== 搜索结果 ===\n");
    printf("%-20s %-15s %-10s %-10s\n", "用户名", "手机号", "发送包裹", "接收包裹");
    printf("--------------------------------------------------------------\n");
    
    int count = 0;
    const User* current = head;
    while (current != NULL) {
        // 在用户名和手机号中搜索
        if (strstr(current->username, search_term) != NULL || 
            strstr(current->phone_number, search_term) != NULL) {
            
            printf("%-20s %-15s %-10d %-10d\n", 
                   current->username, 
                   current->phone_number, 
                   current->package_sent_count, 
                   current->package_received_count);
            
            count++;
        }
        
        current = current->next;
    }
    
    printf("--------------------------------------------------------------\n");
    printf("找到 %d 个匹配用户\n", count);
    
    if (count == 0) {
        printf("未找到匹配 '%s' 的用户\n", search_term);
    }
}

// 用户统计信息
void generateUserStatistics(const User* head) {
    if (head == NULL) {
        printf("系统中没有注册用户\n");
        return;
    }
    
    int total_users = 0;
    int active_users = 0; // 有包裹记录的用户
    int total_sent_packages = 0;
    int total_received_packages = 0;
    
    payment_method most_popular_payment = PAY_CASH;
    int payment_counts[4] = {0}; // 对应四种支付方式的计数
    
    settlement_method most_popular_settlement = SETTLE_PER_ITEM;
    int settlement_counts[2] = {0}; // 对应两种结算方式的计数
    
    // 统计数据
    const User* current = head;
    while (current != NULL) {
        total_users++;
        
        // 计算活跃用户
        if (current->package_sent_count > 0 || current->package_received_count > 0) {
            active_users++;
        }
        
        // 统计包裹数
        total_sent_packages += current->package_sent_count;
        total_received_packages += current->package_received_count;
        
        // 统计支付方式
        payment_counts[current->pay_method - 1]++;
        
        // 统计结算方式
        settlement_counts[current->settle_method - 1]++;
        
        current = current->next;
    }
    
    // 确定最受欢迎的支付和结算方式
    int max_payment = payment_counts[0];
    for (int i = 1; i < 4; i++) {
        if (payment_counts[i] > max_payment) {
            max_payment = payment_counts[i];
            most_popular_payment = (payment_method)(i + 1);
        }
    }
    
    int max_settlement = settlement_counts[0];
    for (int i = 1; i < 2; i++) {
        if (settlement_counts[i] > max_settlement) {
            max_settlement = settlement_counts[i];
            most_popular_settlement = (settlement_method)(i + 1);
        }
    }
    
    // 显示统计结果
    printf("\n=== 用户统计信息 ===\n");
    printf("总用户数: %d\n", total_users);
    printf("活跃用户数: %d (%.1f%%)\n", active_users, 
           total_users > 0 ? (float)active_users / total_users * 100 : 0);
    printf("总发送包裹数: %d\n", total_sent_packages);
    printf("总接收包裹数: %d\n", total_received_packages);
    
    printf("\n支付方式统计:\n");
    printf("现金: %d 用户 (%.1f%%)\n", payment_counts[0], 
           total_users > 0 ? (float)payment_counts[0] / total_users * 100 : 0);
    printf("微信: %d 用户 (%.1f%%)\n", payment_counts[1], 
           total_users > 0 ? (float)payment_counts[1] / total_users * 100 : 0);
    printf("支付宝: %d 用户 (%.1f%%)\n", payment_counts[2], 
           total_users > 0 ? (float)payment_counts[2] / total_users * 100 : 0);
    printf("其他: %d 用户 (%.1f%%)\n", payment_counts[3], 
           total_users > 0 ? (float)payment_counts[3] / total_users * 100 : 0);
    
    printf("最受欢迎的支付方式: ");
    switch (most_popular_payment) {
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
    }
    
    printf("\n结算方式统计:\n");
    printf("一件一结: %d 用户 (%.1f%%)\n", settlement_counts[0], 
           total_users > 0 ? (float)settlement_counts[0] / total_users * 100 : 0);
    printf("月付: %d 用户 (%.1f%%)\n", settlement_counts[1], 
           total_users > 0 ? (float)settlement_counts[1] / total_users * 100 : 0);
    
    printf("最受欢迎的结算方式: ");
    switch (most_popular_settlement) {
        case SETTLE_PER_ITEM:
            printf("一件一结\n");
            break;
        case SETTLE_MONTHLY:
            printf("月付\n");
            break;
    }
    
    printf("========================\n");
}

// 用户管理菜单
void userManagementMenu(User** head, System* system_data) {
    int choice;
    char username[USERNAME_LEN];
    char phone_number[PHONE_NUMBER_LEN];
    char password[PASSWORD_LEN];
    char search_term[USERNAME_LEN];
    int pay_method, settle_method;
    
    do {
        printf("\n=== 用户管理菜单 ===\n");
        printf("1. 添加新用户\n");
        printf("2. 查找用户\n");
        printf("3. 更新用户信息\n");
        printf("4. 删除用户\n");
        printf("5. 显示所有用户\n");
        printf("6. 搜索用户\n");
        printf("7. 用户统计信息\n");
        printf("0. 返回上级菜单\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // 添加新用户
                printf("\n--- 添加新用户 ---\n");
                printf("请输入用户名: ");
                scanf("%s", username);
                printf("请输入手机号: ");
                scanf("%s", phone_number);
                printf("请输入密码: ");
                scanf("%s", password);
                printf("请选择支付方式 (1-现金, 2-微信, 3-支付宝, 4-其他): ");
                scanf("%d", &pay_method);
                printf("请选择结算方式 (1-一件一结, 2-月付): ");
                scanf("%d", &settle_method);
                
                User* new_user = createUser(username, phone_number, password, pay_method, settle_method);
                if (new_user != NULL) {
                    addUser(head, new_user);
                    if (*head != NULL && findUserByUsername(username, *head) != NULL) {
                        system_data->user_count++;
                    }
                }
                break;
                
            case 2: // 查找用户
                printf("\n--- 查找用户 ---\n");
                printf("1. 按用户名查找\n");
                printf("2. 按手机号查找\n");
                printf("请选择查找方式: ");
                int search_method;
                scanf("%d", &search_method);
                
                User* found_user = NULL;
                if (search_method == 1) {
                    printf("请输入用户名: ");
                    scanf("%s", username);
                    found_user = findUserByUsername(username, *head);
                } else if (search_method == 2) {
                    printf("请输入手机号: ");
                    scanf("%s", phone_number);
                    found_user = findUserByPhone(phone_number, *head);
                } else {
                    printf("无效的选择\n");
                    break;
                }
                
                if (found_user != NULL) {
                    displayUser(found_user);
                } else {
                    printf("未找到用户\n");
                }
                break;
                
            case 3: // 更新用户信息
                printf("\n--- 更新用户信息 ---\n");
                printf("请输入用户名: ");
                scanf("%s", username);
                
                User* user_to_update = findUserByUsername(username, *head);
                if (user_to_update != NULL) {
                    printf("当前支付方式: %d\n", user_to_update->pay_method);
                    printf("当前结算方式: %d\n", user_to_update->settle_method);
                    
                    printf("请输入新的支付方式 (1-现金, 2-微信, 3-支付宝, 4-其他): ");
                    scanf("%d", &pay_method);
                    printf("请输入新的结算方式 (1-一件一结, 2-月付): ");
                    scanf("%d", &settle_method);
                    
                    updateUser(user_to_update, pay_method, settle_method);
                    
                    // 添加更新密码选项
                    char change_password;
                    printf("是否更新密码? (Y/N): ");
                    scanf(" %c", &change_password);
                    
                    if (change_password == 'Y' || change_password == 'y') {
                        char old_password[PASSWORD_LEN];
                        char new_password[PASSWORD_LEN];
                        
                        printf("请输入旧密码: ");
                        scanf("%s", old_password);
                        printf("请输入新密码: ");
                        scanf("%s", new_password);
                        
                        updateUserPassword(user_to_update, old_password, new_password);
                    }
                } else {
                    printf("未找到用户 '%s'\n", username);
                }
                break;
                
            case 4: // 删除用户
                printf("\n--- 删除用户 ---\n");
                printf("请输入要删除的用户名: ");
                scanf("%s", username);
                
                // 确认删除
                char confirm;
                printf("确定要删除用户 '%s'? (Y/N): ", username);
                scanf(" %c", &confirm);
                
                if (confirm == 'Y' || confirm == 'y') {
                    // 检查用户是否存在
                    if (findUserByUsername(username, *head) != NULL) {
                        removeUser(head, username);
                        if (system_data->user_count > 0) {
                            system_data->user_count--;
                        }
                    } else {
                        printf("未找到用户 '%s'\n", username);
                    }
                } else {
                    printf("取消删除操作\n");
                }
                break;
                
            case 5: // 显示所有用户
                listAllUsers(*head);
                break;
                
            case 6: // 搜索用户
                printf("\n--- 搜索用户 ---\n");
                printf("请输入搜索关键词: ");
                scanf("%s", search_term);
                searchUsers(*head, search_term);
                break;
                
            case 7: // 用户统计信息
                generateUserStatistics(*head);
                break;
                
            case 0: // 返回上级菜单
                printf("返回上级菜单\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
        }
    } while (choice != 0);
}