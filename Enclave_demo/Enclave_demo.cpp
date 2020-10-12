#include "Enclave_demo_t.h"
#include "sgx_trts.h"
#include <cstring>

void ecall_function(char* str, size_t len)
{
	char* secret = "I am enclave !"; // Наша секретная фраза

	memcpy(str, secret, len); //Копируем секрет по ссылке, которую получили

	ocall_function(secret); //Вызов OCALL-функции
}
