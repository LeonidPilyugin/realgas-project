// 
// streamhandler.hpp
// 
// This file contains StreamHandler class
// 
// Author: Leonid Pilyugin <l.pilyugin04@gmail.com>
// 
#pragma once

// class StreamHandler
// 
// Describes a streem handler
// 
// Methods:
// 1) virtual void Close() = 0
// 2) virtual bool IsOpen() = 0
// 
class StreamHandler {
public:
    // virtual void Close() = 0
    // 
    // Closes stream
    // 
    // Arguments: no
    // 
    // Returns: nothing
    // 
    virtual void Close() = 0;

    // virtual bool IsOpen() = 0
    // 
    // Arguments: no
    // 
    // Returns true if stream is opened, else false
    // 
    virtual bool IsOpen() = 0;
};