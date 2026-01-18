class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // row prefix sum
        vector<vector<long long>> rowPref(m, vector<long long>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowPref[i][j + 1] = rowPref[i][j] + grid[i][j];
            }
        }

        // col prefix sum
        vector<vector<long long>> colPref(m + 1, vector<long long>(n, 0));
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                colPref[i + 1][j] = colPref[i][j] + grid[i][j];
            }
        }

        auto getRowSum = [&](int r, int c, int k) {
            return rowPref[r][c + k] - rowPref[r][c];
        };

        auto getColSum = [&](int r, int c, int k) {
            return colPref[r + k][c] - colPref[r][c];
        };

        int maxK = min(m, n);

        for (int k = maxK; k >= 2; k--) {
            for (int r = 0; r + k <= m; r++) {
                for (int c = 0; c + k <= n; c++) {

                    long long target = getRowSum(r, c, k);

                    // check all rows
                    bool ok = true;
                    for (int i = 0; i < k; i++) {
                        if (getRowSum(r + i, c, k) != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) continue;

                    // check all cols
                    for (int j = 0; j < k; j++) {
                        if (getColSum(r, c + j, k) != target) {
                            ok = false;
                            break;
                        }
                    }
                    if (!ok) continue;

                    // check diagonals
                    long long d1 = 0, d2 = 0;
                    for (int i = 0; i < k; i++) {
                        d1 += grid[r + i][c + i];
                        d2 += grid[r + i][c + (k - 1 - i)];
                    }
                    if (d1 != target || d2 != target) continue;

                    return k; // biggest found
                }
            }
        }

        return 1; // every 1x1 is magic
    }
};
