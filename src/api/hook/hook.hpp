#pragma once 

#include <memory>

#define HOOK_FUNCTION(hook) hook, #hook

#include "../../../dependencies/funchook/src/funchook.h"
#include "virtual.hpp"

inline funchook_t* g_funchookCtx = nullptr;
inline bool g_isShuttingDown = false;

template <typename T>
class CHook {
    std::add_pointer_t<T> m_pOriginal;

public:
    // Template has been used to avoid casts.
    template <typename OriginalT, typename HookT>
    void Hook(OriginalT _pOriginalFn, HookT& pHookFn, const char* szHookName) {
        if (this->m_pOriginal) {
            return;
        }

        void* pOriginalFn = static_cast<void*>(_pOriginalFn);
        if (!pOriginalFn) {

            return;
        }

        this->m_pOriginal =
            reinterpret_cast<decltype(this->m_pOriginal)>(pOriginalFn);
        int rv = funchook_prepare(g_funchookCtx,
            reinterpret_cast<void**>(&this->m_pOriginal),
            reinterpret_cast<void*>(pHookFn));

        if (rv == FUNCHOOK_ERROR_SUCCESS) {

        }
        else {
            this->m_pOriginal = nullptr;

        }
    }

    template <typename HookT>
    void HookVirtual(void* pClass, int index, HookT& pHookFn,
        const char* szHookName) {
        this->Hook(vmt::GetVMethod(index, pClass), pHookFn, szHookName);
    }

    // Shorthand for calling original.
    template <typename... Args>
    auto operator()(Args &&...args) {
        return std::invoke(this->m_pOriginal, std::forward<Args>(args)...);
    }
};