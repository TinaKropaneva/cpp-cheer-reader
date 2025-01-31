#include <iomanip>
#include <iostream>
#include <map>

struct Progress {
    std::map<int, int> users_progress;
    std::map<int, int> book_progress;
    int total_users = 0;
};

void SaveProgress(int user_id, int page_number, Progress& progress) {
    if (progress.users_progress.count(user_id)) {
        int old_page = progress.users_progress[user_id];
        if (--progress.book_progress[old_page] == 0) {
            progress.book_progress.erase(old_page);
        }
    } else {
        progress.total_users++;
    }

    progress.users_progress[user_id] = page_number;
    progress.book_progress[page_number]++;
}

void CheerUser(int user_id, Progress& progress) {
    if (progress.users_progress.count(user_id) == 0) {
        std::cout << std::setprecision(6) << 0.0 << std::endl;
        return;
    }

    if (progress.total_users <= 1) {
        std::cout << std::setprecision(6) << 1.0 << std::endl;
        return;
    }

    int user_page = progress.users_progress[user_id];
    int worse_users = 0;

    for (const auto& [page, count] : progress.book_progress) {
        if (page >= user_page) {
            break;
        }
        worse_users += count;
    }

    double worst_percentage = static_cast<double>(worse_users) / (progress.total_users - 1);
    std::cout << std::setprecision(6) << worst_percentage << std::endl;
}

int main() {
    Progress progress;
    int q = 0;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::string command;
        std::cin >> command;
        if (command == "READ") {
            int user_id, page_number;
            std::cin >> user_id >> page_number;
            SaveProgress(user_id, page_number, progress);
        } else if (command == "CHEER") {
            int user_id;
            std::cin >> user_id;
            CheerUser(user_id, progress);
        }
    }
}
