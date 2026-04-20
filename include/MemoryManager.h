#pragma once

struct AddressTranslation
{
    int virtualAddress; // Virtual address to be translated
    int virtualPageNumber; // Page number from virtual address
    int offset; // Offset within the page in virtual address
    int physicalAddress; // Translated physical address
    int frameNumber; // Physical frame from the virtual page number
    bool valid; // True if translation is valid and the virtual page is mapped to a physical frame, false otherwise
};

// need class mem manager
// define number of frames and page size 
// declare prototypes for accessors to the above, a memory manager constructor using the above, and a function
// to perform address translation through a Process* process and the virtual addy