#include "MTab.hpp"

#include <random>
#include <algorithm>
#include <tuple>
#include <string>
#include <time.h>

namespace SSTabSim
{
    namespace
    {
        int __calcDigs(int v)
        {
            if (v <= 0)
                return 0;
            else if (v >= 10)
                return __calcDigs(v / 10) + 1;
            else
                return 1;
        };

        int __max(int a, int b)
        {
            if (a > b)
                return a;
            else
                return b;
        }
    }

    // static functions

    int MTab::calculateMxl(TableauxShape tb)
    {
        int dig = 0;

        for (auto row : tb)
        {
            for (auto v : row)
            {
                dig = __max(dig, __calcDigs(v));
            }
        }

        return dig;
    }

    MTab MTab::join(MTab left, MTab right)
    {
        TableauxShape lts = left.getShape(), rts = right.getShape();

        if (lts.size() == 0)
            return right;

        int marginSize = lts[0].size();
        int marginHeight = rts.size();

        TableauxShape ret =
            TableauxShape(marginHeight, vector<int>(marginSize, 0));

        int i;

        for (i = 0; i < rts.size(); ++i)
        {
            ret[i].insert(ret[i].end(), rts[i].begin(), rts[i].end());
        }

        ret.insert(ret.end(), lts.begin(), lts.end());

        return ret;
    }

    // constructors

    MTab::MTab() : shape({}), mxl(0){};

    MTab::MTab(TableauxShape shape) : shape(shape), mxl(calculateMxl(shape))
    {
        deleteTailsOfEmpty();

        if (!isWellShaped())
            throw "bad shaped tableaux";
    }

    MTab::MTab(MTab &mtab) : shape(mtab.shape), mxl(mtab.mxl){};

    // methods

    void MTab::setTableaux(TableauxShape shape)
    {
        this->shape = shape;
        mxl = calculateMxl(shape);

        deleteTailsOfEmpty();

        if (!isWellShaped())
            throw "bad shaped tableaux";
    }

    int MTab::getMxl() const { return mxl; }

    TableauxShape MTab::getShape() const { return shape; }

    bool MTab::isWellShaped() const
    {
        int height = shape.size();
        if (height == 0)
            return true;
        int last = shape[0].size(), now;
        int i;

        for (i = 1; i < height; ++i)
        {
            now = shape[i].size();
            if (last < now)
                return false;
            last = now;
        }

        return true;
    }

    bool MTab::isNoEmpty() const
    {
        for (auto row : shape)
        {
            for (auto v : row)
            {
                if (v <= 0)
                    return false;
            }
        }
        return true;
    }

    void MTab::deleteTailsOfEmpty()
    {
        bool end = true;
        int height = shape.size();

        if (height == 0)
            return;

        for (int i = 0; i < height; ++i)
        {
            if (shape[i][shape[i].size() - 1] <= 0)
            {
                if (i != height - 1)
                    if (shape[i].size() == shape[i + 1].size())
                        continue;
                end = false;
                shape[i].pop_back();
            }
        }

        if (shape[height - 1].size() == 0)
        {
            end = false;
            shape.pop_back();
        }

        if (!end)
            deleteTailsOfEmpty();
    }

    void MTab::join(MTab right)
    {
        setTableaux(join(*this, right).getShape());
    }

    void MTab::slideEmptyOnetime()
    {
        using std::tuple;
        using std::vector;

        int i, j, height, width, underwidth;
        /**
         * @brief the fillable squares list
         * @note why list? can this method
         *
         */
        vector<tuple<int, int>> list;

        height = shape.size();
        for (i = 0; i < height; ++i)
        {
            width = shape[i].size();
            for (j = 0; j < width; ++j)
            {
                // is not empty square?
                if (shape[i][j] > 0)
                    continue;
                // is bottom row?
                if (i == height - 1)
                {
                    // is end of row? (this case may not occur)
                    if (j == width - 1)
                        continue;
                    // is next empty?
                    else if (shape[i][j + 1] <= 0)
                        continue;

                    list.push_back(tuple<int, int>(i, j));
                    continue;
                }
                underwidth = shape[i + 1].size();
                // is no square under here?
                if (j >= underwidth)
                {
                    // is last? (this case may not occur)
                    if (j == width - 1)
                        continue;
                    // is next empty?
                    else if (shape[i][j + 1] <= 0)
                        continue;

                    list.push_back(tuple<int, int>(i, j));
                    continue;
                }
                // is end of row? (this case may not occur)
                if (j == width - 1)
                {
                    // is bottom empty?
                    if (shape[i + 1][j] <= 0)
                        continue;

                    list.push_back(tuple<int, int>(i, j));
                    continue;
                }
                // is bottom and right empty?
                if ((shape[i][j + 1] <= 0) || (shape[i + 1][j] <= 0))
                    continue;

                list.push_back(tuple<int, int>(i, j));
            }
        }

        if (list.size() == 0)
            return;

        std::random_device rd;
        std::mt19937_64 mt(rd());

        std::shuffle(list.begin(), list.end(), mt);

        auto [di, dj] = list[0];

        width = shape[di].size();

        if (di == height - 1)
        {
            // bottom row

            shape[di][dj] = shape[di][dj + 1];
            shape[di][dj + 1] = 0;
        }
        else if (dj == width - 1)
        {
            // the end of row

            shape[di][dj] = shape[di + 1][dj];
            shape[di + 1][dj] = 0;
        }
        else if (shape[di + 1][dj] < shape[di][dj + 1])
        {
            shape[di][dj] = shape[di][dj + 1];
            shape[di][dj + 1] = 0;
        }
        else
        {
            shape[di][dj] = shape[di + 1][dj];
            shape[di + 1][dj] = 0;
        }

        deleteTailsOfEmpty();
    }

    void MTab::slideEmptyCompletely()
    {
        while (!isNoEmpty())
        {
            slideEmptyOnetime();
        }
    }

    namespace
    {
        std::string toStringEachSq(int v, int mxl)
        {
            if (v <= 0)
                return std::string(mxl, '_');

            int dig = __calcDigs(v);

            if (dig > mxl)
                throw "mxl was set incorrectly";

            return ((mxl == dig) ? "" : std::string(mxl - dig, ' ')) + std::to_string(v);
        }
    }

    std::ostream &operator<<(std::ostream &os, MTab mtab)
    {
        TableauxShape t = mtab.getShape();

        for (auto row : t)
        {
            for (auto v : row)
            {
                os << toStringEachSq(v, mtab.getMxl());
                os << " ";
            }

            os << std::endl;
        }

        return os;
    }
}