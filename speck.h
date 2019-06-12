// Ray Beaulieu, Stefan Treatman-Clark, Douglas Shors, Bryan Weeks, Jason
// Smith and Louis Wingers. "The SIMON and SPECK lightweight block ciphers," 
// In proceedings of the Design Automation Conference (DAC), 
// 2015 52nd ACM/EDAC/IEEE, pp. 1-6. IEEE, 2015.

#define LCS(X, K)                                                            \
  (X << K) | (X >> (sizeof(uint64_t) * 8 - K)) // left circular shift
#define RCS(X, K)                                                            \
  (X >> K) | (X << (sizeof(uint64_t) * 8 - K)) // right circular shift

// Core SPECK operation
#define R(x, y, k) (x = RCS(x, 8), x += y, x ^= k, y = LCS(y, 3), y ^= x)

void Speck128ExpandKeyAndEncrypt(uint64_t pt[], uint64_t ct[], uint64_t K[]) {
  uint64_t B = K[1], A = K[0];
  ct[0] = pt[0];
  ct[1] = pt[1];
  for (size_t i = 0; i < 32; i += 1) {
    R(ct[1], ct[0], A);
    R(B, A, i);
  }
  return;
}
