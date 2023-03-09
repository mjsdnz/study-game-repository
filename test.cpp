#include <stdio.h>
#include <iostream>
void main()
{
	unsigned long DBaseIndex, DFeInfo, DFeInfo2, DCPUBaseInfo;
	unsigned long DFeIndex, DCPUExInfo, i;
	unsigned long DOther[4], DTLB[4], DProceSN[2];
	char cCom[13];
	char cProStr[49];
	unsigned int j;

	_asm
	{
		xor eax, eax
		cpuid
			mov DBaseIndex, eax
			mov dword ptr cCom, ebx
			mov dword ptr cCom + 4, ecx //AMD CPU要把ecx改为edx
			mov dword ptr cCom + 8, edx //AMD CPU要把edx改为ecx

			mov eax, 1
			cpuid
			mov DCPUBaseInfo, eax
			mov DFeInfo, ebx
			mov DFeInfo2, edx

			mov eax, 0x80000000
			cpuid
			mov DFeIndex, eax

			mov eax, 0x80000001
			cpuid
			mov DCPUExInfo, eax

			mov eax, 0x80000002
			cpuid
			mov dword ptr cProStr, eax
			mov dword ptr cProStr + 4, ebx
			mov dword ptr cProStr + 8, ecx
			mov dword ptr cProStr + 12, edx

			mov eax, 0x80000003
			cpuid
			mov dword ptr cProStr + 16, eax
			mov dword ptr cProStr + 20, ebx
			mov dword ptr cProStr + 24, ecx
			mov dword ptr cProStr + 28, edx

			mov eax, 0x80000004
			cpuid
			mov dword ptr cProStr + 32, eax
			mov dword ptr cProStr + 36, ebx
			mov dword ptr cProStr + 40, ecx
			mov dword ptr cProStr + 44, edx
	}

	if (DBaseIndex >= 2)
	{
		_asm
		{
			mov eax, 2
			cpuid
				mov DTLB[0], eax
				mov DTLB[2], ebx
				mov DTLB[3], ecx
				mov DTLB[4], edx
		}
	}
	if (DBaseIndex == 3)
	{
		_asm
		{
			mov eax, 3
			cpuid
				mov DProceSN[0], ecx
				mov DProceSN[1], edx
		}
	}

	cCom[12] = '/0'; //加一个结尾符
	printf("CPU厂商:  %s\n", cCom);
	printf("CPU字串:  %s\n", cProStr);
	printf("CPU基本参数: Family:%X  Model:%X  Stepping ID:%X\n", (DCPUBaseInfo & 0x0F00) >> 8,
		(DCPUBaseInfo & 0xF0) >> 4, DCPUBaseInfo & 0xF);
	printf("CPU扩展参数: Family:%X  Model:%X  Stepping ID:%X\n", (DCPUExInfo & 0x0F00) >> 8,
		(DCPUExInfo & 0xF0) >> 4, DCPUExInfo & 0xF);

	printf("CPU字串索引: 0x%X\n", DFeInfo & 0xFF);
	printf("CLFLUSH线大小: 0x%X\n", (DFeInfo & 0xFF00) >> 8);
	printf("处理器APIC物理标号:0x%X\n", (DFeInfo & 0xF000) >> 24);
	if (DBaseIndex >= 2)
	{
		printf("CPU Cache & TLB Information: ");
		for (j = 0; j < 4; j++)
		{
			if (!(DTLB[j] & 0xFF)) printf("%.2X ", DTLB[j] & 0xFF);
			if (!((DTLB[j] & 0xFF) >> 8)) printf("%.2X ", (DTLB[j] & 0xFF00) >> 8);
			if (!((DTLB[j] & 0xFF0000) >> 16)) printf("%.2X ", (DTLB[j] & 0xFF0000) >> 16);
			if (!((DTLB[j] & 0xFF000000) >> 24)) printf("%.2X ", (DTLB[j] & 0xFF000000) >> 24);
		}
		printf("\n");
	}

	if (DBaseIndex == 3)
	{
		printf("CPU序列号是:%X%X\n", DProceSN[0], DProceSN[1]);
	}
	printf("FPU:  %d\t\t", DFeInfo2 & 0x00000001); //下面是调用某BLOG上面的代码,懒得写了 ^^
	printf("VME:  %d\t\t", (DFeInfo2 & 0x00000002) >> 1);
	printf("DE:  %d\n", (DFeInfo2 & 0x00000004) >> 2);
	printf("PSE:  %d\t\t", (DFeInfo2 & 0x00000008) >> 3);
	printf("TSC:  %d\t\t", (DFeInfo2 & 0x00000010) >> 4);
	printf("MSR:  %d\n", (DFeInfo2 & 0x00000020) >> 5);
	printf("PAE:  %d\t\t", (DFeInfo2 & 0x00000040) >> 6);
	printf("MCE:  %d\t\t", (DFeInfo2 & 0x00000080) >> 7);
	printf("CX8:  %d\n", (DFeInfo2 & 0x00000100) >> 8);
	printf("APIC:  %d\t", (DFeInfo2 & 0x00000200) >> 9);
	printf("SEP:  %d\t\t", (DFeInfo2 & 0x00000800) >> 11);
	printf("MTRR:  %d\n", (DFeInfo2 & 0x00001000) >> 12);
	printf("PGE:  %d\t\t", (DFeInfo2 & 0x00002000) >> 13);
	printf("MCA:  %d\t\t", (DFeInfo2 & 0x00004000) >> 14);
	printf("CMOV:  %d\n", (DFeInfo2 & 0x00008000) >> 15);
	printf("PAT:  %d\t\t", (DFeInfo2 & 0x00010000) >> 16);
	printf("PSE-36:  %d\t", (DFeInfo2 & 0x00020000) >> 17);
	printf("PSN:  %d\n", (DFeInfo2 & 0x00040000) >> 18);
	printf("CLFSN:  %d\t", (DFeInfo2 & 0x00080000) >> 19);
	printf("DS:  %d\t\t", (DFeInfo2 & 0x00200000) >> 21);
	printf("ACPI:  %d\n", (DFeInfo2 & 0x00400000) >> 22);
	printf("MMX:  %d\t\t", (DFeInfo2 & 0x00800000) >> 23);
	printf("FXSR:  %d\t", (DFeInfo2 & 0x01000000) >> 24);
	printf("SSE:  %d\n", (DFeInfo2 & 0x02000000) >> 25);
	printf("SSE2:  %d\t", (DFeInfo2 & 0x04000000) >> 26);
	printf("SS:  %d\t\t", (DFeInfo2 & 0x08000000) >> 27);
	printf("TM:  %d\n", (DFeInfo2 & 0x20000000) >> 29);

	printf("\n其它信息:\n");
	printf("----------------------------------------\n");
	printf("In \t\tEAX \t\tEBX \t\tECX \t\tEDX");
	for (i = 0x80000004; i <= DFeIndex; ++i)
	{
		DOther[0] = DOther[1] = DOther[2] = DOther[3] = 0;
		_asm
		{
			mov eax, i
			cpuid
				mov DOther[0], eax
				mov DOther[1], ebx
				mov DOther[2], ecx
				mov DOther[3], edx
		}
		printf("\n0x%.8X\t0x%.8X\t0x%.8X\t0x%.8X\t0x%.8X", i, DOther[0], DOther[1], DOther[2], DOther[3]);
	}
	printf("\n");
	system("pause");
}