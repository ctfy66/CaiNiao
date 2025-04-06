#ifndef STATION_H
#define STATION_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

//常量定义
#define MAX_PACKAGES 100      //最大包裹数
#define USERNAME_LEN 21       //最长用户名
#define PASSWORD_LEN 21       //最长密码长度
#define TRACKING_NUM_LEN 15   //最长单号
#define PHONE_NUMBER_LEN 12  //手机号长度+1
#define PICKUP_CODE_LEN 7         //取件码格式：一位大写字母+一位小写字母+四位数字

//支付方式
typedef enum {
    PAY_CASH = 1,               //现金
    PAY_WECHAT,             //微信
    PAY_ALIPAY,                 //支付宝
    PAY_OTHER                   //其他
}payment_method;

//结算方式
typedef enum {
    SETTLE_PER_ITEM = 1,
    SETTLE_MONTHLY
}settlement_method;

//包裹状态
typedef enum {
    STATUS_INSTOCK = 1,             //入库
    STATUS_PENDING_PICKUP,          //待取
    STATUS_PICKEDUP,                //已取
    STATUS_REJECTED,                //拒收
    STATUS_RETURNED,                //退回
}packagestatus;

//保价情况
typedef enum {
    INSURED_NO = 0,
    INSURED_YES = 1
}insurancestatus;

//包裹属性
typedef enum {
    ATTRIBUTE_NORMAL = 1,
    ATTRIBUTE_FRAGILE,
    ATTRIBUTE_REFRIGERATED,
    ATTRIBUTE_OVERSIZE,
    ATTRIBUTE_HIGHVALUE
}packageattribute;

//包裹信息链表节点
typedef struct Package {
    char tracking_number[TRACKING_NUM_LEN];     //单号
    char user_phone_number[PHONE_NUMBER_LEN];   //收件人手机号
    char pickup_code[PICKUP_CODE_LEN];          //取件码
    double weight;                              //重量
    double distance;                            //距离
    packagestatus status;                       //包裹状态
    insurancestatus is_insured;                 //是否保价
    double insured_value;                       //保价金额
    double cost;                                //费用
    struct Package* next;
}Package;

//用户信息链表节点
typedef struct User {
    char username[USERNAME_LEN];            //用户名
    char phone_number[PHONE_NUMBER_LEN];    //手机号
    char password[PASSWORD_LEN];            //密码
    payment_method pay_method;              //1.现金 2.微信 3.支付宝 4.其他
    settlement_method settle_method;        //1.一件一结 2.月付
    int package_sent_count;                 //发包裹数量
    int package_received_count;             //代取包裹数量
    struct User* next;
}User;

//管理员信息结构体
typedef struct Admin {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
}Admin;

//系统信息结构体
typedef struct System {
    double operating_funds;             //运营资金
    double total_revenue;               //总收入
    int user_count;                     //用户数
    int total_packages;                 //历史总包裹数
    int package_int_storage_count;      //库存包裹数
}System;

// 核心数据结构操作 (成员1)
System* loadSystemData();
void saveSystemData(const System* system);
Package* loadPackages();
void savePackages(const Package* head);
User* loadUsers();
void saveUsers(const User* head);
Admin* loadAdmin();
void saveAdmin(const Admin* admin);

// 内存管理函数 (成员1)
void freePackageList(Package* head);
void freeUserList(User* head);

// 初始化系统函数 (成员1)
System* initializeSystem();

// 认证模块 (成员1)
User* userLogin(const char* username, const char* password, const User* user_head);
int adminLogin(const char* username, const char* password, const Admin* admin_data);
int registerUser(const char* username, const char* phone_number, const char* password, int pay_method, int settle_method, User** user_head);
int changePassword(const char* username, const char* old_password, const char* new_password, User* user_head, Admin* admin_data);

// 包裹管理模块 (成员2)
Package* createPackage(const char* tracking_number, const char* user_phone_number, double weight, double distance, int is_insured, double insured_value);
void addPackage(Package** head, Package* new_package);
Package* findPackageByTrackingNumber(const char* tracking_number, const Package* head);
Package* findPackagesByPhone(const char* phone_number, const Package* head); // 返回匹配的第一个包裹，可根据需求修改为返回链表
void updatePackageStatus(const char* tracking_number, int new_status, Package* head);
void removePackage(Package** head, const char* tracking_number);

// 包裹业务逻辑 (成员2)
void generatePickupCode(char* pickup_code);
double calculatePackageCost(double weight, double distance, int is_insured, double insured_value, int attribute); // 增加包裹属性参数

// 用户管理模块 (成员2)
User* createUser(const char* username, const char* phone_number, const char* password, int pay_method, int settle_method);
void addUser(User** head, User* new_user);
User* findUserByPhone(const char* phone_number, const User* head);
User* findUserByUsername(const char* username, const User* head);
void updateUser(User* user, int new_pay_method, int new_settle_method);
void removeUser(User** head, const char* username);

// 业务流程模块 (成员2)
void processPackageInbound(Package** package_head, System* system_data, User* user_head);
void processPackageOutbound(Package** package_head, System* system_data);
void processSendPackage(Package** package_head, User** user_head, System* system_data);
void handleExceptions(int error_code, const char* message);

// 用户界面模块 (成员2)
void displayAdminMenu();
void displayUserMenu();
void displayPackageDetails(const Package* package);
void displayUserDetails(const User* user);
void displaySystemInfo(const System* system);

#endif