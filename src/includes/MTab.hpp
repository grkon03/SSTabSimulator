#pragma once

#include <iostream>

#include "types.hpp"

namespace SSTabSim
{
    class MTab
    {
    private:
        // variables

        // variables

        /**
         * @brief Middle Tableaux
         *
         */
        TableauxShape shape;

        /**
         * @brief Max length of all integers in tableux
         * when expressing these integers in decimal.
         */
        unsigned int mxl;

    public:
        // static functions

        /**
         * @brief
         *
         * @param tab
         * @return mxl(Max length of all integers in tableux
         * when expressing these integers in decimal.)
         */
        static int calculateMxl(TableauxShape tab);

        /**
         * @brief join the tableauxs
         *
         * @param left tableaux joined by left side
         * @param right tabeaux joined by right side
         * @return joined MTab
         */
        static MTab join(MTab left, MTab right);

        // constructors

        MTab(TableauxShape);

        // methods

        /**
         * @brief Get the mxl
         *
         * @return mxl
         */
        int getMxl() const;

        /**
         * @brief verify whether this tableaux is young tableaux shaped.
         *
         * @return wheter this is well shaped.
         */
        bool isWellShaped() const;

        /**
         * @brief verify wheter there are no empty square.
         *
         * @return wheter there are no empty.
         */
        bool isNoEmpty() const;

        /**
         * @brief join right to this by right side
         *
         * @param right tableaux joined by right side
         */
        void join(MTab right);

        /**
         * @brief slide a numbered square to a empty square like 15-game ruled.
         *
         */
        void slideEmptyOnetime();

        /**
         * @brief slide numbered squares to empty squares like 15-game ruled
         * until there are no empty square.
         *
         */
        void slideEmptyCompletely();
    };

    // ostream operation

    std::ostream &operator<<(std::ostream &os, MTab mtab);
}