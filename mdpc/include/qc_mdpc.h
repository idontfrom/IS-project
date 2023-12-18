#pragma once

#include <algorithm>
#include <vector>
#include <random>
#include "Matrix.hpp"
#include "BinMatrix.h"

class qc_mdpc
{
private:
    using row_t = std::vector<bool>;
public:
    qc_mdpc(int n0, int p, int w, int seed = -1);
    int codeword_length() const { return n; }
    int word_length() const { return k; }
    int perm_size() const { return p; }
    int row_weight(int row) const { return w; }
    int col_weight(int col) const {
        return get_row_weight(col / perm_size() * perm_size(),
                              (col / perm_size() + 1) * perm_size());
    }
    int adjacent_var_node(int check, int id) const { return row_col[check][id]; };
    int adjacent_check_node(int var, int id) const { return col_row[var][id]; };
    BinMatrix parity_check_matrix() const;
    BinMatrix generator_matrix() const;
    BinMatrix encode(const BinMatrix& vec) const;
    BinMatrix decode(const BinMatrix& codeword) const;
    BinMatrix decode(const BinMatrix& parity_check, const BinMatrix& codeword) const;

private:
    void reset_row();
    int get_row_weight(int begin, int end) const;
    static row_t shift_row(const row_t& row, int shift = 1);
    row_t splice_row(int begin, int end) const;
    BinMatrix make_matrix(int nrows, int ncols, const row_t& row) const;
    void fill_reverse();
private:
    std::mt19937 gen;
    row_t row; // one row is enough to describe the whole MDPC matrix
    /*
     * n0 -- number of circular blocks H = (h_0 | h_1 | ... | h_{n0-1})
     * p -- permutation size of each circular block
     * n = n0 * p -- number of columns in the matrix (codeword's length)
     * r = p -- number of rows in the matrix
     * k = n - r -- non encoded word's length
     * w -- row weight
     */
    int n0, p, w, n, k, r;
    mtrx::Matrix_t<int> row_col; // positions of ones in rows
    mtrx::Matrix_t<int> col_row; // positions of ones in columns
};

