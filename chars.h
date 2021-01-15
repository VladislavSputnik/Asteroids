#pragma once

#define A_LEN 10
#define B_LEN 11
#define C_LEN 6
#define D_LEN 6
#define E_LEN 9
#define F_LEN 7
#define G_LEN 12
#define H_LEN 8
#define I_LEN 8
#define J_LEN 6
#define K_LEN 7
#define L_LEN 4
#define M_LEN 8
#define N_LEN 6
#define O_LEN 4
#define P_LEN 5
#define Q_LEN 9
#define R_LEN 7
#define S_LEN 10
#define T_LEN 5
#define U_LEN 6
#define V_LEN 4
#define W_LEN 8
#define X_LEN 6
#define Y_LEN 6
#define Z_LEN 6
#define EMPTY 2

#define ZERO_LEN 4
#define ONE_LEN 2
#define TWO_LEN 10
#define THREE_LEN 9
#define FOUR_LEN 7
#define FIVE_LEN 10
#define SIX_LEN 5
#define SEVEN_LEN 4
#define EIGHT_LEN 7
#define NINE_LEN 5

namespace Tmpl8
{
//---------------------------------------------------------------
// Char shape data
//---------------------------------------------------------------

	int charPolygonLength[37] = { A_LEN, B_LEN, C_LEN, D_LEN, E_LEN, F_LEN, G_LEN, H_LEN, I_LEN,
								J_LEN, K_LEN, L_LEN, M_LEN, N_LEN, O_LEN, P_LEN, Q_LEN, R_LEN,
								S_LEN, T_LEN, U_LEN, V_LEN, W_LEN, X_LEN, Y_LEN, Z_LEN,

								ZERO_LEN, ONE_LEN, TWO_LEN, THREE_LEN, FOUR_LEN, FIVE_LEN, SIX_LEN, SEVEN_LEN, EIGHT_LEN, NINE_LEN,
								EMPTY };

	vec2 char_EMPTY[EMPTY]{
		{-1.f,-1.f},
		{1.f, -1.f}
	};

#pragma region Chars
	vec2 char_A[A_LEN] = {
		{-1.f,-1.f},
		{-1.f,1.f},
		{0.f,2.f},
		{1.f,1.f},
		{1.f,0.f},
		{-1.f,0.f},
		{1.f,0.f},
		{1.f,-1.f},
		{1.f,0.f},
		{-1.f,0.f}
	};

	vec2 char_B[B_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{0.6f,2.f},
		{1.f,1.6f},
		{1.f,0.9f},
		{0.6f,0.5f},
		{-1.f,0.5f},
		{0.6f,0.5f},
		{1.f,0.1f},
		{1.f,-0.6f},
		{0.6f,-1.f}
	};

	vec2 char_C[C_LEN] = {
		{1.f,-1.f},
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{-1.f,-1.f}
	};

	vec2 char_D[D_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{0.6f,2.f},
		{1.f,1.6f},
		{1.f,-0.6f},
		{0.6f,-1.f}
	};

	vec2 char_E[E_LEN] = {
		{1.f,-1.f},
		{-1.f,-1.f},
		{-1.f,0.5f},
		{0.2f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{-1.f,-1.f}
	};

	vec2 char_F[F_LEN] = {
		{-1.f,-1.f},
		{-1.f,0.5f},
		{0.f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,2.f}
	};

	vec2 char_G[G_LEN] = {
		{0.f,0.f},
		{1.f,0.f},
		{1.f,-1.f},
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,1.f},
		{1.f,2.f},
		{-1.f,2.f},
		{-1.f,-1.f},
		{1.f,-1.f},
		{1.f,0.f}
	};

	vec2 char_H[H_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,2.f},
		{1.f,-1.f},
		{1.f,0.5f},
		{-1.f,0.5f}
	};

	vec2 char_I[I_LEN] = {
		{-1.f,-1.f},
		{1.f,-1.f},
		{0.f,-1.f},
		{0.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{0.f,2.f},
		{0.f,-1.f}
	};

	vec2 char_J[J_LEN] = {
		{1.f,2.f},
		{1.f,-1.f},
		{0.f,-1.f},
		{-1.f,0.f},
		{0.f,-1.f},
		{1.f,-1.f}
	};

	vec2 char_K[K_LEN] = {
		{-1.f,-1.f},
		{-1.f,0.5f},
		{1.f,-1.f},
		{-1.f,0.5f},
		{1.f,2.f},
		{-1.f,0.5f},
		{-1.f,2.f}
	};

	vec2 char_L[L_LEN] = {
		{1.f,-1.f},
		{-1.f,-1.f},
		{-1.f,2.f},
		{-1.f,-1.f}
	};

	vec2 char_M[M_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{0.f,1.f},
		{1.f,2.f},
		{1.f,-1.f},
		{1.f,2.f},
		{0.f,1.f},
		{-1.f,2.f}
	};

	vec2 char_N[N_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,-1.f},
		{1.f,2.f},
		{1.f,-1.f},
		{-1.f,2.f}
	};

	vec2 char_O[O_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,-1.f}
	};

	vec2 char_P[P_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,0.5f},
		{-1.f,0.5f}
	};

	vec2 char_Q[Q_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,0.f},
		{0.5f,-0.5f},
		{0.f,0.f},
		{1.f,-1.f},
		{0.5f,-0.5f},
		{0.f,-1.f}
	};

	vec2 char_R[R_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{1.f,-1.f},
		{-1.f,0.5f}
	};

	vec2 char_S[S_LEN] = {
		{-1.f,-1.f},
		{1.f,-1.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,-1.f}
	};

	vec2 char_T[T_LEN] = {
		{0.f,-1.f},
		{0.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{0.f,2.f}
	};

	vec2 char_U[U_LEN] = {
		{-1.f,2.f},
		{-1.f,-1.f},
		{1.f,-1.f},
		{1.f,2.f},
		{1.f,-1.f},
		{-1.f,-1.f}
	};

	vec2 char_V[V_LEN] = {
		{-1.f,2.f},
		{0.f,-1.f},
		{1.f,2.f},
		{0.f,-1.f}
	};

	vec2 char_W[W_LEN] = {
		{-1.f,2.f},
		{-1.f,-1.f},
		{0.f,0.f},
		{1.f,-1.f},
		{1.f,2.f},
		{1.f,-1.f},
		{0.f,0.f},
		{-1.f,-1.f}
	};

	vec2 char_X[X_LEN] = {
		{-1.f,-1.f},
		{1.f,2.f},
		{0.f,0.5f},
		{-1.f,2.f},
		{1.f,-1.f},
		{0.f,0.5f}
	};

	vec2 char_Y[Y_LEN] = {
		{0.f,-1.f},
		{0.f,1.f},
		{-1.f,2.f},
		{0.f,1.f},
		{1.f,2.f},
		{0.f,1.f}
	};

	vec2 char_Z[Z_LEN] = {
		{1.f,-1.f},
		{-1.f,-1.f},
		{1.f,2.f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,-1.f}
	};
#pragma endregion

#pragma region Numbers
	vec2 char_ZERO[ZERO_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,-1.f}
	};
	vec2 char_ONE[ONE_LEN] = {
		{0.f,-1.f},
		{0.f,2.f}
	};
	vec2 char_TWO[TWO_LEN] = {
		{1.f,-1.f},
		{-1.f,-1.f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,2.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{-1.f,-1.f}
	};
	vec2 char_THREE[THREE_LEN] = {
		{-1.f,-1.f},
		{1.f,-1.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,2.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,-1.f}
	};
	vec2 char_FOUR[FOUR_LEN] = {
		{1.f,-1.f},
		{1.f,2.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{-1.f,0.5f},
		{1.f,0.5f}
	};
	vec2 char_FIVE[FIVE_LEN] = {
		{-1.f,-1.f},
		{1.f,-1.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{1.f,2.f},
		{-1.f,2.f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,-1.f}
	};
	vec2 char_SIX[SIX_LEN] = {
		{-1.f,2.f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,-1.f},
		{-1.f,-1.f}
	};
	vec2 char_SEVEN[SEVEN_LEN] = {
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,-1.f},
		{1.f,2.f}
	};
	vec2 char_EIGHT[EIGHT_LEN] = {
		{-1.f,-1.f},
		{-1.f,2.f},
		{1.f,2.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{1.f,0.5f},
		{1.f,-1.f}
	};
	vec2 char_NINE[NINE_LEN] = {
		{1.f,-1.f},
		{1.f,0.5f},
		{-1.f,0.5f},
		{-1.f,2.f},
		{1.f,2.f}
	};
#pragma endregion
};