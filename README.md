```
--------------------------------------------------------------------------
Benchmark                                   Time           CPU Iterations
--------------------------------------------------------------------------
Fixture/push_back                    10550020 ns   10546265 ns         63
Fixture/push_back_with_reserve        2671354 ns    2670105 ns        250
Fixture/resize_and_memcpy              364385 ns     364347 ns       1814
Fixture/assign                         271599 ns     271275 ns       2644
Fixture/swap                           265243 ns     265242 ns       2661
Fixture/insert                         258958 ns     258957 ns       2619
Fixture/insert_with_reserve            258743 ns     258730 ns       2686
Fixture/insert_from_vector             519594 ns     519591 ns       1062
Fixture/back_inserter                12063501 ns   12062643 ns         59
Fixture/back_inserter_with_reserve    2696150 ns    2695984 ns        258
```
