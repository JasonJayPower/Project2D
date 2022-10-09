#pragma once

template <typename T>
class Delegate;

template <typename R, typename... Args>
class Delegate<R(Args...)>
{
    using Callee   = void*;
    using Callback = R (*)(void*, Args...);

  public:
    template <auto callback, typename T>
    static Delegate bind(T* objPtr)
    {
        return { objPtr, func<callback, T> };
    }

    R operator()(Args... args) const noexcept
    {
        return m_callback(m_callee, std::forward<Args>(args)...);
    }

  private:
    Delegate(Callee obj, Callback fun)
        : m_callee  { obj }
        , m_callback{ fun }
    {
    }

    template <auto callBack, typename T>
    static R func(void* callee, Args... args)
    {
        return (static_cast<T*>(callee)->*callBack)(std::forward<Args>(args)...);
    }

    Callee m_callee     = nullptr;
    Callback m_callback = nullptr;
};
