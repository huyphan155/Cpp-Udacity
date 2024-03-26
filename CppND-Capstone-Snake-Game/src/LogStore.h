#ifndef LOGSTORE_H
#define LOGSTORE_H

#include <mutex>

class LogStore {
public:
    LogStore();

    void LogSpecialItem();

    int GetSpecialItemCount() const;

private:
    int specialItemCount;
    std::mutex mutex;
};

#endif
