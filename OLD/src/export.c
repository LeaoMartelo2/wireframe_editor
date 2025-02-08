#include "export.h"

void export_map(int geometry_ammount, Geometry *map_geometry) {
    FILE *file = fopen("map_geometry.wireframe", "w");

    if (file == NULL) {
        perror("Error exporting to file");
        return;
    }

    /*  temp hard-coded ground until i find a better solution*/
    fprintf(file, "ground_geometry[0].size = (Vector3){2000, 1, 2000};\n"
                  "ground_geometry[0].mesh = GenMeshCube(2000, 1, 2000);\n"
                  "ground_geometry[0].model = LoadModelFromMesh(ground_geometry[0].mesh);\n"
                  "ground_geometry[0].pos = (Vector3){0, 0, 0};\n\n");

    fprintf(file, "int solid_count = 0;\n\n");

    for (int i = 0; i < geometry_ammount; i++) {
        fprintf(file, "solids[%d].size = (Vector3){%f, %f, %f};\n",
                i, map_geometry[i].size.x, map_geometry[i].size.y, map_geometry[i].size.z);

        fprintf(file, "solids[%d].mesh = GenMeshCube(%f, %f, %f);\n",
                i, map_geometry[i].size.x, map_geometry[i].size.y, map_geometry[i].size.z);

        fprintf(file, "solids[%d].model = LoadModelFromMesh(solids[%d].mesh);\n", i, i);

        fprintf(file, "solids[%d].pos = (Vector3){%f, %f, %f};\n",
                i, map_geometry[i].pos.x, map_geometry[i].pos.y, map_geometry[i].pos.z);

        fprintf(file, "solids[%d].see_through = %d;\n", i,
                map_geometry[i].see_through);
        fprintf(file, "solid_count++;\n\n");
    }

    fprintf(file, "*count = solid_count;\n");

    fclose(file);
}
