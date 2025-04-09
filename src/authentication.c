//认证模块
#include "../include/station.h"

//用户登录验证
User* userLogin(const char* username, const char* password, const User* user_head){
    const User* current=user_head;
    while(current!=NULL){
        if(strcmp(current->username,username)==0&&strcmp(current->password,password)==0){
            printf("用户登录成功！\n");
            return (User*)current;
        }
        current=current->next;
    }
    printf("用户名或密码错误！\n");
    return NULL;
}

//管理员登录验证
int adminLogin(const char* username, const char* password, const Admin* admin_data){
    if (admin_data == NULL) {
        return 0;
    }
    return (strcmp(admin_data->username, username) == 0 
        && strcmp(admin_data->password, password) == 0);
}

//用户注册函数
User* createUser(const char* username, const char* phone_number, const char* password,
    int pay_method, int settle_method)
int registerUser(const char* username, const char* phone_number, const char* password,
    int pay_method, int settle_method, User** user_head) {
    //检查用户名是否已存在
    User* current = *user_head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return 0;
        }
        current = current->next;
    }
    //创建新用户节点
    User* new_user = (User*)malloc(sizeof(user));
    if (user == NULL) {
        printf("内存分配失败\n");
        return 0;
    }

    strcpy(new_user->username, username);
    strcpy(new_user->phone_number, phone_number);
    strcpy(new_user->password, password);
    new_user->pay_method = (payment_method)pay_method;
    new_user->settle_method = (settlement_method)settle_method;
    new_user->package_sent_count = 0;
    new_user->package_received_count = 0;
    new_user->next = *user_head;
    *user_head = new_user;

    return 1;//注册成功
}

//密码修改函数
int changePassword(const char* username, const char* old_password,
    const char* new_password, User* user_head, Admin* admin_data) {
    if (strcmp(admin_data->username, username == 0)) {
        if (strcmp(admin_data->password,old_password) != 0) {
            return 0
        }
        strcpy(admin_data->password, new_password);
        saveAdmin(admin_data);
        return 1;
    }
    User* user = findUserByUsername(username, user_head);
    if (user == NULL) {
        return0;
    }
    if (strcmp(user->password, old_password) != 0) {
        return 0;
    }
    if (updateUserPassword(user, old_password, new_password)) {
        saveUsers(user_head);
        return 1;
    }
    return 0;
}
