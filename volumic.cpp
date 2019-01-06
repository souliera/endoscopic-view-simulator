#include <iostream>

#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char const *argv[]) {
    if(argc != 5) {
        cout << "Usage: " << argv[0] << " img camX camY camZ" << endl;
        return 1;
    }

    // ###################
    // ### DECLARATION ###
    // ###################

    CImg<float> scanner, visu;
    CImgDisplay disp;

    float voxelSize[3];

    int width, height, depth, size;
    int camX, camY, camZ, camSize;

    int count;

    int a, b;
    float m;

    // ######################
    // ### INITIALISATION ###
    // ######################

    scanner.load_analyze((char*)argv[1], voxelSize);
    width = scanner.width();
    height = scanner.height();
    depth = scanner.depth();
    cout << width << " " << height << " " << depth << endl;

    bool redraw = true;


    camX = atoi(argv[2]);
    camY = atoi(argv[3]);
    camZ = atoi(argv[4]);

    camSize = 100;

    visu.resize(camSize, camSize, 1, 3);
    disp.resize(visu.width(), visu.height(), "");

    count = 0;

    a = b = 0;
    m = 0.0f;

    // #################
    // ### PROGRAMME ###
    // #################

    cout << "Begin" << endl;

    for(int i = camX - 50; i < camX + 50; i++) {
        for(int j = camY - 50; j < camY + 50; j++) {
            count = 0;
            for(int k = camZ; k < depth; k++) {
                m = (k - camZ) / 10.0f;
                a = m * (i - camX) + camX;
                b = m * (j - camY) + camY;

                if(a < 0 || b < 0 || a > width || b > height) {
                    break;
                }

                if(scanner(a, b, k) == 0) {
                    visu(i-(camX - 50), j-(camY - 50), 0, 0) += 255.0f;
                    visu(i-(camX - 50), j-(camY - 50), 0, 1) += 0.0f;
                    visu(i-(camX - 50), j-(camY - 50), 0, 2) += 0.0f;
                    count++;
                }
                if(scanner(a, b, k) == 1) {
                    visu(i-(camX - 50), j-(camY - 50), 0, 0) += 255.0f;
                    visu(i-(camX - 50), j-(camY - 50), 0, 1) += 255.0f;
                    visu(i-(camX - 50), j-(camY - 50), 0, 2) += 255.0f;
                    count++;
                    break;
                }
                if(count == 10) {
                    break;
                }
            }
            if(count != 0) {
                visu(i-(camX - 50), j-(camY - 50), 0, 0) /= count;
                visu(i-(camX - 50), j-(camY - 50), 0, 1) /= count;
                visu(i-(camX - 50), j-(camY - 50), 0, 2) /= count;
            } else {
                visu(i-(camX - 50), j-(camY - 50), 0, 0) = 0.0f;
                visu(i-(camX - 50), j-(camY - 50), 0, 1) = 0.0f;
                visu(i-(camX - 50), j-(camY - 50), 0, 2) = 0.0f;
            }
        }
    }

    while(!disp.is_closed()) {
        // if(redraw) {
            visu.display(disp);
            // redraw = false;
        // }
    }

    visu.save_png("rsc/test.png");

    cout << "End" << endl;

    return 0;
}

// int main(int argc, char *argv[]) {
//     if(argc != 5) {
//         cout << "Usage: " << argv[0] << " img centerX centerZ step" << endl;
//         return 1;
//     }
//     //*
//
//     // ###################
//     // ### DECLARATION ###
//     // ###################
//
//     CImg<> scanner, visu(600, 600, 1, 3, 0);
//     CImgDisplay disp(visu, "[#19] - Double 3D Torus");
//     float voxelSize[3];
//     unsigned int width, height, depth;
//     unsigned int nbVoxel;
//
//     int bornX;
//     int bornZ;
//     int step;
//
//     CImg<float> vertices, verts;
//     CImgList<int> primitives, prims;
//     CImgList<unsigned char> colors, colsB, colsM;
//     CImg<float> opacities, opacsB, opacsM;
//
//     float x, y, z, t;
//     bool redraw;
//
//     // ######################
//     // ### INITIALISATION ###
//     // ######################
//
//     //*
//     scanner.load_analyze((char*)argv[1], voxelSize);
//     width = scanner.width();
//     height = scanner.height();
//     depth = scanner.depth();
//     cout << width << " " << height << " " << depth << endl;
//
//     bornX = atoi(argv[2]);
//     bornZ = atoi(argv[3]);
//     step = atoi(argv[4]);
//
//     if(bornX < 0 || bornX > width || bornZ < 0 || bornZ > depth) {
//         cout << "Born out of range" << endl;
//         return 2;
//     }
//
//     if(bornX - step < 0 || bornX + step > width || bornZ - step < 0 || bornZ + step > depth) {
//         cout << "Step out of range" << endl;
//         return 3;
//     }
//
//     cout << "Begin" << endl;
//     nbVoxel = 0;
//     cout << "Count voxel..." << endl;
//     for(unsigned int i = bornX-step; i < bornX+step; i++) {
//         for(unsigned int j = 0; j < height; j++) {
//             for(unsigned int k = bornZ-step; k < bornZ+step; k++) {
//                 if(scanner(i, j, k) == 1 || scanner(i, j, k) == 0) {
//                     nbVoxel++;
//                 }
//             }
//         }
//     }
//
//     cout << "Create array..." << endl;
//     vertices = CImg<float>(nbVoxel*8, 3, 1);
//
//     primitives = CImgList<unsigned char>(nbVoxel*6, 1, 4, 1);
//
//     colsB = CImgList<unsigned char>(6, CImg<>::vector(255, 255, 255));
//     colsM = CImgList<unsigned char>(6, CImg<>::vector(255, 0, 0));
//     colors = CImgList<unsigned char>(nbVoxel*6, 1, 3, 1);
//
//     opacsB = CImg<float>(6, 1, 1, 1, 1.0f);
//     opacsM = CImg<float>(6, 1, 1, 1, 0.3f);
//     opacities = CImg<float>(nbVoxel*6, 1, 1, 1, 0.0f);
//
//     z = -500.0f;
//     redraw = true;
//
//     // #################
//     // ### PROGRAMME ###
//     // #################
//
//     //*
//     // i 40
//     // j 131
//     // k 110
//
//     cout << "Create 3D model..." << endl;
//     int index6 = 0;
//     int index8 = 0;
//     for(unsigned int i = bornX-step; i < bornX+step; i++) {
//         for(unsigned int j = 0; j < height; j++) {
//             for(unsigned int k = bornZ-step; k < bornZ+step; k++) {
//                 switch((int)scanner(i, j, k)) {
//                     case 0: // mucous
//                         // new voxel
//                         verts = CImg<float>::box3d(prims, 1, 1, 1);
//                         // update position
//                         for(unsigned int l = 0; l < 8; l++) {
//                                 vertices(index8+l, 0, 0) = verts(l, 0, 0) + i;
//                                 vertices(index8+l, 1, 0) = verts(l, 1, 0) + j;
//                                 vertices(index8+l, 2, 0) = verts(l, 2, 0) + k;
//                         }
//                         // add to scene
//                         for(int l = 0; l < 6; l++) {
//                             primitives[index6+l] = prims[l]+index8;
//                             colors[index6+l] = colsM[l];
//                             opacities(index6+l, 0, 0) = opacsM(l, 0, 0);
//                         }
//                         index6 += 6;
//                         index8 += 8;
//                         // vertices.append_object3d(primitives, verts, prims);
//                         // colors = (+colors, colsM);
//                         // opacities = (opacities, opacsM)>'x';
//                         break;
//
//                     case 1: // bones
//                         // new voxel
//                         verts = CImg<float>::box3d(prims, 1, 1, 1);
//                         // update position
//                         for(unsigned int l = 0; l < 8; l++) {
//                                 vertices(index8+l, 0, 0) = verts(l, 0, 0) + i;
//                                 vertices(index8+l, 1, 0) = verts(l, 1, 0) + j;
//                                 vertices(index8+l, 2, 0) = verts(l, 2, 0) + k;
//                         }
//                         // add to scene
//                         for(int l = 0; l < 6; l++) {
//                             primitives[index6+l] = prims[l]+index8;
//                             colors[index6+l] = colsB[l];
//                             opacities(index6+l, 0, 0) = opacsB(l, 0, 0);
//                         }
//                         index6 += 6;
//                         index8 += 8;
//                         // vertices.append_object3d(primitives, verts, prims);
//                         // colors = (+colors, colsB);
//                         // opacities = (opacities, opacsB)>'x';
//                         break;
//                 }
//             }
//         }
//     }
//
//     cout << "Registration 3D model..." << endl;
//     float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
//     for(int i = 0; i <  vertices.width(); i++) {
//         sumX += vertices(i, 0, 0);
//         sumY += vertices(i, 1, 0);
//         sumZ += vertices(i, 2, 0);
//     }
//     for(int i = 0; i <  vertices.width(); i++) {
//         vertices(i, 0, 0) -= sumX / vertices.width();
//         vertices(i, 1, 0) -= sumY / vertices.width();
//         vertices(i, 2, 0) -= sumZ / vertices.width();
//     }
//
//     CImg<float> rvertices = CImg<float>::rotation_matrix(1, 0, 0, 90) * vertices;
//
//     while(!disp.is_closed() && !disp.is_keyESC()) {
//         if(disp.is_keyPADSUB()) {
//             z += 10;
//             redraw = true;
//         }
//         if(disp.is_keyPADADD()) {
//             z -= 10;
//             redraw = true;
//         }
//
//         if(redraw) {
//             visu.fill(0);
//             visu.draw_object3d(disp.width()/2.0f, disp.height()/2.0f, z, rvertices, primitives, colors, opacities, 3, false, 700).display(disp);
//             redraw = false;
//         }
//     }
//     //*/
//
//     cout << "End" << endl;
//
//     return 0;
// }
