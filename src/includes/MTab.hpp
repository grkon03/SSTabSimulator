#pragma once

#include <iostream>

#include "types.hpp"

namespace SSTabSim
{
    class MTab
    {
    protected:
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
        static MTab join(const MTab left, const MTab right);

        // constructors

        MTab();

        MTab(TableauxShape);

        MTab(const MTab &);

        // methods

        /**
         * @brief Set the tableaux and set the mxl
         *
         * @param tableaux
         */
        void setTableaux(TableauxShape tableaux);

        /**
         * @brief Get the mxl
         *
         * @return mxl
         */
        int getMxl() const;

        /**
         * @brief Get the Tableaux Shape object
         *
         * @return TableauxShape
         */
        TableauxShape getShape() const;

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
         * @brief delete all empty squares of tails
         *
         */
        void deleteTailsOfEmpty();

        /**
         * @brief join right to this by right side
         *
         * @param right tableaux joined by right side
         */
        void join(MTab right);

        /**
         * @brief slide a numbered square to a empty square like 15-game ruled.
         * The square which will be filled is selected randomly from able squares.
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