#pragma once
#include <fstream>
#include <iostream>
#include <memory>
#include "interfaces.hpp"

template<typename T>
class FileReader : public IReadable<T>, public IWriteable<T>
{
private:
    std::string filename;
    std::ofstream outFile;



public:
    explicit FileReader(const std::string& file, const std::string& logFile = "log.txt")
        : filename(file)
    {
        outFile.open(logFile, std::ios::out | std::ios::trunc);
        if (!outFile.is_open())
            throw std::runtime_error("Cannot open log file: " + logFile);
    }
    ~FileReader() {
        if (outFile.is_open()) outFile.close();
    }

    void write(const T& value) override
    {
        if (outFile.is_open())
            outFile << value<<" ";
    }
    void read(IEventManager<T>& event,
              IProducable<T>& producer,
              IConsumable<T>& consumer) override
    {
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        T value;
        while (infile >> value) {
            producer.run(value, event);   // исправлено
        }

        infile.close();
        consumer.stop();
    }
};
