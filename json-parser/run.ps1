/* SPDX-License-Identifier: Apache-2.0 */

# Compile the C files
gcc -o json_parser json_parser.c headers/utils.c

# Execute the compiled program
./json_parser