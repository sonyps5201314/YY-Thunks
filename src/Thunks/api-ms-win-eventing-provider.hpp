#if (YY_Thunks_Target < __WindowsNT6_2)
#include <evntprov.h>
#endif

#if (YY_Thunks_Target < __WindowsNT6)
#include <evntrace.h>
#endif

#if (YY_Thunks_Target < __WindowsNT6_1) && !defined(__Comment_Lib_advapi32)
#define __Comment_Lib_advapi32
#pragma comment(lib, "Advapi32.lib")
#endif

namespace YY::Thunks
{
#if (YY_Thunks_Target < __WindowsNT6_2)

    // 最低受支持的客户端	Windows 8 [桌面应用|UWP 应用]
    // 最低受支持的服务器	Windows Server 2012[桌面应用 | UWP 应用]
    __DEFINE_THUNK(
    ntdll,
    20,
    ULONG,
    __stdcall,
    EtwEventSetInformation,
        _In_ REGHANDLE _hRegHandle,
        _In_ EVENT_INFO_CLASS _eInformationClass,
        _In_reads_bytes_(_cbInformationLength) PVOID _pEventInformation,
        _In_ ULONG _cbInformationLength
        )
    {
        if (auto const _pfnEtwEventSetInformation = try_get_EtwEventSetInformation())
        {
            return _pfnEtwEventSetInformation(_hRegHandle, _eInformationClass, _pEventInformation, _cbInformationLength);
        }

        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // Minimum supported client	Windows Vista [desktop apps | UWP apps]
    // Minimum supported server	Windows Server 2008[desktop apps | UWP apps]
    __DEFINE_THUNK(
    ntdll,
    8,
    ULONG,
    WINAPI,
    EtwEventActivityIdControl,
        _In_ ULONG _uControlCode,
        _Inout_ LPGUID _pActivityId
        )
    {
        if (auto const _pfnEtwEventActivityIdControl = try_get_EtwEventActivityIdControl())
        {
            return _pfnEtwEventActivityIdControl(_uControlCode, _pActivityId);
        }
            
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // Minimum supported client	Windows Vista [desktop apps | UWP apps]
    // Minimum supported server	Windows Server 2008[desktop apps | UWP apps]
    __DEFINE_THUNK(
    ntdll,
    16,
    ULONG,
    WINAPI,
    EtwEventRegister,
        _In_ LPCGUID _pProviderId,
        _In_opt_ PENABLECALLBACK _pfnEnableCallback,
        _In_opt_ PVOID _pCallbackContext,
        _Out_ PREGHANDLE _phRegHandle
        )
    {
        if (auto const _pfnEtwEventRegister = try_get_EtwEventRegister())
        {
            return _pfnEtwEventRegister(_pProviderId, _pfnEnableCallback, _pCallbackContext, _phRegHandle);
        }
            
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // Minimum supported client	Windows Vista [desktop apps | UWP apps]
    // Minimum supported server	Windows Server 2008[desktop apps | UWP apps]
    __DEFINE_THUNK(
    ntdll,
    8,
    ULONG,
    WINAPI,
    EtwEventUnregister,
        _In_ REGHANDLE _hRegHandle
        )
    {
        if (auto const _pfnEtwEventUnregister = try_get_EtwEventUnregister())
        {
            return _pfnEtwEventUnregister(_hRegHandle);
        }
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // Minimum supported client	Windows Vista [desktop apps | UWP apps]
    // Minimum supported server	Windows Server 2008[desktop apps | UWP apps]
    __DEFINE_THUNK(
    advapi32,
    24,
    ULONG,
    WINAPI,
    EnumerateTraceGuidsEx,
        _In_ TRACE_QUERY_INFO_CLASS TraceQueryInfoClass,
        _In_reads_bytes_opt_(InBufferSize) PVOID InBuffer,
        _In_ ULONG InBufferSize,
        _Out_writes_bytes_opt_(OutBufferSize) PVOID OutBuffer,
        _In_ ULONG OutBufferSize,
        _Out_ PULONG ReturnLength
        )
    {
        if (auto const _pfnEnumerateTraceGuidsEx = try_get_EnumerateTraceGuidsEx())
        {
            return _pfnEnumerateTraceGuidsEx(TraceQueryInfoClass, InBuffer, InBufferSize, OutBuffer, OutBufferSize, ReturnLength);
        }
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // Minimum supported client	Windows Vista [desktop apps | UWP apps]
    // Minimum supported server	Windows Server 2008[desktop apps | UWP apps]
    __DEFINE_THUNK(
    ntdll,
    28,
    ULONG,
    WINAPI,
    EtwEventWriteTransfer,
        _In_ REGHANDLE RegHandle,
        _In_ PCEVENT_DESCRIPTOR EventDescriptor,
        _In_opt_ LPCGUID ActivityId,
        _In_opt_ LPCGUID RelatedActivityId,
        _In_range_(0, MAX_EVENT_DATA_DESCRIPTORS) ULONG UserDataCount,
        _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
        )
    {
        if (auto const _pfnEtwEventWriteTransfer = try_get_EtwEventWriteTransfer())
        {
            return _pfnEtwEventWriteTransfer(RegHandle, EventDescriptor, ActivityId, RelatedActivityId, UserDataCount, UserData);
        }
            
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // 最低受支持的客户端	Windows Vista [仅限桌面应用]
    // 最低受支持的服务器	Windows Server 2008[仅限桌面应用]
    __DEFINE_THUNK(
    ntdll,
    12,
    BOOLEAN,
    WINAPI,
    EtwEventEnabled,
        _In_ REGHANDLE RegHandle,
        _In_ PCEVENT_DESCRIPTOR EventDescriptor
        )
    {
        if (auto const _pfnEtwEventEnabled = try_get_EtwEventEnabled())
        {
            return _pfnEtwEventEnabled(RegHandle, EventDescriptor);
        }
            
        return FALSE;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // 最低受支持的客户端	Windows Vista [桌面应用 | UWP 应用]
    // 最低受支持的服务器	Windows Server 2008[桌面应用 | UWP 应用]
    __DEFINE_THUNK(
    ntdll,
    20,
    ULONG,
    WINAPI,
    EtwEventWrite,
        _In_ REGHANDLE RegHandle,
        _In_ PCEVENT_DESCRIPTOR EventDescriptor,
        _In_range_(0, MAX_EVENT_DATA_DESCRIPTORS) ULONG UserDataCount,
        _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
        )
    {
        if (auto const _pfnEtwEventWrite = try_get_EtwEventWrite())
        {
            return _pfnEtwEventWrite(RegHandle, EventDescriptor, UserDataCount, UserData);
        }
            
        return ERROR_NOT_SUPPORTED;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6_1)

    // 最低受支持的客户端	Windows 7 [桌面应用 |UWP 应用]
    // 最低受支持的服务器	Windows Server 2008 R2[桌面应用 | UWP 应用]
    __DEFINE_THUNK(
    ntdll,
    40,
    ULONG,
    WINAPI,
    EtwEventWriteEx,
        _In_ REGHANDLE RegHandle,
        _In_ PCEVENT_DESCRIPTOR EventDescriptor,
        _In_ ULONG64 Filter,
        _In_ ULONG Flags,
        _In_opt_ LPCGUID ActivityId,
        _In_opt_ LPCGUID RelatedActivityId,
        _In_range_(0, MAX_EVENT_DATA_DESCRIPTORS) ULONG UserDataCount,
        _In_reads_opt_(UserDataCount) PEVENT_DATA_DESCRIPTOR UserData
        )
    {
        if (auto const _pfnEtwEventWriteEx = try_get_EtwEventWriteEx())
        {
            return _pfnEtwEventWriteEx(RegHandle, EventDescriptor, Filter, Flags, ActivityId, RelatedActivityId, UserDataCount, UserData);
        }
            
        return ::EtwEventWriteTransfer(RegHandle, EventDescriptor, ActivityId, RelatedActivityId, UserDataCount, UserData);
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6)

    // 最低受支持的客户端	Windows Vista [桌面应用 | UWP 应用]
    // 最低受支持的服务器	Windows Server 2008[桌面应用 | UWP 应用]
    __DEFINE_THUNK(
    ntdll,
    24,
    ULONG,
    WINAPI,
    EtwEventWriteString,
        _In_ REGHANDLE RegHandle,
        _In_ UCHAR Level,
        _In_ ULONGLONG Keyword,
        _In_ PCWSTR String
        )
    {
        if (auto const _pfnEtwEventWriteString = try_get_EtwEventWriteString())
        {
            return _pfnEtwEventWriteString(RegHandle, Level, Keyword, String);
        }
        return ERROR_NOT_SUPPORTED;
    }
#endif
}
