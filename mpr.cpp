#include <iostream>

#include "CImg.h"

using namespace std;
using namespace cimg_library;

template<typename T>
CImg<T> get_planeX(const CImg<T> origin, const unsigned int x, const unsigned int y, const unsigned int z) {
    CImg<> imgTmp(origin.height(), origin.depth(), 1);

    for(int y = 0; y < origin.height(); y++) {
        for(int z = 0; z < origin.depth(); z++) {
            imgTmp(y, z, 0) = origin(x, y, z);
        }
    }

    return imgTmp;
}

template<typename T>
CImg<T> get_planeY(const CImg<T> origin, const unsigned int x, const unsigned int y, const unsigned int z) {
    CImg<> imgTmp(origin.width(), origin.depth(), 1);

    for(int x = 0; x < origin.width(); x++) {
        for(int z = 0; z < origin.depth(); z++) {
            imgTmp(x, z, 0) = origin(x, y, z);
        }
    }

    return imgTmp;
}

template<typename T>
CImg<T> get_planeZ(const CImg<T> origin, const unsigned int x, const unsigned int y, const unsigned int z) {
    CImg<> imgTmp(origin.width(), origin.height(), 1);

    for(int x = 0; x < origin.width(); x++) {
        for(int y = 0; y < origin.height(); y++) {
            imgTmp(x, y, 0) = origin(x, y, z);
        }
    }

    return imgTmp;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <image.hdr>" << endl;
        exit(EXIT_FAILURE);
    }

    // ****************************
    // *** VARIABLE DECLARATION ***
    // ****************************

    CImg<> imgOrigin;
    CImg<> imgX, imgY, imgZ;
    CImg<> row0, row1, grid;
    CImgDisplay disp, dispTest;

    float voxelSize[3];

    unsigned int width;
    unsigned int height;
    unsigned int depth;

    unsigned int displayedColumn;
    unsigned int displayedRow;
    unsigned int displayedSlice;

    bool redraw;

    // *******************************
    // *** VARIABLE INITAILIZATION ***
    // *******************************

    imgOrigin.load_analyze(argv[1], voxelSize);

    width = imgOrigin.width();
    height = imgOrigin.height();
    depth = imgOrigin.depth();

    imgX.resize(height, depth, 1, 1);
    imgY.resize(width, depth, 1, 1);
    imgZ.resize(width, height, 1, 1);

    disp.resize(width, height);
    dispTest.resize(width, height);

    displayedColumn = width / 2;
    displayedRow = height / 2;
    displayedSlice = depth / 2;
    redraw = true;

    // ***************
    // *** PROGRAM ***
    // ***************

    while(!disp.is_closed() && !disp.is_keyESC()) {
        if(disp.wheel()) {
            if(displayedColumn != depth-1 && disp.wheel() > 0) {
                displayedColumn++;
                redraw = true;
            }
            if(displayedColumn != 0 && disp.wheel() < 0) {
                displayedColumn--;
                redraw = true;
            }

            if(displayedRow != depth-1 && disp.wheel() > 0) {
                displayedRow++;
                redraw = true;
            }
            if(displayedRow != 0 && disp.wheel() < 0) {
                displayedRow--;
                redraw = true;
            }

            if(displayedSlice != depth-1 && disp.wheel() > 0) {
                displayedSlice++;
                redraw = true;
            }
            if(displayedSlice != 0 && disp.wheel() < 0) {
                displayedSlice--;
                redraw = true;
            }

            //reinitialise l'event wheel (set to 0)
            disp.set_wheel();
        }

        // if(disp.button()&1) {
        //     cout << disp.mouse_x() << " " << disp.mouse_y() << endl;
        //
        // }

        if(redraw) {
            imgOrigin.display(dispTest);
            imgX = get_planeX(imgOrigin, displayedColumn, height, depth);
            // for(int x = 0; x < height; x++) {
            //     for(int y = 0; y < depth; y++) {
            //         imgX(x, y, 0) = imgOrigin(displayedColumn, x, y);
            //     }
            // }
            imgY = get_planeY(imgOrigin, width, displayedRow, depth);
            // for(int x = 0; x < width; x++) {
            //     for(int y = 0; y < depth; y++) {
            //         imgY(x, y, 0) = imgOrigin(x, displayedRow, y);
            //     }
            // }
            imgZ = get_planeZ(imgOrigin, width, height, displayedSlice);
            // for(int x = 0; x < width; x++) {
            //     for(int y = 0; y < height; y++) {
            //         imgZ(x, y, 0) = imgOrigin(x, y, displayedSlice);
            //     }
            // }
            grid = imgX.append(imgY, 'x');
            grid = grid.append(imgZ, 'y');
            grid.display(disp);
            redraw = false;
        }
    }

    // **************************
    // *** VARIABLE RELEASING ***
    // **************************

    exit(EXIT_SUCCESS);
}
