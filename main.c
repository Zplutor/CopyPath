#include <Windows.h>
#include <Shlwapi.h>
#include <strsafe.h>

static DWORD SetStringToClipboard(LPCWSTR string);
static DWORD CopyStringToMemory(LPCWSTR string, int copied_length, HGLOBAL memory_handle);


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    int argument_count = 0;
    LPWSTR* arguments = CommandLineToArgvW(GetCommandLine(), &argument_count);
    if (argument_count < 3) {
        return ERROR_INVALID_PARAMETER;
    }

    BOOL name_only = FALSE;
    if (lstrcmp(arguments[1], L"-n") == 0) {
        name_only = TRUE;
    }
    else if (lstrcmp(arguments[1], L"-p") == 0) {
        name_only = FALSE;
    }
    else {
        return ERROR_INVALID_PARAMETER;
    }

    LPWSTR string_to_set = arguments[2];
    if (name_only) {
        string_to_set = PathFindFileName(string_to_set);
    }

    BOOL is_succeeded = OpenClipboard(NULL);
    if (!is_succeeded) {
        return GetLastError();
    }

    EmptyClipboard();
    DWORD error = SetStringToClipboard(string_to_set);
    CloseClipboard();

    return error;
}


static DWORD SetStringToClipboard(LPCWSTR string) {

    int string_length = lstrlen(string);
    int memory_size = (string_length + 1) * sizeof(wchar_t);

    HGLOBAL memory_handle = GlobalAlloc(GMEM_MOVEABLE, memory_size);
    if (memory_handle == NULL) {
        return GetLastError();
    }    

    DWORD error = CopyStringToMemory(string, string_length, memory_handle);
    if (error != ERROR_SUCCESS) {
        GlobalFree(memory_handle);
        return error;
    }

    HANDLE result = SetClipboardData(CF_UNICODETEXT, memory_handle);
    error = GetLastError();
    if (result == NULL) {
        GlobalFree(memory_handle);
        return error;
    }

    return ERROR_SUCCESS;
}


static DWORD CopyStringToMemory(LPCWSTR string, int copied_length, HGLOBAL memory_handle) {

    LPVOID memory = GlobalLock(memory_handle);
    if (memory == NULL) {
        return GetLastError();
    }

    HRESULT result = StringCchCopy(memory, copied_length + 1, string);
    GlobalUnlock(memory_handle);

    if (FAILED(result)) {
        return ERROR_OUTOFMEMORY;
    }

    return ERROR_SUCCESS;
}