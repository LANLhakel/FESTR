#ifndef LANL_ASC_PEM_BYTES_H_
#define LANL_ASC_PEM_BYTES_H_

/**
 * @file bytes.h
 * @brief Object serialization and deserialization.
 * @author Peter Hakel
 * @version 0.0
 * @date Created on 23 November 2020\n
 * Last modified on 9 January 2021
 * @copyright (c) 2020, Triad National Security, LLC.
 * All rights reserved.\n
 */

#include <cstdlib>
#include <cstring>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

//-----------------------------------------------------------------------------

/**
 * @brief Object serialization and deserialization of fundamental types and
 *        1-D std::vectors of fundamental types, and packing/unpacking them
 *        into std::tuples
 */
struct bytes
{
    /**
     * @brief Data size in bytes
     * @param[in] d Data
     * @return Data size in bytes
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value, int>::type
    size_of(const T d)
    {
        return sizeof(d);
    }

    /**
     * @brief Data size in bytes
     * @param[in] d String data
     * @return Data size in bytes
     */
    static int size_of(const std::string& d)
    {
        return d.size() + 1;
    }

    /**
     * @brief Data size in bytes
     * @param[in] d Vector of data
     * @return Data size in bytes
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value, int>::type
    size_of(const std::vector<T>& d)
    {
        return d.size() * sizeof(T);
    }

    /**
     * @brief Data size in bytes
     * @param[in] d Vector of string data
     * @return Data size in bytes
     */
    static int size_of(const std::vector<std::string>& d)
    {
        int nbytes = 0;
        int n = d.size();
        for (int i = 0; i < n; ++i) nbytes += size_of(d[i]);
        return nbytes;
    }

//-----------------------------------------------------------------------------

    /**
     * @brief Pack data
     * @param[in, out] b Buffer
     * @param[in] d Data
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value>::type
    pack_data(char *b, const T d)
    {
        memcpy(b, &d, sizeof(d));
    }

    /**
     * @brief Pack data
     * @param[in, out] b Buffer
     * @param[in] d String data
     */
    static void pack_data(char *b, const std::string& d)
    {
        strcpy(b, d.c_str());
    }

    /**
     * @brief Pack data
     * @param[in, out] b Buffer
     * @param[in] d Vector of data
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value>::type
    pack_data(char *b, const std::vector<T>& d)
    {
        int n = d.size();
        int chunk_size = sizeof(T);
        int c = 0;
        for (int i = 0; i < n; ++i)
        {
            memcpy(b+c, &d[i], chunk_size);
            c += chunk_size;
        }
    }

    /**
     * @brief Pack data
     * @param[in, out] b Buffer
     * @param[in] d Vector of string data
     */
    static void pack_data(char *b, const std::vector<std::string>& d)
    {
        int n = d.size();
        int c = 0;
        for (int i = 0; i < n; ++i)
        {
            strcpy(b+c, d[i].c_str());
            c += size_of(d[i]);
        }
    }

//-----------------------------------------------------------------------------

    /**
     * @brief Unpack data
     * @param[out] d Data
     * @param[in] b Buffer
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value>::type
    unpack_data(T& d, const char *b)
    {
        memcpy(&d, b, sizeof(d));
    }

    /**
     * @brief Unpack data
     * @param[out] d Data
     * @param[in] b Buffer
     */
    static void unpack_data(std::string& d, const char *b)
    {
        d = b;
    }

    /**
     * @brief Unpack vector of data
     * @param[out] d Vector of data
     * @param[in] b Buffer
     * @param[in] n Number of elements
     */
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value>::type
    unpack_data_vector(std::vector<T>& d, const char *b, const int n)
    {
        d.resize(n);
        int chunk_size = sizeof(T);
        int c = 0;
        for (int i = 0; i < n; ++i)
        {
            memcpy(&d[i], b+c, chunk_size);
            c += chunk_size;
        }
    }

    /**
     * @brief Unpack vector of data
     * @param[out] d Vector of data
     * @param[in] b Buffer
     * @param[in] n Number of elements
     */
    static void unpack_data_vector(std::vector<std::string>& d, const char *b, const int n)
    {
        d.resize(n, "");
        int c = 0;
        for (int i = 0; i < n; ++i)
        {
            d[i] = b+c;
            c += strlen(b+c) + 1;
        }
    }

//-----------------------------------------------------------------------------

    /// Detect std::vector trait
    template <typename>
    struct is_std_vector : std::false_type {};

    template <typename T, typename A>
    struct is_std_vector<std::vector<T,A>> : std::true_type {};

//-----------------------------------------------------------------------------

    /**
     * @brief Size of a tuple in bytes
     * @param[in] t Tuple of data
     * @return t Size of a tuple in bytes
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts), int>::type
    size_of_tuple(std::tuple<Ts...> t)
    {
        return size_of(std::get<I>(t)) + size_of_tuple<I+1>(t);
    }

    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts), int>::type
    size_of_tuple(std::tuple<Ts...> t)
    {
        return 0; // base case (already iterated through all members)
    }

//-----------------------------------------------------------------------------

    /**
     * @brief Pack tuple into buffer
     * @param[in,out] b Buffer
     * @param[in] t Tuple of data
     * @param[in] c Buffer cursor
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts)>::type
    pack_tuple(char *b, std::tuple<Ts...> t, const int c = 0)
    {
        pack_data(b+c, std::get<I>(t));
        pack_tuple<I+1>(b, t, c + size_of(std::get<I>(t)));
    }

    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts)>::type
    pack_tuple(char *b, std::tuple<Ts...> t, const int c = 0) {}

//-----------------------------------------------------------------------------

    /// Extract the fundamental data type
    template <typename T>
    struct get_ftype {using type = T;};

    template <typename T>
    struct get_ftype<std::vector<T>> {using type = T;};

//-----------------------------------------------------------------------------

    /// Assign data values if their data types match
    template <typename Ltype, typename Rtype>
    static typename std::enable_if<std::is_same<Ltype, Rtype>::value>::type
    assign_data(Ltype& lhs, Rtype&& rhs) {lhs = std::forward<Rtype>(rhs);}

    template <typename Ltype, typename Rtype>
    static typename std::enable_if<(!std::is_same<Ltype, Rtype>::value)>::type
    assign_data(Ltype& lhs, Rtype&& rhs) {}

//-----------------------------------------------------------------------------

    /**
     * @brief Unpack tuple from buffer
     * @param[in,out] t Tuple of data
     * @param[in] b Buffer
     * @param[in] c Buffer cursor
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts)>::type
    unpack_tuple(std::tuple<Ts...>& t, const char *b, const int c = 0)
    {
        using Itype = typename std::remove_reference<decltype(std::get<I>(t))>::type;
        using Ftype = typename get_ftype<Itype>::type;
        if (is_std_vector<Itype>::value)
        {
            // the number of elements is immediately preceding in the buffer
            int n = 0;
            unpack_data(n, (b+c)-sizeof(int));
            std::vector<Ftype> v;
            unpack_data_vector(v, b+c, n);
            assign_data(std::get<I>(t), std::move(v));
        }
        else // Itype is not std::vector
        {
            // unpack_data(std::get<I>(t), b+c);
            Ftype d;
            unpack_data(d, b+c);
            assign_data(std::get<I>(t), std::move(d));
        }
        unpack_tuple<I+1>(t, b, c + size_of(std::get<I>(t)));
    }

    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts)>::type
    unpack_tuple(std::tuple<Ts...>& t, const char *b, const int c = 0) {}

//-----------------------------------------------------------------------------

};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_BYTES_H_
