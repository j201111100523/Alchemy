#ifndef ALCHEMY_CORE_TYPES_HPP
#define ALCHEMY_CORE_TYPES_HPP

#include <cassert>
#include "util/saturate.h"

namespace alchemy
{

//////////////////////////////////////////////////////////////////////////
template<typename _Tp, int n> _Vec<_Tp, n>::_Vec()
{
    for (int i = 0; i < n; ++i)
        data_[i] = _Tp(0);
}
template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(_Tp v0)
{
    assert(n >= 1);
    data_[0] = v0;
    for (int i = 1; i < n; ++i) data_[i] = _Tp(0);
}
template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(_Tp v0, _Tp v1)
{
    assert(n >= 2);
    data_[0] = v0, data_[1] = v1;
    for (int i = 2; i < n; ++i) data_[i] = _Tp(0);
}
template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(_Tp v0, _Tp v1, _Tp v2)
{
    assert(n >= 3);
    data_[0] = v0, data_[1] = v1, data_[2] = v2;
    for (int i = 3; i < n; ++i) data_[i] = _Tp(0);
}
template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(_Tp v0, _Tp v1, _Tp v2, _Tp v3)
{
    assert(n >= 4);
    data_[0] = v0, data_[1] = v1, data_[2] = v2, data_[3] = v3;
    for (int i = 4; i < n; ++i) data_[i] = _Tp(0);
}

template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(const _Tp* vals)
{
    for (int i = 0; i < n; ++i)
        data_[i] = vals[i];
}

template<typename _Tp, int n> _Vec<_Tp, n>::_Vec(const _Vec<_Tp, n>&v) :_Vec<_Tp, n>(v.data_) {  }

template<typename _Tp, int n> _Vec<_Tp, n>& _Vec<_Tp, n >::operator = (std::initializer_list<_Tp> list)
{
    assert(list.size() >= n);

    int idx = 0;
    for (const auto& i : list)
        data_[idx++] = i;

    for (; idx < n; ++idx)
        data_[idx] = _Tp(0);

    return *this;
}

template<typename _Tp, int n>
const _Tp& _Vec<_Tp, n >::operator[](int i) const
{
    assert((static_cast<unsigned>(i) < static_cast<unsigned>(n)));
    return data_[i];
}

template<typename _Tp, int n>
_Tp& _Vec<_Tp, n >::operator[](int i)
{
    assert((static_cast<unsigned>(i) < static_cast<unsigned>(n)));
    return data_[i];
}

template<typename _Tp, int n>
const _Tp& _Vec<_Tp, n >::operator()(int i) const
{
    assert((static_cast<unsigned>(i) < static_cast<unsigned>(n)));
    return data_[i];
}

template<typename _Tp, int n>
_Tp& _Vec<_Tp, n >::operator()(int i)
{
    assert(static_cast<unsigned>(i) < static_cast<unsigned>(n));
    return data_[i];
}

template<typename _Tp, int n>
_Vec<_Tp, n> _Vec<_Tp, n>::all(_Tp val)
{
    _Vec<_Tp, n> v;
    for (int i = 0; i < n; ++i)
        v.data_[i] = val;
    return v;
}

template<typename _Tp, int n>
_Vec<_Tp, n> _Vec<_Tp, n >::zeros()
{
    return all(0);
}
template<typename _Tp, int n>
_Vec<_Tp, n> _Vec<_Tp, n >::ones()
{
    return all(1);
}

/////////////////////////////////////////_Size////////////////////////////////////////////
template<class _Tp> _Size<_Tp>::_Size() :width(0), height(0) {}
template<class _Tp> _Size<_Tp>::_Size(_Tp _width, _Tp _height) : width(_width), height(_height) {}
template<class _Tp> _Size<_Tp>::_Size(const _Size& sz) : width(sz.width), height(sz.height) {}
template<class _Tp> _Tp _Size<_Tp>::area() const { return width * height; }


/////////////////////////////////////////_Point////////////////////////////////////////////
template<class _Tp> _Point<_Tp>::_Point() : x(0), y(0) { }
template<class _Tp> _Point<_Tp>::_Point(_Tp _x, _Tp _y) : x(_x), y(_y) { }
template<class _Tp> _Point<_Tp>::_Point(const _Point& pt) : x(pt.x), y(pt.y) { }
template<class _Tp> _Point<_Tp>& _Point<_Tp>::operator = (const _Point& pt) { x = pt.x; y = pt.y; return *this; }
template<class _Tp> _Tp _Point<_Tp>::dot(const _Point& pt) const { return static_cast<_Tp>(x)*pt.x + static_cast<_Tp>(y)*pt.y; }
template<class _Tp> double _Point<_Tp>::cross(const _Point<_Tp>& pt) const
{
    return (static_cast<double>(x)*pt.y - static_cast<double>(y)*pt.x);
}

template<typename _T> std::ostream &operator<<(std::ostream &os, _Point<_T> &p)
{
    if (sizeof(_T) == 1)
        os << "[" << static_cast<int>(p.x) << ", " << static_cast<int>(p.y) << "]";
    else
        os << "[" << p.x << ", " << p.y << "]";

    return os;
}

/////////////////////////////////////////_Point3////////////////////////////////////////////
template<class _Tp> _Point3<_Tp>::_Point3() : x(0), y(0), z(0) { }
template<class _Tp> _Point3<_Tp>::_Point3(_Tp _x, _Tp _y, _Tp _z) : x(_x), y(_y), z(_z) { }
template<class _Tp> _Point3<_Tp>::_Point3(const _Point3& pt) : x(pt.x), y(pt.y), z(pt.z) { }
template<class _Tp> _Point3<_Tp>& _Point3<_Tp>::operator = (const _Point3& pt) { x = pt.x; y = pt.y; z = pt.z; return *this; }
template<class _Tp> _Tp _Point3<_Tp>::dot(const _Point3& pt) const { return x*pt.x + y*pt.y + z*pt.z; }
template<typename _Tp> _Point3<_Tp> _Point3<_Tp>::cross(const _Point3<_Tp>& pt) const
{
    return _Point3<_Tp>(y*pt.z - z*pt.y, z*pt.x - x*pt.z, x*pt.y - y*pt.x);
}

/////////////////////////////////////////_Rect////////////////////////////////////////////
template<class _Tp> _Rect<_Tp>::_Rect() : x(0), y(0), width(0), height(0) { }
template<class _Tp> _Rect<_Tp>::_Rect(const _Rect& r) : x(r.x), y(r.y), width(r.width), height(r.height) { }
template<class _Tp> _Rect<_Tp>::_Rect(_Tp _x, _Tp _y, _Tp _width, _Tp _height) : x(_x), y(_y), width(_width), height(_height) { }
template<class _Tp> _Rect<_Tp>::_Rect(const _Point<_Tp>& org, const _Size<_Tp>& sz) :
        x(org.x), y(org.y), width(sz.width), height(sz.height) {}
template<class _Tp> _Rect<_Tp>::_Rect(const _Point<_Tp>& pt1, const _Point<_Tp>& pt2)
{
    if (pt1.x < pt2.x) {
        x = pt1.x;
        width = pt2.x - pt1.x;
    }
    else {
        x = pt2.x;
        width = pt1.x - pt2.x;
    }

    if (pt1.y < pt2.y) {
        y = pt1.y;
        height = pt2.y - pt1.y;
    }
    else {
        y = pt2.y;
        height = pt1.y - pt2.y;
    }
}

template<class _Tp> _Rect<_Tp>& _Rect<_Tp>:: operator = (const _Rect& r)
{
    x = r.x;
    y = r.y;
    width = r.width;
    height = r.height;
    return *this;
}


/////////////////////////////////////////_Scalar////////////////////////////////////////////
template<class _Tp> _Scalar<_Tp>::_Scalar() { v[0] = v[1] = v[2] = v[3] = 0; }
template<class _Tp> _Scalar<_Tp>::_Scalar(_Tp _v0) { v[0] = _v0; v[1] = v[2] = v[3] = 0; }
template<class _Tp> _Scalar<_Tp>::_Scalar(_Tp _v0, _Tp _v1, _Tp _v2, _Tp _v3)
{
    v[0] = _v0;
    v[1] = _v1;
    v[2] = _v2;
    v[3] = _v3;
}

template<class _Tp> void _Scalar<_Tp>::init(_Tp _v0) { v[0] = v[1] = v[2] = v[3] = _v0; }
template<class _Tp> _Scalar<_Tp> _Scalar<_Tp>::conj() const { return _Scalar<_Tp>(v[0], -v[1], -v[2], -v[3]); }
template<class _Tp> bool _Scalar<_Tp>::isReal() const { return (v[1] == 0 && v[2] == 0 && v[3] == 0); }


template <typename _Tp>
bool operator==(const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    return a.v[0] == b.v[0] && a.v[1] == b.v[1] && a.v[2] == b.v[2] && a.v[3] == b.v[3];
}

template <typename _Tp>
bool operator!=(const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    return !(a == b);
}

template<typename _Tp>
_Scalar<_Tp> operator += (const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    a.v[0] += b.v[0];
    a.v[1] += b.v[1];
    a.v[2] += b.v[2];
    a.v[3] += b.v[3];
    return a;
}


template <typename _Tp>
_Scalar<_Tp> operator -= (const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    a.v[0] -= b.v[0];
    a.v[1] -= b.v[1];
    a.v[2] -= b.v[2];
    a.v[3] -= b.v[3];
    return a;
}

template<typename _Tp>
_Scalar<_Tp> operator *= (const _Scalar<_Tp>& a, _Tp v)
{
    a.v[0] *= v;
    a.v[1] *= v;
    a.v[2] *= v;
    a.v[3] *= v;
    return a;
}

template<typename _Tp>
_Scalar<_Tp> operator + (const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    // Auto cast
    return alchemy::_Scalar<_Tp>(
        a.v[0] + b.v[0],
        a.v[1] + b.v[1],
        a.v[2] + b.v[2],
        a.v[3] + b.v[3]);
}


template <typename _Tp>
_Scalar<_Tp> operator - (const _Scalar<_Tp>& a, const _Scalar<_Tp>& b)
{
    return _Scalar<_Tp>(
        saturate_cast<_Tp>(a.v[0] - b.v[0]),
        saturate_cast<_Tp>(a.v[1] - b.v[1]),
        saturate_cast<_Tp>(a.v[2] - b.v[2]),
        saturate_cast<_Tp>(a.v[3] - b.v[3]));
}

template<typename _Tp>
_Scalar<_Tp> operator * (const _Scalar<_Tp>& a, _Tp v)
{
    return _Scalar<_Tp>(a.v[0] * v,
        a.v[1] * v,
        a.v[2] * v,
        a.v[3] * v);
}


template<typename _Tp>
_Scalar<_Tp> operator * (_Tp v, const _Scalar<_Tp>& a)
{
    return a * v;
}

template<typename _Tp>
_Scalar<_Tp> operator - (const _Scalar<_Tp>& s)
{
    return _Scalar<_Tp>(
        saturate_cast<_Tp>(-s.v[0]),
        saturate_cast<_Tp>(-s.v[1]),
        saturate_cast<_Tp>(-s.v[2]),
        saturate_cast<_Tp>(-s.v[3]));
}

template <typename _Tp>
std::ostream &operator<<(std::ostream & os, const _Scalar<_Tp> &item)
{
    os << "[" << item[0] << ", " << item[1] << ", " << item[2] << ", " << item[3] << "]";
    return os;
}

};

#endif //! ALCHEMY_CORE_TYPES_HPP