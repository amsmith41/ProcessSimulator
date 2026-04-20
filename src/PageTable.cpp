#include "../include/PageTable.h"

// Initialization of all entries as unmapped
PageTable::PageTable(int numPages)
{
    entries.resize(numPages, {-1, false}); // Initialize all entries as unmapped
}

// Map virtual page to a physical frame
void PageTable::mapPage(int virtualPageNumber, int physicalFrameNumber)
{
    if (virtualPageNumber >= 0 && virtualPageNumber < entries.size())
    {
        entries[virtualPageNumber].valid = true;
        entries[virtualPageNumber].physicalFrameNumber = physicalFrameNumber;
    }
};

// Unmap a virtual page (-1)
// When valid bit is implemented, set to false
void PageTable::unmapPage(int virtualPageNumber)
{
    if (virtualPageNumber >= 0 && virtualPageNumber < entries.size())
    {
        entries[virtualPageNumber].valid = false;
        entries[virtualPageNumber].physicalFrameNumber = -1; // Frame reset to -1 to represent unmapped
    }
}

// Check if a virtual page is mapped
// Return false if unmapped
bool PageTable::isMapped(int virtualPageNumber) const
{
    if (virtualPageNumber >= 0 && virtualPageNumber < entries.size())
    {
        return entries[virtualPageNumber].valid; // Return valid bit since to indicate mapping
    }
    return false; // Not mapped
}

// Get the physical frame number, return -1 if unmapped
int PageTable::getPhysicalFrameNumber(int virtualPageNumber) const
{
    if (virtualPageNumber >= 0 && virtualPageNumber < entries.size() && entries[virtualPageNumber].valid)
    {
        return entries[virtualPageNumber].physicalFrameNumber; // Return physical frame number since it is mapped
    }
    return -1; // Not mapped
}

int PageTable::getNumPages() const
{
    return entries.size();
}