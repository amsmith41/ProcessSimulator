#include "../include/MemoryManager.h"
#include "../include/Process.h"
#include "../include/PageTable.h"

// Constructor to initialize page size and number of frames
MemoryManager::MemoryManager(int pageSize, int numFrames)
    : pageSize(pageSize), numFrames(numFrames)
{
}

// Translate virtual address to physical address using the page table
AddressTranslation MemoryManager::translateAddress(Process* process, int virtualAddress) const
{
    AddressTranslation translation;
    translation.valid = false; // Default
    translation.virtualAddress = virtualAddress; // Default since that's passsed through as a parameter
    translation.virtualPageNumber = -1; // Default
    translation.offset = -1; // Default
    translation.frameNumber = -1; // Default
    translation.physicalAddress = -1; // Default

    // Guard against invalid attempts to translate an address
    if (process == nullptr || virtualAddress < 0 || pageSize <= 0)
    {
        return translation; // Invalid translation attempt, return default invalid translation
    }
    
    // Calculate virtual page number and offset
    int virtualPageNumber = virtualAddress / pageSize; // Typically, this is calculated as bit shift,  performance should increase if this was a bit operation
    int offset = virtualAddress % pageSize;

    const PageTable& pageTable = process->getPageTable();

    translation.virtualPageNumber = virtualPageNumber;
    translation.offset = offset;

    if (!pageTable.isMapped(virtualPageNumber))
    {
        return translation; // Virtual page is not mapped, return invalid translation
        // There may be redundancy in validity checks, but better safe than sorry
    }

    int frameNumber = pageTable.getPhysicalFrameNumber(virtualPageNumber);

    if (frameNumber < 0 || frameNumber >= numFrames)
    {
        return translation; // Invalid frame number
    }

    int physicalAddress = frameNumber * pageSize + offset;

    translation.valid = true;
    translation.frameNumber = frameNumber;
    translation.physicalAddress = physicalAddress;

    return translation; // Return translation, it should be valid if the if checks passed
}

int MemoryManager::getPageSize() const
{
    return pageSize;
}

int MemoryManager::getNumFrames() const
{
    return numFrames;
}