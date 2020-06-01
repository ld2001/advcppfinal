//
// Created by LDin21 on 5/31/2020.
//

#include "bitmap.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>

using point = pair<int,int>;

map <pair<int,int>,int> makeMap (double percentile, int height, int width) {

    srand((unsigned) time(0));

    map <pair<int,int>,int> mapArray;

    if(percentile > 1 || percentile < 0) {
        cout << "Please return a valid percentile range" << endl;
        return mapArray;
    }

    const int percent = (int) (percentile * 100);

    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int random = rand();
            if(random % 100 < percent) {
                if(random % 2 == 0) {
                    mapArray[make_pair(i, j)] = 1;
                } else {
                    mapArray[make_pair(i, j)] = -1;
                }
            }
        }
    }

    return mapArray;

}

double returnMatch (Bitmap & b, map <pair<int,int>,int> signal, Bitmap & c, uint8_t gap) {
    int match = 0;
    int total = 0;
    char data2Mask[3] = {'r', 'g', 'b'};

    for ( int i = 0; i < b.imageHeight * b.imageWidth; i++ ) {
        uint8_t bColor = b.getColorVal(b.data2[i],data2Mask[0]);
        uint8_t cColor = c.getColorVal(c.data2[i],data2Mask[0]);

        if((bColor < cColor && cColor - bColor <= gap) || (bColor >= cColor && bColor - cColor <= gap)) {
            match += 1;
            total += 1;
        } else {
            total += 1;
        }
    }

    double returnVal = (double) match/total;

    return returnVal;
}

map <pair<int,int>,int> sequenceMap (double percentile, int height, int width, int cycles) {

    map <pair <int,int>,int> returnMap;

    vector<vector<int> > countVec (height);
    vector<vector<int> > totalVec (height);

    for (int i = 0; i < height; i++) {
        // declare  the i-th row to size of column
        countVec[i] = vector<int>(width,0);
        totalVec[i] = vector<int>(width,0);
    }
    int counter = 0;

    for(int k = 0; k < cycles; k++) {
        map<pair<int,int>,int> iterMap = makeMap(percentile,height,width);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pair<int, int> x = make_pair(i, j);
                if(iterMap.find(x) == iterMap.end()) {
                    continue;
                } else {
                    totalVec[i][j] += iterMap[x];
                    countVec[i][j] += 1;
                }
            }
        }
        counter += 1;
        cout << counter << endl;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(countVec[i][j] == 0) {
                continue;
            } else {
                pair<int, int> x = make_pair(i, j);
                returnMap[x] = totalVec[i][j] / countVec[i][j];
            }
        }
    }

    return returnMap;
}