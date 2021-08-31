#ifndef MATRIX_H
#define MATRIX_H

#include <bits/stdc++.h>

using Matrix = std::vector<std::vector<long double>>;
class matrix
{
    public:
    
    Matrix mat;
    
    matrix();
    matrix(Matrix);
    ~matrix();

    void Print();


    //‰‰ŽZ
    matrix operator + (matrix obj)
    {
        int objrow = obj.mat.size();
        int objcol = obj.mat[0].size();
        int thisrow = this->mat.size();
        int thiscol = this->mat[0].size();

        matrix ans(std::vector<std::vector<long double>>(objrow, std::vector<long double>(objcol)));

        //std::cout << objrow << " " << objcol << " " << thisrow << " " << thiscol << std::endl;

        if(objrow == 0 || objcol == 0 || thisrow == 0|| thiscol == 0)return ans;
        if(objrow != thisrow || objcol != thiscol)return ans;

        for (int ar = 0; ar < objrow; ar++)
        {
            for (int ac = 0; ac < objcol; ac++)
            {
                ans.mat[ar][ac] = obj.mat[ar][ac] + this->mat[ar][ac];
            }
        }
        
        return ans;
    }
    matrix operator * (matrix obj)
    {
        int objrow = obj.mat.size();
        int objcol = obj.mat[0].size();
        int thisrow = this->mat.size();
        int thiscol = this->mat[0].size();

        matrix ans(std::vector<std::vector<long double>>(thisrow, std::vector<long double>(objcol)));

        //std::cout << objrow << " " << objcol << " " << thisrow << " " << thiscol << std::endl;

        if(thisrow == 0 || thiscol == 0 || objrow == 0|| objcol == 0)return ans;
        if(thiscol != objrow)return ans;

        for (int ar = 0; ar < thisrow; ar++)
        {
            for (int bc = 0; bc < objcol; bc++)
            {
                long double term = 0.0L;
                for (int ac = 0; ac < thiscol; ac++)
                {
                    term += this->mat[ar][ac] * obj.mat[ac][bc];
                }
                ans.mat[ar][bc] = term;
            }
        }

        return ans;
    }
};

#endif