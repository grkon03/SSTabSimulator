#include "SSTab.hpp"

namespace SSTabSim
{
    // constructors

    SSTab::SSTab() : MTab(){};

    SSTab::SSTab(TableauxShape shape) : MTab(shape)
    {
        if (!isWellNumbered())
            throw "bad numbered tableaux as semistandard";
    }

    SSTab::SSTab(MTab mtab) : MTab(mtab){};

    SSTab::SSTab(const SSTab &sstab) : SSTab(sstab.getShape()){};

    // methods

    bool SSTab::isWellNumbered() const
    {
        int i, j, width, underwidth, height;

        height = shape.size();

        for (i = 0; i < height; ++i)
        {
            width = shape[i].size();
            if (i == height - 1)
            {
                underwidth = 0;
            }
            else
            {
                underwidth = shape[i + 1].size();
            }
            for (j = 0; j < width; ++j)
            {
                if (j < underwidth)
                    if (shape[i][j] <= shape[i + 1][j])
                        return false;

                if (j != width - 1)
                {
                    if (shape[i][j] < shape[i][j + 1])
                        return false;
                }
            }
        }

        return true;
    }

    // operators

    SSTab SSTab::operator*(const SSTab &right) const
    {
        MTab m = MTab::join(MTab(shape), MTab(right.shape));

        m.slideEmptyCompletely();

        return SSTab(m.getShape());
    }

    SSTab &SSTab::operator*=(const SSTab &right)
    {
        setTableaux((*this * right).getShape());

        return *this;
    }

    std::ostream &operator<<(std::ostream &os, SSTab sstab)
    {
        os << MTab(sstab.getShape());

        return os;
    }
}