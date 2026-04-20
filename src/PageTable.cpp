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