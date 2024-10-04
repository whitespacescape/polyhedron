#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VERTICES 12 * (1 << (2 * 10)) // Maximum number of vertices (for 10 subdivisions)

typedef struct {
    float x, y, z;
} Vector3;

Vector3 vertices[MAX_VERTICES];
int num_vertices = 0;
int num_faces = 0;

// Function to normalize a vector
void normalize(Vector3* v) {
    float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= length;
    v->y /= length;
    v->z /= length;
}

// Function to add a vertex to the array and return its index
int add_vertex(Vector3 v) {
    normalize(&v);
    vertices[num_vertices] = v;
    return num_vertices++;
}

// Function to get the middle point of two vertices
int get_middle_point(int p1, int p2) {
    Vector3 middle = {
        (vertices[p1].x + vertices[p2].x) / 2.0f,
        (vertices[p1].y + vertices[p2].y) / 2.0f,
        (vertices[p1].z + vertices[p2].z) / 2.0f
    };
    return add_vertex(middle);
}

// Function to create an icosphere
void create_icosphere(int subdivisions) {
    num_vertices = 0;
    num_faces = 0;

    // Create initial icosahedron
    float t = (1.0f + sqrt(5.0f)) / 2.0f;

    add_vertex((Vector3){-1, t, 0});
    add_vertex((Vector3){1, t, 0});
    add_vertex((Vector3){-1, -t, 0});
    add_vertex((Vector3){1, -t, 0});

    add_vertex((Vector3){0, -1, t});
    add_vertex((Vector3){0, 1, t});
    add_vertex((Vector3){0, -1, -t});
    add_vertex((Vector3){0, 1, -t});

    add_vertex((Vector3){t, 0, -1});
    add_vertex((Vector3){t, 0, 1});
    add_vertex((Vector3){-t, 0, -1});
    add_vertex((Vector3){-t, 0, 1});

    // Create initial faces
    int faces[20][3] = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    // Subdivide faces
    for (int i = 0; i < subdivisions; i++) {
        int num_faces_prev = (i == 0) ? 20 : num_faces;
        num_faces = 0;
        for (int j = 0; j < num_faces_prev; j++) {
            int a = get_middle_point(faces[j][0], faces[j][1]);
            int b = get_middle_point(faces[j][1], faces[j][2]);
            int c = get_middle_point(faces[j][2], faces[j][0]);
        
        faces[num_faces][0] = faces[j][0];
        faces[num_faces][1] = a;
        faces[num_faces][2] = c;
        num_faces++;

        faces[num_faces][0] = faces[j][1];
        faces[num_faces][1] = b;
        faces[num_faces][2] = a;
        num_faces++;

        faces[num_faces][0] = faces[j][2];
        faces[num_faces][1] = c;
        faces[num_faces][2] = b;
        num_faces++;

        faces[num_faces][0] = a;
        faces[num_faces][1] = b;
        faces[num_faces][2] = c;
        num_faces++;
        }
    }

    printf("Subdivision level: %d\n", subdivisions);
    printf("Number of vertices: %d\n", num_vertices);
    printf("Number of faces: %d\n", num_faces);
}

int main() {
    for (int i = 0; i <= 6; i++) {
        create_icosphere(i);
        printf("\n");
    }
    return 0;
}
