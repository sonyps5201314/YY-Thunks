

namespace YY::Thunks
{
#if (YY_Thunks_Target < __WindowsNT5_2_SP1)

    //Windows XP with SP2, Windows Server 2003 with SP1
    __DEFINE_THUNK(
    ntdll,
    4,
    PVOID,
    WINAPI,
    RtlDecodePointer,
        _In_opt_ PVOID Ptr
        )
    {
        if (auto const pRtlDecodePointer = try_get_RtlDecodePointer())
        {
            return pRtlDecodePointer(Ptr);
        }
        else
        {
            return Ptr;
        }
    }
#endif


#if (YY_Thunks_Target < __WindowsNT5_2_SP1)

    //Windows XP with SP2, Windows Server 2003 with SP1
    __DEFINE_THUNK(
    ntdll,
    4,
    PVOID,
    WINAPI,
        RtlEncodePointer,
        _In_opt_ PVOID Ptr
        )
    {
        if (auto const pRtlEncodePointer = try_get_RtlEncodePointer())
        {
            return pRtlEncodePointer(Ptr);
        }
        else
        {
            return Ptr;
        }
    }
#endif
} //namespace YY::Thunks
