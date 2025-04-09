//�ͷ��ڴ漰ϵͳ��ʼ��ģ��
#include "../include/station.h"

//�ͷŰ��������ڴ�
void freePackageList(Package* head) {
	Package* current = head;
	Package* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}

//�ͷ��û������ڴ�
void freeUserList(User* head) {
	User* current = head;
	User* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}

//��ʼ��ϵͳ����
System* initializeSyetem() {
	return loadSystemData();
}