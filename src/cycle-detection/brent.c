/**
 * This is a Brent's algorithm implementation for cycle detection.
 * https://en.wikipedia.org/wiki/Cycle_detection#Brent's_algorithm
 *
 * @param array which contains cycles
 * @param length array length
 * @return length of the cycle
 */
int brent(int *array, int length) {
    // Search successive powers of two
    int power_of_two = 1;
    int period = 1; // Length of the cycle

    int tortoise_pos = 0;
    int hare_pos = 1;

    int tortoise = array[tortoise_pos];
    int hare = array[hare_pos];

    while ((tortoise != hare) && (tortoise_pos < length)) {
        // Time to start a new power of two?
        if (power_of_two == period) {
            // Move tortoise forward to hare pos
            tortoise_pos = hare_pos;
            tortoise = array[tortoise_pos];

            power_of_two *= 2;
            period = 0;
        }

        // Move hare 1 step forward the hare
        hare_pos++;
        hare = array[hare_pos];

        period += 1;
    }

    return tortoise == hare ? period : 0;
}