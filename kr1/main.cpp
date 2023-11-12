#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

std::mutex ioMutex;
std::mutex balanceMutex;
double accountBalance = 0.0;

const int operationDelayMean = 50;  
const int operationDelayDeviation = 25;  
const int maxRetryAttempts = 3;

void updateBalanceWithDelay(const std::vector<double>& scenario, int threadId) {
    for (double change : scenario) {
        int retryAttempts = 0;

        while (retryAttempts < maxRetryAttempts) {
            std::unique_lock<std::mutex> lock(balanceMutex);

            if (accountBalance + change >= 0) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::normal_distribution<> delayDistribution(operationDelayMean, operationDelayDeviation);
                int delay = std::max(0, static_cast<int>(delayDistribution(gen)));

                std::this_thread::sleep_for(std::chrono::milliseconds(delay));

                double oldBalance = accountBalance;
                accountBalance += change;
                double newBalance = accountBalance;

                lock.unlock();

                {
                    std::unique_lock<std::mutex> ioLock(ioMutex);
                    std::cout << "Thread " << threadId << ": было=" << oldBalance << ", операция " << (change >= 0 ? "+" : "-") << std::abs(change) << ", стало=" << newBalance << std::endl;
                }

                break; 
            }
            else {
                lock.unlock();

                {
                    std::unique_lock<std::mutex> ioLock(ioMutex);
                    std::cout << "Thread " << threadId << ": Операция " << (change >= 0 ? "+" : "-") << std::abs(change) << " не выполнена (недостаточно средств). Попытка " << retryAttempts + 1 << "/" << maxRetryAttempts << std::endl;
                }

                ++retryAttempts;
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
            }
        }
    }
}

double getBalance() {
    std::unique_lock<std::mutex> lock(balanceMutex);
    return accountBalance;
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int numThreads = 3;

    std::vector<std::vector<double>> scenarios = {
        {100, -50, 30, -20},
        {-10, 20, -15, 25},
        {50, -40, 10, -30}
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(updateBalanceWithDelay, std::ref(scenarios[i]), i + 1);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::unique_lock<std::mutex> lock(ioMutex);
    std::cout << "Баланс: " << getBalance() << std::endl;

    return 0;
}
