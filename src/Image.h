#ifndef _Image_
#define _Image_

#include <cassert>
#include <vector>
using namespace std;

#include "Color.h"

class Image
{
public:
    Image(int iW=0,int iH=0,int iP=1)
    {
	    resize(iW,iH,iP);
    }

    virtual ~Image()
    { }

    int width() const
    {
        return _iW;
    }

    int height() const
    {
        return _iH;
    }

    int planes() const
    {
        return _iP;
    }

    int size() const
    {
        return _iH * _iW * _iP;
    }

    void resize(int iW,int iH,int iP)
    {
        assert(iW>=0);
        assert(iH>=0);
        assert(iP>=0);

        _iW=iW;
        _iH=iH;
        _iP=iP;
        _data.resize((size_t)_iW * (size_t)_iH * (size_t)_iP);
    }

    unsigned char* data()
    {
        return _data.data();
    }

    const unsigned char* pixel(int iX,int iY,int iP=0) const
    {
        assert(iX>=0);
        assert(iY>=0);
        assert(iP>=0);
        assert(iX<_iW);
        assert(iY<_iH);
        assert(iP<_iP);

        return _data.data() + iP + _iP * _iW * iY + iX * _iP;
    }

    unsigned char* pixel(int iX, int iY, int iP = 0)
    {
        assert(iX >= 0);
        assert(iY >= 0);
        assert(iP >= 0);
        assert(iX < _iW);
        assert(iY < _iH);
        assert(iP < _iP);

        return _data.data() + iP + _iP * _iW * iY + iX * _iP;
    }

    unsigned char& operator()(int iX,int iY,int iP=0)
    {
        assert(iX>=0);
        assert(iY>=0);
        assert(iP>=0);
        assert(iX<_iW);
        assert(iY<_iH);
        assert(iP<_iP);

        return *(_data.data() + iP + _iP * _iW * iY + iX * _iP);
    }

    unsigned char operator()(int iX, int iY, int iP = 0) const
    {
        assert(iX >= 0);
        assert(iY >= 0);
        assert(iP >= 0);
        assert(iX < _iW);
        assert(iY < _iH);
        assert(iP < _iP);

        return *(_data.data() + iP + _iP * _iW * iY + iX * _iP);
    }

    void to_double(vector<double>& img)
    {
        img.resize(size());
        for (size_t ligne = 0; ligne < (size_t)width(); ligne++)
            for (size_t colonne = 0; colonne < (size_t)height(); colonne++)
                img[colonne + ligne * width()] = (*this)((int)ligne, (int)colonne);
    }

private:
    int _iW,_iH,_iP;
    vector<unsigned char> _data;
};

#endif
