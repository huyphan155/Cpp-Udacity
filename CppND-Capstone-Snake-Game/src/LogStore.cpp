#include "LogStore.h"

LogStore::LogStore() : specialItemCount(0) {}

void LogStore::LogSpecialItem() {
    std::lock_guard<std::mutex> lock(mutex);
    specialItemCount++;
}

int LogStore::GetSpecialItemCount() const {
    return specialItemCount;
}
