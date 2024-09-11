#define NT_SUCCESS(Status)  (((NTSTATUS)(Status)) >= 0)

#define LDR_IS_DATAFILE(DllHandle) (((ULONG_PTR)(DllHandle)) & (ULONG_PTR)1)
#define LDR_IS_IMAGEMAPPING(DllHandle) (((ULONG_PTR)(DllHandle)) & (ULONG_PTR)2)
#define LDR_IS_RESOURCE(DllHandle) (LDR_IS_IMAGEMAPPING(DllHandle) || LDR_IS_DATAFILE(DllHandle))
#define LDR_MAPPEDVIEW_TO_DATAFILE(BaseAddress) ((PVOID)(((ULONG_PTR)(BaseAddress)) | (ULONG_PTR)1))
#define LDR_MAPPEDVIEW_TO_IMAGEMAPPING(BaseAddress) ((PVOID)(((ULONG_PTR)(BaseAddress)) | (ULONG_PTR)2))
#define LDR_DATAFILE_TO_MAPPEDVIEW(DllHandle) ((PVOID)(((ULONG_PTR)(DllHandle)) & ~(ULONG_PTR)1))
#define LDR_IMAGEMAPPING_TO_MAPPEDVIEW(DllHandle) ((PVOID)(((ULONG_PTR)(DllHandle)) & ~(ULONG_PTR)2))

#define ARGUMENT_PRESENT(ArgumentPointer)    (\
    (CHAR *)((ULONG_PTR)(ArgumentPointer)) != (CHAR *)(NULL) )

static
VOID APIENTRY RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, CONST ULONG_PTR* lpArguments)
{
    EXCEPTION_RECORD ExceptionRecord;
    ULONG n;
    PULONG_PTR s, d;
    ExceptionRecord.ExceptionCode = (DWORD)dwExceptionCode;
    ExceptionRecord.ExceptionFlags = dwExceptionFlags & EXCEPTION_NONCONTINUABLE;
    ExceptionRecord.ExceptionRecord = NULL;
    ExceptionRecord.ExceptionAddress = (PVOID)RaiseException;
    if (ARGUMENT_PRESENT(lpArguments)) {
        n = nNumberOfArguments;
        if (n > EXCEPTION_MAXIMUM_PARAMETERS) {
            n = EXCEPTION_MAXIMUM_PARAMETERS;
        }
        ExceptionRecord.NumberParameters = n;
        s = (PULONG_PTR)lpArguments;
        d = ExceptionRecord.ExceptionInformation;
        while (n--) {
            *d++ = *s++;
        }
    }
    else {
        ExceptionRecord.NumberParameters = 0;
    }
    RtlRaiseException(&ExceptionRecord);
}

static
DWORD WINAPI GetLastError(VOID)
{
    return (DWORD)NtCurrentTeb()->LastErrorValue;
}

static
VOID WINAPI SetLastError(_In_ DWORD dwErrCode)
{
    PTEB Teb = NtCurrentTeb();

    if (Teb->LastErrorValue != dwErrCode) {
        Teb->LastErrorValue = dwErrCode;
    }
}

static
DWORD WINAPI GetCurrentProcessId(VOID)
{
    return HandleToUlong(NtCurrentTeb()->ClientId.UniqueProcess);
}

static
DWORD APIENTRY GetCurrentThreadId(VOID)
{
    return HandleToUlong(NtCurrentTeb()->ClientId.UniqueThread);
}

static
HMODULE WINAPI GetModuleHandleW(_In_opt_ LPCWSTR lpModuleName)
{
    HMODULE hModule;
    NTSTATUS Status;
    struct _UNICODE_STRING DllName_U;
    PVOID DllHandle;

    hModule = nullptr;
    if (!lpModuleName)
        return (HMODULE)NtCurrentTeb()->ProcessEnvironmentBlock->ImageBaseAddress;
    RtlInitUnicodeString(&DllName_U, lpModuleName);
    Status = LdrGetDllHandle(nullptr, nullptr, &DllName_U, &DllHandle);
    if (Status >= 0)
        return (HMODULE)DllHandle;
    YY::Thunks::internal::BaseSetLastNTError((unsigned int)Status);
    return hModule;
}

static
BOOL WINAPI FreeLibrary(_In_ HMODULE hLibModule)
{
    NTSTATUS Status;

    if (LDR_IS_DATAFILE(hLibModule)) {

        if (RtlImageNtHeader(LDR_DATAFILE_TO_MAPPEDVIEW(hLibModule))) {

            Status = NtUnmapViewOfSection(NtCurrentProcess(),
                LDR_DATAFILE_TO_MAPPEDVIEW(hLibModule)
            );
            LdrUnloadAlternateResourceModule(hLibModule);

        }
        else {
            Status = STATUS_INVALID_IMAGE_FORMAT;
        }
    }
    else {
        Status = LdrUnloadDll((PVOID)hLibModule);
    }

    if (!NT_SUCCESS(Status)) {
        YY::Thunks::internal::BaseSetLastNTError(Status);
        return FALSE;
    }
    else {
        return TRUE;
    }
}

static
HANDLE WINAPI OpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId)
{
    NTSTATUS Status;
    OBJECT_ATTRIBUTES Obja;
    HANDLE Handle;
    CLIENT_ID ClientId;

    ClientId.UniqueThread = (HANDLE)LongToHandle(dwThreadId);
    ClientId.UniqueProcess = (HANDLE)NULL;

    InitializeObjectAttributes(
        &Obja,
        NULL,
        (bInheritHandle ? OBJ_INHERIT : 0),
        NULL,
        NULL
    );
    Status = NtOpenThread(
        &Handle,
        (ACCESS_MASK)dwDesiredAccess,
        &Obja,
        &ClientId
    );
    if (NT_SUCCESS(Status)) {
        return Handle;
    }
    else {
        YY::Thunks::internal::BaseSetLastNTError(Status);
        return NULL;
    }
}
