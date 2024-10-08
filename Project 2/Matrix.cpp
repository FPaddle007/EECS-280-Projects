// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height)
{

    mat->width = width;
    mat->height = height;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os)
{
    os << mat->width << " " << mat->height << std::endl;

    for (int i = 0; i < mat->width; i++) {
        for (int j = 0; j < mat->height; j++) {
            os << *Matrix_at(mat, i, j) << " ";
        }

        os << std::endl;
    }
}


// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat)
{

    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat)
{
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr)
{
    int width = Matrix_width(mat);
    int index = ptr - mat->data;
    return index / width;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr)
{
    int width = Matrix_width(mat);
    int index = ptr - mat->data;
    return index % width;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column)
{
    int element = (row * mat->width) + column;

    return &(mat->data[element]);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column)
{
    const int element = (row * mat->width) + column;

    const int* ptr = &(mat->data[element]);
    return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value)
{ 
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *Matrix_at(mat, i, j) = value;
        }
    }
  
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value)
{
    int height = Matrix_height(mat);
    int width = Matrix_width(mat);

    if (height < 3 && width < 3) {
        Matrix_fill(mat, value);
    }

    // fills top row of matrix
    for (int i = 0; i < width - 1; ++i)
    {
        mat->data[i] = value;
    }

    // fills border values of inner rows
    for (int i = 0; i < width * height; ++i)
    {
        if (i % width == 0 || i % width == width - 1)
        {
            mat->data[i] = value;
        }
    }

    // fills bottom row of matrix
    for (int i = (width * height) - width; i < height * width; ++i)
    {

        mat->data[i] = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat)
{
    int max = mat->data[0];

    for (int i = 1; i < Matrix_height(mat) * Matrix_width(mat); ++i)

    {
        if (mat->data[i] > max)
        {
            max = mat->data[i];
        }
    }

    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
    int column_start, int column_end)
{

    int min = *Matrix_at(mat, row, column_start);
    int min_column_element = column_start;

    for (int i = column_start; i < column_end; ++i)
    {
        if ((*Matrix_at(mat, row, i)) < min)
        {
            min = *Matrix_at(mat, row, i);
            min_column_element = i;
        }
    }

    return min_column_element;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
    int column_start, int column_end)
{
    

    int width = Matrix_width(mat);
    int min = mat->data[(row * width) + column_start];

    for (int i = (row * width) + column_start; i < ((row * width) + column_end); ++i)
    {
        if (mat->data[i] < min)
        {
            min = mat->data[i];
        }
    }

    return min;
}