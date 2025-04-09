#include "../include/station.h"

int main() {

    // 初始化
    System* system_data = initializeSystem();
    Package* package_head = loadPackages();
    User* user_head = loadUsers();
    Admin* admin_data = loadAdmin();
    User* current_user = NULL;


    welcomeScreen();



    // 登录
    int login_result = loginInterface(&user_head, admin_data, &current_user);
    if (login_result == 1) {
        mainMenuInterface(current_user, &package_head, &user_head, system_data, admin_data);
    }
    else if (login_result == 2) {
        adminConsoleInterface(&package_head, &user_head, system_data, admin_data);
    }

    // 保存数据到文件
    saveSystemData(system_data);
    savePackages(package_head);
    saveUsers(user_head);
    saveAdmin(admin_data);

    // 释放内存
    freePackageList(package_head);
    freeUserList(user_head);
    free(system_data);
    free(admin_data);

    return 0;
}