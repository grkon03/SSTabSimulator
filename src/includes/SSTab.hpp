#pragma once

#include "MTab.hpp"
#include "types.hpp"

namespace SSTabSim
{
    class SSTab : public MTab
    {
    public:
        // constructors

        SSTab();

        SSTab(TableauxShape);

        SSTab(MTab);

        SSTab(const SSTab &);

        // methods

        /**
         * @brief verify the numbers meets the SSTab conditions
         *
         * @return result of the verification
         */
        bool isWellNumbered() const;

        // operators

        SSTab operator*(const SSTab &) const;
        SSTab &operator*=(const SSTab &);

        // static functions

        static SSTab multiplicationTimeLapse(const SSTab &, const SSTab &);
    };

    std::ostream &operator<<(std::ostream &os, SSTab sstab);
}