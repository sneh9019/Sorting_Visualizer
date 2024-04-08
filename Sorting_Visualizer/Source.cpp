#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include<string>

const int SCREEN_WIDTH = 910;
const int SCREEN_HEIGHT = 750;
const int BAR_WIDTH = 4;
const int MAX_BAR_HEIGHT = 600;
const int NUM_BARS = SCREEN_WIDTH / BAR_WIDTH;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

void initializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void drawBars(const std::vector<int>& bars) {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    for (int i = 0; i < NUM_BARS; ++i) {
        SDL_Rect barRect = { i * BAR_WIDTH, SCREEN_HEIGHT - bars[i], BAR_WIDTH, bars[i] };
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderFillRect(gRenderer, &barRect);
    }

    SDL_RenderPresent(gRenderer);
}

void bubbleSort(std::vector<int>& bars) {
    for (int i = 0; i < NUM_BARS - 1; ++i) {
        for (int j = 0; j < NUM_BARS - i - 1; ++j) {
            if (bars[j] > bars[j + 1]) {
                std::swap(bars[j], bars[j + 1]);
                drawBars(bars);
                SDL_Delay(1);
            }
        }
    }
}

void selectionSort(std::vector<int>& bars) {
    int n = bars.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (bars[j] < bars[min_index]) {
                min_index = j;
            }
        }
        std::swap(bars[i], bars[min_index]);
        drawBars(bars);
        SDL_Delay(1);
    }
}
void insertionSort(std::vector<int>& bars) {
    int n = bars.size();
    for (int i = 1; i < n; ++i) {
        int key = bars[i];
        int j = i - 1;
        while (j >= 0 && bars[j] > key) {
            bars[j + 1] = bars[j];
            j = j - 1;
        }
        bars[j + 1] = key;
        drawBars(bars);
        SDL_Delay(5);
    }
}

void merge(std::vector<int>& bars, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = bars[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = bars[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            bars[k] = L[i];
            ++i;
        }
        else {
            bars[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        bars[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        bars[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSortHelper(std::vector<int>& bars, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSortHelper(bars, l, m);
    mergeSortHelper(bars, m + 1, r);
    merge(bars, l, m, r);
    drawBars(bars);
    SDL_Delay(5);
}

void mergeSort(std::vector<int>& bars) {
    mergeSortHelper(bars, 0, bars.size() - 1);
}

int partition(std::vector<int>& bars, int low, int high) {
    int pivot = bars[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (bars[j] < pivot) {
            ++i;
            std::swap(bars[i], bars[j]);
            drawBars(bars);
            SDL_Delay(5);
        }
    }
    std::swap(bars[i + 1], bars[high]);
    drawBars(bars);
    SDL_Delay(5);
    return i + 1;
}

void quickSortHelper(std::vector<int>& bars, int low, int high) {
    if (low < high) {
        int pi = partition(bars, low, high);
        quickSortHelper(bars, low, pi - 1);
        quickSortHelper(bars, pi + 1, high);
    }
}

void quickSort(std::vector<int>& bars) {
    quickSortHelper(bars, 0, bars.size() - 1);
}

void heapify(std::vector<int>& bars, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && bars[left] > bars[largest])
        largest = left;

    if (right < n && bars[right] > bars[largest])
        largest = right;

    if (largest != i) {
        std::swap(bars[i], bars[largest]);
        drawBars(bars);
        SDL_Delay(5);
        heapify(bars, n, largest);
    }
}

void heapSort(std::vector<int>& bars) {
    int n = bars.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(bars, n, i);

    for (int i = n - 1; i > 0; --i) {
        std::swap(bars[0], bars[i]);
        drawBars(bars);
        SDL_Delay(5);
        heapify(bars, i, 0);
    }
}

bool controls()
{
    std::cout  
        << "Available Controls inside Sorting Visualizer:-\n"
        << "    Use 1 to start Bubble Sort Algorithm.\n"
        << "    Use 2 to start Selection Sort Algorithm.\n"
        << "    Use 3 to start Insertion Sort Algorithm.\n"
        << "    Use 4 to start Merge Sort Algorithm.\n"
        << "    Use 5 to start Quick Sort Algorithm.\n"
        << "    Use 6 to start Heap Sort Algorithm.\n"
        << "    Use q to exit out of Sorting Visualizer\n\n";

    std::string s;
    getline(std::cin, s);
    if (s == "-1")
    {
        return false;
    }
    //else if(s=="\n")
    //{
    //    return true;
    //}
    return true;
}

void execute()
{

    std::vector<int> bars(NUM_BARS);
    srand(time(nullptr));
    for (int i = 0; i < NUM_BARS; ++i) {
        bars[i] = rand() % MAX_BAR_HEIGHT;
    }

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        initializeSDL();
        std::cout << "Bubble sort started \n";
        bubbleSort(bars);
        std::cout << "Bubble sort ended \n";
        break;
    case 2:
        initializeSDL();
        std::cout << "selection sort started \n";
        selectionSort(bars);
        std::cout << "Selection sort ended \n";
        break;
    case 3:
        initializeSDL();
        std::cout << "Insertion sort started \n";
        insertionSort(bars);
        std::cout << "Insertion sort ended \n";
        break;
    case 4:
        initializeSDL();
        std::cout << "Merge sort started \n";
        mergeSort(bars);
        std::cout << "Merge sort ended \n";
        break;
    case 5:
        initializeSDL();
        std::cout << "Quick sort started \n";
        quickSort(bars);
        std::cout << "Quick sort ended \n";
        break;
    case 6:
        initializeSDL();
        std::cout << "Heap sort started \n";
        heapSort(bars);
        std::cout << "Heap sort ended \n";
        break;

    default:
        std::cout << "Invalid choice\n";
        break;
    }
    SDL_Delay(1000);
    closeSDL();
}
     




int main(int argc, char* args[]) {
   
    SDL_Delay(1000);
    while (1)
    {
        std::cout << '\n';
        if (controls())
            execute();
        else
        {
            std::cout << "\nEXITING PROGRAM.\n";
            break;
        }
    }
    return 0;
}
 
    