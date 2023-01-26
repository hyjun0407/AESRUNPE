#include <string>
#include <windows.h>
#include "sk.h"
using namespace std;

bool hijackCmdline = false;
char* sz_masqCmd_Ansi = NULL, *sz_masqCmd_ArgvAnsi[100] = {  };
wchar_t* sz_masqCmd_Widh = NULL, *sz_masqCmd_ArgvWidh[100] = { };
int int_masqCmd_Argc = 0;
LPWSTR hookGetCommandLineW() { return sz_masqCmd_Widh; }
LPSTR hookGetCommandLineA() { return sz_masqCmd_Ansi;  }

int __wgetmainargs(int* _Argc, wchar_t*** _Argv, wchar_t*** _Env, int _useless_, void* _useless) {
	*_Argc = int_masqCmd_Argc;
	*_Argv = (wchar_t **)sz_masqCmd_ArgvWidh;
	return 0;
}
int __getmainargs(int* _Argc, char*** _Argv, char*** _Env, int _useless_, void* _useless) {
	*_Argc = int_masqCmd_Argc;
	*_Argv = (char **)sz_masqCmd_ArgvAnsi;
	return 0;
}


bool fixIAT(PVOID modulePtr)
{
	IMAGE_DATA_DIRECTORY *importsDir = getPeDir(modulePtr, IMAGE_DIRECTORY_ENTRY_IMPORT);
	if (importsDir == NULL) return false;

	size_t maxSize = importsDir->Size;
	size_t impAddr = importsDir->VirtualAddress;

	IMAGE_IMPORT_DESCRIPTOR* lib_desc = NULL;
	size_t parsedSize = 0;

	for (; parsedSize < maxSize; parsedSize += sizeof(IMAGE_IMPORT_DESCRIPTOR)) {
		lib_desc = (IMAGE_IMPORT_DESCRIPTOR*)(impAddr + parsedSize + (ULONG_PTR)modulePtr);

		if (lib_desc->OriginalFirstThunk == NULL && lib_desc->FirstThunk == NULL) break;
		LPSTR lib_name = (LPSTR)((ULONGLONG)modulePtr + lib_desc->Name);

		size_t call_via = lib_desc->FirstThunk;
		size_t thunk_addr = lib_desc->OriginalFirstThunk;
		if (thunk_addr == NULL) thunk_addr = lib_desc->FirstThunk;

		size_t offsetField = 0;
		size_t offsetThunk = 0;
		while (true)
		{
			IMAGE_THUNK_DATA* fieldThunk = (IMAGE_THUNK_DATA*)(size_t(modulePtr) + offsetField + call_via);
			IMAGE_THUNK_DATA* orginThunk = (IMAGE_THUNK_DATA*)(size_t(modulePtr) + offsetThunk + thunk_addr);

			if (orginThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32 || orginThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64) // check if using ordinal (both x86 && x64)
            {
                size_t addr = (size_t)GetProcAddress(LoadLibraryA(lib_name), (char *)(orginThunk->u1.Ordinal & 0xFFFF));
                fieldThunk->u1.Function = addr;
            }
			
			if (fieldThunk->u1.Function == NULL) break;

			if (fieldThunk->u1.Function == orginThunk->u1.Function) {
				
				PIMAGE_IMPORT_BY_NAME by_name = (PIMAGE_IMPORT_BY_NAME)(size_t(modulePtr) + orginThunk->u1.AddressOfData);

				LPSTR func_name = (LPSTR)by_name->Name;
				size_t addr = (size_t)GetProcAddress(LoadLibraryA(lib_name), func_name);
				auto coma = skCrypt("GetCommandLineA");
				auto comaw = skCrypt("GetCommandLineW");
				auto wget = skCrypt("__wgetmainargs");
				auto getm = skCrypt("__getmainargs");
				if (hijackCmdline && strcmpi(func_name, coma) == 0)
					fieldThunk->u1.Function = (size_t)hookGetCommandLineA;
				else if (hijackCmdline && strcmpi(func_name, comaw) == 0)
					fieldThunk->u1.Function = (size_t)hookGetCommandLineW;
				else if (hijackCmdline && strcmpi(func_name, wget) == 0)
					fieldThunk->u1.Function = (size_t)__wgetmainargs;
				else if (hijackCmdline && strcmpi(func_name, getm) == 0)
					fieldThunk->u1.Function = (size_t)__getmainargs;
				else
					fieldThunk->u1.Function = addr;
				coma.encrypt();
				comaw.encrypt();
				wget.encrypt();
				getm.encrypt();

			}
			offsetField += sizeof(IMAGE_THUNK_DATA);
			offsetThunk += sizeof(IMAGE_THUNK_DATA);
		}
	}
	return true;
}
