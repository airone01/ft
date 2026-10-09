#ifndef SRC_MATH_MATH_H
#define SRC_MATH_MATH_H

/**
 * @brief Calculates a standard internet checksum according to RFC 1071.
 */
unsigned short calculate_checksum(unsigned short *addr, int len);

#endif /* SRC_MATH_MATH_H */
