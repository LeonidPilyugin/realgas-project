// 
// lammpssaver.hpp
// 
// Contains LammpsSaver class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

#include <fstream>
#include "saver.hpp"
#include "streamhandler.hpp"

// class LammpsSaver : public Saver, public StreamHandler
// 
// Describes saver to .lammpstrj file
// 
// Methods:
// 1) LammpsSaver(LammpsSaver&&)
// 2) LammpsSaver& operator=(LammpsSaver&&)
// 3) LammpsSaver(std::string &path)
// 4) void Save(const Environment&, uint64_t) override
// 5) bool IsOpen() override
// 6) void Close() override
// 
class LammpsSaver : public Saver, public StreamHandler {
public:
    // LammpsSaver() = delete
    // 
    // Deleted default constructor
    // 
    LammpsSaver() = delete;

    // LammpsSaver(const LammpsSaver&) = delete
    // 
    // Deleted copy constructor
    // 
    LammpsSaver(const LammpsSaver&) = delete;

    // LammpsSaver(const LammpsSaver&) = delete
    // 
    // Deleted copy assigment operator
    // 
    LammpsSaver& operator=(const LammpsSaver&) = delete;

    // LammpsSaver(LammpsSaver&& saver)
    // 
    // Move constructor
    // 
    // Arguments:
    // 1) LammpsSaver&& saver -- saver to move
    // 
    LammpsSaver(LammpsSaver&& saver);

    // LammpsSaver& operator=(LammpsSaver&& saver)
    // 
    // Move assigment operator
    // 
    // Arguments:
    // 1) LammpsSaver&& saver -- saver to move
    // 
    // Return *this
    //  
    LammpsSaver& operator=(LammpsSaver&& saver);

    // LammpsSaver(std::string &path)
    // 
    // Constructor
    // 
    // Arguments:
    // 1) std::string &path -- path to file
    // 
    LammpsSaver(std::string &path);

    // ~LammpsSaver()
    // 
    // Destructor
    // 
    ~LammpsSaver();

    // void Save(const Environment&, uint64_t) override
    // 
    // Saves environment and step
    // 
    // Arguments:
    // 1) const Environment &env -- environment to save
    // 2) uint64_t step -- step to save
    // 
    // Returns nothing
    // 
    void Save(const Environment &env, uint64_t step) override;

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
    std::ofstream output;  // output file stream

private:
    // void Move(LammpsSaver& saver)
    // 
    // Moves saver to this object
    // 
    // Arguments:
    // 1) LammpsSaver& saver
    // 
    // Returns nothing
    // 
    void Move(LammpsSaver& saver);
};
 