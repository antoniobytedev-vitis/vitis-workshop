#include <stdint.h>

#define MAX_ITEMS 32


void sort(float ratio[MAX_ITEMS],float values[MAX_ITEMS],float weights[MAX_ITEMS])
{
for (int i = 0; i < MAX_ITEMS - 1; i++) {
        int max_index = i;
        for (int j = i + 1; j < MAX_ITEMS; j++) {
            if (ratio[j] > ratio[max_index]) {
                max_index = j;
            }
        }
        // Swap values
        float temp_ratio = ratio[max_index];
        ratio[max_index] = ratio[i];
        ratio[i] = temp_ratio;

        float temp_val = values[max_index];
        values[max_index] = values[i];
        values[i] = temp_val;

        float temp_w = weights[max_index];
        weights[max_index] = weights[i];
        weights[i] = temp_w;
    }
}
float pick_items(float& total_value,float weights[MAX_ITEMS],
                          float values[MAX_ITEMS],float capacity)
{
// Greedy pick
    total_value = 0.0f;

    pick_items:
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (capacity == 0)
            break;

        if (weights[i] <= capacity) {
            total_value += values[i];
            capacity -= weights[i];
        } else {
            float fraction = capacity / weights[i];
            total_value += values[i] * fraction;
            capacity = 0;
        }
    }
}
// Top function
void fractional_knapsack(float weights[MAX_ITEMS],
                          float values[MAX_ITEMS],
                          
                          float capacity,float &total_value) {


    float ratio[MAX_ITEMS];

    // Compute value-to-weight ratio
    compute_ratio:
    for (int i = 0; i < MAX_ITEMS; i++) {
        ratio[i] = values[i] / weights[i];
    }

    // Sort items by ratio (descending) using selection sort
    
    sort(ratio,values,weights);
    pick_items(total_value,weights,values,capacity);

    

   
}