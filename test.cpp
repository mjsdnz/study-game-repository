
#include <iostream>

using namespace std;
#define BYTE unsigned char
#define UINT unsigned int

int main(int argc, char* argv[])
{

	BYTE szCPU[16] = { 0 }; //定义存放CPU类型的数组
	UINT uCPUID = 0U;       //定义存放CPU ID的数组
	_asm                     //开始执行汇编
	{
		mov eax, 0 //获取CPU型号
			cpuid
			mov dword ptr szCPU[0], ebx
			mov dword ptr szCPU[4], edx
			mov dword ptr szCPU[8], ecx
			mov eax, 1
			cpuid
			mov uCPUID, edx
	}
	cout << szCPU << endl;
	cout << uCPUID << endl;


	getchar();
	return 0;
}

