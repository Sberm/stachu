#include <iostream>
#include <vector>
#include <string>
#include <set>

#define CYAN "\x1b[;36m"
#define RESET "\x1b[;39m"

static bool starts_with(const std::string& str, const std::string& prefix)
{
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

static void print_tasks(std::set<std::pair<unsigned long long, std::string>> &task_set)
{
    unsigned long long fake_idx = 1;
    for (auto iter = task_set.rbegin(); iter != task_set.rend(); ++iter) {
        std::cout << fake_idx << ". " << CYAN << iter->second << RESET << std::endl;
        ++fake_idx;
    }
}

static int start()
{
    unsigned long long cnt = 0ULL;
    std::set<std::pair<unsigned long long, std::string>> task_set;
    std::string user_input;
    auto prompt = []() {
        std::cout << "stachu > " << std::flush;
    };
    const std::string rm = "rm ";

    prompt();
    while (std::getline(std::cin, user_input)) {
        if (starts_with(user_input, rm)) {
            unsigned long long idx = 0;
            unsigned long long user_idx = 0;
            bool removed = false;
            size_t pos = user_input.find(rm) + rm.size();
            std::string rest = user_input.substr(pos, user_input.size() - pos);

            try {
                 user_idx = std::stoull(rest);
            } catch (...) {
            }

            for (auto iter = task_set.rbegin(); iter != task_set.rend(); ++iter) {
                if (idx == user_idx - 1) {
                    task_set.erase(std::next(iter).base());
                    removed = true;
                    break;
                }
                idx += 1;
            }
            if (!removed)
                std::cout << "task of \'" << user_idx << "\' doesn't exist" << std::endl;
            else
                print_tasks(task_set);
        } else if (user_input.size() == 0 || (user_input.size() > 0 && std::isspace(user_input[0]))) {
        } else if (user_input == "p") {
            print_tasks(task_set);
        } else if (user_input == "q") {
            exit(0);
        } else {
            task_set.insert(make_pair(cnt, user_input));
            cnt += 1;
            print_tasks(task_set);
        }
        prompt();
    }
    return 0;
}

int main()
{
    return start();
}
