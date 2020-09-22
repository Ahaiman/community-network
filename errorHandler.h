
/* errorHandler.h - Header File
 *
 * A header file for handling errors during the program, according to different types.
 *
 * returnErrorByType - Throws an error
 */

#ifndef ERRORHANDLER_H_
#define ERRORHANDLER_H_

/**
 * The function prints an error message according to the type of the error,
 * then exists the program without releasing memory.
 *
 * @param integer - a value representing the error type.
 */

void	 returnErrorByType(int);

#endif
