#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

void spiralPrinter(int n);
void recursiveSpiralFiller(std::vector<std::vector<int>>& vecs, int n);

int main() 
{
    // just random testing of the functionality
    int testCases[] = { 11, 14, 16, 19, 22, 25, 28, 34, 40, 49, 50, 51, 56, 57, 58, 63, 64, 65, 66, 67, 71, 72, 73, 74, 75 };
    
    for (int i = 1; i < 10; i++)
    {
        spiralPrinter(i);
    }
    
    for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++)
    {
        spiralPrinter(testCases[i]);
    }
    
    spiralPrinter(666);
    
    return 0;
}

void spiralPrinter(int n)
{
    int numVecs = std::ceil(sqrt(n));
    std::vector<std::vector<int>> spiral(numVecs);
    
    recursiveSpiralFiller(spiral, n);
    
    int width = (int)(log10(n) + 1);
    
    for (auto vec : spiral)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            std::cout << std::right << std::setw(width) << std::setfill(' ');
            
            // the filler assigns zeroes to empty places, so this is where we put spaces
            if (vec[i] == 0)
            { 
                std::cout << ' ';
            }
            else
            {
                std::cout << vec[i];
            }
            
            if (i < vec.size() - 1) [[likely]]
            {
                std::cout << ' ';
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void recursiveSpiralFiller(std::vector<std::vector<int>>& vecs, int n)
{
    if (n == 1)
    {
        vecs[0].push_back(n);
        return;
    }
    
    int sizeOfSide = (int)std::ceil(sqrt(n));
    int nextSquare = (int)pow(sizeOfSide - 1, 2);
    
    if (nextSquare & 1)
    {
        int num = nextSquare + 1;
        
        // fill left column
        for (int j = 0; j < vecs.size() - 1; j++)
        {
            vecs[vecs.size() - 1 - j].push_back(num > n ? 0 : num);
            num++;
        }
        
        // fill top row
        for (int j = 0; j < sizeOfSide; j++)
        {
            vecs[0].push_back(num > n ? 0 : num);
            num++;
        }
        
        // fill next spiral and assign it to current state
        std::vector<std::vector<int>> nextSpiral;
        nextSpiral.assign(vecs.begin() + 1, vecs.end());
        
        recursiveSpiralFiller(nextSpiral, nextSquare);
        
        vecs.erase(vecs.begin() + 1, vecs.end());
        vecs.insert(vecs.end(), nextSpiral.begin(), nextSpiral.end());
    }
    else
    {
        // fill next spiral and assign it to current state
        std::vector<std::vector<int>> nextSpiral;
        nextSpiral.assign(vecs.begin(), vecs.end() - 1);
        
        recursiveSpiralFiller(nextSpiral, nextSquare);
        
        vecs.erase(vecs.begin(), vecs.end() - 1);
        vecs.insert(vecs.begin(), nextSpiral.begin(), nextSpiral.end());
        
        int prevSquare = (int)pow(sizeOfSide, 2);
        int num = prevSquare;
        
        // fill bottom row
        for (int j = 0; j < sizeOfSide; j++)
        {
            vecs[vecs.size() - 1].push_back(num > n ? 0 : num);
            num--;
        }
        
        // fill right column
        for (int j = 0; j < vecs.size() - 1; j++)
        {
            vecs[vecs.size() - 2 - j].push_back(num > n ? 0 : num);
            num--;
        }
    }
}
