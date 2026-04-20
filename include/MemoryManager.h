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

