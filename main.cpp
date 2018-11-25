// These are some microbenchmarks to test the best way of initializing a vector
// from an existing data array. The use case is copying data into a ROS message,
// whose array type is a vector. The vector is default initialized as part of
// the message construction. However, these benchmarks include the construction
// time of the vector into the benchmark.
//
// some of these versions taken from:
// https://stackoverflow.com/questions/259297/how-do-you-copy-the-contents-of-an-array-to-a-stdvector-in-c-without-looping

#include <benchmark/benchmark.h>
#include <vector>
#include <cstring>
#include <stdint.h>

class Fixture : public benchmark::Fixture {
    public:
        uint8_t* data;

        // simulating a 720p RGB image
        int width = 1280;
        int height = 720;
        int bpp = 3;
        int size = width * height * bpp;

        Fixture() {
            data = new uint8_t[size];
            for (int i = 0; i < size; ++i) {
                data[i] = i % 256;
            }
        }

        ~Fixture() {
            delete[] data;
        }
};

BENCHMARK_F(Fixture, push_back)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        for (int i = 0; i < size; ++i) {
            vec.push_back(data[i]);
        }
    }
}

BENCHMARK_F(Fixture, push_back_with_reserve)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.reserve(size);
        for (int i = 0; i < size; ++i) {
            vec.push_back(data[i]);
        }
    }
}

BENCHMARK_F(Fixture, resize_and_memcpy)(benchmark::State& st) {
   for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.resize(size);
        std::memcpy((char*)(&vec[0]), data, size);
  }
}

BENCHMARK_F(Fixture, assign)(benchmark::State& st) {
   for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.assign(data, data+size);
  }
}

BENCHMARK_F(Fixture, swap)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        std::vector<uint8_t> vec2(data, data+size);
        vec.swap(vec2);
    }
}

BENCHMARK_F(Fixture, insert)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.insert(vec.begin(), data, data+size);
    }
}

BENCHMARK_F(Fixture, insert_with_reserve)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.reserve(size);
        vec.insert(vec.begin(), data, data+size);
    }
}

BENCHMARK_F(Fixture, insert_from_vector)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        std::vector<uint8_t> vec2(data, data+size);
        vec.insert(vec.begin(), vec2.begin(), vec2.end());
    }
}

BENCHMARK_F(Fixture, back_inserter)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        std::copy(data, data+size, std::back_inserter(vec));
    }
}

BENCHMARK_F(Fixture, back_inserter_with_reserve)(benchmark::State& st) {
    for (auto _ : st) {
        std::vector<uint8_t> vec;
        vec.reserve(size);
        std::copy(data, data+size, std::back_inserter(vec));
    }
}


BENCHMARK_MAIN();
