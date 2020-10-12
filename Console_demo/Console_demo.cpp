#define ENCLAVE_FILE "Enclave.signed.dll" //Библиотека, через которую осуществляется подпись анклава
#define BUFFER_LEN 256 //Размер буфера данных, которые мы отправляем в анклав

#include "sgx_urts.h"  //Базовый заголовочный файл, в котором реализованы функции управления анклавом
#include "Enclave_demo_u.h" //Подключение автоматически сгенерированного файла
#include "stdio.h"

void ocall_function(char* buf) //OCALL функция для вывода текстовой строки - секрета из анклава. Вызов из анклава.
{
	printf("+++ OCALL output: %s\n", buf);
}

static sgx_enclave_id_t enclave_id = 0; // id анклава, в проекте может быть несколько анклавов, каждый со своим id
static sgx_status_t enclave_ret = SGX_SUCCESS; //Статус выполнения операции
static sgx_launch_token_t enclave_token = { 0 }; //Массив нициализации токена запуска для анклава
static int enclave_token_updated = 0; // Флаг, что токен запуска не был изменен 
static char buffer[BUFFER_LEN]; // Буфер, в который будет записан секрет из анклава

int main()
{
	sgx_status_t ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &enclave_token, &enclave_token_updated, &enclave_id, NULL); //Функция создания анклава

	if (ret != SGX_SUCCESS)
	{
		printf("+++ Failed to create enclave: %x\n", ret);
		return 0;
	}

	ecall_function(enclave_id, buffer, BUFFER_LEN); //Вызов ECALL функции 

	printf("\n+++ ECALL Output: %s\n", buffer); //Вывод полученного секрета

	system("pause");
}