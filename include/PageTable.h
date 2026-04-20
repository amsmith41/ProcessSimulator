#pragma once
#include <vector>

// Structure to represent a singular page table entry
struct PageTableEntry
{
    int physicalFrameNumber; // Physical frame number
    bool valid; // True if virtual page is mapped to a physical frame, false if not
    // Dirty bit not implemented
    // Reference bit not implemented
};

// Representation of a page table for a single process
// Index in table corresonds to a virtual page number
// Entry @ index reveals if page is mapped and the physical frame it's mapped to if it is mapped
class PageTable
{
    private:
        std::vector<PageTableEntry> entries; // Vector to hold page table entries

    public:
        PageTable(int numPages); // Constructor to initialize page table, fixed nubmer of pages, all entries are unmapped by default
        void mapPage(int virtualPageNumber, int physicalFrameNumber); // Map virtual page to a physical frame
        void unmapPage(int virtualPageNumber); // Unmap a virtual page
        bool isMapped(int virtualPageNumber) const; // Check if a virtual page is mapped
        int getPhysicalFrameNumber(int virtualPageNumber) const; // Get the physical frame number
        int getNumPages() const; // Get the number of pages in the page table
};