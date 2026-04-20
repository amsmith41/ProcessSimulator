#include "../include/PageTable.h"

PageTable::PageTable(int numPages)
{
    entries.resize(numPages, {-1, false}); // Initialize all entries as unmapped
}

