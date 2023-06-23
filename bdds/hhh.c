
bool ip_addr_eq(void* a, void* b) ;
uint32_t ip_addr_hash(void* obj) ;
void DynamicValue_allocate(void* obj) ;
void ip_addr_allocate(void* obj) ;
struct Map* map;
struct DoubleChain* dchain;
struct Vector* vector;
struct Vector* vector_1;
struct Map* map_1;
struct DoubleChain* dchain_1;
struct Vector* vector_2;
struct Vector* vector_3;
struct Map* map_2;
struct DoubleChain* dchain_2;
struct Vector* vector_4;
struct Vector* vector_5;

bool nf_init() {
  int map_allocation_succeeded__1 = map_allocate(ip_addr_eq, ip_addr_hash, 65536u, &map);

  // 1891
  // 1892
  // 1893
  // 1894
  // 1895
  // 1896
  // 1897
  // 1898
  // 1899
  // 1900
  // 1901
  // 1902
  if (map_allocation_succeeded__1) {
    int is_dchain_allocated__4 = dchain_allocate(65536u, &dchain);

    // 1891
    // 1892
    // 1893
    // 1894
    // 1895
    // 1896
    // 1897
    // 1898
    // 1899
    // 1900
    // 1901
    if (is_dchain_allocated__4) {
      int vector_alloc_success__7 = vector_allocate(16u, 65536u, DynamicValue_allocate, &vector);

      // 1891
      // 1892
      // 1893
      // 1894
      // 1895
      // 1896
      // 1897
      // 1898
      // 1899
      // 1900
      if (vector_alloc_success__7) {
        int vector_alloc_success__10 = vector_allocate(4u, 65536u, ip_addr_allocate, &vector_1);

        // 1891
        // 1892
        // 1893
        // 1894
        // 1895
        // 1896
        // 1897
        // 1898
        // 1899
        if (vector_alloc_success__10) {
          int map_allocation_succeeded__13 = map_allocate(ip_addr_eq, ip_addr_hash, 65536u, &map_1);

          // 1891
          // 1892
          // 1893
          // 1894
          // 1895
          // 1896
          // 1897
          // 1898
          if (map_allocation_succeeded__13) {
            int is_dchain_allocated__16 = dchain_allocate(65536u, &dchain_1);

            // 1891
            // 1892
            // 1893
            // 1894
            // 1895
            // 1896
            // 1897
            if (is_dchain_allocated__16) {
              int vector_alloc_success__19 = vector_allocate(16u, 65536u, DynamicValue_allocate, &vector_2);

              // 1891
              // 1892
              // 1893
              // 1894
              // 1895
              // 1896
              if (vector_alloc_success__19) {
                int vector_alloc_success__22 = vector_allocate(4u, 65536u, ip_addr_allocate, &vector_3);

                // 1891
                // 1892
                // 1893
                // 1894
                // 1895
                if (vector_alloc_success__22) {
                  int map_allocation_succeeded__25 = map_allocate(ip_addr_eq, ip_addr_hash, 65536u, &map_2);

                  // 1891
                  // 1892
                  // 1893
                  // 1894
                  if (map_allocation_succeeded__25) {
                    int is_dchain_allocated__28 = dchain_allocate(65536u, &dchain_2);

                    // 1891
                    // 1892
                    // 1893
                    if (is_dchain_allocated__28) {
                      int vector_alloc_success__31 = vector_allocate(16u, 65536u, DynamicValue_allocate, &vector_4);

                      // 1891
                      // 1892
                      if (vector_alloc_success__31) {
                        int vector_alloc_success__34 = vector_allocate(4u, 65536u, ip_addr_allocate, &vector_5);

                        // 1891
                        if (vector_alloc_success__34) {
                          return 1;
                        }

                        // 1892
                        else {
                          return 0;
                        } // !vector_alloc_success__34

                      }

                      // 1893
                      else {
                        return 0;
                      } // !vector_alloc_success__31

                    }

                    // 1894
                    else {
                      return 0;
                    } // !is_dchain_allocated__28

                  }

                  // 1895
                  else {
                    return 0;
                  } // !map_allocation_succeeded__25

                }

                // 1896
                else {
                  return 0;
                } // !vector_alloc_success__22

              }

              // 1897
              else {
                return 0;
              } // !vector_alloc_success__19

            }

            // 1898
            else {
              return 0;
            } // !is_dchain_allocated__16

          }

          // 1899
          else {
            return 0;
          } // !map_allocation_succeeded__13

        }

        // 1900
        else {
          return 0;
        } // !vector_alloc_success__10

      }

      // 1901
      else {
        return 0;
      } // !vector_alloc_success__7

    }

    // 1902
    else {
      return 0;
    } // !is_dchain_allocated__4

  }

  // 1903
  else {
    return 0;
  } // !map_allocation_succeeded__1

}

int nf_process(uint16_t device, uint8_t* packet, uint16_t packet_length, int64_t now) {
  struct rte_ether_hdr* ether_header_1 = (struct rte_ether_hdr*)(packet);

  // 1905
  // 1906
  // 1907
  // 1908
  // 1909
  // 1910
  // 1911
  // 1912
  // 1913
  // 1914
  // 1915
  // 1916
  // 1917
  // 1918
  // 1919
  // 1920
  // 1921
  // 1922
  // 1923
  // 1924
  // 1925
  // 1926
  // 1927
  // 1928
  // 1929
  // 1930
  // 1931
  // 1932
  // 1933
  // 1934
  // 1935
  // 1936
  // 1937
  // 1938
  // 1939
  // 1940
  // 1941
  // 1942
  // 1943
  // 1944
  // 1945
  // 1946
  // 1947
  // 1948
  // 1949
  // 1950
  // 1951
  // 1952
  // 1953
  // 1954
  // 1955
  // 1956
  // 1957
  // 1958
  // 1959
  // 1960
  // 1961
  // 1962
  // 1963
  // 1964
  // 1965
  // 1966
  // 1967
  // 1968
  // 1969
  // 1970
  // 1971
  // 1972
  // 1973
  // 1974
  // 1975
  // 1976
  // 1977
  // 1978
  // 1979
  // 1980
  // 1981
  // 1982
  // 1983
  // 1984
  // 1985
  // 1986
  // 1987
  // 1988
  // 1989
  // 1990
  // 1991
  // 1992
  // 1993
  // 1994
  // 1995
  // 1996
  // 1997
  // 1998
  // 1999
  // 2000
  // 2001
  // 2002
  // 2003
  // 2004
  // 2005
  // 2006
  // 2007
  // 2008
  // 2009
  // 2010
  // 2011
  // 2012
  // 2013
  // 2014
  // 2015
  // 2016
  // 2017
  // 2018
  // 2019
  // 2020
  // 2021
  // 2022
  // 2023
  // 2024
  // 2025
  // 2026
  // 2027
  // 2028
  // 2029
  // 2030
  // 2031
  // 2032
  // 2033
  // 2034
  // 2035
  // 2036
  // 2037
  // 2038
  // 2039
  // 2040
  // 2041
  // 2042
  // 2043
  // 2044
  // 2045
  // 2046
  // 2047
  // 2048
  // 2049
  // 2050
  // 2051
  // 2052
  // 2053
  // 2054
  // 2055
  // 2056
  // 2057
  // 2058
  // 2059
  // 2060
  // 2061
  if (0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul))) {
    struct rte_ipv4_hdr* ipv4_header_1 = (struct rte_ipv4_hdr*)(packet + 14u);
    int number_of_freed_flows__56 = expire_items_single_map(dchain, vector_1, map, now - 6000000000000000ul);
    int number_of_freed_flows__57 = expire_items_single_map(dchain_1, vector_3, map_1, now - 6000000000000000ul);
    int number_of_freed_flows__58 = expire_items_single_map(dchain_2, vector_5, map_2, now - 6000000000000000ul);

    // 1905
    if (device) {
      return 0;
    }

    // 1906
    // 1907
    // 1908
    // 1909
    // 1910
    // 1911
    // 1912
    // 1913
    // 1914
    // 1915
    // 1916
    // 1917
    // 1918
    // 1919
    // 1920
    // 1921
    // 1922
    // 1923
    // 1924
    // 1925
    // 1926
    // 1927
    // 1928
    // 1929
    // 1930
    // 1931
    // 1932
    // 1933
    // 1934
    // 1935
    // 1936
    // 1937
    // 1938
    // 1939
    // 1940
    // 1941
    // 1942
    // 1943
    // 1944
    // 1945
    // 1946
    // 1947
    // 1948
    // 1949
    // 1950
    // 1951
    // 1952
    // 1953
    // 1954
    // 1955
    // 1956
    // 1957
    // 1958
    // 1959
    // 1960
    // 1961
    // 1962
    // 1963
    // 1964
    // 1965
    // 1966
    // 1967
    // 1968
    // 1969
    // 1970
    // 1971
    // 1972
    // 1973
    // 1974
    // 1975
    // 1976
    // 1977
    // 1978
    // 1979
    // 1980
    // 1981
    // 1982
    // 1983
    // 1984
    // 1985
    // 1986
    // 1987
    // 1988
    // 1989
    // 1990
    // 1991
    // 1992
    // 1993
    // 1994
    // 1995
    // 1996
    // 1997
    // 1998
    // 1999
    // 2000
    // 2001
    // 2002
    // 2003
    // 2004
    // 2005
    // 2006
    // 2007
    // 2008
    // 2009
    // 2010
    // 2011
    // 2012
    // 2013
    // 2014
    // 2015
    // 2016
    // 2017
    // 2018
    // 2019
    // 2020
    // 2021
    // 2022
    // 2023
    // 2024
    // 2025
    // 2026
    // 2027
    // 2028
    // 2029
    // 2030
    // 2031
    // 2032
    // 2033
    // 2034
    // 2035
    // 2036
    // 2037
    // 2038
    // 2039
    // 2040
    // 2041
    // 2042
    // 2043
    // 2044
    // 2045
    // 2046
    // 2047
    // 2048
    // 2049
    // 2050
    // 2051
    // 2052
    // 2053
    // 2054
    // 2055
    // 2056
    // 2057
    // 2058
    // 2059
    // 2060
    // 2061
    else {
      uint8_t map_key[4];
      map_key[0u] = ipv4_header_1->src_addr & 0xff;
      map_key[1u] = 0u;
      map_key[2u] = 0u;
      map_key[3u] = 0u;
      int map_value_out;
      int map_has_this_key__68 = map_get(map, &map_key, &map_value_out);

      // 1906
      // 1907
      // 1908
      // 1909
      // 1910
      // 1911
      // 1912
      // 1913
      // 1914
      // 1915
      // 1916
      // 1917
      // 1918
      // 1919
      // 1920
      // 1921
      // 1922
      // 1923
      // 1924
      // 1925
      // 1926
      // 1927
      // 1928
      // 1929
      // 1930
      // 1931
      // 1932
      // 1933
      // 1934
      // 1935
      // 1936
      // 1937
      if (0u == map_has_this_key__68) {
        uint32_t new_index__71;
        int out_of_space__71 = !dchain_allocate_new_index(dchain, &new_index__71, now);

        // 1906
        // 1907
        // 1908
        // 1909
        // 1910
        // 1911
        // 1912
        // 1913
        // 1914
        // 1915
        // 1916
        // 1917
        // 1918
        // 1919
        // 1920
        // 1921
        // 1922
        // 1923
        // 1924
        // 1925
        // 1926
        // 1927
        // 1928
        // 1929
        // 1930
        // 1931
        // 1932
        // 1933
        // 1934
        // 1935
        // 1936
        if (false == ((out_of_space__71) & (0u == number_of_freed_flows__56))) {
          uint8_t* vector_value_out = 0u;
          vector_borrow(vector_1, new_index__71, (void**)(&vector_value_out));
          vector_value_out[0u] = ipv4_header_1->src_addr & 0xff;
          vector_value_out[1u] = 0u;
          vector_value_out[2u] = 0u;
          vector_value_out[3u] = 0u;
          uint8_t* vector_value_out_1 = 0u;
          vector_borrow(vector, new_index__71, (void**)(&vector_value_out_1));
          vector_value_out_1[0u] = 3750000000ul - packet_length;
          vector_value_out_1[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
          vector_value_out_1[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
          vector_value_out_1[3u] = 223u;
          vector_value_out_1[4u] = 0u;
          vector_value_out_1[5u] = 0u;
          vector_value_out_1[6u] = 0u;
          vector_value_out_1[7u] = 0u;
          vector_value_out_1[8u] = now & 0xff;
          vector_value_out_1[9u] = (now >> 8) & 0xff;
          vector_value_out_1[10u] = (now >> 16) & 0xff;
          vector_value_out_1[11u] = (now >> 24) & 0xff;
          vector_value_out_1[12u] = (now >> 32) & 0xff;
          vector_value_out_1[13u] = (now >> 40) & 0xff;
          vector_value_out_1[14u] = (now >> 48) & 0xff;
          vector_value_out_1[15u] = (now >> 56) & 0xff;
          map_put(map, vector_value_out, new_index__71);
          vector_return(vector_1, new_index__71, vector_value_out);
          vector_return(vector, new_index__71, vector_value_out_1);
          uint8_t map_key_1[4];
          map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
          map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
          map_key_1[2u] = 0u;
          map_key_1[3u] = 0u;
          int map_value_out_1;
          int map_has_this_key__79 = map_get(map_1, &map_key_1, &map_value_out_1);

          // 1906
          // 1907
          // 1908
          // 1909
          // 1910
          // 1911
          // 1912
          if (0u == map_has_this_key__79) {
            uint32_t new_index__82;
            int out_of_space__82 = !dchain_allocate_new_index(dchain_1, &new_index__82, now);

            // 1906
            // 1907
            // 1908
            // 1909
            // 1910
            // 1911
            if (false == ((out_of_space__82) & (0u == number_of_freed_flows__57))) {
              uint8_t* vector_value_out_2 = 0u;
              vector_borrow(vector_3, new_index__82, (void**)(&vector_value_out_2));
              vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
              vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              vector_value_out_2[2u] = 0u;
              vector_value_out_2[3u] = 0u;
              uint8_t* vector_value_out_3 = 0u;
              vector_borrow(vector_2, new_index__82, (void**)(&vector_value_out_3));
              vector_value_out_3[0u] = 3750000000ul - packet_length;
              vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
              vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
              vector_value_out_3[3u] = 223u;
              vector_value_out_3[4u] = 0u;
              vector_value_out_3[5u] = 0u;
              vector_value_out_3[6u] = 0u;
              vector_value_out_3[7u] = 0u;
              vector_value_out_3[8u] = now & 0xff;
              vector_value_out_3[9u] = (now >> 8) & 0xff;
              vector_value_out_3[10u] = (now >> 16) & 0xff;
              vector_value_out_3[11u] = (now >> 24) & 0xff;
              vector_value_out_3[12u] = (now >> 32) & 0xff;
              vector_value_out_3[13u] = (now >> 40) & 0xff;
              vector_value_out_3[14u] = (now >> 48) & 0xff;
              vector_value_out_3[15u] = (now >> 56) & 0xff;
              map_put(map_1, vector_value_out_2, new_index__82);
              vector_return(vector_3, new_index__82, vector_value_out_2);
              vector_return(vector_2, new_index__82, vector_value_out_3);
              uint8_t map_key_2[4];
              map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_2[3u] = 0u;
              int map_value_out_2;
              int map_has_this_key__90 = map_get(map_2, &map_key_2, &map_value_out_2);

              // 1906
              // 1907
              if (0u == map_has_this_key__90) {
                uint32_t new_index__93;
                int out_of_space__93 = !dchain_allocate_new_index(dchain_2, &new_index__93, now);

                // 1906
                if (false == ((out_of_space__93) & (0u == number_of_freed_flows__58))) {
                  uint8_t* vector_value_out_4 = 0u;
                  vector_borrow(vector_5, new_index__93, (void**)(&vector_value_out_4));
                  vector_value_out_4[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_4[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_4[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  vector_value_out_4[3u] = 0u;
                  uint8_t* vector_value_out_5 = 0u;
                  vector_borrow(vector_4, new_index__93, (void**)(&vector_value_out_5));
                  vector_value_out_5[0u] = 3750000000ul - packet_length;
                  vector_value_out_5[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_5[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_5[3u] = 223u;
                  vector_value_out_5[4u] = 0u;
                  vector_value_out_5[5u] = 0u;
                  vector_value_out_5[6u] = 0u;
                  vector_value_out_5[7u] = 0u;
                  vector_value_out_5[8u] = now & 0xff;
                  vector_value_out_5[9u] = (now >> 8) & 0xff;
                  vector_value_out_5[10u] = (now >> 16) & 0xff;
                  vector_value_out_5[11u] = (now >> 24) & 0xff;
                  vector_value_out_5[12u] = (now >> 32) & 0xff;
                  vector_value_out_5[13u] = (now >> 40) & 0xff;
                  vector_value_out_5[14u] = (now >> 48) & 0xff;
                  vector_value_out_5[15u] = (now >> 56) & 0xff;
                  map_put(map_2, vector_value_out_4, new_index__93);
                  vector_return(vector_5, new_index__93, vector_value_out_4);
                  vector_return(vector_4, new_index__93, vector_value_out_5);
                  return 1;
                }

                // 1907
                else {
                  return 1;
                } // !(false == ((out_of_space__93) & (0u == number_of_freed_flows__58)))

              }

              // 1908
              // 1909
              // 1910
              // 1911
              else {
                dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                uint8_t* vector_value_out_4 = 0u;
                vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_4));
                vector_value_out_4[0u] = 3750000000ul - packet_length;
                vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_4[3u] = 223u;
                vector_value_out_4[4u] = 0u;
                vector_value_out_4[5u] = 0u;
                vector_value_out_4[6u] = 0u;
                vector_value_out_4[7u] = 0u;
                vector_value_out_4[8u] = now & 0xff;
                vector_value_out_4[9u] = (now >> 8) & 0xff;
                vector_value_out_4[10u] = (now >> 16) & 0xff;
                vector_value_out_4[11u] = (now >> 24) & 0xff;
                vector_value_out_4[12u] = (now >> 32) & 0xff;
                vector_value_out_4[13u] = (now >> 40) & 0xff;
                vector_value_out_4[14u] = (now >> 48) & 0xff;
                vector_value_out_4[15u] = (now >> 56) & 0xff;

                // 1908
                // 1909
                // 1910
                if ((now - vector_value_out_4[8ul]) < 6000000000000000ul) {

                  // 1908
                  // 1909
                  if (false == (3750000000ul < (vector_value_out_4[0ul] + ((625ul * (now - vector_value_out_4[8ul])) / 1000000000ul)))) {

                    // 1908
                    if (false == (packet_length < (vector_value_out_4[0ul] + ((625ul * (now - vector_value_out_4[8ul])) / 1000000000ul)))) {
                      vector_return(vector_4, map_value_out_2, vector_value_out_4);
                      return 1;
                    }

                    // 1909
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_4);
                      return 1;
                    } // !(false == (packet_length < (vector_value_out_4[0ul] + ((625ul * (now - vector_value_out_4[8ul])) / 1000000000ul))))

                  }

                  // 1910
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_4);
                    return 1;
                  } // !(false == (3750000000ul < (vector_value_out_4[0ul] + ((625ul * (now - vector_value_out_4[8ul])) / 1000000000ul))))

                }

                // 1911
                else {
                  vector_return(vector_4, map_value_out_2, vector_value_out_4);
                  return 1;
                } // !((now - vector_value_out_4[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__90)

            }

            // 1912
            else {
              return 1;
            } // !(false == ((out_of_space__82) & (0u == number_of_freed_flows__57)))

          }

          // 1913
          // 1914
          // 1915
          // 1916
          // 1917
          // 1918
          // 1919
          // 1920
          // 1921
          // 1922
          // 1923
          // 1924
          // 1925
          // 1926
          // 1927
          // 1928
          // 1929
          // 1930
          // 1931
          // 1932
          // 1933
          // 1934
          // 1935
          // 1936
          else {
            dchain_rejuvenate_index(dchain_1, map_value_out_1, now);
            uint8_t* vector_value_out_2 = 0u;
            vector_borrow(vector_2, map_value_out_1, (void**)(&vector_value_out_2));
            vector_value_out_2[0u] = 3750000000ul - packet_length;
            vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
            vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
            vector_value_out_2[3u] = 223u;
            vector_value_out_2[4u] = 0u;
            vector_value_out_2[5u] = 0u;
            vector_value_out_2[6u] = 0u;
            vector_value_out_2[7u] = 0u;
            vector_value_out_2[8u] = now & 0xff;
            vector_value_out_2[9u] = (now >> 8) & 0xff;
            vector_value_out_2[10u] = (now >> 16) & 0xff;
            vector_value_out_2[11u] = (now >> 24) & 0xff;
            vector_value_out_2[12u] = (now >> 32) & 0xff;
            vector_value_out_2[13u] = (now >> 40) & 0xff;
            vector_value_out_2[14u] = (now >> 48) & 0xff;
            vector_value_out_2[15u] = (now >> 56) & 0xff;

            // 1913
            // 1914
            // 1915
            // 1916
            // 1917
            // 1918
            // 1919
            // 1920
            // 1921
            // 1922
            // 1923
            // 1924
            // 1925
            // 1926
            // 1927
            // 1928
            // 1929
            // 1930
            if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

              // 1913
              // 1914
              // 1915
              // 1916
              // 1917
              // 1918
              // 1919
              // 1920
              // 1921
              // 1922
              // 1923
              // 1924
              if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                // 1913
                // 1914
                // 1915
                // 1916
                // 1917
                // 1918
                if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                  vector_return(vector_2, map_value_out_1, vector_value_out_2);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__171 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1913
                  // 1914
                  if (0u == map_has_this_key__171) {
                    uint32_t new_index__174;
                    int out_of_space__174 = !dchain_allocate_new_index(dchain_2, &new_index__174, now);

                    // 1913
                    if (false == ((out_of_space__174) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_5, new_index__174, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_3[3u] = 0u;
                      uint8_t* vector_value_out_4 = 0u;
                      vector_borrow(vector_4, new_index__174, (void**)(&vector_value_out_4));
                      vector_value_out_4[0u] = 3750000000ul - packet_length;
                      vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_4[3u] = 223u;
                      vector_value_out_4[4u] = 0u;
                      vector_value_out_4[5u] = 0u;
                      vector_value_out_4[6u] = 0u;
                      vector_value_out_4[7u] = 0u;
                      vector_value_out_4[8u] = now & 0xff;
                      vector_value_out_4[9u] = (now >> 8) & 0xff;
                      vector_value_out_4[10u] = (now >> 16) & 0xff;
                      vector_value_out_4[11u] = (now >> 24) & 0xff;
                      vector_value_out_4[12u] = (now >> 32) & 0xff;
                      vector_value_out_4[13u] = (now >> 40) & 0xff;
                      vector_value_out_4[14u] = (now >> 48) & 0xff;
                      vector_value_out_4[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_3, new_index__174);
                      vector_return(vector_5, new_index__174, vector_value_out_3);
                      vector_return(vector_4, new_index__174, vector_value_out_4);
                      return 1;
                    }

                    // 1914
                    else {
                      return 1;
                    } // !(false == ((out_of_space__174) & (0u == number_of_freed_flows__58)))

                  }

                  // 1915
                  // 1916
                  // 1917
                  // 1918
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;

                    // 1915
                    // 1916
                    // 1917
                    if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                      // 1915
                      // 1916
                      if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                        // 1915
                        if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        }

                        // 1916
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                      }

                      // 1917
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 1918
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__171)

                }

                // 1919
                // 1920
                // 1921
                // 1922
                // 1923
                // 1924
                else {
                  vector_return(vector_2, map_value_out_1, vector_value_out_2);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__237 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1919
                  // 1920
                  if (0u == map_has_this_key__237) {
                    uint32_t new_index__240;
                    int out_of_space__240 = !dchain_allocate_new_index(dchain_2, &new_index__240, now);

                    // 1919
                    if (false == ((out_of_space__240) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_5, new_index__240, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_3[3u] = 0u;
                      uint8_t* vector_value_out_4 = 0u;
                      vector_borrow(vector_4, new_index__240, (void**)(&vector_value_out_4));
                      vector_value_out_4[0u] = 3750000000ul - packet_length;
                      vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_4[3u] = 223u;
                      vector_value_out_4[4u] = 0u;
                      vector_value_out_4[5u] = 0u;
                      vector_value_out_4[6u] = 0u;
                      vector_value_out_4[7u] = 0u;
                      vector_value_out_4[8u] = now & 0xff;
                      vector_value_out_4[9u] = (now >> 8) & 0xff;
                      vector_value_out_4[10u] = (now >> 16) & 0xff;
                      vector_value_out_4[11u] = (now >> 24) & 0xff;
                      vector_value_out_4[12u] = (now >> 32) & 0xff;
                      vector_value_out_4[13u] = (now >> 40) & 0xff;
                      vector_value_out_4[14u] = (now >> 48) & 0xff;
                      vector_value_out_4[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_3, new_index__240);
                      vector_return(vector_5, new_index__240, vector_value_out_3);
                      vector_return(vector_4, new_index__240, vector_value_out_4);
                      return 1;
                    }

                    // 1920
                    else {
                      return 1;
                    } // !(false == ((out_of_space__240) & (0u == number_of_freed_flows__58)))

                  }

                  // 1921
                  // 1922
                  // 1923
                  // 1924
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;

                    // 1921
                    // 1922
                    // 1923
                    if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                      // 1921
                      // 1922
                      if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                        // 1921
                        if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        }

                        // 1922
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                      }

                      // 1923
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 1924
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__237)

                } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

              }

              // 1925
              // 1926
              // 1927
              // 1928
              // 1929
              // 1930
              else {
                vector_return(vector_2, map_value_out_1, vector_value_out_2);
                uint8_t map_key_2[4];
                map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                map_key_2[3u] = 0u;
                int map_value_out_2;
                int map_has_this_key__303 = map_get(map_2, &map_key_2, &map_value_out_2);

                // 1925
                // 1926
                if (0u == map_has_this_key__303) {
                  uint32_t new_index__306;
                  int out_of_space__306 = !dchain_allocate_new_index(dchain_2, &new_index__306, now);

                  // 1925
                  if (false == ((out_of_space__306) & (0u == number_of_freed_flows__58))) {
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_5, new_index__306, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                    vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    vector_value_out_3[3u] = 0u;
                    uint8_t* vector_value_out_4 = 0u;
                    vector_borrow(vector_4, new_index__306, (void**)(&vector_value_out_4));
                    vector_value_out_4[0u] = 3750000000ul - packet_length;
                    vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_4[3u] = 223u;
                    vector_value_out_4[4u] = 0u;
                    vector_value_out_4[5u] = 0u;
                    vector_value_out_4[6u] = 0u;
                    vector_value_out_4[7u] = 0u;
                    vector_value_out_4[8u] = now & 0xff;
                    vector_value_out_4[9u] = (now >> 8) & 0xff;
                    vector_value_out_4[10u] = (now >> 16) & 0xff;
                    vector_value_out_4[11u] = (now >> 24) & 0xff;
                    vector_value_out_4[12u] = (now >> 32) & 0xff;
                    vector_value_out_4[13u] = (now >> 40) & 0xff;
                    vector_value_out_4[14u] = (now >> 48) & 0xff;
                    vector_value_out_4[15u] = (now >> 56) & 0xff;
                    map_put(map_2, vector_value_out_3, new_index__306);
                    vector_return(vector_5, new_index__306, vector_value_out_3);
                    vector_return(vector_4, new_index__306, vector_value_out_4);
                    return 1;
                  }

                  // 1926
                  else {
                    return 1;
                  } // !(false == ((out_of_space__306) & (0u == number_of_freed_flows__58)))

                }

                // 1927
                // 1928
                // 1929
                // 1930
                else {
                  dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                  uint8_t* vector_value_out_3 = 0u;
                  vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                  vector_value_out_3[0u] = 3750000000ul - packet_length;
                  vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_3[3u] = 223u;
                  vector_value_out_3[4u] = 0u;
                  vector_value_out_3[5u] = 0u;
                  vector_value_out_3[6u] = 0u;
                  vector_value_out_3[7u] = 0u;
                  vector_value_out_3[8u] = now & 0xff;
                  vector_value_out_3[9u] = (now >> 8) & 0xff;
                  vector_value_out_3[10u] = (now >> 16) & 0xff;
                  vector_value_out_3[11u] = (now >> 24) & 0xff;
                  vector_value_out_3[12u] = (now >> 32) & 0xff;
                  vector_value_out_3[13u] = (now >> 40) & 0xff;
                  vector_value_out_3[14u] = (now >> 48) & 0xff;
                  vector_value_out_3[15u] = (now >> 56) & 0xff;

                  // 1927
                  // 1928
                  // 1929
                  if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                    // 1927
                    // 1928
                    if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                      // 1927
                      if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      }

                      // 1928
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 1929
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                  }

                  // 1930
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_3);
                    return 1;
                  } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                } // !(0u == map_has_this_key__303)

              } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

            }

            // 1931
            // 1932
            // 1933
            // 1934
            // 1935
            // 1936
            else {
              vector_return(vector_2, map_value_out_1, vector_value_out_2);
              uint8_t map_key_2[4];
              map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_2[3u] = 0u;
              int map_value_out_2;
              int map_has_this_key__369 = map_get(map_2, &map_key_2, &map_value_out_2);

              // 1931
              // 1932
              if (0u == map_has_this_key__369) {
                uint32_t new_index__372;
                int out_of_space__372 = !dchain_allocate_new_index(dchain_2, &new_index__372, now);

                // 1931
                if (false == ((out_of_space__372) & (0u == number_of_freed_flows__58))) {
                  uint8_t* vector_value_out_3 = 0u;
                  vector_borrow(vector_5, new_index__372, (void**)(&vector_value_out_3));
                  vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  vector_value_out_3[3u] = 0u;
                  uint8_t* vector_value_out_4 = 0u;
                  vector_borrow(vector_4, new_index__372, (void**)(&vector_value_out_4));
                  vector_value_out_4[0u] = 3750000000ul - packet_length;
                  vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_4[3u] = 223u;
                  vector_value_out_4[4u] = 0u;
                  vector_value_out_4[5u] = 0u;
                  vector_value_out_4[6u] = 0u;
                  vector_value_out_4[7u] = 0u;
                  vector_value_out_4[8u] = now & 0xff;
                  vector_value_out_4[9u] = (now >> 8) & 0xff;
                  vector_value_out_4[10u] = (now >> 16) & 0xff;
                  vector_value_out_4[11u] = (now >> 24) & 0xff;
                  vector_value_out_4[12u] = (now >> 32) & 0xff;
                  vector_value_out_4[13u] = (now >> 40) & 0xff;
                  vector_value_out_4[14u] = (now >> 48) & 0xff;
                  vector_value_out_4[15u] = (now >> 56) & 0xff;
                  map_put(map_2, vector_value_out_3, new_index__372);
                  vector_return(vector_5, new_index__372, vector_value_out_3);
                  vector_return(vector_4, new_index__372, vector_value_out_4);
                  return 1;
                }

                // 1932
                else {
                  return 1;
                } // !(false == ((out_of_space__372) & (0u == number_of_freed_flows__58)))

              }

              // 1933
              // 1934
              // 1935
              // 1936
              else {
                dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                uint8_t* vector_value_out_3 = 0u;
                vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                vector_value_out_3[0u] = 3750000000ul - packet_length;
                vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_3[3u] = 223u;
                vector_value_out_3[4u] = 0u;
                vector_value_out_3[5u] = 0u;
                vector_value_out_3[6u] = 0u;
                vector_value_out_3[7u] = 0u;
                vector_value_out_3[8u] = now & 0xff;
                vector_value_out_3[9u] = (now >> 8) & 0xff;
                vector_value_out_3[10u] = (now >> 16) & 0xff;
                vector_value_out_3[11u] = (now >> 24) & 0xff;
                vector_value_out_3[12u] = (now >> 32) & 0xff;
                vector_value_out_3[13u] = (now >> 40) & 0xff;
                vector_value_out_3[14u] = (now >> 48) & 0xff;
                vector_value_out_3[15u] = (now >> 56) & 0xff;

                // 1933
                // 1934
                // 1935
                if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                  // 1933
                  // 1934
                  if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                    // 1933
                    if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    }

                    // 1934
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                  }

                  // 1935
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_3);
                    return 1;
                  } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                }

                // 1936
                else {
                  vector_return(vector_4, map_value_out_2, vector_value_out_3);
                  return 1;
                } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__369)

            } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

          } // !(0u == map_has_this_key__79)

        }

        // 1937
        else {
          return 1;
        } // !(false == ((out_of_space__71) & (0u == number_of_freed_flows__56)))

      }

      // 1938
      // 1939
      // 1940
      // 1941
      // 1942
      // 1943
      // 1944
      // 1945
      // 1946
      // 1947
      // 1948
      // 1949
      // 1950
      // 1951
      // 1952
      // 1953
      // 1954
      // 1955
      // 1956
      // 1957
      // 1958
      // 1959
      // 1960
      // 1961
      // 1962
      // 1963
      // 1964
      // 1965
      // 1966
      // 1967
      // 1968
      // 1969
      // 1970
      // 1971
      // 1972
      // 1973
      // 1974
      // 1975
      // 1976
      // 1977
      // 1978
      // 1979
      // 1980
      // 1981
      // 1982
      // 1983
      // 1984
      // 1985
      // 1986
      // 1987
      // 1988
      // 1989
      // 1990
      // 1991
      // 1992
      // 1993
      // 1994
      // 1995
      // 1996
      // 1997
      // 1998
      // 1999
      // 2000
      // 2001
      // 2002
      // 2003
      // 2004
      // 2005
      // 2006
      // 2007
      // 2008
      // 2009
      // 2010
      // 2011
      // 2012
      // 2013
      // 2014
      // 2015
      // 2016
      // 2017
      // 2018
      // 2019
      // 2020
      // 2021
      // 2022
      // 2023
      // 2024
      // 2025
      // 2026
      // 2027
      // 2028
      // 2029
      // 2030
      // 2031
      // 2032
      // 2033
      // 2034
      // 2035
      // 2036
      // 2037
      // 2038
      // 2039
      // 2040
      // 2041
      // 2042
      // 2043
      // 2044
      // 2045
      // 2046
      // 2047
      // 2048
      // 2049
      // 2050
      // 2051
      // 2052
      // 2053
      // 2054
      // 2055
      // 2056
      // 2057
      // 2058
      // 2059
      // 2060
      // 2061
      else {
        dchain_rejuvenate_index(dchain, map_value_out, now);
        uint8_t* vector_value_out = 0u;
        vector_borrow(vector, map_value_out, (void**)(&vector_value_out));
        vector_value_out[0u] = 3750000000ul - packet_length;
        vector_value_out[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
        vector_value_out[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
        vector_value_out[3u] = 223u;
        vector_value_out[4u] = 0u;
        vector_value_out[5u] = 0u;
        vector_value_out[6u] = 0u;
        vector_value_out[7u] = 0u;
        vector_value_out[8u] = now & 0xff;
        vector_value_out[9u] = (now >> 8) & 0xff;
        vector_value_out[10u] = (now >> 16) & 0xff;
        vector_value_out[11u] = (now >> 24) & 0xff;
        vector_value_out[12u] = (now >> 32) & 0xff;
        vector_value_out[13u] = (now >> 40) & 0xff;
        vector_value_out[14u] = (now >> 48) & 0xff;
        vector_value_out[15u] = (now >> 56) & 0xff;

        // 1938
        // 1939
        // 1940
        // 1941
        // 1942
        // 1943
        // 1944
        // 1945
        // 1946
        // 1947
        // 1948
        // 1949
        // 1950
        // 1951
        // 1952
        // 1953
        // 1954
        // 1955
        // 1956
        // 1957
        // 1958
        // 1959
        // 1960
        // 1961
        // 1962
        // 1963
        // 1964
        // 1965
        // 1966
        // 1967
        // 1968
        // 1969
        // 1970
        // 1971
        // 1972
        // 1973
        // 1974
        // 1975
        // 1976
        // 1977
        // 1978
        // 1979
        // 1980
        // 1981
        // 1982
        // 1983
        // 1984
        // 1985
        // 1986
        // 1987
        // 1988
        // 1989
        // 1990
        // 1991
        // 1992
        // 1993
        // 1994
        // 1995
        // 1996
        // 1997
        // 1998
        // 1999
        // 2000
        // 2001
        // 2002
        // 2003
        // 2004
        // 2005
        // 2006
        // 2007
        // 2008
        // 2009
        // 2010
        // 2011
        // 2012
        // 2013
        // 2014
        // 2015
        // 2016
        // 2017
        // 2018
        // 2019
        // 2020
        // 2021
        // 2022
        // 2023
        // 2024
        // 2025
        // 2026
        // 2027
        // 2028
        // 2029
        // 2030
        if ((now - vector_value_out[8ul]) < 6000000000000000ul) {

          // 1938
          // 1939
          // 1940
          // 1941
          // 1942
          // 1943
          // 1944
          // 1945
          // 1946
          // 1947
          // 1948
          // 1949
          // 1950
          // 1951
          // 1952
          // 1953
          // 1954
          // 1955
          // 1956
          // 1957
          // 1958
          // 1959
          // 1960
          // 1961
          // 1962
          // 1963
          // 1964
          // 1965
          // 1966
          // 1967
          // 1968
          // 1969
          // 1970
          // 1971
          // 1972
          // 1973
          // 1974
          // 1975
          // 1976
          // 1977
          // 1978
          // 1979
          // 1980
          // 1981
          // 1982
          // 1983
          // 1984
          // 1985
          // 1986
          // 1987
          // 1988
          // 1989
          // 1990
          // 1991
          // 1992
          // 1993
          // 1994
          // 1995
          // 1996
          // 1997
          // 1998
          // 1999
          if (false == (3750000000ul < (vector_value_out[0ul] + ((625ul * (now - vector_value_out[8ul])) / 1000000000ul)))) {

            // 1938
            // 1939
            // 1940
            // 1941
            // 1942
            // 1943
            // 1944
            // 1945
            // 1946
            // 1947
            // 1948
            // 1949
            // 1950
            // 1951
            // 1952
            // 1953
            // 1954
            // 1955
            // 1956
            // 1957
            // 1958
            // 1959
            // 1960
            // 1961
            // 1962
            // 1963
            // 1964
            // 1965
            // 1966
            // 1967
            // 1968
            if (false == (packet_length < (vector_value_out[0ul] + ((625ul * (now - vector_value_out[8ul])) / 1000000000ul)))) {
              vector_return(vector, map_value_out, vector_value_out);
              uint8_t map_key_1[4];
              map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_1[2u] = 0u;
              map_key_1[3u] = 0u;
              int map_value_out_1;
              int map_has_this_key__450 = map_get(map_1, &map_key_1, &map_value_out_1);

              // 1938
              // 1939
              // 1940
              // 1941
              // 1942
              // 1943
              // 1944
              if (0u == map_has_this_key__450) {
                uint32_t new_index__453;
                int out_of_space__453 = !dchain_allocate_new_index(dchain_1, &new_index__453, now);

                // 1938
                // 1939
                // 1940
                // 1941
                // 1942
                // 1943
                if (false == ((out_of_space__453) & (0u == number_of_freed_flows__57))) {
                  uint8_t* vector_value_out_1 = 0u;
                  vector_borrow(vector_3, new_index__453, (void**)(&vector_value_out_1));
                  vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_1[2u] = 0u;
                  vector_value_out_1[3u] = 0u;
                  uint8_t* vector_value_out_2 = 0u;
                  vector_borrow(vector_2, new_index__453, (void**)(&vector_value_out_2));
                  vector_value_out_2[0u] = 3750000000ul - packet_length;
                  vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_2[3u] = 223u;
                  vector_value_out_2[4u] = 0u;
                  vector_value_out_2[5u] = 0u;
                  vector_value_out_2[6u] = 0u;
                  vector_value_out_2[7u] = 0u;
                  vector_value_out_2[8u] = now & 0xff;
                  vector_value_out_2[9u] = (now >> 8) & 0xff;
                  vector_value_out_2[10u] = (now >> 16) & 0xff;
                  vector_value_out_2[11u] = (now >> 24) & 0xff;
                  vector_value_out_2[12u] = (now >> 32) & 0xff;
                  vector_value_out_2[13u] = (now >> 40) & 0xff;
                  vector_value_out_2[14u] = (now >> 48) & 0xff;
                  vector_value_out_2[15u] = (now >> 56) & 0xff;
                  map_put(map_1, vector_value_out_1, new_index__453);
                  vector_return(vector_3, new_index__453, vector_value_out_1);
                  vector_return(vector_2, new_index__453, vector_value_out_2);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__461 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1938
                  // 1939
                  if (0u == map_has_this_key__461) {
                    uint32_t new_index__464;
                    int out_of_space__464 = !dchain_allocate_new_index(dchain_2, &new_index__464, now);

                    // 1938
                    if (false == ((out_of_space__464) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_5, new_index__464, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_3[3u] = 0u;
                      uint8_t* vector_value_out_4 = 0u;
                      vector_borrow(vector_4, new_index__464, (void**)(&vector_value_out_4));
                      vector_value_out_4[0u] = 3750000000ul - packet_length;
                      vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_4[3u] = 223u;
                      vector_value_out_4[4u] = 0u;
                      vector_value_out_4[5u] = 0u;
                      vector_value_out_4[6u] = 0u;
                      vector_value_out_4[7u] = 0u;
                      vector_value_out_4[8u] = now & 0xff;
                      vector_value_out_4[9u] = (now >> 8) & 0xff;
                      vector_value_out_4[10u] = (now >> 16) & 0xff;
                      vector_value_out_4[11u] = (now >> 24) & 0xff;
                      vector_value_out_4[12u] = (now >> 32) & 0xff;
                      vector_value_out_4[13u] = (now >> 40) & 0xff;
                      vector_value_out_4[14u] = (now >> 48) & 0xff;
                      vector_value_out_4[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_3, new_index__464);
                      vector_return(vector_5, new_index__464, vector_value_out_3);
                      vector_return(vector_4, new_index__464, vector_value_out_4);
                      return 1;
                    }

                    // 1939
                    else {
                      return 1;
                    } // !(false == ((out_of_space__464) & (0u == number_of_freed_flows__58)))

                  }

                  // 1940
                  // 1941
                  // 1942
                  // 1943
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;

                    // 1940
                    // 1941
                    // 1942
                    if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                      // 1940
                      // 1941
                      if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                        // 1940
                        if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        }

                        // 1941
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                      }

                      // 1942
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 1943
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__461)

                }

                // 1944
                else {
                  return 1;
                } // !(false == ((out_of_space__453) & (0u == number_of_freed_flows__57)))

              }

              // 1945
              // 1946
              // 1947
              // 1948
              // 1949
              // 1950
              // 1951
              // 1952
              // 1953
              // 1954
              // 1955
              // 1956
              // 1957
              // 1958
              // 1959
              // 1960
              // 1961
              // 1962
              // 1963
              // 1964
              // 1965
              // 1966
              // 1967
              // 1968
              else {
                dchain_rejuvenate_index(dchain_1, map_value_out_1, now);
                uint8_t* vector_value_out_1 = 0u;
                vector_borrow(vector_2, map_value_out_1, (void**)(&vector_value_out_1));
                vector_value_out_1[0u] = 3750000000ul - packet_length;
                vector_value_out_1[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_1[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_1[3u] = 223u;
                vector_value_out_1[4u] = 0u;
                vector_value_out_1[5u] = 0u;
                vector_value_out_1[6u] = 0u;
                vector_value_out_1[7u] = 0u;
                vector_value_out_1[8u] = now & 0xff;
                vector_value_out_1[9u] = (now >> 8) & 0xff;
                vector_value_out_1[10u] = (now >> 16) & 0xff;
                vector_value_out_1[11u] = (now >> 24) & 0xff;
                vector_value_out_1[12u] = (now >> 32) & 0xff;
                vector_value_out_1[13u] = (now >> 40) & 0xff;
                vector_value_out_1[14u] = (now >> 48) & 0xff;
                vector_value_out_1[15u] = (now >> 56) & 0xff;

                // 1945
                // 1946
                // 1947
                // 1948
                // 1949
                // 1950
                // 1951
                // 1952
                // 1953
                // 1954
                // 1955
                // 1956
                // 1957
                // 1958
                // 1959
                // 1960
                // 1961
                // 1962
                if ((now - vector_value_out_1[8ul]) < 6000000000000000ul) {

                  // 1945
                  // 1946
                  // 1947
                  // 1948
                  // 1949
                  // 1950
                  // 1951
                  // 1952
                  // 1953
                  // 1954
                  // 1955
                  // 1956
                  if (false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {

                    // 1945
                    // 1946
                    // 1947
                    // 1948
                    // 1949
                    // 1950
                    if (false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {
                      vector_return(vector_2, map_value_out_1, vector_value_out_1);
                      uint8_t map_key_2[4];
                      map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                      map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      map_key_2[3u] = 0u;
                      int map_value_out_2;
                      int map_has_this_key__542 = map_get(map_2, &map_key_2, &map_value_out_2);

                      // 1945
                      // 1946
                      if (0u == map_has_this_key__542) {
                        uint32_t new_index__545;
                        int out_of_space__545 = !dchain_allocate_new_index(dchain_2, &new_index__545, now);

                        // 1945
                        if (false == ((out_of_space__545) & (0u == number_of_freed_flows__58))) {
                          uint8_t* vector_value_out_2 = 0u;
                          vector_borrow(vector_5, new_index__545, (void**)(&vector_value_out_2));
                          vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                          vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                          vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                          vector_value_out_2[3u] = 0u;
                          uint8_t* vector_value_out_3 = 0u;
                          vector_borrow(vector_4, new_index__545, (void**)(&vector_value_out_3));
                          vector_value_out_3[0u] = 3750000000ul - packet_length;
                          vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                          vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                          vector_value_out_3[3u] = 223u;
                          vector_value_out_3[4u] = 0u;
                          vector_value_out_3[5u] = 0u;
                          vector_value_out_3[6u] = 0u;
                          vector_value_out_3[7u] = 0u;
                          vector_value_out_3[8u] = now & 0xff;
                          vector_value_out_3[9u] = (now >> 8) & 0xff;
                          vector_value_out_3[10u] = (now >> 16) & 0xff;
                          vector_value_out_3[11u] = (now >> 24) & 0xff;
                          vector_value_out_3[12u] = (now >> 32) & 0xff;
                          vector_value_out_3[13u] = (now >> 40) & 0xff;
                          vector_value_out_3[14u] = (now >> 48) & 0xff;
                          vector_value_out_3[15u] = (now >> 56) & 0xff;
                          map_put(map_2, vector_value_out_2, new_index__545);
                          vector_return(vector_5, new_index__545, vector_value_out_2);
                          vector_return(vector_4, new_index__545, vector_value_out_3);
                          return 1;
                        }

                        // 1946
                        else {
                          return 1;
                        } // !(false == ((out_of_space__545) & (0u == number_of_freed_flows__58)))

                      }

                      // 1947
                      // 1948
                      // 1949
                      // 1950
                      else {
                        dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = 3750000000ul - packet_length;
                        vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_2[3u] = 223u;
                        vector_value_out_2[4u] = 0u;
                        vector_value_out_2[5u] = 0u;
                        vector_value_out_2[6u] = 0u;
                        vector_value_out_2[7u] = 0u;
                        vector_value_out_2[8u] = now & 0xff;
                        vector_value_out_2[9u] = (now >> 8) & 0xff;
                        vector_value_out_2[10u] = (now >> 16) & 0xff;
                        vector_value_out_2[11u] = (now >> 24) & 0xff;
                        vector_value_out_2[12u] = (now >> 32) & 0xff;
                        vector_value_out_2[13u] = (now >> 40) & 0xff;
                        vector_value_out_2[14u] = (now >> 48) & 0xff;
                        vector_value_out_2[15u] = (now >> 56) & 0xff;

                        // 1947
                        // 1948
                        // 1949
                        if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                          // 1947
                          // 1948
                          if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                            // 1947
                            if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            }

                            // 1948
                            else {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                          }

                          // 1949
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1950
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                      } // !(0u == map_has_this_key__542)

                    }

                    // 1951
                    // 1952
                    // 1953
                    // 1954
                    // 1955
                    // 1956
                    else {
                      vector_return(vector_2, map_value_out_1, vector_value_out_1);
                      uint8_t map_key_2[4];
                      map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                      map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      map_key_2[3u] = 0u;
                      int map_value_out_2;
                      int map_has_this_key__608 = map_get(map_2, &map_key_2, &map_value_out_2);

                      // 1951
                      // 1952
                      if (0u == map_has_this_key__608) {
                        uint32_t new_index__611;
                        int out_of_space__611 = !dchain_allocate_new_index(dchain_2, &new_index__611, now);

                        // 1951
                        if (false == ((out_of_space__611) & (0u == number_of_freed_flows__58))) {
                          uint8_t* vector_value_out_2 = 0u;
                          vector_borrow(vector_5, new_index__611, (void**)(&vector_value_out_2));
                          vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                          vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                          vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                          vector_value_out_2[3u] = 0u;
                          uint8_t* vector_value_out_3 = 0u;
                          vector_borrow(vector_4, new_index__611, (void**)(&vector_value_out_3));
                          vector_value_out_3[0u] = 3750000000ul - packet_length;
                          vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                          vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                          vector_value_out_3[3u] = 223u;
                          vector_value_out_3[4u] = 0u;
                          vector_value_out_3[5u] = 0u;
                          vector_value_out_3[6u] = 0u;
                          vector_value_out_3[7u] = 0u;
                          vector_value_out_3[8u] = now & 0xff;
                          vector_value_out_3[9u] = (now >> 8) & 0xff;
                          vector_value_out_3[10u] = (now >> 16) & 0xff;
                          vector_value_out_3[11u] = (now >> 24) & 0xff;
                          vector_value_out_3[12u] = (now >> 32) & 0xff;
                          vector_value_out_3[13u] = (now >> 40) & 0xff;
                          vector_value_out_3[14u] = (now >> 48) & 0xff;
                          vector_value_out_3[15u] = (now >> 56) & 0xff;
                          map_put(map_2, vector_value_out_2, new_index__611);
                          vector_return(vector_5, new_index__611, vector_value_out_2);
                          vector_return(vector_4, new_index__611, vector_value_out_3);
                          return 1;
                        }

                        // 1952
                        else {
                          return 1;
                        } // !(false == ((out_of_space__611) & (0u == number_of_freed_flows__58)))

                      }

                      // 1953
                      // 1954
                      // 1955
                      // 1956
                      else {
                        dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = 3750000000ul - packet_length;
                        vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_2[3u] = 223u;
                        vector_value_out_2[4u] = 0u;
                        vector_value_out_2[5u] = 0u;
                        vector_value_out_2[6u] = 0u;
                        vector_value_out_2[7u] = 0u;
                        vector_value_out_2[8u] = now & 0xff;
                        vector_value_out_2[9u] = (now >> 8) & 0xff;
                        vector_value_out_2[10u] = (now >> 16) & 0xff;
                        vector_value_out_2[11u] = (now >> 24) & 0xff;
                        vector_value_out_2[12u] = (now >> 32) & 0xff;
                        vector_value_out_2[13u] = (now >> 40) & 0xff;
                        vector_value_out_2[14u] = (now >> 48) & 0xff;
                        vector_value_out_2[15u] = (now >> 56) & 0xff;

                        // 1953
                        // 1954
                        // 1955
                        if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                          // 1953
                          // 1954
                          if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                            // 1953
                            if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            }

                            // 1954
                            else {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                          }

                          // 1955
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1956
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                      } // !(0u == map_has_this_key__608)

                    } // !(false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

                  }

                  // 1957
                  // 1958
                  // 1959
                  // 1960
                  // 1961
                  // 1962
                  else {
                    vector_return(vector_2, map_value_out_1, vector_value_out_1);
                    uint8_t map_key_2[4];
                    map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                    map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    map_key_2[3u] = 0u;
                    int map_value_out_2;
                    int map_has_this_key__674 = map_get(map_2, &map_key_2, &map_value_out_2);

                    // 1957
                    // 1958
                    if (0u == map_has_this_key__674) {
                      uint32_t new_index__677;
                      int out_of_space__677 = !dchain_allocate_new_index(dchain_2, &new_index__677, now);

                      // 1957
                      if (false == ((out_of_space__677) & (0u == number_of_freed_flows__58))) {
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_5, new_index__677, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                        vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                        vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                        vector_value_out_2[3u] = 0u;
                        uint8_t* vector_value_out_3 = 0u;
                        vector_borrow(vector_4, new_index__677, (void**)(&vector_value_out_3));
                        vector_value_out_3[0u] = 3750000000ul - packet_length;
                        vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_3[3u] = 223u;
                        vector_value_out_3[4u] = 0u;
                        vector_value_out_3[5u] = 0u;
                        vector_value_out_3[6u] = 0u;
                        vector_value_out_3[7u] = 0u;
                        vector_value_out_3[8u] = now & 0xff;
                        vector_value_out_3[9u] = (now >> 8) & 0xff;
                        vector_value_out_3[10u] = (now >> 16) & 0xff;
                        vector_value_out_3[11u] = (now >> 24) & 0xff;
                        vector_value_out_3[12u] = (now >> 32) & 0xff;
                        vector_value_out_3[13u] = (now >> 40) & 0xff;
                        vector_value_out_3[14u] = (now >> 48) & 0xff;
                        vector_value_out_3[15u] = (now >> 56) & 0xff;
                        map_put(map_2, vector_value_out_2, new_index__677);
                        vector_return(vector_5, new_index__677, vector_value_out_2);
                        vector_return(vector_4, new_index__677, vector_value_out_3);
                        return 1;
                      }

                      // 1958
                      else {
                        return 1;
                      } // !(false == ((out_of_space__677) & (0u == number_of_freed_flows__58)))

                    }

                    // 1959
                    // 1960
                    // 1961
                    // 1962
                    else {
                      dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = 3750000000ul - packet_length;
                      vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_2[3u] = 223u;
                      vector_value_out_2[4u] = 0u;
                      vector_value_out_2[5u] = 0u;
                      vector_value_out_2[6u] = 0u;
                      vector_value_out_2[7u] = 0u;
                      vector_value_out_2[8u] = now & 0xff;
                      vector_value_out_2[9u] = (now >> 8) & 0xff;
                      vector_value_out_2[10u] = (now >> 16) & 0xff;
                      vector_value_out_2[11u] = (now >> 24) & 0xff;
                      vector_value_out_2[12u] = (now >> 32) & 0xff;
                      vector_value_out_2[13u] = (now >> 40) & 0xff;
                      vector_value_out_2[14u] = (now >> 48) & 0xff;
                      vector_value_out_2[15u] = (now >> 56) & 0xff;

                      // 1959
                      // 1960
                      // 1961
                      if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                        // 1959
                        // 1960
                        if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                          // 1959
                          if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          }

                          // 1960
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1961
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 1962
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                    } // !(0u == map_has_this_key__674)

                  } // !(false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

                }

                // 1963
                // 1964
                // 1965
                // 1966
                // 1967
                // 1968
                else {
                  vector_return(vector_2, map_value_out_1, vector_value_out_1);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__740 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1963
                  // 1964
                  if (0u == map_has_this_key__740) {
                    uint32_t new_index__743;
                    int out_of_space__743 = !dchain_allocate_new_index(dchain_2, &new_index__743, now);

                    // 1963
                    if (false == ((out_of_space__743) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_5, new_index__743, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_2[3u] = 0u;
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_4, new_index__743, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = 3750000000ul - packet_length;
                      vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_3[3u] = 223u;
                      vector_value_out_3[4u] = 0u;
                      vector_value_out_3[5u] = 0u;
                      vector_value_out_3[6u] = 0u;
                      vector_value_out_3[7u] = 0u;
                      vector_value_out_3[8u] = now & 0xff;
                      vector_value_out_3[9u] = (now >> 8) & 0xff;
                      vector_value_out_3[10u] = (now >> 16) & 0xff;
                      vector_value_out_3[11u] = (now >> 24) & 0xff;
                      vector_value_out_3[12u] = (now >> 32) & 0xff;
                      vector_value_out_3[13u] = (now >> 40) & 0xff;
                      vector_value_out_3[14u] = (now >> 48) & 0xff;
                      vector_value_out_3[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_2, new_index__743);
                      vector_return(vector_5, new_index__743, vector_value_out_2);
                      vector_return(vector_4, new_index__743, vector_value_out_3);
                      return 1;
                    }

                    // 1964
                    else {
                      return 1;
                    } // !(false == ((out_of_space__743) & (0u == number_of_freed_flows__58)))

                  }

                  // 1965
                  // 1966
                  // 1967
                  // 1968
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = 3750000000ul - packet_length;
                    vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_2[3u] = 223u;
                    vector_value_out_2[4u] = 0u;
                    vector_value_out_2[5u] = 0u;
                    vector_value_out_2[6u] = 0u;
                    vector_value_out_2[7u] = 0u;
                    vector_value_out_2[8u] = now & 0xff;
                    vector_value_out_2[9u] = (now >> 8) & 0xff;
                    vector_value_out_2[10u] = (now >> 16) & 0xff;
                    vector_value_out_2[11u] = (now >> 24) & 0xff;
                    vector_value_out_2[12u] = (now >> 32) & 0xff;
                    vector_value_out_2[13u] = (now >> 40) & 0xff;
                    vector_value_out_2[14u] = (now >> 48) & 0xff;
                    vector_value_out_2[15u] = (now >> 56) & 0xff;

                    // 1965
                    // 1966
                    // 1967
                    if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                      // 1965
                      // 1966
                      if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                        // 1965
                        if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        }

                        // 1966
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 1967
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 1968
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__740)

                } // !((now - vector_value_out_1[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__450)

            }

            // 1969
            // 1970
            // 1971
            // 1972
            // 1973
            // 1974
            // 1975
            // 1976
            // 1977
            // 1978
            // 1979
            // 1980
            // 1981
            // 1982
            // 1983
            // 1984
            // 1985
            // 1986
            // 1987
            // 1988
            // 1989
            // 1990
            // 1991
            // 1992
            // 1993
            // 1994
            // 1995
            // 1996
            // 1997
            // 1998
            // 1999
            else {
              vector_return(vector, map_value_out, vector_value_out);
              uint8_t map_key_1[4];
              map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_1[2u] = 0u;
              map_key_1[3u] = 0u;
              int map_value_out_1;
              int map_has_this_key__806 = map_get(map_1, &map_key_1, &map_value_out_1);

              // 1969
              // 1970
              // 1971
              // 1972
              // 1973
              // 1974
              // 1975
              if (0u == map_has_this_key__806) {
                uint32_t new_index__809;
                int out_of_space__809 = !dchain_allocate_new_index(dchain_1, &new_index__809, now);

                // 1969
                // 1970
                // 1971
                // 1972
                // 1973
                // 1974
                if (false == ((out_of_space__809) & (0u == number_of_freed_flows__57))) {
                  uint8_t* vector_value_out_1 = 0u;
                  vector_borrow(vector_3, new_index__809, (void**)(&vector_value_out_1));
                  vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_1[2u] = 0u;
                  vector_value_out_1[3u] = 0u;
                  uint8_t* vector_value_out_2 = 0u;
                  vector_borrow(vector_2, new_index__809, (void**)(&vector_value_out_2));
                  vector_value_out_2[0u] = 3750000000ul - packet_length;
                  vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_2[3u] = 223u;
                  vector_value_out_2[4u] = 0u;
                  vector_value_out_2[5u] = 0u;
                  vector_value_out_2[6u] = 0u;
                  vector_value_out_2[7u] = 0u;
                  vector_value_out_2[8u] = now & 0xff;
                  vector_value_out_2[9u] = (now >> 8) & 0xff;
                  vector_value_out_2[10u] = (now >> 16) & 0xff;
                  vector_value_out_2[11u] = (now >> 24) & 0xff;
                  vector_value_out_2[12u] = (now >> 32) & 0xff;
                  vector_value_out_2[13u] = (now >> 40) & 0xff;
                  vector_value_out_2[14u] = (now >> 48) & 0xff;
                  vector_value_out_2[15u] = (now >> 56) & 0xff;
                  map_put(map_1, vector_value_out_1, new_index__809);
                  vector_return(vector_3, new_index__809, vector_value_out_1);
                  vector_return(vector_2, new_index__809, vector_value_out_2);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__817 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1969
                  // 1970
                  if (0u == map_has_this_key__817) {
                    uint32_t new_index__820;
                    int out_of_space__820 = !dchain_allocate_new_index(dchain_2, &new_index__820, now);

                    // 1969
                    if (false == ((out_of_space__820) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_5, new_index__820, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_3[3u] = 0u;
                      uint8_t* vector_value_out_4 = 0u;
                      vector_borrow(vector_4, new_index__820, (void**)(&vector_value_out_4));
                      vector_value_out_4[0u] = 3750000000ul - packet_length;
                      vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_4[3u] = 223u;
                      vector_value_out_4[4u] = 0u;
                      vector_value_out_4[5u] = 0u;
                      vector_value_out_4[6u] = 0u;
                      vector_value_out_4[7u] = 0u;
                      vector_value_out_4[8u] = now & 0xff;
                      vector_value_out_4[9u] = (now >> 8) & 0xff;
                      vector_value_out_4[10u] = (now >> 16) & 0xff;
                      vector_value_out_4[11u] = (now >> 24) & 0xff;
                      vector_value_out_4[12u] = (now >> 32) & 0xff;
                      vector_value_out_4[13u] = (now >> 40) & 0xff;
                      vector_value_out_4[14u] = (now >> 48) & 0xff;
                      vector_value_out_4[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_3, new_index__820);
                      vector_return(vector_5, new_index__820, vector_value_out_3);
                      vector_return(vector_4, new_index__820, vector_value_out_4);
                      return 1;
                    }

                    // 1970
                    else {
                      return 1;
                    } // !(false == ((out_of_space__820) & (0u == number_of_freed_flows__58)))

                  }

                  // 1971
                  // 1972
                  // 1973
                  // 1974
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;

                    // 1971
                    // 1972
                    // 1973
                    if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                      // 1971
                      // 1972
                      if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                        // 1971
                        if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        }

                        // 1972
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_3);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                      }

                      // 1973
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 1974
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__817)

                }

                // 1975
                else {
                  return 1;
                } // !(false == ((out_of_space__809) & (0u == number_of_freed_flows__57)))

              }

              // 1976
              // 1977
              // 1978
              // 1979
              // 1980
              // 1981
              // 1982
              // 1983
              // 1984
              // 1985
              // 1986
              // 1987
              // 1988
              // 1989
              // 1990
              // 1991
              // 1992
              // 1993
              // 1994
              // 1995
              // 1996
              // 1997
              // 1998
              // 1999
              else {
                dchain_rejuvenate_index(dchain_1, map_value_out_1, now);
                uint8_t* vector_value_out_1 = 0u;
                vector_borrow(vector_2, map_value_out_1, (void**)(&vector_value_out_1));
                vector_value_out_1[0u] = 3750000000ul - packet_length;
                vector_value_out_1[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_1[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_1[3u] = 223u;
                vector_value_out_1[4u] = 0u;
                vector_value_out_1[5u] = 0u;
                vector_value_out_1[6u] = 0u;
                vector_value_out_1[7u] = 0u;
                vector_value_out_1[8u] = now & 0xff;
                vector_value_out_1[9u] = (now >> 8) & 0xff;
                vector_value_out_1[10u] = (now >> 16) & 0xff;
                vector_value_out_1[11u] = (now >> 24) & 0xff;
                vector_value_out_1[12u] = (now >> 32) & 0xff;
                vector_value_out_1[13u] = (now >> 40) & 0xff;
                vector_value_out_1[14u] = (now >> 48) & 0xff;
                vector_value_out_1[15u] = (now >> 56) & 0xff;

                // 1976
                // 1977
                // 1978
                // 1979
                // 1980
                // 1981
                // 1982
                // 1983
                // 1984
                // 1985
                // 1986
                // 1987
                // 1988
                // 1989
                // 1990
                // 1991
                // 1992
                // 1993
                if ((now - vector_value_out_1[8ul]) < 6000000000000000ul) {

                  // 1976
                  // 1977
                  // 1978
                  // 1979
                  // 1980
                  // 1981
                  // 1982
                  // 1983
                  // 1984
                  // 1985
                  // 1986
                  // 1987
                  if (false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {

                    // 1976
                    // 1977
                    // 1978
                    // 1979
                    // 1980
                    // 1981
                    if (false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {
                      vector_return(vector_2, map_value_out_1, vector_value_out_1);
                      uint8_t map_key_2[4];
                      map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                      map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      map_key_2[3u] = 0u;
                      int map_value_out_2;
                      int map_has_this_key__898 = map_get(map_2, &map_key_2, &map_value_out_2);

                      // 1976
                      // 1977
                      if (0u == map_has_this_key__898) {
                        uint32_t new_index__901;
                        int out_of_space__901 = !dchain_allocate_new_index(dchain_2, &new_index__901, now);

                        // 1976
                        if (false == ((out_of_space__901) & (0u == number_of_freed_flows__58))) {
                          uint8_t* vector_value_out_2 = 0u;
                          vector_borrow(vector_5, new_index__901, (void**)(&vector_value_out_2));
                          vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                          vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                          vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                          vector_value_out_2[3u] = 0u;
                          uint8_t* vector_value_out_3 = 0u;
                          vector_borrow(vector_4, new_index__901, (void**)(&vector_value_out_3));
                          vector_value_out_3[0u] = 3750000000ul - packet_length;
                          vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                          vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                          vector_value_out_3[3u] = 223u;
                          vector_value_out_3[4u] = 0u;
                          vector_value_out_3[5u] = 0u;
                          vector_value_out_3[6u] = 0u;
                          vector_value_out_3[7u] = 0u;
                          vector_value_out_3[8u] = now & 0xff;
                          vector_value_out_3[9u] = (now >> 8) & 0xff;
                          vector_value_out_3[10u] = (now >> 16) & 0xff;
                          vector_value_out_3[11u] = (now >> 24) & 0xff;
                          vector_value_out_3[12u] = (now >> 32) & 0xff;
                          vector_value_out_3[13u] = (now >> 40) & 0xff;
                          vector_value_out_3[14u] = (now >> 48) & 0xff;
                          vector_value_out_3[15u] = (now >> 56) & 0xff;
                          map_put(map_2, vector_value_out_2, new_index__901);
                          vector_return(vector_5, new_index__901, vector_value_out_2);
                          vector_return(vector_4, new_index__901, vector_value_out_3);
                          return 1;
                        }

                        // 1977
                        else {
                          return 1;
                        } // !(false == ((out_of_space__901) & (0u == number_of_freed_flows__58)))

                      }

                      // 1978
                      // 1979
                      // 1980
                      // 1981
                      else {
                        dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = 3750000000ul - packet_length;
                        vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_2[3u] = 223u;
                        vector_value_out_2[4u] = 0u;
                        vector_value_out_2[5u] = 0u;
                        vector_value_out_2[6u] = 0u;
                        vector_value_out_2[7u] = 0u;
                        vector_value_out_2[8u] = now & 0xff;
                        vector_value_out_2[9u] = (now >> 8) & 0xff;
                        vector_value_out_2[10u] = (now >> 16) & 0xff;
                        vector_value_out_2[11u] = (now >> 24) & 0xff;
                        vector_value_out_2[12u] = (now >> 32) & 0xff;
                        vector_value_out_2[13u] = (now >> 40) & 0xff;
                        vector_value_out_2[14u] = (now >> 48) & 0xff;
                        vector_value_out_2[15u] = (now >> 56) & 0xff;

                        // 1978
                        // 1979
                        // 1980
                        if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                          // 1978
                          // 1979
                          if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                            // 1978
                            if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            }

                            // 1979
                            else {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                          }

                          // 1980
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1981
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                      } // !(0u == map_has_this_key__898)

                    }

                    // 1982
                    // 1983
                    // 1984
                    // 1985
                    // 1986
                    // 1987
                    else {
                      vector_return(vector_2, map_value_out_1, vector_value_out_1);
                      uint8_t map_key_2[4];
                      map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                      map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      map_key_2[3u] = 0u;
                      int map_value_out_2;
                      int map_has_this_key__964 = map_get(map_2, &map_key_2, &map_value_out_2);

                      // 1982
                      // 1983
                      if (0u == map_has_this_key__964) {
                        uint32_t new_index__967;
                        int out_of_space__967 = !dchain_allocate_new_index(dchain_2, &new_index__967, now);

                        // 1982
                        if (false == ((out_of_space__967) & (0u == number_of_freed_flows__58))) {
                          uint8_t* vector_value_out_2 = 0u;
                          vector_borrow(vector_5, new_index__967, (void**)(&vector_value_out_2));
                          vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                          vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                          vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                          vector_value_out_2[3u] = 0u;
                          uint8_t* vector_value_out_3 = 0u;
                          vector_borrow(vector_4, new_index__967, (void**)(&vector_value_out_3));
                          vector_value_out_3[0u] = 3750000000ul - packet_length;
                          vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                          vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                          vector_value_out_3[3u] = 223u;
                          vector_value_out_3[4u] = 0u;
                          vector_value_out_3[5u] = 0u;
                          vector_value_out_3[6u] = 0u;
                          vector_value_out_3[7u] = 0u;
                          vector_value_out_3[8u] = now & 0xff;
                          vector_value_out_3[9u] = (now >> 8) & 0xff;
                          vector_value_out_3[10u] = (now >> 16) & 0xff;
                          vector_value_out_3[11u] = (now >> 24) & 0xff;
                          vector_value_out_3[12u] = (now >> 32) & 0xff;
                          vector_value_out_3[13u] = (now >> 40) & 0xff;
                          vector_value_out_3[14u] = (now >> 48) & 0xff;
                          vector_value_out_3[15u] = (now >> 56) & 0xff;
                          map_put(map_2, vector_value_out_2, new_index__967);
                          vector_return(vector_5, new_index__967, vector_value_out_2);
                          vector_return(vector_4, new_index__967, vector_value_out_3);
                          return 1;
                        }

                        // 1983
                        else {
                          return 1;
                        } // !(false == ((out_of_space__967) & (0u == number_of_freed_flows__58)))

                      }

                      // 1984
                      // 1985
                      // 1986
                      // 1987
                      else {
                        dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = 3750000000ul - packet_length;
                        vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_2[3u] = 223u;
                        vector_value_out_2[4u] = 0u;
                        vector_value_out_2[5u] = 0u;
                        vector_value_out_2[6u] = 0u;
                        vector_value_out_2[7u] = 0u;
                        vector_value_out_2[8u] = now & 0xff;
                        vector_value_out_2[9u] = (now >> 8) & 0xff;
                        vector_value_out_2[10u] = (now >> 16) & 0xff;
                        vector_value_out_2[11u] = (now >> 24) & 0xff;
                        vector_value_out_2[12u] = (now >> 32) & 0xff;
                        vector_value_out_2[13u] = (now >> 40) & 0xff;
                        vector_value_out_2[14u] = (now >> 48) & 0xff;
                        vector_value_out_2[15u] = (now >> 56) & 0xff;

                        // 1984
                        // 1985
                        // 1986
                        if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                          // 1984
                          // 1985
                          if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                            // 1984
                            if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            }

                            // 1985
                            else {
                              vector_return(vector_4, map_value_out_2, vector_value_out_2);
                              return 1;
                            } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                          }

                          // 1986
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1987
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                      } // !(0u == map_has_this_key__964)

                    } // !(false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

                  }

                  // 1988
                  // 1989
                  // 1990
                  // 1991
                  // 1992
                  // 1993
                  else {
                    vector_return(vector_2, map_value_out_1, vector_value_out_1);
                    uint8_t map_key_2[4];
                    map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                    map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    map_key_2[3u] = 0u;
                    int map_value_out_2;
                    int map_has_this_key__1030 = map_get(map_2, &map_key_2, &map_value_out_2);

                    // 1988
                    // 1989
                    if (0u == map_has_this_key__1030) {
                      uint32_t new_index__1033;
                      int out_of_space__1033 = !dchain_allocate_new_index(dchain_2, &new_index__1033, now);

                      // 1988
                      if (false == ((out_of_space__1033) & (0u == number_of_freed_flows__58))) {
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_5, new_index__1033, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                        vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                        vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                        vector_value_out_2[3u] = 0u;
                        uint8_t* vector_value_out_3 = 0u;
                        vector_borrow(vector_4, new_index__1033, (void**)(&vector_value_out_3));
                        vector_value_out_3[0u] = 3750000000ul - packet_length;
                        vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_3[3u] = 223u;
                        vector_value_out_3[4u] = 0u;
                        vector_value_out_3[5u] = 0u;
                        vector_value_out_3[6u] = 0u;
                        vector_value_out_3[7u] = 0u;
                        vector_value_out_3[8u] = now & 0xff;
                        vector_value_out_3[9u] = (now >> 8) & 0xff;
                        vector_value_out_3[10u] = (now >> 16) & 0xff;
                        vector_value_out_3[11u] = (now >> 24) & 0xff;
                        vector_value_out_3[12u] = (now >> 32) & 0xff;
                        vector_value_out_3[13u] = (now >> 40) & 0xff;
                        vector_value_out_3[14u] = (now >> 48) & 0xff;
                        vector_value_out_3[15u] = (now >> 56) & 0xff;
                        map_put(map_2, vector_value_out_2, new_index__1033);
                        vector_return(vector_5, new_index__1033, vector_value_out_2);
                        vector_return(vector_4, new_index__1033, vector_value_out_3);
                        return 1;
                      }

                      // 1989
                      else {
                        return 1;
                      } // !(false == ((out_of_space__1033) & (0u == number_of_freed_flows__58)))

                    }

                    // 1990
                    // 1991
                    // 1992
                    // 1993
                    else {
                      dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = 3750000000ul - packet_length;
                      vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_2[3u] = 223u;
                      vector_value_out_2[4u] = 0u;
                      vector_value_out_2[5u] = 0u;
                      vector_value_out_2[6u] = 0u;
                      vector_value_out_2[7u] = 0u;
                      vector_value_out_2[8u] = now & 0xff;
                      vector_value_out_2[9u] = (now >> 8) & 0xff;
                      vector_value_out_2[10u] = (now >> 16) & 0xff;
                      vector_value_out_2[11u] = (now >> 24) & 0xff;
                      vector_value_out_2[12u] = (now >> 32) & 0xff;
                      vector_value_out_2[13u] = (now >> 40) & 0xff;
                      vector_value_out_2[14u] = (now >> 48) & 0xff;
                      vector_value_out_2[15u] = (now >> 56) & 0xff;

                      // 1990
                      // 1991
                      // 1992
                      if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                        // 1990
                        // 1991
                        if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                          // 1990
                          if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          }

                          // 1991
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 1992
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 1993
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                    } // !(0u == map_has_this_key__1030)

                  } // !(false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

                }

                // 1994
                // 1995
                // 1996
                // 1997
                // 1998
                // 1999
                else {
                  vector_return(vector_2, map_value_out_1, vector_value_out_1);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__1096 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 1994
                  // 1995
                  if (0u == map_has_this_key__1096) {
                    uint32_t new_index__1099;
                    int out_of_space__1099 = !dchain_allocate_new_index(dchain_2, &new_index__1099, now);

                    // 1994
                    if (false == ((out_of_space__1099) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_5, new_index__1099, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_2[3u] = 0u;
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_4, new_index__1099, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = 3750000000ul - packet_length;
                      vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_3[3u] = 223u;
                      vector_value_out_3[4u] = 0u;
                      vector_value_out_3[5u] = 0u;
                      vector_value_out_3[6u] = 0u;
                      vector_value_out_3[7u] = 0u;
                      vector_value_out_3[8u] = now & 0xff;
                      vector_value_out_3[9u] = (now >> 8) & 0xff;
                      vector_value_out_3[10u] = (now >> 16) & 0xff;
                      vector_value_out_3[11u] = (now >> 24) & 0xff;
                      vector_value_out_3[12u] = (now >> 32) & 0xff;
                      vector_value_out_3[13u] = (now >> 40) & 0xff;
                      vector_value_out_3[14u] = (now >> 48) & 0xff;
                      vector_value_out_3[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_2, new_index__1099);
                      vector_return(vector_5, new_index__1099, vector_value_out_2);
                      vector_return(vector_4, new_index__1099, vector_value_out_3);
                      return 1;
                    }

                    // 1995
                    else {
                      return 1;
                    } // !(false == ((out_of_space__1099) & (0u == number_of_freed_flows__58)))

                  }

                  // 1996
                  // 1997
                  // 1998
                  // 1999
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = 3750000000ul - packet_length;
                    vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_2[3u] = 223u;
                    vector_value_out_2[4u] = 0u;
                    vector_value_out_2[5u] = 0u;
                    vector_value_out_2[6u] = 0u;
                    vector_value_out_2[7u] = 0u;
                    vector_value_out_2[8u] = now & 0xff;
                    vector_value_out_2[9u] = (now >> 8) & 0xff;
                    vector_value_out_2[10u] = (now >> 16) & 0xff;
                    vector_value_out_2[11u] = (now >> 24) & 0xff;
                    vector_value_out_2[12u] = (now >> 32) & 0xff;
                    vector_value_out_2[13u] = (now >> 40) & 0xff;
                    vector_value_out_2[14u] = (now >> 48) & 0xff;
                    vector_value_out_2[15u] = (now >> 56) & 0xff;

                    // 1996
                    // 1997
                    // 1998
                    if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                      // 1996
                      // 1997
                      if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                        // 1996
                        if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        }

                        // 1997
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 1998
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 1999
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__1096)

                } // !((now - vector_value_out_1[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__806)

            } // !(false == (packet_length < (vector_value_out[0ul] + ((625ul * (now - vector_value_out[8ul])) / 1000000000ul))))

          }

          // 2000
          // 2001
          // 2002
          // 2003
          // 2004
          // 2005
          // 2006
          // 2007
          // 2008
          // 2009
          // 2010
          // 2011
          // 2012
          // 2013
          // 2014
          // 2015
          // 2016
          // 2017
          // 2018
          // 2019
          // 2020
          // 2021
          // 2022
          // 2023
          // 2024
          // 2025
          // 2026
          // 2027
          // 2028
          // 2029
          // 2030
          else {
            vector_return(vector, map_value_out, vector_value_out);
            uint8_t map_key_1[4];
            map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
            map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
            map_key_1[2u] = 0u;
            map_key_1[3u] = 0u;
            int map_value_out_1;
            int map_has_this_key__1162 = map_get(map_1, &map_key_1, &map_value_out_1);

            // 2000
            // 2001
            // 2002
            // 2003
            // 2004
            // 2005
            // 2006
            if (0u == map_has_this_key__1162) {
              uint32_t new_index__1165;
              int out_of_space__1165 = !dchain_allocate_new_index(dchain_1, &new_index__1165, now);

              // 2000
              // 2001
              // 2002
              // 2003
              // 2004
              // 2005
              if (false == ((out_of_space__1165) & (0u == number_of_freed_flows__57))) {
                uint8_t* vector_value_out_1 = 0u;
                vector_borrow(vector_3, new_index__1165, (void**)(&vector_value_out_1));
                vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
                vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                vector_value_out_1[2u] = 0u;
                vector_value_out_1[3u] = 0u;
                uint8_t* vector_value_out_2 = 0u;
                vector_borrow(vector_2, new_index__1165, (void**)(&vector_value_out_2));
                vector_value_out_2[0u] = 3750000000ul - packet_length;
                vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_2[3u] = 223u;
                vector_value_out_2[4u] = 0u;
                vector_value_out_2[5u] = 0u;
                vector_value_out_2[6u] = 0u;
                vector_value_out_2[7u] = 0u;
                vector_value_out_2[8u] = now & 0xff;
                vector_value_out_2[9u] = (now >> 8) & 0xff;
                vector_value_out_2[10u] = (now >> 16) & 0xff;
                vector_value_out_2[11u] = (now >> 24) & 0xff;
                vector_value_out_2[12u] = (now >> 32) & 0xff;
                vector_value_out_2[13u] = (now >> 40) & 0xff;
                vector_value_out_2[14u] = (now >> 48) & 0xff;
                vector_value_out_2[15u] = (now >> 56) & 0xff;
                map_put(map_1, vector_value_out_1, new_index__1165);
                vector_return(vector_3, new_index__1165, vector_value_out_1);
                vector_return(vector_2, new_index__1165, vector_value_out_2);
                uint8_t map_key_2[4];
                map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                map_key_2[3u] = 0u;
                int map_value_out_2;
                int map_has_this_key__1173 = map_get(map_2, &map_key_2, &map_value_out_2);

                // 2000
                // 2001
                if (0u == map_has_this_key__1173) {
                  uint32_t new_index__1176;
                  int out_of_space__1176 = !dchain_allocate_new_index(dchain_2, &new_index__1176, now);

                  // 2000
                  if (false == ((out_of_space__1176) & (0u == number_of_freed_flows__58))) {
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_5, new_index__1176, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                    vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    vector_value_out_3[3u] = 0u;
                    uint8_t* vector_value_out_4 = 0u;
                    vector_borrow(vector_4, new_index__1176, (void**)(&vector_value_out_4));
                    vector_value_out_4[0u] = 3750000000ul - packet_length;
                    vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_4[3u] = 223u;
                    vector_value_out_4[4u] = 0u;
                    vector_value_out_4[5u] = 0u;
                    vector_value_out_4[6u] = 0u;
                    vector_value_out_4[7u] = 0u;
                    vector_value_out_4[8u] = now & 0xff;
                    vector_value_out_4[9u] = (now >> 8) & 0xff;
                    vector_value_out_4[10u] = (now >> 16) & 0xff;
                    vector_value_out_4[11u] = (now >> 24) & 0xff;
                    vector_value_out_4[12u] = (now >> 32) & 0xff;
                    vector_value_out_4[13u] = (now >> 40) & 0xff;
                    vector_value_out_4[14u] = (now >> 48) & 0xff;
                    vector_value_out_4[15u] = (now >> 56) & 0xff;
                    map_put(map_2, vector_value_out_3, new_index__1176);
                    vector_return(vector_5, new_index__1176, vector_value_out_3);
                    vector_return(vector_4, new_index__1176, vector_value_out_4);
                    return 1;
                  }

                  // 2001
                  else {
                    return 1;
                  } // !(false == ((out_of_space__1176) & (0u == number_of_freed_flows__58)))

                }

                // 2002
                // 2003
                // 2004
                // 2005
                else {
                  dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                  uint8_t* vector_value_out_3 = 0u;
                  vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                  vector_value_out_3[0u] = 3750000000ul - packet_length;
                  vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_3[3u] = 223u;
                  vector_value_out_3[4u] = 0u;
                  vector_value_out_3[5u] = 0u;
                  vector_value_out_3[6u] = 0u;
                  vector_value_out_3[7u] = 0u;
                  vector_value_out_3[8u] = now & 0xff;
                  vector_value_out_3[9u] = (now >> 8) & 0xff;
                  vector_value_out_3[10u] = (now >> 16) & 0xff;
                  vector_value_out_3[11u] = (now >> 24) & 0xff;
                  vector_value_out_3[12u] = (now >> 32) & 0xff;
                  vector_value_out_3[13u] = (now >> 40) & 0xff;
                  vector_value_out_3[14u] = (now >> 48) & 0xff;
                  vector_value_out_3[15u] = (now >> 56) & 0xff;

                  // 2002
                  // 2003
                  // 2004
                  if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                    // 2002
                    // 2003
                    if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                      // 2002
                      if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      }

                      // 2003
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_3);
                        return 1;
                      } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                    }

                    // 2004
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                  }

                  // 2005
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_3);
                    return 1;
                  } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

                } // !(0u == map_has_this_key__1173)

              }

              // 2006
              else {
                return 1;
              } // !(false == ((out_of_space__1165) & (0u == number_of_freed_flows__57)))

            }

            // 2007
            // 2008
            // 2009
            // 2010
            // 2011
            // 2012
            // 2013
            // 2014
            // 2015
            // 2016
            // 2017
            // 2018
            // 2019
            // 2020
            // 2021
            // 2022
            // 2023
            // 2024
            // 2025
            // 2026
            // 2027
            // 2028
            // 2029
            // 2030
            else {
              dchain_rejuvenate_index(dchain_1, map_value_out_1, now);
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector_2, map_value_out_1, (void**)(&vector_value_out_1));
              vector_value_out_1[0u] = 3750000000ul - packet_length;
              vector_value_out_1[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
              vector_value_out_1[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
              vector_value_out_1[3u] = 223u;
              vector_value_out_1[4u] = 0u;
              vector_value_out_1[5u] = 0u;
              vector_value_out_1[6u] = 0u;
              vector_value_out_1[7u] = 0u;
              vector_value_out_1[8u] = now & 0xff;
              vector_value_out_1[9u] = (now >> 8) & 0xff;
              vector_value_out_1[10u] = (now >> 16) & 0xff;
              vector_value_out_1[11u] = (now >> 24) & 0xff;
              vector_value_out_1[12u] = (now >> 32) & 0xff;
              vector_value_out_1[13u] = (now >> 40) & 0xff;
              vector_value_out_1[14u] = (now >> 48) & 0xff;
              vector_value_out_1[15u] = (now >> 56) & 0xff;

              // 2007
              // 2008
              // 2009
              // 2010
              // 2011
              // 2012
              // 2013
              // 2014
              // 2015
              // 2016
              // 2017
              // 2018
              // 2019
              // 2020
              // 2021
              // 2022
              // 2023
              // 2024
              if ((now - vector_value_out_1[8ul]) < 6000000000000000ul) {

                // 2007
                // 2008
                // 2009
                // 2010
                // 2011
                // 2012
                // 2013
                // 2014
                // 2015
                // 2016
                // 2017
                // 2018
                if (false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {

                  // 2007
                  // 2008
                  // 2009
                  // 2010
                  // 2011
                  // 2012
                  if (false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {
                    vector_return(vector_2, map_value_out_1, vector_value_out_1);
                    uint8_t map_key_2[4];
                    map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                    map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    map_key_2[3u] = 0u;
                    int map_value_out_2;
                    int map_has_this_key__1254 = map_get(map_2, &map_key_2, &map_value_out_2);

                    // 2007
                    // 2008
                    if (0u == map_has_this_key__1254) {
                      uint32_t new_index__1257;
                      int out_of_space__1257 = !dchain_allocate_new_index(dchain_2, &new_index__1257, now);

                      // 2007
                      if (false == ((out_of_space__1257) & (0u == number_of_freed_flows__58))) {
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_5, new_index__1257, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                        vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                        vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                        vector_value_out_2[3u] = 0u;
                        uint8_t* vector_value_out_3 = 0u;
                        vector_borrow(vector_4, new_index__1257, (void**)(&vector_value_out_3));
                        vector_value_out_3[0u] = 3750000000ul - packet_length;
                        vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_3[3u] = 223u;
                        vector_value_out_3[4u] = 0u;
                        vector_value_out_3[5u] = 0u;
                        vector_value_out_3[6u] = 0u;
                        vector_value_out_3[7u] = 0u;
                        vector_value_out_3[8u] = now & 0xff;
                        vector_value_out_3[9u] = (now >> 8) & 0xff;
                        vector_value_out_3[10u] = (now >> 16) & 0xff;
                        vector_value_out_3[11u] = (now >> 24) & 0xff;
                        vector_value_out_3[12u] = (now >> 32) & 0xff;
                        vector_value_out_3[13u] = (now >> 40) & 0xff;
                        vector_value_out_3[14u] = (now >> 48) & 0xff;
                        vector_value_out_3[15u] = (now >> 56) & 0xff;
                        map_put(map_2, vector_value_out_2, new_index__1257);
                        vector_return(vector_5, new_index__1257, vector_value_out_2);
                        vector_return(vector_4, new_index__1257, vector_value_out_3);
                        return 1;
                      }

                      // 2008
                      else {
                        return 1;
                      } // !(false == ((out_of_space__1257) & (0u == number_of_freed_flows__58)))

                    }

                    // 2009
                    // 2010
                    // 2011
                    // 2012
                    else {
                      dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = 3750000000ul - packet_length;
                      vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_2[3u] = 223u;
                      vector_value_out_2[4u] = 0u;
                      vector_value_out_2[5u] = 0u;
                      vector_value_out_2[6u] = 0u;
                      vector_value_out_2[7u] = 0u;
                      vector_value_out_2[8u] = now & 0xff;
                      vector_value_out_2[9u] = (now >> 8) & 0xff;
                      vector_value_out_2[10u] = (now >> 16) & 0xff;
                      vector_value_out_2[11u] = (now >> 24) & 0xff;
                      vector_value_out_2[12u] = (now >> 32) & 0xff;
                      vector_value_out_2[13u] = (now >> 40) & 0xff;
                      vector_value_out_2[14u] = (now >> 48) & 0xff;
                      vector_value_out_2[15u] = (now >> 56) & 0xff;

                      // 2009
                      // 2010
                      // 2011
                      if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                        // 2009
                        // 2010
                        if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                          // 2009
                          if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          }

                          // 2010
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 2011
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 2012
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                    } // !(0u == map_has_this_key__1254)

                  }

                  // 2013
                  // 2014
                  // 2015
                  // 2016
                  // 2017
                  // 2018
                  else {
                    vector_return(vector_2, map_value_out_1, vector_value_out_1);
                    uint8_t map_key_2[4];
                    map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                    map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    map_key_2[3u] = 0u;
                    int map_value_out_2;
                    int map_has_this_key__1320 = map_get(map_2, &map_key_2, &map_value_out_2);

                    // 2013
                    // 2014
                    if (0u == map_has_this_key__1320) {
                      uint32_t new_index__1323;
                      int out_of_space__1323 = !dchain_allocate_new_index(dchain_2, &new_index__1323, now);

                      // 2013
                      if (false == ((out_of_space__1323) & (0u == number_of_freed_flows__58))) {
                        uint8_t* vector_value_out_2 = 0u;
                        vector_borrow(vector_5, new_index__1323, (void**)(&vector_value_out_2));
                        vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                        vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                        vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                        vector_value_out_2[3u] = 0u;
                        uint8_t* vector_value_out_3 = 0u;
                        vector_borrow(vector_4, new_index__1323, (void**)(&vector_value_out_3));
                        vector_value_out_3[0u] = 3750000000ul - packet_length;
                        vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                        vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                        vector_value_out_3[3u] = 223u;
                        vector_value_out_3[4u] = 0u;
                        vector_value_out_3[5u] = 0u;
                        vector_value_out_3[6u] = 0u;
                        vector_value_out_3[7u] = 0u;
                        vector_value_out_3[8u] = now & 0xff;
                        vector_value_out_3[9u] = (now >> 8) & 0xff;
                        vector_value_out_3[10u] = (now >> 16) & 0xff;
                        vector_value_out_3[11u] = (now >> 24) & 0xff;
                        vector_value_out_3[12u] = (now >> 32) & 0xff;
                        vector_value_out_3[13u] = (now >> 40) & 0xff;
                        vector_value_out_3[14u] = (now >> 48) & 0xff;
                        vector_value_out_3[15u] = (now >> 56) & 0xff;
                        map_put(map_2, vector_value_out_2, new_index__1323);
                        vector_return(vector_5, new_index__1323, vector_value_out_2);
                        vector_return(vector_4, new_index__1323, vector_value_out_3);
                        return 1;
                      }

                      // 2014
                      else {
                        return 1;
                      } // !(false == ((out_of_space__1323) & (0u == number_of_freed_flows__58)))

                    }

                    // 2015
                    // 2016
                    // 2017
                    // 2018
                    else {
                      dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = 3750000000ul - packet_length;
                      vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_2[3u] = 223u;
                      vector_value_out_2[4u] = 0u;
                      vector_value_out_2[5u] = 0u;
                      vector_value_out_2[6u] = 0u;
                      vector_value_out_2[7u] = 0u;
                      vector_value_out_2[8u] = now & 0xff;
                      vector_value_out_2[9u] = (now >> 8) & 0xff;
                      vector_value_out_2[10u] = (now >> 16) & 0xff;
                      vector_value_out_2[11u] = (now >> 24) & 0xff;
                      vector_value_out_2[12u] = (now >> 32) & 0xff;
                      vector_value_out_2[13u] = (now >> 40) & 0xff;
                      vector_value_out_2[14u] = (now >> 48) & 0xff;
                      vector_value_out_2[15u] = (now >> 56) & 0xff;

                      // 2015
                      // 2016
                      // 2017
                      if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                        // 2015
                        // 2016
                        if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                          // 2015
                          if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          }

                          // 2016
                          else {
                            vector_return(vector_4, map_value_out_2, vector_value_out_2);
                            return 1;
                          } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                        }

                        // 2017
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 2018
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                    } // !(0u == map_has_this_key__1320)

                  } // !(false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

                }

                // 2019
                // 2020
                // 2021
                // 2022
                // 2023
                // 2024
                else {
                  vector_return(vector_2, map_value_out_1, vector_value_out_1);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__1386 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 2019
                  // 2020
                  if (0u == map_has_this_key__1386) {
                    uint32_t new_index__1389;
                    int out_of_space__1389 = !dchain_allocate_new_index(dchain_2, &new_index__1389, now);

                    // 2019
                    if (false == ((out_of_space__1389) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_5, new_index__1389, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_2[3u] = 0u;
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_4, new_index__1389, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = 3750000000ul - packet_length;
                      vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_3[3u] = 223u;
                      vector_value_out_3[4u] = 0u;
                      vector_value_out_3[5u] = 0u;
                      vector_value_out_3[6u] = 0u;
                      vector_value_out_3[7u] = 0u;
                      vector_value_out_3[8u] = now & 0xff;
                      vector_value_out_3[9u] = (now >> 8) & 0xff;
                      vector_value_out_3[10u] = (now >> 16) & 0xff;
                      vector_value_out_3[11u] = (now >> 24) & 0xff;
                      vector_value_out_3[12u] = (now >> 32) & 0xff;
                      vector_value_out_3[13u] = (now >> 40) & 0xff;
                      vector_value_out_3[14u] = (now >> 48) & 0xff;
                      vector_value_out_3[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_2, new_index__1389);
                      vector_return(vector_5, new_index__1389, vector_value_out_2);
                      vector_return(vector_4, new_index__1389, vector_value_out_3);
                      return 1;
                    }

                    // 2020
                    else {
                      return 1;
                    } // !(false == ((out_of_space__1389) & (0u == number_of_freed_flows__58)))

                  }

                  // 2021
                  // 2022
                  // 2023
                  // 2024
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = 3750000000ul - packet_length;
                    vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_2[3u] = 223u;
                    vector_value_out_2[4u] = 0u;
                    vector_value_out_2[5u] = 0u;
                    vector_value_out_2[6u] = 0u;
                    vector_value_out_2[7u] = 0u;
                    vector_value_out_2[8u] = now & 0xff;
                    vector_value_out_2[9u] = (now >> 8) & 0xff;
                    vector_value_out_2[10u] = (now >> 16) & 0xff;
                    vector_value_out_2[11u] = (now >> 24) & 0xff;
                    vector_value_out_2[12u] = (now >> 32) & 0xff;
                    vector_value_out_2[13u] = (now >> 40) & 0xff;
                    vector_value_out_2[14u] = (now >> 48) & 0xff;
                    vector_value_out_2[15u] = (now >> 56) & 0xff;

                    // 2021
                    // 2022
                    // 2023
                    if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                      // 2021
                      // 2022
                      if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                        // 2021
                        if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        }

                        // 2022
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 2023
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 2024
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__1386)

                } // !(false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

              }

              // 2025
              // 2026
              // 2027
              // 2028
              // 2029
              // 2030
              else {
                vector_return(vector_2, map_value_out_1, vector_value_out_1);
                uint8_t map_key_2[4];
                map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                map_key_2[3u] = 0u;
                int map_value_out_2;
                int map_has_this_key__1452 = map_get(map_2, &map_key_2, &map_value_out_2);

                // 2025
                // 2026
                if (0u == map_has_this_key__1452) {
                  uint32_t new_index__1455;
                  int out_of_space__1455 = !dchain_allocate_new_index(dchain_2, &new_index__1455, now);

                  // 2025
                  if (false == ((out_of_space__1455) & (0u == number_of_freed_flows__58))) {
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_5, new_index__1455, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                    vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    vector_value_out_2[3u] = 0u;
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, new_index__1455, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;
                    map_put(map_2, vector_value_out_2, new_index__1455);
                    vector_return(vector_5, new_index__1455, vector_value_out_2);
                    vector_return(vector_4, new_index__1455, vector_value_out_3);
                    return 1;
                  }

                  // 2026
                  else {
                    return 1;
                  } // !(false == ((out_of_space__1455) & (0u == number_of_freed_flows__58)))

                }

                // 2027
                // 2028
                // 2029
                // 2030
                else {
                  dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                  uint8_t* vector_value_out_2 = 0u;
                  vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                  vector_value_out_2[0u] = 3750000000ul - packet_length;
                  vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_2[3u] = 223u;
                  vector_value_out_2[4u] = 0u;
                  vector_value_out_2[5u] = 0u;
                  vector_value_out_2[6u] = 0u;
                  vector_value_out_2[7u] = 0u;
                  vector_value_out_2[8u] = now & 0xff;
                  vector_value_out_2[9u] = (now >> 8) & 0xff;
                  vector_value_out_2[10u] = (now >> 16) & 0xff;
                  vector_value_out_2[11u] = (now >> 24) & 0xff;
                  vector_value_out_2[12u] = (now >> 32) & 0xff;
                  vector_value_out_2[13u] = (now >> 40) & 0xff;
                  vector_value_out_2[14u] = (now >> 48) & 0xff;
                  vector_value_out_2[15u] = (now >> 56) & 0xff;

                  // 2027
                  // 2028
                  // 2029
                  if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                    // 2027
                    // 2028
                    if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                      // 2027
                      if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      }

                      // 2028
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 2029
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                  }

                  // 2030
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_2);
                    return 1;
                  } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                } // !(0u == map_has_this_key__1452)

              } // !((now - vector_value_out_1[8ul]) < 6000000000000000ul)

            } // !(0u == map_has_this_key__1162)

          } // !(false == (3750000000ul < (vector_value_out[0ul] + ((625ul * (now - vector_value_out[8ul])) / 1000000000ul))))

        }

        // 2031
        // 2032
        // 2033
        // 2034
        // 2035
        // 2036
        // 2037
        // 2038
        // 2039
        // 2040
        // 2041
        // 2042
        // 2043
        // 2044
        // 2045
        // 2046
        // 2047
        // 2048
        // 2049
        // 2050
        // 2051
        // 2052
        // 2053
        // 2054
        // 2055
        // 2056
        // 2057
        // 2058
        // 2059
        // 2060
        // 2061
        else {
          vector_return(vector, map_value_out, vector_value_out);
          uint8_t map_key_1[4];
          map_key_1[0u] = ipv4_header_1->src_addr & 0xff;
          map_key_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
          map_key_1[2u] = 0u;
          map_key_1[3u] = 0u;
          int map_value_out_1;
          int map_has_this_key__1518 = map_get(map_1, &map_key_1, &map_value_out_1);

          // 2031
          // 2032
          // 2033
          // 2034
          // 2035
          // 2036
          // 2037
          if (0u == map_has_this_key__1518) {
            uint32_t new_index__1521;
            int out_of_space__1521 = !dchain_allocate_new_index(dchain_1, &new_index__1521, now);

            // 2031
            // 2032
            // 2033
            // 2034
            // 2035
            // 2036
            if (false == ((out_of_space__1521) & (0u == number_of_freed_flows__57))) {
              uint8_t* vector_value_out_1 = 0u;
              vector_borrow(vector_3, new_index__1521, (void**)(&vector_value_out_1));
              vector_value_out_1[0u] = ipv4_header_1->src_addr & 0xff;
              vector_value_out_1[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              vector_value_out_1[2u] = 0u;
              vector_value_out_1[3u] = 0u;
              uint8_t* vector_value_out_2 = 0u;
              vector_borrow(vector_2, new_index__1521, (void**)(&vector_value_out_2));
              vector_value_out_2[0u] = 3750000000ul - packet_length;
              vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
              vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
              vector_value_out_2[3u] = 223u;
              vector_value_out_2[4u] = 0u;
              vector_value_out_2[5u] = 0u;
              vector_value_out_2[6u] = 0u;
              vector_value_out_2[7u] = 0u;
              vector_value_out_2[8u] = now & 0xff;
              vector_value_out_2[9u] = (now >> 8) & 0xff;
              vector_value_out_2[10u] = (now >> 16) & 0xff;
              vector_value_out_2[11u] = (now >> 24) & 0xff;
              vector_value_out_2[12u] = (now >> 32) & 0xff;
              vector_value_out_2[13u] = (now >> 40) & 0xff;
              vector_value_out_2[14u] = (now >> 48) & 0xff;
              vector_value_out_2[15u] = (now >> 56) & 0xff;
              map_put(map_1, vector_value_out_1, new_index__1521);
              vector_return(vector_3, new_index__1521, vector_value_out_1);
              vector_return(vector_2, new_index__1521, vector_value_out_2);
              uint8_t map_key_2[4];
              map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_2[3u] = 0u;
              int map_value_out_2;
              int map_has_this_key__1529 = map_get(map_2, &map_key_2, &map_value_out_2);

              // 2031
              // 2032
              if (0u == map_has_this_key__1529) {
                uint32_t new_index__1532;
                int out_of_space__1532 = !dchain_allocate_new_index(dchain_2, &new_index__1532, now);

                // 2031
                if (false == ((out_of_space__1532) & (0u == number_of_freed_flows__58))) {
                  uint8_t* vector_value_out_3 = 0u;
                  vector_borrow(vector_5, new_index__1532, (void**)(&vector_value_out_3));
                  vector_value_out_3[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_3[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_3[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  vector_value_out_3[3u] = 0u;
                  uint8_t* vector_value_out_4 = 0u;
                  vector_borrow(vector_4, new_index__1532, (void**)(&vector_value_out_4));
                  vector_value_out_4[0u] = 3750000000ul - packet_length;
                  vector_value_out_4[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_4[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_4[3u] = 223u;
                  vector_value_out_4[4u] = 0u;
                  vector_value_out_4[5u] = 0u;
                  vector_value_out_4[6u] = 0u;
                  vector_value_out_4[7u] = 0u;
                  vector_value_out_4[8u] = now & 0xff;
                  vector_value_out_4[9u] = (now >> 8) & 0xff;
                  vector_value_out_4[10u] = (now >> 16) & 0xff;
                  vector_value_out_4[11u] = (now >> 24) & 0xff;
                  vector_value_out_4[12u] = (now >> 32) & 0xff;
                  vector_value_out_4[13u] = (now >> 40) & 0xff;
                  vector_value_out_4[14u] = (now >> 48) & 0xff;
                  vector_value_out_4[15u] = (now >> 56) & 0xff;
                  map_put(map_2, vector_value_out_3, new_index__1532);
                  vector_return(vector_5, new_index__1532, vector_value_out_3);
                  vector_return(vector_4, new_index__1532, vector_value_out_4);
                  return 1;
                }

                // 2032
                else {
                  return 1;
                } // !(false == ((out_of_space__1532) & (0u == number_of_freed_flows__58)))

              }

              // 2033
              // 2034
              // 2035
              // 2036
              else {
                dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                uint8_t* vector_value_out_3 = 0u;
                vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_3));
                vector_value_out_3[0u] = 3750000000ul - packet_length;
                vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_3[3u] = 223u;
                vector_value_out_3[4u] = 0u;
                vector_value_out_3[5u] = 0u;
                vector_value_out_3[6u] = 0u;
                vector_value_out_3[7u] = 0u;
                vector_value_out_3[8u] = now & 0xff;
                vector_value_out_3[9u] = (now >> 8) & 0xff;
                vector_value_out_3[10u] = (now >> 16) & 0xff;
                vector_value_out_3[11u] = (now >> 24) & 0xff;
                vector_value_out_3[12u] = (now >> 32) & 0xff;
                vector_value_out_3[13u] = (now >> 40) & 0xff;
                vector_value_out_3[14u] = (now >> 48) & 0xff;
                vector_value_out_3[15u] = (now >> 56) & 0xff;

                // 2033
                // 2034
                // 2035
                if ((now - vector_value_out_3[8ul]) < 6000000000000000ul) {

                  // 2033
                  // 2034
                  if (false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {

                    // 2033
                    if (false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul)))) {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    }

                    // 2034
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_3);
                      return 1;
                    } // !(false == (packet_length < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                  }

                  // 2035
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_3);
                    return 1;
                  } // !(false == (3750000000ul < (vector_value_out_3[0ul] + ((625ul * (now - vector_value_out_3[8ul])) / 1000000000ul))))

                }

                // 2036
                else {
                  vector_return(vector_4, map_value_out_2, vector_value_out_3);
                  return 1;
                } // !((now - vector_value_out_3[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__1529)

            }

            // 2037
            else {
              return 1;
            } // !(false == ((out_of_space__1521) & (0u == number_of_freed_flows__57)))

          }

          // 2038
          // 2039
          // 2040
          // 2041
          // 2042
          // 2043
          // 2044
          // 2045
          // 2046
          // 2047
          // 2048
          // 2049
          // 2050
          // 2051
          // 2052
          // 2053
          // 2054
          // 2055
          // 2056
          // 2057
          // 2058
          // 2059
          // 2060
          // 2061
          else {
            dchain_rejuvenate_index(dchain_1, map_value_out_1, now);
            uint8_t* vector_value_out_1 = 0u;
            vector_borrow(vector_2, map_value_out_1, (void**)(&vector_value_out_1));
            vector_value_out_1[0u] = 3750000000ul - packet_length;
            vector_value_out_1[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
            vector_value_out_1[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
            vector_value_out_1[3u] = 223u;
            vector_value_out_1[4u] = 0u;
            vector_value_out_1[5u] = 0u;
            vector_value_out_1[6u] = 0u;
            vector_value_out_1[7u] = 0u;
            vector_value_out_1[8u] = now & 0xff;
            vector_value_out_1[9u] = (now >> 8) & 0xff;
            vector_value_out_1[10u] = (now >> 16) & 0xff;
            vector_value_out_1[11u] = (now >> 24) & 0xff;
            vector_value_out_1[12u] = (now >> 32) & 0xff;
            vector_value_out_1[13u] = (now >> 40) & 0xff;
            vector_value_out_1[14u] = (now >> 48) & 0xff;
            vector_value_out_1[15u] = (now >> 56) & 0xff;

            // 2038
            // 2039
            // 2040
            // 2041
            // 2042
            // 2043
            // 2044
            // 2045
            // 2046
            // 2047
            // 2048
            // 2049
            // 2050
            // 2051
            // 2052
            // 2053
            // 2054
            // 2055
            if ((now - vector_value_out_1[8ul]) < 6000000000000000ul) {

              // 2038
              // 2039
              // 2040
              // 2041
              // 2042
              // 2043
              // 2044
              // 2045
              // 2046
              // 2047
              // 2048
              // 2049
              if (false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {

                // 2038
                // 2039
                // 2040
                // 2041
                // 2042
                // 2043
                if (false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul)))) {
                  vector_return(vector_2, map_value_out_1, vector_value_out_1);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__1610 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 2038
                  // 2039
                  if (0u == map_has_this_key__1610) {
                    uint32_t new_index__1613;
                    int out_of_space__1613 = !dchain_allocate_new_index(dchain_2, &new_index__1613, now);

                    // 2038
                    if (false == ((out_of_space__1613) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_5, new_index__1613, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_2[3u] = 0u;
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_4, new_index__1613, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = 3750000000ul - packet_length;
                      vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_3[3u] = 223u;
                      vector_value_out_3[4u] = 0u;
                      vector_value_out_3[5u] = 0u;
                      vector_value_out_3[6u] = 0u;
                      vector_value_out_3[7u] = 0u;
                      vector_value_out_3[8u] = now & 0xff;
                      vector_value_out_3[9u] = (now >> 8) & 0xff;
                      vector_value_out_3[10u] = (now >> 16) & 0xff;
                      vector_value_out_3[11u] = (now >> 24) & 0xff;
                      vector_value_out_3[12u] = (now >> 32) & 0xff;
                      vector_value_out_3[13u] = (now >> 40) & 0xff;
                      vector_value_out_3[14u] = (now >> 48) & 0xff;
                      vector_value_out_3[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_2, new_index__1613);
                      vector_return(vector_5, new_index__1613, vector_value_out_2);
                      vector_return(vector_4, new_index__1613, vector_value_out_3);
                      return 1;
                    }

                    // 2039
                    else {
                      return 1;
                    } // !(false == ((out_of_space__1613) & (0u == number_of_freed_flows__58)))

                  }

                  // 2040
                  // 2041
                  // 2042
                  // 2043
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = 3750000000ul - packet_length;
                    vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_2[3u] = 223u;
                    vector_value_out_2[4u] = 0u;
                    vector_value_out_2[5u] = 0u;
                    vector_value_out_2[6u] = 0u;
                    vector_value_out_2[7u] = 0u;
                    vector_value_out_2[8u] = now & 0xff;
                    vector_value_out_2[9u] = (now >> 8) & 0xff;
                    vector_value_out_2[10u] = (now >> 16) & 0xff;
                    vector_value_out_2[11u] = (now >> 24) & 0xff;
                    vector_value_out_2[12u] = (now >> 32) & 0xff;
                    vector_value_out_2[13u] = (now >> 40) & 0xff;
                    vector_value_out_2[14u] = (now >> 48) & 0xff;
                    vector_value_out_2[15u] = (now >> 56) & 0xff;

                    // 2040
                    // 2041
                    // 2042
                    if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                      // 2040
                      // 2041
                      if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                        // 2040
                        if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        }

                        // 2041
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 2042
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 2043
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__1610)

                }

                // 2044
                // 2045
                // 2046
                // 2047
                // 2048
                // 2049
                else {
                  vector_return(vector_2, map_value_out_1, vector_value_out_1);
                  uint8_t map_key_2[4];
                  map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                  map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  map_key_2[3u] = 0u;
                  int map_value_out_2;
                  int map_has_this_key__1676 = map_get(map_2, &map_key_2, &map_value_out_2);

                  // 2044
                  // 2045
                  if (0u == map_has_this_key__1676) {
                    uint32_t new_index__1679;
                    int out_of_space__1679 = !dchain_allocate_new_index(dchain_2, &new_index__1679, now);

                    // 2044
                    if (false == ((out_of_space__1679) & (0u == number_of_freed_flows__58))) {
                      uint8_t* vector_value_out_2 = 0u;
                      vector_borrow(vector_5, new_index__1679, (void**)(&vector_value_out_2));
                      vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                      vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                      vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                      vector_value_out_2[3u] = 0u;
                      uint8_t* vector_value_out_3 = 0u;
                      vector_borrow(vector_4, new_index__1679, (void**)(&vector_value_out_3));
                      vector_value_out_3[0u] = 3750000000ul - packet_length;
                      vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                      vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                      vector_value_out_3[3u] = 223u;
                      vector_value_out_3[4u] = 0u;
                      vector_value_out_3[5u] = 0u;
                      vector_value_out_3[6u] = 0u;
                      vector_value_out_3[7u] = 0u;
                      vector_value_out_3[8u] = now & 0xff;
                      vector_value_out_3[9u] = (now >> 8) & 0xff;
                      vector_value_out_3[10u] = (now >> 16) & 0xff;
                      vector_value_out_3[11u] = (now >> 24) & 0xff;
                      vector_value_out_3[12u] = (now >> 32) & 0xff;
                      vector_value_out_3[13u] = (now >> 40) & 0xff;
                      vector_value_out_3[14u] = (now >> 48) & 0xff;
                      vector_value_out_3[15u] = (now >> 56) & 0xff;
                      map_put(map_2, vector_value_out_2, new_index__1679);
                      vector_return(vector_5, new_index__1679, vector_value_out_2);
                      vector_return(vector_4, new_index__1679, vector_value_out_3);
                      return 1;
                    }

                    // 2045
                    else {
                      return 1;
                    } // !(false == ((out_of_space__1679) & (0u == number_of_freed_flows__58)))

                  }

                  // 2046
                  // 2047
                  // 2048
                  // 2049
                  else {
                    dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = 3750000000ul - packet_length;
                    vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_2[3u] = 223u;
                    vector_value_out_2[4u] = 0u;
                    vector_value_out_2[5u] = 0u;
                    vector_value_out_2[6u] = 0u;
                    vector_value_out_2[7u] = 0u;
                    vector_value_out_2[8u] = now & 0xff;
                    vector_value_out_2[9u] = (now >> 8) & 0xff;
                    vector_value_out_2[10u] = (now >> 16) & 0xff;
                    vector_value_out_2[11u] = (now >> 24) & 0xff;
                    vector_value_out_2[12u] = (now >> 32) & 0xff;
                    vector_value_out_2[13u] = (now >> 40) & 0xff;
                    vector_value_out_2[14u] = (now >> 48) & 0xff;
                    vector_value_out_2[15u] = (now >> 56) & 0xff;

                    // 2046
                    // 2047
                    // 2048
                    if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                      // 2046
                      // 2047
                      if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                        // 2046
                        if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        }

                        // 2047
                        else {
                          vector_return(vector_4, map_value_out_2, vector_value_out_2);
                          return 1;
                        } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                      }

                      // 2048
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 2049
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                  } // !(0u == map_has_this_key__1676)

                } // !(false == (packet_length < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

              }

              // 2050
              // 2051
              // 2052
              // 2053
              // 2054
              // 2055
              else {
                vector_return(vector_2, map_value_out_1, vector_value_out_1);
                uint8_t map_key_2[4];
                map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
                map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                map_key_2[3u] = 0u;
                int map_value_out_2;
                int map_has_this_key__1742 = map_get(map_2, &map_key_2, &map_value_out_2);

                // 2050
                // 2051
                if (0u == map_has_this_key__1742) {
                  uint32_t new_index__1745;
                  int out_of_space__1745 = !dchain_allocate_new_index(dchain_2, &new_index__1745, now);

                  // 2050
                  if (false == ((out_of_space__1745) & (0u == number_of_freed_flows__58))) {
                    uint8_t* vector_value_out_2 = 0u;
                    vector_borrow(vector_5, new_index__1745, (void**)(&vector_value_out_2));
                    vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                    vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                    vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                    vector_value_out_2[3u] = 0u;
                    uint8_t* vector_value_out_3 = 0u;
                    vector_borrow(vector_4, new_index__1745, (void**)(&vector_value_out_3));
                    vector_value_out_3[0u] = 3750000000ul - packet_length;
                    vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                    vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                    vector_value_out_3[3u] = 223u;
                    vector_value_out_3[4u] = 0u;
                    vector_value_out_3[5u] = 0u;
                    vector_value_out_3[6u] = 0u;
                    vector_value_out_3[7u] = 0u;
                    vector_value_out_3[8u] = now & 0xff;
                    vector_value_out_3[9u] = (now >> 8) & 0xff;
                    vector_value_out_3[10u] = (now >> 16) & 0xff;
                    vector_value_out_3[11u] = (now >> 24) & 0xff;
                    vector_value_out_3[12u] = (now >> 32) & 0xff;
                    vector_value_out_3[13u] = (now >> 40) & 0xff;
                    vector_value_out_3[14u] = (now >> 48) & 0xff;
                    vector_value_out_3[15u] = (now >> 56) & 0xff;
                    map_put(map_2, vector_value_out_2, new_index__1745);
                    vector_return(vector_5, new_index__1745, vector_value_out_2);
                    vector_return(vector_4, new_index__1745, vector_value_out_3);
                    return 1;
                  }

                  // 2051
                  else {
                    return 1;
                  } // !(false == ((out_of_space__1745) & (0u == number_of_freed_flows__58)))

                }

                // 2052
                // 2053
                // 2054
                // 2055
                else {
                  dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                  uint8_t* vector_value_out_2 = 0u;
                  vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                  vector_value_out_2[0u] = 3750000000ul - packet_length;
                  vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_2[3u] = 223u;
                  vector_value_out_2[4u] = 0u;
                  vector_value_out_2[5u] = 0u;
                  vector_value_out_2[6u] = 0u;
                  vector_value_out_2[7u] = 0u;
                  vector_value_out_2[8u] = now & 0xff;
                  vector_value_out_2[9u] = (now >> 8) & 0xff;
                  vector_value_out_2[10u] = (now >> 16) & 0xff;
                  vector_value_out_2[11u] = (now >> 24) & 0xff;
                  vector_value_out_2[12u] = (now >> 32) & 0xff;
                  vector_value_out_2[13u] = (now >> 40) & 0xff;
                  vector_value_out_2[14u] = (now >> 48) & 0xff;
                  vector_value_out_2[15u] = (now >> 56) & 0xff;

                  // 2052
                  // 2053
                  // 2054
                  if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                    // 2052
                    // 2053
                    if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                      // 2052
                      if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      }

                      // 2053
                      else {
                        vector_return(vector_4, map_value_out_2, vector_value_out_2);
                        return 1;
                      } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                    }

                    // 2054
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                  }

                  // 2055
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_2);
                    return 1;
                  } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

                } // !(0u == map_has_this_key__1742)

              } // !(false == (3750000000ul < (vector_value_out_1[0ul] + ((625ul * (now - vector_value_out_1[8ul])) / 1000000000ul))))

            }

            // 2056
            // 2057
            // 2058
            // 2059
            // 2060
            // 2061
            else {
              vector_return(vector_2, map_value_out_1, vector_value_out_1);
              uint8_t map_key_2[4];
              map_key_2[0u] = ipv4_header_1->src_addr & 0xff;
              map_key_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
              map_key_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
              map_key_2[3u] = 0u;
              int map_value_out_2;
              int map_has_this_key__1808 = map_get(map_2, &map_key_2, &map_value_out_2);

              // 2056
              // 2057
              if (0u == map_has_this_key__1808) {
                uint32_t new_index__1811;
                int out_of_space__1811 = !dchain_allocate_new_index(dchain_2, &new_index__1811, now);

                // 2056
                if (false == ((out_of_space__1811) & (0u == number_of_freed_flows__58))) {
                  uint8_t* vector_value_out_2 = 0u;
                  vector_borrow(vector_5, new_index__1811, (void**)(&vector_value_out_2));
                  vector_value_out_2[0u] = ipv4_header_1->src_addr & 0xff;
                  vector_value_out_2[1u] = (ipv4_header_1->src_addr >> 8) & 0xff;
                  vector_value_out_2[2u] = (ipv4_header_1->src_addr >> 16) & 0xff;
                  vector_value_out_2[3u] = 0u;
                  uint8_t* vector_value_out_3 = 0u;
                  vector_borrow(vector_4, new_index__1811, (void**)(&vector_value_out_3));
                  vector_value_out_3[0u] = 3750000000ul - packet_length;
                  vector_value_out_3[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                  vector_value_out_3[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                  vector_value_out_3[3u] = 223u;
                  vector_value_out_3[4u] = 0u;
                  vector_value_out_3[5u] = 0u;
                  vector_value_out_3[6u] = 0u;
                  vector_value_out_3[7u] = 0u;
                  vector_value_out_3[8u] = now & 0xff;
                  vector_value_out_3[9u] = (now >> 8) & 0xff;
                  vector_value_out_3[10u] = (now >> 16) & 0xff;
                  vector_value_out_3[11u] = (now >> 24) & 0xff;
                  vector_value_out_3[12u] = (now >> 32) & 0xff;
                  vector_value_out_3[13u] = (now >> 40) & 0xff;
                  vector_value_out_3[14u] = (now >> 48) & 0xff;
                  vector_value_out_3[15u] = (now >> 56) & 0xff;
                  map_put(map_2, vector_value_out_2, new_index__1811);
                  vector_return(vector_5, new_index__1811, vector_value_out_2);
                  vector_return(vector_4, new_index__1811, vector_value_out_3);
                  return 1;
                }

                // 2057
                else {
                  return 1;
                } // !(false == ((out_of_space__1811) & (0u == number_of_freed_flows__58)))

              }

              // 2058
              // 2059
              // 2060
              // 2061
              else {
                dchain_rejuvenate_index(dchain_2, map_value_out_2, now);
                uint8_t* vector_value_out_2 = 0u;
                vector_borrow(vector_4, map_value_out_2, (void**)(&vector_value_out_2));
                vector_value_out_2[0u] = 3750000000ul - packet_length;
                vector_value_out_2[1u] = ((3750000000ul - packet_length) >> 8ul) & 0xff;
                vector_value_out_2[2u] = ((3750000000ul - packet_length) >> 16ul) & 0xff;
                vector_value_out_2[3u] = 223u;
                vector_value_out_2[4u] = 0u;
                vector_value_out_2[5u] = 0u;
                vector_value_out_2[6u] = 0u;
                vector_value_out_2[7u] = 0u;
                vector_value_out_2[8u] = now & 0xff;
                vector_value_out_2[9u] = (now >> 8) & 0xff;
                vector_value_out_2[10u] = (now >> 16) & 0xff;
                vector_value_out_2[11u] = (now >> 24) & 0xff;
                vector_value_out_2[12u] = (now >> 32) & 0xff;
                vector_value_out_2[13u] = (now >> 40) & 0xff;
                vector_value_out_2[14u] = (now >> 48) & 0xff;
                vector_value_out_2[15u] = (now >> 56) & 0xff;

                // 2058
                // 2059
                // 2060
                if ((now - vector_value_out_2[8ul]) < 6000000000000000ul) {

                  // 2058
                  // 2059
                  if (false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {

                    // 2058
                    if (false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul)))) {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    }

                    // 2059
                    else {
                      vector_return(vector_4, map_value_out_2, vector_value_out_2);
                      return 1;
                    } // !(false == (packet_length < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                  }

                  // 2060
                  else {
                    vector_return(vector_4, map_value_out_2, vector_value_out_2);
                    return 1;
                  } // !(false == (3750000000ul < (vector_value_out_2[0ul] + ((625ul * (now - vector_value_out_2[8ul])) / 1000000000ul))))

                }

                // 2061
                else {
                  vector_return(vector_4, map_value_out_2, vector_value_out_2);
                  return 1;
                } // !((now - vector_value_out_2[8ul]) < 6000000000000000ul)

              } // !(0u == map_has_this_key__1808)

            } // !((now - vector_value_out_1[8ul]) < 6000000000000000ul)

          } // !(0u == map_has_this_key__1518)

        } // !((now - vector_value_out[8ul]) < 6000000000000000ul)

      } // !(0u == map_has_this_key__68)

    } // !device

  }

  // 2062
  else {
    // dropping
    return device;
  } // !(0u == ((8u != ether_header_1->ether_type) | ((4294967282u + packet_length) < 20ul)))

}
