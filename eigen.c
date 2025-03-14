#include <stdio.h>
#include <math.h>

#define No_DISEASES 3
#define No_SYMPTOMS 4
// Disease names
const char *disease_names[No_DISEASES] = {
    "Flu", "Common Cold", "Allergy"
};
// Symptom names
const char *symptom_names[No_SYMPTOMS] = {
    "Fever", "Cough", "Sneezing", "Body Ache"
};
// Original symptom vectors for diseases (1 = present, 0 = absent)
double disease_vectors[No_DISEASES][No_SYMPTOMS] = {
    {1, 1, 0, 1},  // Flu
    {0, 1, 1, 0},  // Common Cold
    {0, 0, 1, 0}   // Allergy
};
// Function to compute Euclidean distance
double calculate_distance(double user_symptoms[], double disease_vector[]) {
    double sum = 0.0;
    for (int i = 0; i < No_SYMPTOMS; i++) {
        sum += pow(user_symptoms[i] - disease_vector[i], 2);
    }
    return sqrt(sum);
}
// Function to compute dot product of two vectors
double dot_product(double vec1[], double vec2[]) {
    double sum = 0.0;
    for (int i = 0; i < No_SYMPTOMS; i++) {
        sum += vec1[i] * vec2[i];
    }
    return sum;
}
// Function to compute the norm of a vector
double vector_norm(double vec[]) {
    return sqrt(dot_product(vec, vec));
}
// Function to subtract projection of vec2 onto vec1
void subtract_projection(double vec1[], double vec2[], double result[]) {
    double dot = dot_product(vec1, vec2);
    double norm_sq = dot_product(vec1, vec1);
    
    for (int i = 0; i < No_SYMPTOMS; i++) {
        result[i] = vec2[i] - (dot / norm_sq) * vec1[i];
    }
}
// Gram-Schmidt Orthonormalization
void gram_schmidt(double vectors[No_DISEASES][No_SYMPTOMS], double ortho_vectors[No_DISEASES][No_SYMPTOMS]) {
    double temp_vectors[No_DISEASES][No_SYMPTOMS];
    // Copy the first vector as it is
    for (int i = 0; i < No_SYMPTOMS; i++) {
        temp_vectors[0][i] = vectors[0][i];
    }

    // Apply Gram-Schmidt process
    for (int i = 1; i < No_DISEASES; i++) {
        double temp[No_SYMPTOMS];
        for (int j = 0; j < No_SYMPTOMS; j++) {
            temp[j] = vectors[i][j];
        }

        for (int j = 0; j < i; j++) {
            subtract_projection(temp_vectors[j], vectors[i], temp);
        }

        for (int j = 0; j < No_SYMPTOMS; j++) {
            temp_vectors[i][j] = temp[j];
        }
    }

    // Normalize the vectors:--
    for (int i = 0; i < No_DISEASES; i++) {
        double norm = vector_norm(temp_vectors[i]);
        for (int j = 0; j < No_SYMPTOMS; j++) {
            ortho_vectors[i][j] = temp_vectors[i][j] / norm;
        }}}
int main() {
    double user_symptoms[No_SYMPTOMS];
    // Get user symptoms:--
    printf("Enter your symptoms (1 for Yes, 0 for No):\n");
    for (int i = 0; i < No_SYMPTOMS; i++) {
        printf("Do you have %s? ", symptom_names[i]);
        scanf("%lf", &user_symptoms[i]);
    }
    // Find the closest matching disease:--
    int best_match = 0;
    double min_distance = calculate_distance(user_symptoms, disease_vectors[0]);
    for (int i = 1; i < No_DISEASES; i++) {
        double distance = calculate_distance(user_symptoms, disease_vectors[i]);
        if (distance < min_distance) {
            min_distance = distance;
            best_match = i;
        }}
    // Display the predicted disease:--
    printf("\nBased on your symptoms, the most likely diagnosis is: **%s**\n", disease_names[best_match]);
    // Perform Gram-Schmidt Orthonormalization
    double ortho_vectors[No_DISEASES][No_SYMPTOMS];
    gram_schmidt(disease_vectors, ortho_vectors);
    // Print the orthonormal vectors:--
    printf("\nOrthonormalized Disease Vectors:\n");
    for (int i = 0; i < No_DISEASES; i++) {
        printf("Vector %d: [", i + 1);
        for (int j = 0; j < No_SYMPTOMS; j++) {
            printf("%.3f ", ortho_vectors[i][j]);    }
        printf("]\n");    }
    return 0;}