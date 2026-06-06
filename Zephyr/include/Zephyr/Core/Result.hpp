#pragma once

#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

namespace Zephyr
{

template<typename T, typename E = std::string>
class Result
{
public:
    static Result Ok(T value)
    {
        Result r;
        r.m_data = std::move(value);
        return r;
    }

    static Result Err(E error)
    {
        Result r;
        r.m_data = std::move(error);
        return r;
    }

    bool IsOk() const { return std::holds_alternative<T>(m_data); }
    bool IsErr() const { return std::holds_alternative<E>(m_data); }

    T& Value()
    {
        if (IsErr())
            throw std::logic_error("Result::Value called on an error result");
        return std::get<T>(m_data);
    }

    const T& Value() const
    {
        if (IsErr())
            throw std::logic_error("Result::Value called on an error result");
        return std::get<T>(m_data);
    }

    E& Error()
    {
        if (IsOk())
            throw std::logic_error("Result::Error called on an ok result");
        return std::get<E>(m_data);
    }

    const E& Error() const
    {
        if (IsOk())
            throw std::logic_error("Result::Error called on an ok result");
        return std::get<E>(m_data);
    }

    T ValueOr(T fallback) const
    {
        return IsOk() ? std::get<T>(m_data) : std::move(fallback);
    }

    explicit operator bool() const { return IsOk(); }

private:
    std::variant<T, E> m_data;
};

template<typename E>
class Result<void, E>
{
public:
    static Result Ok()
    {
        Result r;
        r.m_ok = true;
        return r;
    }

    static Result Err(E error)
    {
        Result r;
        r.m_ok = false;
        r.m_error = std::move(error);
        return r;
    }

    bool IsOk() const { return m_ok; }
    bool IsErr() const { return !m_ok; }

    E& Error()
    {
        if (m_ok)
            throw std::logic_error("Result::Error called on an ok result");
        return m_error;
    }

    const E& Error() const
    {
        if (m_ok)
            throw std::logic_error("Result::Error called on an ok result");
        return m_error;
    }

    explicit operator bool() const { return m_ok; }

private:
    bool m_ok = false;
    E m_error{};
};

}
