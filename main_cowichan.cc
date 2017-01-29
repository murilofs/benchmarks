#include <fstream>
#include <iostream>
#include <db.h>
#include "cowichan.h"
#include "Timer.h"
#include "database.h"

int main() {
    DB *dbp;
    u_int32_t flags;
    int ret;

    ret = db_create(&dbp, NULL, 0);
    if(ret != 0){

    }

    flags = DB_CREATE;

    ret = dbp->open(dbp, NULL, "report.db", NULL, DB_BTREE, flags, 0);

    if(ret != 0){

    }

    auto matrix = cowichan::mandel(600, 900, -2, -1, 3, 2);

    struct execution_t execution;
    for(int i = 0; i < EXECUTIONS; i++) {
        Timer timer = Timer();
        auto matrix_rand = cowichan::randmat(10, 10, 46);
        auto matrix = cowichan::mandel(600, 900, -2, -1, 3, 2);
        execution.time[i] = timer.elapsed();
        execution.timestamp[i] = time(NULL);
        timer.reset();
    }

    for(int i = 0; i < EXECUTIONS; i++) {
        std::cout << "timestamp:" << asctime(localtime(&execution.timestamp[i])) << "elapsed:" << execution.time[i] << std::endl;
    }

//    std::ofstream img;
//    img.open("mandel.ppm");
//    img << "P3" << std::endl;
//    img << 900 << " " << 600 << std::endl;
//    img << 150 << std::endl;
//
//    for (int i = 0; i < matrix.size(); i++) {
//        for (int j = 0; j < matrix[i].size(); j++) {
//            img << matrix[i][j] << " " << matrix[i][j] << " " << matrix[i][j] << " ";
//        }
//        img << std::endl;
//    }
//
//    img.close();

    if(dbp != NULL) {
        dbp->close(dbp, 0);
    }

}
