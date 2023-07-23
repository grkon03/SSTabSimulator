#pragma once

#include "MTab.hpp"
#include "types.hpp"

namespace SSTabSim
{
    class SSTab : public MTab
    {
    public:
        // constructors

        SSTab(TableauxShape);

        // methods

        /**
         * @brief verify the numbers meets the SSTab conditions
         *
         * @return result of the verification
         */
        bool isWellNumbered() const;

        // operators

        SSTab operator*(const SSTab &);
        SSTab &operator*=(const SSTab &);
    };
}