#pragma once

#include "Core/Types.h"

namespace Quantum
{
    class DateTime
    {
    private:
        std::tm m_Time;
    public:
        DateTime(const std::tm& time);

        std::tm Get() const;

        String GetDate() const;
        String GetTime() const;

        bool operator==(const DateTime& other) const;
        bool operator!=(const DateTime& other) const;

        bool operator<(const DateTime& other) const;
        bool operator>(const DateTime& other) const;

        bool operator<=(const DateTime& other) const;
        bool operator>=(const DateTime& other) const;

        static DateTime FromCompileTime();
        static DateTime FromFileCreationTime(StringView path);
        static DateTime Now();
    private:
        static int GetMonthFromAbbreviation(const char* monthAbbreviation);
    };
}
