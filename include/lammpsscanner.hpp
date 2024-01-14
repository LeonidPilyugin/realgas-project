// 
// lammpsscanner.hpp
// 
// Contains LammpsScanner class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once
 
#include <string>
#include <fstream>
#include "scanner.hpp"
#include "streamhandler.hpp"

// class LammpsScanner : public Scanner, public StreamHandler
// 
// Describes scanner from .lammpstrj file
// 
// Methods:
// 1) LammpsScanner(LammpsScanner&& scanner)
// 2) LammpsScanner& operator=(LammpsScanner&& scanner)
// 3) LammpsScanner(std::string &path)
// 4) Environment Scan() override
// 5) bool IsOpen() override
// 6) void Close() override
// 
class LammpsScanner : public Scanner, public StreamHandler {
public:
    // LammpsScanner() = delete
    // 
    // Deleted default constructor
    // 
    LammpsScanner() = delete;

    //  LammpsScanner(const LammpsScanner&) = delete
    // 
    // Deleted copy constructor
    // 
    LammpsScanner(const LammpsScanner&) = delete;

    // LammpsScanner& operator=(const LammpsScanner&) = delete
    // 
    // Deleted copy assigment operator
    // 
    LammpsScanner& operator=(const LammpsScanner&) = delete;

    // LammpsScanner(LammpsScanner&& scanner)
    // 
    // Move constructor
    // 
    // Arguments:
    // 1) LammpsScanner&& scanner -- scanner to move
    // 
    LammpsScanner(LammpsScanner&& scanner);

    // LammpsScanner& operator=(LammpsScanner&& scanner)
    // 
    // Move assigment operator
    // 
    // Arguments:
    // 1) LammpsScanner&& scanner -- scanner to move
    // 
    // Return *this
    //  
    LammpsScanner& operator=(LammpsScanner&& scanner);

    // LammpsScanner(std::string &path)
    // 
    // Constructor
    // 
    // Arguments:
    // 1) std::string &path -- path to file
    // 
    LammpsScanner(std::string &path);

    // ~LammpsScanner()
    // 
    // Destructor
    // 
    ~LammpsScanner();

    // Environment Scan()
    // 
    // Scans environment
    // 
    // Arguments: no
    // 
    // Returns scanned environment
    // 
    Environment Scan() override;

    // bool IsOpen() override
    // 
    // Arguments: no
    // 
    // Returns true if stream is opened, else false
    // 
    bool IsOpen() override;

    // void Close() override
    // 
    // Closes stream
    // 
    // Arguments: no
    // 
    // Returns: nothing
    // 
    void Close() override;

protected:
    std::ifstream input;  // input file stream

private:
    // void Move(LammpsScanner& scanner)
    // 
    // Moves scanner to this object
    // 
    // Arguments:
    // 1) LammpsScanner& scanner
    // 
    // Returns nothing
    // 
    void Move(LammpsScanner& scanner);
};
