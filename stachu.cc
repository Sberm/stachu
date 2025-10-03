#include <iostream>
#include <vector>
#include <string>
#include <set>

#define CYAN "\x1b[;36m"
#define RESET "\x1b[;39m"

static const std::string rm = "rm ";
using task_set_t = std::set<std::pair<unsigned long long, std::string>>;

static bool starts_with(const std::string& str, const std::string& prefix)
{
    size_t prefix_siz = prefix.size();

    if (prefix_siz > str.size())
        return false;

    return !str.compare(0, prefix_siz, prefix);
}


#define print_coloredl(stuff) \
    std::cout << CYAN << stuff << RESET;

static void print_tasks(task_set_t &task_set)
{
    unsigned long long fake_idx = 1;
    for (auto iter = task_set.rbegin(); iter != task_set.rend(); ++iter) {
        print_coloredl(fake_idx << ". " << CYAN << iter->second);
        std::cout << std::endl;
        ++fake_idx;
    }
}

static void operate(std::string& user_input, task_set_t &task_set, unsigned long long &cnt,
                    unsigned long long &completed)
{
    if (starts_with(user_input, rm)) {
        unsigned long long idx = 0;
        unsigned long long user_idx = 0;
        bool removed = false;
        size_t pos = user_input.find(rm) + rm.size();
        std::string rest = user_input.substr(pos, user_input.size() - pos);

        try {
            user_idx = std::stoull(rest);
        } catch (...) {
            std::cout << "std::stoull failed" << std::endl;
        }

        for (auto iter = task_set.rbegin(); iter != task_set.rend(); ++iter) {
            if (idx == user_idx - 1) {
                task_set.erase(std::next(iter).base());
                removed = true;
                break;
            }
            idx += 1;
        }
        if (!removed) {
            std::cout << "task of \'" << user_idx << "\' doesn't exist" << std::endl;
        } else {
            print_tasks(task_set);
            completed += 1;
        }
    } else if (user_input.size() == 0 || (user_input.size() > 0 && std::isspace(user_input[0]))) {
    } else if (user_input == "n") {
        print_coloredl(completed << " completed");
        std::cout << std::endl;
    } else if (user_input == "p") {
        print_tasks(task_set);
    } else if (user_input == "q") {
        exit(0);
    } else {
        task_set.insert(make_pair(cnt, user_input));
        cnt += 1;
        print_tasks(task_set);
    }
}

static int start()
{
    unsigned long long cnt = 0ULL;
    unsigned long long completed = 0;
    task_set_t task_set;
    std::string user_input;
    auto prompt = []() {
        std::cout << "stachu > " << std::flush;
    };

    prompt();
    while (std::getline(std::cin, user_input)) {
        operate(user_input, task_set, cnt, completed);
        prompt();
    }
    return 0;
}

int main()
{
    return start();
}
