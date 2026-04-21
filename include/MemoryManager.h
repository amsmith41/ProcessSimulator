#pragma once

class Process;

struct AddressTranslation
{
    int virtualAddress; // Virtual address to be translated
    int virtualPageNumber; // Page number from virtual address
    int offset; // Offset within the page in virtual address
    int physicalAddress; // Translated physical address
    int frameNumber; // Physical frame from the virtual page number
    bool valid; // True if translation is valid and the virtual page is mapped to a physical frame, false otherwise
};

class MemoryManager
{
    private:
        int pageSize;
        int numFrames;

    public:
        MemoryManager(int pageSize, int numFrames); // Constructor to initialize page size and number of frames
        AddressTranslation translateAddress(Process* process, int virtualAddress) const; // Translate virtual address to physical address using the page table

        int getPageSize() const; // Get page size
        int getNumFrames() const; // Get number of frames
};