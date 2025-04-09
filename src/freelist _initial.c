//释放内存及系统初始化模块
#include "../include/station.h"

//释放包裹链表内存
void freePackageList(Package* head) {
	Package* current = head;
	Package* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}

//释放用户链表内存
void freeUserList(User* head) {
	User* current = head;
	User* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}

//初始化系统数据
System* initializeSyetem() {
	return loadSystemData();
}