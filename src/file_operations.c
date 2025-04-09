//文件读写模块
#include "../include/station.h"

//从文件加载系统数据
System* loadSystemData() {
	System* system = (System*)malloc(sizeof(System));
	if (system == NULL) {
		printf("内存分配失败\n");
		return NULL;
	}
	FILE* file = fopen("system_data.txt", "r");
	if (file == NULL) {
		//文件不存在，初始化默认值
		system->operating_funds = 0;
		system->total_revenue = 0;
		system->user_count = 0;
		system->total_packages = 0;
		system->package_int_storage_count = 0;
		return system;
	}
	fscanf(file, "%lf %lf %d %d %d",
		&system->operating_funds,
		&system->total_revenue,
		&system->user_count,
		&system->total_packages,
		&system->package_int_storage_count);
	fclose(file);
	return system;
}

//保存系统数据到文件
void saveSystemData(const System* system) {
	FILE* file = fopen("system_data.txt", "w");
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	fprintf(file, "%lf %lf %d %d %d",
		system->operating_funds,
		system->total_revenue,
		system->user_count,
		system->total_packages,
		system->package_int_storage_count);
	fclose(file);
}

//从文件加载包裹数据
Package* loadPackages() {
	Package* head = NULL;
	FILE* file = fopen("packages.txt", "r");
	if (file == NULL) {
		printf("无法打开文件\n");
		return head;
	}
	int temp_status, temp_is_insured;//临时未类型转换的变量
	while(!feof(file)) {
		Package* new_package = (Package*)malloc(sizeof(Package));
		if (new_package == NULL) {
			printf("内存分配失败\n");
			while (head != NULL) {//分配失败释放所有已分配的内存
				Package* temp = head;
				head = head->next;
				free(temp);
			}
			fclose(file);
			return head;
		}
		if (fscanf(file, "%s %s %s %lf %lf %d %d %lf %lf",
			&new_package->tracking_number, &new_package->user_phone_number,
			&new_package->pickup_code, &new_package->weight,
			&new_package->distance, &temp_status, &temp_is_insured,
			&new_package->insured_value,&new_package->cost)!= 9) {//读取数据不足九个可能是格式错误
			free(new_package);
			break;
		}
			new_package->status=(packagestatus)temp_status;//类型转换
			new_package->is_insured = (insurancestatus)temp_is_insured;
			new_package->next = NULL;
			addPackage(&head,new_package);
	}
	fclose(file);
	return head;
}

//保存包裹数据到文件
void savePackages(const Package* head) {
	FILE* file = fopen("packages.txt", "w");
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	const Package* current = head;
	while (current != NULL) {
		fprintf(file, "%s %s %s %lf %lf %d %d %lf %lf\n",
			current->tracking_number, current->user_phone_number,
			current->pickup_code, current->weight, current->distance,
			(int)current->status, (int)current->is_insured,
			current->insured_value, current->cost);
		current = current->next;
	}
	fclose(file);
}

//从文件加载用户数据
User* loadUsers() {
	User* head = NULL;
	FILE* file = fopen("users.txt", "r");
	if (file == NULL) {
		printf("无法打开文件\n");
		return head;
	}
	char username[USERNAME_LEN];
	char phone_number[PHONE_NUMBER_LEN];
	char password[PASSWORD_LEN];
	int pay_method;
	int settle_method;
	int package_sent_count;
	int package_received_count;
	while (fscanf(file, "%s %s %s %d %d %d %d",
		username, phone_number, password, pay_method, settle_method,
		package_sent_count, package_received_count) != EOF) {
		User* new_user = createUser(username, phone_number, password,pay_method, settle_method);
		if (new_user == NULL) {//内存分配失败释放所有已分配内存
			printf("内存分配失败\n");
			while (head != NULL) {
				User* temp = head;
				head = head->next;
				free(temp);
			}
			fclose(file);
			return NULL;

		}
		new_user->package_sent_count = package_sent_count;
		new_user->package_received_count = package_received_count;
		addUser(&head, new_user);
	}
	fclose(file);
	return head;
}

//保存用户数据到文件
void saveUsers(const User* head) {
	FILE* file = fopen("users.txt", "w");
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	const User* current = head;
	while (current != NULL) {
		fprintf(file, "%s %s %s %d %d %d %d\n",
			current->username, current->phone_number,
			current->password, current->pay_method,
			current->settle_method, current->package_sent_count,
			current->package_received_count);
		current = current->next;
	}
	fclose(file);
}

//从文件加载管理员数据
Admin* loadAdmin() {
	Admin* admin = (Admin*)malloc(sizeof(Admin));
	if (admin == NULL) {
		printf("内存分配失败\n");
		return NULL;
	}
	FILE* file = fopen("admin.txt", "r");
	if (file == NULL) {//文件不存在，初始化默认值
		strcpy(admin->username, "admin");
		strcpy(admin->password, "admin");
		return admin;
	}
	fscanf(file, "%s %s", admin->username, admin->password);
	fclose(file);
	return admin;
}

//保存管理员数据到文件
void saveAdmin(const Admin* admin) {
	FILE* file = fopen("admin.txt", "w");
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}
	fprintf(file, "%s %s", admin->username, admin->password);
	fclose(file);
}
