#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <int nb_parametre, typename type> class Point
{

public:
    std::array<type, nb_parametre> values;

    Point() = default;
    Point(type x, type y, type z) : values { x, y, z } {}
    Point(type x, type y) : values { x, y } { assert(nb_parametre == 2); }
    Point(std::array<type, nb_parametre> v) : values { v } {}

    type& x() { return values[0]; }
    type x() const { return values[0]; }

    type& y()
    {
        static_assert(nb_parametre > 1);
        return values[1];
    }
    type y() const
    {
        static_assert(nb_parametre > 1);
        return values[1];
    }

    type& z()
    {
        static_assert(nb_parametre > 2);
        return values[2];
    }
    type z() const
    {
        static_assert(nb_parametre > 2);
        return values[2];
    }

    Point<nb_parametre, type>& operator+=(const Point<nb_parametre, type>& other)
    {
        int i = 0;
        std::transform(values.begin(), values.end(), values.begin(),
                       [&i, &other](const type v) { return other.values[i++] + v; });
        return *this;
    }

    Point<nb_parametre, type>& operator-=(const Point<nb_parametre, type>& other)
    {
        int i = 0;
        std::transform(values.begin(), values.end(), values.begin(),
                       [&i, &other](const type v) { return v - other.values[i++]; });
        return *this;
    }

    Point<nb_parametre, type>& operator*=(const type scalar)
    {
        std::transform(values.begin(), values.end(), values.begin(),
                       [scalar](const type v) { return v * scalar; });
        return *this;
    }

    Point<nb_parametre, type> operator+(const Point<nb_parametre, type>& other) const
    {
        Point<nb_parametre, type> result = *this;
        result += other;
        return result;
    }

    Point<nb_parametre, type> operator-(const Point<nb_parametre, type>& other) const
    {
        Point<nb_parametre, type> result = *this;
        result -= other;
        return result;
    }

    Point<nb_parametre, type> operator*(const type scalar) const
    {
        Point<nb_parametre, type> result = *this;
        result *= scalar;
        return result;
    }

    Point<nb_parametre, type> operator*(const Point<2, float> scalar) const
    {
        Point<nb_parametre, type> result = *this;
        result *= scalar;
        return result;
    }

    Point<nb_parametre, type>& operator*=(const Point<2, float>& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point<nb_parametre, type> operator-() const
    {
        std::array<type, nb_parametre> v;
        for (int i = 0; i < nb_parametre; i++)
        {
            v[i] = -values.at(i);
        }
        return Point<nb_parametre, type> { v };
    }

    type length() const
    {
        return std::sqrt(std::accumulate(
            values.begin(), values.end(), (type)0,
            // important ! la valeur neutre doit etre du meme type que la valeur de retour attendue !
            [](const type& v1, const type& v2) { return v1 + v2 * v2; }));
    }

    Point<nb_parametre, type>& normalize(const float target_len = 1.0f)
    {
        assert(nb_parametre == 3);
        assert(typeid(type) == typeid(float));
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point<nb_parametre, type>& cap_length(const float max_len)
    {
        assert(max_len > 0);
        assert(nb_parametre == 3);
        assert(typeid(type) == typeid(float));

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    float distance_to(const Point<3, float>& other) const
    {
        assert(nb_parametre == 3);
        assert(typeid(type) == typeid(float));
        return (*this - other).length();
    }
};