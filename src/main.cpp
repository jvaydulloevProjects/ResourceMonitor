#include <fstream>
#include <memory>
#include "../include/Producer.hpp"
#include "../include/Consumer.hpp"
#include "../include/Logger.hpp"
#include "../include/FileReader.hpp"
#include "../include/EventManager.hpp"
#include "../include/interfaces.hpp"
#include <thread>
#include <functional>
#include <random>
#include <atomic>

void generateRandomFile(const std::string& filename, std::size_t count, int minValue = 1, int maxValue = 1000000) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(minValue, maxValue);

    for (std::size_t i = 0; i < count; ++i) {
        outFile << dist(gen) << "\n";
    }
}

int main()
{
    try {
        generateRandomFile("input.txt", 10000); 
        std::cout << "File generated successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    EventManager<int> manager;
    std::shared_ptr<TaskQueue<int>> tasks = std::make_shared<TaskQueue<int>>();
    FileReader<int> file("input.txt","../logs/log.txt");

    Producer<int> prod(tasks);
    Consumer<int> con(tasks, [](int& task){
        task /=2;
    });
    Logger<int> log(manager);

    // Поток для чтения и добавления задач
    std::thread producerThread([&]() {
        file.read(manager, prod, con);
    });

    // Поток для обработки задач
    std::thread consumerThread([&]() {
        con.run(manager,file);
    });

    producerThread.join();
    consumerThread.join();


    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Processing completed in " << duration.count() << " ms!" << std::endl;

    return 0;
}
