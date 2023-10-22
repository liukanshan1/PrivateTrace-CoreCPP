//
// Created by 12695 on 2023/3/18.
//

#ifndef PriCT_UTILS_HPP
#define PriCT_UTILS_HPP

#include <cmath>
#include "../Global.hpp"
#include "gmp.h"
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
using namespace std;

int FIXED_POINT = 6;

void encryptDouble(double d, mpz_t enc, int scale = FIXED_POINT) {
    mpz_t tmp;
    mpz_init(tmp);
    mpz_set_si(tmp, (long) (d * pow(10, scale)));
    Global::pai.encrypt(enc, tmp);
}

vector<string> ls(string path) {
    if (path[path.length() - 1] == '/') {
        struct dirent *ptr;
        DIR *dir;
        dir=opendir(path.c_str());
        vector<string> files;
        while((ptr=readdir(dir))!=NULL)
        {
            //跳过'.'和'..'两个目录
            if(ptr->d_name[0] == '.')
                continue;
            files.push_back(path + ptr->d_name);
        }
        closedir(dir);
        return files;
    }
    cout << "File!! " << endl;
    vector<string> files;
    files.push_back(path);
    return files;
}

#endif //PriCT_UTILS_HPP
