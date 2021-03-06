#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "kmeans.h"

#define _usage printf(\
"Usage:\n\
    kmeanspp generate_dataset <dataset_size>\n\
    kmeanspp clusterize <dataset> <number_of_clusters>\n\
    kmeanspp export\n");

int main(int argc, char** argv) {
    if(argc < 2)
        _usage

    else {
        if(strcmp(argv[1], "generate_dataset") == 0 && argc == 3) {
            srand(time(NULL));
            generate_dataset(atoi(argv[2]));
        }
        else if(strcmp(argv[1], "clusterize") == 0 && argc == 4) {
            int c_nb = atoi(argv[3]);

            srand(time(NULL));
            dataset* myDataset = dataset_from_csv(argv[2]);

            if(!myDataset) {
                printf("[!] File error\n");
                exit(EXIT_SUCCESS);
            }

            cluster* c = initialize_clusters(myDataset, c_nb);

            if(c) {
                cluster_update_loop(*myDataset, c, c_nb);

                printf("[ ] Clusters found, writing to out.csv...\n");
                export_csv(myDataset);

                free_cluster(c);
            }

            free_dataset(myDataset);
        }
        else if(strcmp(argv[1], "export") == 0)
            export_svg();
        else
            _usage
    }

    return 0;
}

void cluster_update_loop(dataset d, cluster* c, int c_nb) {
    int i = 0;
    do {
        printf("[ ] Updating clusters (iteration %d)...\n", i);
        i++;
    } while(update_clusters(d, c, c_nb));
}
